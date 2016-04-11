%function [Md] = ChhabraJensen(x, y, qi, qf, dq, Np, RmDq, RmFa, Io)
qi=-5;
qf=5;
dq=1;
Np=9;
Io=0;
series = load('series.txt');
x = series(:,1);
y = series(:,2);
N = length(x);
RmDq=0.95;
RmFa=0.95;

%% NORMALISING THE VALUES OF THE VECTOR X
x =x/x(end);

%% ESTIMATING THE SUM OF ALL ELEMENTS IN THE TIME SERIES SEGMENT
SumY = sum(y);


%% THIS VARIABLE INDICATES THE NUMBER OF SCALES WHICH WILL BE REMOVED FROM THE PARTITION FUNCTION DURING THE CALCULUS
% THIS IS MADE IN ORDER TO REMOVE CERTAIN SCALES THAT MIGHT NOT
% FOLLOW THE SCALING PATTERN

I=Io;

%% LOOP OVER ALL THE Q VALUES, FROM THE INTIAL Q (qi) TO THE FINAL ONE (qf) WITH INCREASES OF (dq).
% THIS LOOP IS INTENDED TO REALISE THE CALCULATIONS FOR ALL THE Q VALUES IN
% ORDER TO DERIVE THE SPECTRA

qix=((qf-qi)/dq)+1;     %NUMBER OF VALUES OF q

Mq = zeros(qix,Np+1);
Md = zeros(qix,Np+1);
spectr = zeros(qix,6);
qDq = zeros(qix,5);

for q=qi:dq:qf
    
    %% ALOCATING VARIABLES
    Ma = zeros(Np+1,1);
    Mf = zeros(Np+1,1);
    mye = zeros(Np+1,1);
    
    %% LOOP FOR ALL PARTITION SIZES
    for k=I:Np
        
        Nor=0;
        m=0;
        
        Pr = 2^k;                 % MAXIMUM NUMBER OF POINTS (DYADIC SCALE)
        E = 1/Pr;                 % SIZE OF EACH PARTITION
        pos = k-I+1;
        mye(pos,1) = log10(E);
        val = mye(pos);
        
        for i=1:Pr
            
            %% ESTIMATING m(epsilon,i) AND p(epsilon)
            
            m = calcSumM(x,y,(i-1)*E,i*E);
            p = m/SumY;
            
            
            %% ESTIMATING THE GENERIC MEASURES FAMILY (mu(q,episilon))
            if(p~=0)
                
                Nor = Nor + p^q;
                
                %THIS IF STATEMENT AVOID ERRORS WHEN p AND q ARE EQUAL TO 0
                
            end
            
        end
        
        for i=1:Pr % loop for scan over the segments
            
            p = calcSumM(x,y,(i-1)*E,i*E)/SumY;
            
            %% IF TO AVOID DIVERGENCE DUE TO NULL MEASURES
            if(p~=0)
                
                if(q > (1-dq/2) && q < (1+dq/2))
                    
                    Md(((q-qi)/dq)+1,k-I+1) = Md(((q-qi)/dq)+1,k-I+1) + ((p*log10(p))/Nor);
                    
                else
                    
                    Md(((q-qi)/dq)+1,k-I+1)= Md(((q-qi)/dq)+1,k-I+1) + p^q;
                    pq = p^q;
                    mu= pq/Nor;
                    
                    Ma(k-I+1,1) = Ma(k-I+1,1) + mu*log10(p);
                    Mf(k-I+1) = Mf(k-I+1) + mu*log10(mu);
                    
                end
                
                mu = (p^q)/Nor;
                Ma(k-I+1,1) = Ma(k-I+1,1) + mu*log10(m);
                Mf(k-I+1) = Mf(k-I+1) + mu*log10(mu);
                
            end
            
            
        end
        
        if(~(q > (1-dq/2) && q < (1+dq/2)))
            
            %IF q!=1
            Md(((q-qi)/dq)+1,k-I+1)= log10(Md(((q-qi)/dq)+1,k-I+1));
            
        end
    end
    
    
    %% LINEAR REGRESSION AND EQUATION VARIABLES
    FAq = fitlm(mye,Ma);
    FFq = fitlm(mye,Mf);
    
       
    spectr((q-qi)/dq+1,1) = FAq.Coefficients.Estimate(2);
    spectr((q-qi)/dq+1,2) = FAq.Coefficients.SE(2);
    spectr((q-qi)/dq+1,3) = FAq.Rsquared.Adjusted;
    spectr((q-qi)/dq+1,4) = FFq.Coefficients.Estimate(2);
    spectr((q-qi)/dq+1,5) = FFq.Coefficients.SE(2);
    spectr((q-qi)/dq+1,6) = FFq.Rsquared.Adjusted;
    
%     FFq = fitting(mye,Mf,Np);
%     FDq = fitting(mye,Md((((q-qi)/dq)+1),:)',Np);
%     
%     if((q>(1-dq/2) && q<(1+dq/2)))
%         
%         Dq = FDq.sl;
%         
%     else
%         
%         Dq = FDq.sl/(q-1);
%         FDq.sd = FDq.sd/round(q-1); %***
%         
%     end
%     
%     if(FAq.r>=RmFa && FFq.r>=RmFa)
%         
%         spectr((q-qi)/dq+1,1) = FAq.sl;
%         spectr((q-qi)/dq+1,2) = FAq.sd;
%         spectr((q-qi)/dq+1,3) = FAq.r;
%         spectr((q-qi)/dq+1,4) = FFq.sl;
%         spectr((q-qi)/dq+1,5) = FFq.sd;
%         spectr((q-qi)/dq+1,6) = FFq.r;
%         
%     end
%     
%     if(FDq.r >= RmDq)
%         
%         qDq((q-qi)/dq+1,1) = q;
%         qDq((q-qi)/dq+1,2) = Dq;
%         qDq((q-qi)/dq+1,3) = Dq*(q-1);
%         qDq((q-qi)/dq+1,4) = FDq.sd;
%         qDq((q-qi)/dq+1,5) = FDq.r;
%         
%     end
end