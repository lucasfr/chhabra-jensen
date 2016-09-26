%%% THIS FUNCTION WAS DEVELOPED IN ORDER TO ESTIMATE THE MULTIFRACTAL SPECTRA 
%%% FROM TIME SERIES AND WAS DEVOLEP BASED ON A CODE ORIGINALLY WRITTEN BY
%%% J. G. V. MIRANDA.

% L. G. S. FRANCA - lucas.franca.14@ucl.ac.uk

%%% THE VARIABLES OF THE FUNCTION CHJ CORRESPOND TO:

%%% qInitial - INITIAL VALUE OF q
%%% qFinal - FINAL VALUE OF q
%%% qVar - INCREMENT TO MADE ON THE q VALUE AT EACH ITERATION
%%% rDq AND rAlpha - MINIMUM R2 VALUE FOR q AND alpha, RESPECTIVELY
%%% initialScale - INITIAL SCALE (DYADIC)
%%% y - INPUT TIME SERIES


function [qDq,spectr,partFunc] = ChhabraJensen(y, qInitial, qFinal,...
    qVar, scaleNum, rAlpha, rDq, initialScale)

% ELEMENTS INDEX
x = 1:length(y);

% NORMALISING THE VALUES OF THE VECTOR X FOR THE PARTITION ESTIMATION
x =x/x(end);

% ESTIMATING THE SUM OF ALL ELEMENTS IN THE TIME SERIES SEGMENT
sumY = sum(y);

% LOOP OVER ALL THE Q VALUES, FROM THE INTIAL Q (qInitial) TO THE FINAL 
% ONE (qFinal) WITH INCREASES (qVar).

% THIS LOOP IS INTENDED TO REALISE THE CALCULATIONS FOR ALL THE Q VALUES IN
% ORDER TO DERIVE THE SPECTRA

qValues=((qFinal-qInitial)/qVar)+1;     % NUMBER OF VALUES OF q

Mq = zeros(qValues,scaleNum+1);
Md = zeros(qValues,scaleNum+1);
spectr = [];
qDq = [];

