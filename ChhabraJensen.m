function [qDq,spectr] = ChhabraJensen(x, y, qi, qf, dq, Np, Ra, Rq, Io)

%% CALCULATING THE NUMBER OF ELEMENTS
N = length(x);

%% NORMALISING THE VALUES OF THE VECTOR X
x =x/x(end);

%% ESTIMATING THE SUM OF ALL ELEMENTS IN THE TIME SERIES SEGMENT
SumY = sum(y);


%% THIS VARIABLE INDICATES THE NUMBER OF SCALES WHICH WILL BE REMOVED 
%% FROM THE PARTITION FUNCTION DURING THE CALCULUS

% THIS IS MADE IN ORDER TO REMOVE CERTAIN SCALES THAT MIGHT NOT
% FOLLOW THE SCALING PATTERN

I=Io;

%% LOOP OVER ALL THE Q VALUES, FROM THE INTIAL Q (qi) TO THE FINAL ONE (qf)
%% WITH INCREASES OF (dq).

% THIS LOOP IS INTENDED TO REALISE THE CALCULATIONS FOR ALL THE Q VALUES IN
% ORDER TO DERIVE THE SPECTRA

qix=((qf-qi)/dq)+1;     %NUMBER OF VALUES OF q

Mq = zeros(qix,Np+1);
Md = zeros(qix,Np+1);
spectr = [];
qDq = [];

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
                    
                    Md(int64((q-qi)/dq)+1,k-I+1) = Md(int64((q-qi)/dq)+1,k-I+1)...
                        + ((p*log10(p))/Nor);
                    
                else
                    
                    Md(int64((q-qi)/dq)+1,k-I+1)= Md(int64((q-qi)/dq)+1,k-I+1)...
                        + p^q;

                    
                end
                
                mu = (p^q)/Nor;
                Ma(k-I+1,1) = Ma(k-I+1,1) + mu*log10(p);
                Mf(k-I+1) = Mf(k-I+1) + mu*log10(mu);
                
            end
            
            
        end
        
        %% IF STATEMENT FOR q!=1
        if(~(q > (1-dq/2) && q < (1+dq/2)))
            
            Md(int64((q-qi)/dq)+1,k-I+1)= log10(Md(int64((q-qi)/dq)+1,k-I+1));
            
        end
    end
    
    
    %% LINEAR REGRESSION AND EQUATION VARIABLES
    FAq = fitlm(mye,Ma);
    FFq = fitlm(mye,Mf);
    FDq = fitlm(mye,Md((int64((q-qi)/dq)+1),:)');
    
    %% f(alpha) SPECTRUM VARIABLES
    if ( FAq.Rsquared.Adjusted >= Ra && FFq.Rsquared.Adjusted >= Ra)
        
        spectr(end+1,1) = q;                           % q
        spectr(end,2) = FAq.Coefficients.Estimate(2);% alpha
        spectr(end,3) = FAq.Coefficients.SE(2);      % alpha-STD
        spectr(end,4) = FAq.Rsquared.Adjusted;       % alpha-R2
        spectr(end,5) = FFq.Coefficients.Estimate(2);% f
        spectr(end,6) = FFq.Coefficients.SE(2);      % f-STD
        spectr(end,7) = FFq.Rsquared.Adjusted;       % f-R2
    
    end
    
    %% Dq SPECTRUM VARIABLES
    
    %% IF STATEMENT FOR q=1
    if((q>(1-dq/2) && q<(1+dq/2)))
        
        Dq = FDq.Coefficients.Estimate(2);
        
    else
        
        Dq = FDq.Coefficients.Estimate(2)/(q-1);
        DqStd = FDq.Coefficients.SE(2)/abs(q-1);
        
    end
    
    if ( FDq.Rsquared.Adjusted >= Rq)
        
        qDq(end+1,1) = q;                        % q
        qDq(end,2) = Dq;                       % Dq
        qDq(end,3) = Dq*(q-1);                 % tau(q)
        qDq(end,4) = DqStd;                    % SE/(q-1)
        qDq(end,5) = FDq.Rsquared.Adjusted;    % Dq-R2
           
    end


end
end