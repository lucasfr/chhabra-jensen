% LICENSE
% 
% This software is licensed under an MIT License.
% 
% Copyright (c) 2018 Lucas G S França, Yujiang Wang, José Miranda.
% 
% Permission is hereby granted, free of charge, to any person obtaining a 
% copy of this software and associated documentation files (the "Software"), 
% to deal in the Software without restriction, including without limitation 
% the rights to use, copy, modify, merge, publish, distribute, sublicense, 
% and/or sell copies of the Software, and to permit persons to whom the 
% Software is furnished to do so, subject to the following conditions:
% 
% The above copyright notice and this permission notice shall be included 
% in all copies or substantial portions of the Software.
% 
% THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
% OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
% FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
% AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
% LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
% FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
% DEALINGS IN THE SOFTWARE.
% 
% Authors: Lucas França(1), Yujiang Wang(1,2,3), José Miranda (4)
% 
% 1 Department of Clinical and Experimental Epilepsy, UCL Institute of Neurology,
% University College London, London, United Kingdom
% 
% 2 Interdisciplinary Computing and Complex BioSystems (ICOS) research group,
% School of Computing Science, Newcastle University, Newcastle upon Tyne,
% United Kingdom
% 
% 3 Institute of Neuroscience, Newcastle University, Newcastle upon Tyne,
% United Kingdom
%
% 4 Institute of Physics, Federal University of Bahia, Salvador, Bahia,
% Brazil
% 
% email address: lucas.franca.14@ucl.ac.uk, Yujiang.Wang@newcastle.ac.uk
% Website: https://lucasfr.github.io/, http://xaphire.de/

%%% THIS FUNCTION WAS DEVELOPED IN ORDER TO ESTIMATE THE MULTIFRACTAL SPECTRA 
%%% FROM TIME SERIES AND WAS DEVOLEP BASED ON A CODE ORIGINALLY WRITTEN BY
%%% J. G. V. MIRANDA, modified by L. G. S. FRANCA. It is based on the
%%% publication by Chhabra & Jensen 1989 PRL.

% This version is a faster and cleaner version of the previous codes
% written by Yujiang.Wang@newcastle.ac.uk 15th Dec 2016. It fully utilises
% the vectorisation in Matlab to speed up operations. A diagram summary of
% the algorithm can be found on the author's website www.ywang.co.uk


function [alpha,falpha,Dq,Rsqr_alpha,Rsqr_falpha,Rsqr_Dq,muScale,Md,Ma,Mf]=ChhabraJensen_Yuj_w0(Timeseries,qValues,scales)
%INPUT:
%Timeseries, qValues, and scales are all row vectors
%This function assumes that your time series is all positive values (sigm transform it if needed) 
%None of the qValue can be between 0 and 1.

%OUTPUT:
%alpha and falpha scattered against each other give the multifractal spectrum
%qValues and Dq scattered against each other give the generalised dimensions spectrum
%Rsqr_alpha, Rsqr_falpha, and Rsqr_Dq are the R^2 values for each of the values in alpha, falpha, and Dq respectively. It is recommended to run the following code outside of the function:
% Rrej=0.9; %R^2 value below which values are rejected
% kid=Rsqr_alpha>Rrej & Rsqr_falpha>Rrej;
% alpha=alpha(kid);
% falpha=falpha(kid);
%muScale, Md, Ma, and Mf are the basic matricies from which alpha, falpha, and Dq can be constructed by linear regression (see code below line 81 - 92 for details). They are included in the output mainly for completeness.

    %% initialise
    nq=length(qValues);
    ns=length(scales);
    Ma=zeros(nq,ns);
    Mf=zeros(nq,ns);
    Md=zeros(nq,ns);
    
    muScale=-log10((2.^scales));
    %muScale=[muScale 0];
    
    alpha=zeros(nq,1);
    falpha=zeros(nq,1);
    Dq=zeros(nq,1);
    
    Rsqr_alpha=zeros(nq,1);
    Rsqr_falpha=zeros(nq,1);
    Rsqr_Dq=zeros(nq,1);
    
    
    %% calculating Ma_ij Mf_ij Md_ij
    for i=1:nq
        q=qValues(i);
        for j=1:ns
            
            %determine how many windows we will have at this scale
            window=2^scales(j);
            
            %break the time series into windows & sum
            TimeseriesReshaped=reshape(Timeseries,[],window);
            TimeseriesSummed=sum(Timeseries);
            
            %calculate p
            ps=sum(TimeseriesReshaped,1);
            p=ps./TimeseriesSummed;
            
            
            Nor=sum(p.^q);
            
            
            %calculation of Md
            Md(i,j)=log10(Nor);%not accounting for q between 0 and 1
            if q<=1 && q>0
                Md(i,j)=sum(p.*log10(p))/Nor;
            end
            
            %Ma & Mf
            mu=(p.^q)/Nor;
            Ma(i,j)=sum(mu.*log10(p));
            Mf(i,j)=sum(mu.*log10(mu));
            
        end%looping through scales
        
        
        %% regression part
        [b_Ma,R2_Ma]=fitting(muScale,Ma(i,:));
        [b_Mf,R2_Mf]=fitting(muScale,Mf(i,:));
        [b_Md,R2_Md]=fitting(muScale,Md(i,:));
        
        alpha(i)=b_Ma;
        falpha(i)=b_Mf;
        Dq(i)=b_Md/(q-1);
        if q<=1 && q>0
                Dq(i)=b_Md;
        end
        
        Rsqr_alpha(i)=R2_Ma;
        Rsqr_falpha(i)=R2_Mf;
        Rsqr_Dq(i)=R2_Md;
        
    end%looping through qValues
    
    
    
end % end of main function

%% fitting function
function [b,R2] = fitting(x,y)


y=y';
% CALCULATING THE COEFFICIENTS
X = [ones(length(x),1) x'];
B = X\y;

b = B(2);
%a = B(1);

% ESTIMATING THE LINE
yF = X*B;

% CALCULATING THE R2
R2 = 1 - sum((y - yF).^2)/sum((y - mean(y)).^2);

end