for q=qInitial:qVar:qFinal
    
    % ALOCATING VARIABLES
    Ma = zeros(scaleNum+1,1);
    Mf = zeros(scaleNum+1,1);
    muScales = zeros(scaleNum+1,1);
    
    %% I - CALCULATING THE PARTITION FUNCTION
    % FOR ALL THE SCALE SIZES
    for k=initialScale:scaleNum
        
        Nor=0;
        
        window = 2^k;  % MAXIMUM NUMBER OF POINTS (DYADIC SCALE)
        
        E = 1/window;  % SIZE OF EACH PARTITION (X AXIS)- DIVIDING THE
                       % SEGMENTS IN SMALLER PIECES. 
                       
        pos = k-initialScale+1; % TO ADAPT THE VECTOR TO MATLAB INDEXING
                                % (STARTING ON 1)
                                
        muScales(pos,1) = log10(E); % LOG OF THE SEGMENT SIZE
        
        % AT EACH WINDOW ON THE TIME SERIES
        for i=1:window
            
            % ESTIMATING m(epsilon,i) AND p(epsilon)
            
            m = calcSumM(x,y,(i-1)*E,i*E);
            p = m/sumY;
            
            % THIS IF STATEMENT AVOIDS ERRORS WHEN p AND q ARE EQUAL TO 0
            if(p~=0)
                
                Nor = Nor + p^q;     % THIS IS THE NORMALISATION FACTOR
                
            end
            
        end
        
 %% II - CALCULATING THE MEASURES
        for i=1:window % loop for scan over the segments
            
            p = calcSumM(x,y,(i-1)*E,i*E)/sumY;
            
            % IF TO AVOID DIVERGENCE DUE TO NULL MEASURES
            if(p~=0)
                
                % IF q IS BIGGER THAN 0 AND SMALLER THAN 1
                % THIS IS MADE IN ORDER TO AVOID ISSUES WITH THE EXPONENT
                if(q > (1-qVar/2) && q < (1+qVar/2))
                    
                    Md(int64((q-qInitial)/qVar)+1,k-initialScale+1) = ...
                        Md(int64((q-qInitial)/qVar)+1,k-initialScale+1)...
                            + ((p*log10(p))/Nor);
                
                % FOR ANY OTHER VALUE OF q
                else
                    
                    Md(int64((q-qInitial)/qVar)+1,k-initialScale+1) = ...
                    Md(int64((q-qInitial)/qVar)+1,k-initialScale+1) + p^q;
     
                end
                
                mu = (p^q)/Nor;    % NORMALISED MEASURE
                
                Ma(k-initialScale+1,1) = Ma(k-initialScale+1,1)...
                    + mu*log10(p); % MEASURE TO OBTAIN alpha
                
                Mf(k-initialScale+1) = Mf(k-initialScale+1) + mu*log10(mu);
                                    % MEASURE TO OBTAIN f
                                    
            end
            
            
        end
        
        % FOR q < 0 && q > 1 | LOG OF THE SUM
        if(~(q > (1-qVar/2) && q < (1+qVar/2)))
            
            Md(int64((q-qInitial)/qVar)+1,k-initialScale+1)= log10(Md(int64((q-qInitial)/qVar)+1,k-initialScale+1));
            
        end
    end
    
    
    %% III - LINEAR REGRESSION AND EQUATION VARIABLES
    
    % THIS PIECE ESTIMATES THE SPECTRAL VALUES FOR EACH VALUE OF q BASED ON
    % THE REGRESSION OF THE VALUES OBTAINED FOR EACH SCALE
    [FAqb,~,FAqR2] = fitting(muScales,Ma);
    [FFqb,~,FFqR2] = fitting(muScales,Mf);
    [FDqb,~,FDqR2] = fitting(muScales,Md((int64((q-qInitial)/qVar)+1),:)');
    
    
    %% IV - ACCEPTANCE OR DENIAL OF VALUES
    % f(alpha) SPECTRUM VARIABLES
    % IF STATEMENT TO CHECK WHETHER THE R2 FOR THE FIT REACH A MINIMUM
    % THRESHOLD OR NOT - alpha AND f(alpha)
    if ( FAqR2 >= rAlpha && FFqR2 >= rAlpha || q==0)
        
        spectr(end+1,1) = q;              % q
        spectr(end,2) = FAqb;             % alpha
        spectr(end,3) = FAqR2;            % alpha-R2
        spectr(end,4) = FFqb;             % f
        spectr(end,5) = FFqR2;            % f-R2
        
    end
    
    % Dq SPECTRUM VARIABLES
    % IF STATEMENT FOR q=1
    if((q>(1-qVar/2) && q<(1+qVar/2)))
        
        Dq = FDqb;
        
    else
        
        Dq = FDqb/(q-1);
        
    end
    
    %% IF STATEMENT TO CHECK WHETHER THE R2 FOR THE FIT REACH A MINIMUM
    % THRESHOLD OR NOT - Dq
    if ( FDqR2 >= rDq || q == 0)
        
        qDq(end+1,1) = q;                      % q
        qDq(end,2) = Dq;                       % Dq
        qDq(end,3) = Dq*(q-1);                 % tau(q)
        qDq(end,4) = FDqR2;                    % Dq-R2
        
    end
    
    % PARTITION FUNCTION
    partFunc = vertcat(muScales',Md);
    
end
end

%% SUMMATION FUNCTION

% THE FUNCTION RECEIVES 4 INPUT VARIABLES, THE 'x' AND 'y' VARIABLES OF A
% TIME SERIES, THE INITIAL POINT OF THE WINDOW 'Ei' AND THE FINAL 'Ef'.

function [mySum] = calcSumM(x, y, Ei, Ef)

% THE VARIAVLE 'mysum' WILL RETURN THE SUM OF ALL ELEMENTS IN A GIVEN WINDOW
mySum = sum(y(x>Ei & x<=Ef));

end

%% FITTING FUNCTION
function [b,a,R2] = fitting(x,y)

% CALCULATING THE COEFFICIENTS
X = [ones(length(x),1) x];
B = X\y;

b = B(2);
a = B(1);

% ESTIMATING TE LINE
yF = X*B;

% CALCULATING THE R2
R2 = 1 - sum((y - yF).^2)/sum((y - mean(y)).^2);

end