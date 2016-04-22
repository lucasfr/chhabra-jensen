%% THIS FUNCTION WAS DEVELOPED IN ORDER TO ESTIMATE THE MULTIFRACTAL SPECTRA 
%% FROM TIME SERIES AND WAS DEVOLEP BASED ON A CODE ORIGINALLY WRITTEN BY
%% J. G. V. MIRANDA.

% L. G. S. FRANÇA - lucas.franca.14@ucl.ac.uk

%% THE VARIABLES OF THE FUNCTION CHJ CORRESPOND TO:

% % qi - INITIAL VALUE OF q
% % qf - FINAL VALUE OF q
% % dq - INCREMENT TO MADE ON THE q VALUE AT EACH ITERATION
% % Rq AND Ra - MINIMUM R2 VALUE FOR q AND alpha, RESPECTIVELY
% % Io - INITIAL SCALE (DYADIC)
% % x AND y - x AND Y COORDINATES OF THE INPUT TIME SERIES


%% ACKNOWLEDGEMENTS: I WOULD LIKE TO THANK J. G. V. MIRANDA, C. N. DE SANTANA 
%% AND M. P. LEITE FOR THE COMMENTS AND SUPPORT ON THE DEVELOPMENT OF THIS
%% CODE


function [qDq,spectr,partFunc] = ChhabraJensen(x, y, qi, qf, dq, Np, Ra, Rq, Io)

%% NORMALISING THE VALUES OF THE VECTOR X
x =x/x(end);

%% ESTIMATING THE SUM OF ALL ELEMENTS IN THE TIME SERIES SEGMENT
SumY = sum(y);


%% THIS VARIABLE INDICATES THE NUMBER OF SCALES WHICH WILL BE REMOVED
%% FROM THE PARTITION FUNCTION DURING THE CALCULUS

% THIS IS MADE IN ORDER TO REMOVE CERTAIN SCALES THAT MIGHT NOT
% FOLLOW THE SCALING PATTERN

I=Io;

%% VARIABLES ALLOCATION
qix=((qf-qi)/dq)+1;     % NUMBER OF VALUES OF q
Md = zeros(qix,Np-Io+1);
spectr = [];
qDq = [];


%% LOOP OVER ALL THE Q VALUES, FROM THE INTIAL Q (qi) TO THE FINAL ONE (qf)
%% WITH INCREASES OF (dq).

% THIS LOOP IS INTENDED TO REALISE THE CALCULATIONS FOR ALL THE Q VALUES IN
% ORDER TO DERIVE THE SPECTRA

for q=qi:dq:qf
    
    %% ALOCATING VARIABLES
    Ma = zeros(Np-Io+1,1);
    Mf = zeros(Np-Io+1,1);
    mye = zeros(Np-Io+1,1);
    
    %% LOOP FOR ALL PARTITION SIZES
    for k=I:Np
        
        Nor=0;
        
        Pr = 2^k;                 % MAXIMUM NUMBER OF POINTS (DYADIC SCALE)
        E = 1/Pr;                 % SIZE OF EACH PARTITION
        pos = k-I+1;
        mye(pos,1) = log10(E);
        
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
        
        %% LOOP TO SCAN OVER ALL SEGMENTS
        for i=1:Pr
            
            p = calcSumM(x,y,(i-1)*E,i*E)/SumY;
            
            %% IF TO ERROR WHEN p=0
            if(p~=0)
                
                %% IF STATEMENT TO AVOID ERRORS WHEN q=1
                if(q > (1-dq/2) && q < (1+dq/2))
                    
                    Md(int64((q-qi)/dq)+1,k-I+1) = ...
                        Md(int64((q-qi)/dq)+1,k-I+1) + ((p*log10(p))/Nor);
                    
                else                 
                    
                    Md(int64((q-qi)/dq)+1,k-I+1)= ...
                        Md(int64((q-qi)/dq)+1,k-I+1)+ p^q;
                                        
                end
                
                % GENERALISED MEASURE
                mu = (p^q)/Nor;
                
                Ma(k-I+1,1) = Ma(k-I+1,1) + mu*log10(p);
                Mf(k-I+1) = Mf(k-I+1) + mu*log10(mu);
                
            end
            
            
        end
        
        %% IF STATEMENT FOR q!=1
        if(~(q > (1-dq/2) && q < (1+dq/2)))
            
            % PARTITION FUNCTION ESTIMATION
            Md(int64((q-qi)/dq)+1,k-I+1)= log10(Md(int64((q-qi)/dq)+1,k-I+1));
            
        end
    end
    
    
    %% LINEAR REGRESSION AND EQUATION VARIABLES

    [FAqb,~,FAqR2] = fitting(mye,Ma);
    [FFqb,~,FFqR2] = fitting(mye,Mf);
    [FDqb,~,FDqR2] = fitting(mye,Md((int64((q-qi)/dq)+1),:)');
    
    %% f(alpha) SPECTRUM VARIABLES
    %% IF STATEMENT TO CHECK WHETHER THE R2 FOR THE FIT REACH A MINIMUM
    %% THRESHOLD OR NOT - alpha AND f(alpha)
    if ( FAqR2 >= Ra && FFqR2 >= Ra)
        
        spectr(end+1,1) = q;              % q
        spectr(end,2) = FAqb;             % alpha
        spectr(end,3) = FAqR2;            % alpha-R2
        spectr(end,4) = FFqb;             % f
        spectr(end,5) = FFqR2;            % f-R2
        
    end
    
    %% Dq SPECTRUM VARIABLES
    
    %% IF STATEMENT FOR q=1
    if((q>(1-dq/2) && q<(1+dq/2)))
        
        Dq = FDqb;
        
    else
        
        Dq = FDqb/(q-1);
        
    end
    
    %% IF STATEMENT TO CHECK WHETHER THE R2 FOR THE FIT REACH A MINIMUM
    %% THRESHOLD OR NOT - Dq
    if ( FDqR2 >= Rq)
        
        qDq(end+1,1) = q;                      % q
        qDq(end,2) = Dq;                       % Dq
        qDq(end,3) = Dq*(q-1);                 % tau(q)
        qDq(end,4) = FDqR2;                    % Dq-R2
        
    end
    
    %% PARTITION FUNCTION TO EXPORT
    partFunc = vertcat(mye',Md);
    
end
end

%% THIS ROUTINE WAS CREATED FOR THE ESTIMATION OF THE PARTITION FNCTIONS

% IT WAS CONCEIVED FOR BEING USED WITH THE CHHABRA-JENSEN METHOD ALGORITHM,
% ORIGINALLY

% THE FUNCTION RECEIVES 5 INPUT VARIABLES, THE 'x' AND 'y' VARIABLES OF A TIME
% SERIES, THE INITIAL POINT OF THE WINDOW 'EI' AND THE FINAL 'Ef' AND TOTAL
% NUMBER OF POINTS IN THE TIME SERIES.

function [mysum] = calcSumM(x, y, Ei, Ef)

% THE VARIAVLE 'mysum' WILL RETURN THE SUM OF ALL ELEMENTS IN A GIVEN WINDOW
mysum = sum(y(x>Ei & x<=Ef));

end

function [b,a,R2] = fitting(x,y)

%% CALCULATING THE COEFFICIENTS
X = [ones(length(x),1) x];
B = X\y;

b = B(2);
a = B(1);

%% ESTIMATING TE LINE
yF = X*B;

%% CALCULATING THE R2
R2 = 1 - sum((y - yF).^2)/sum((y - mean(y)).^2);

end