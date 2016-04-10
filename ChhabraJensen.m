%function [Md] = ChhabraJensen(x, y, qi, qf, dq, Np, RmDq, RmFa, Io)
qi=-5;
qf=5;
dq=1;
Np=9;
Io=0;
series = load('series.txt');
x = series(:,1);
y = series(:,2);
x =x/x(end);%x/norm(x,inf);
N = length(x);
RmDq=0.95;
RmFa=0.95;

%% INITIALISATION OF MULTIFRACTAL MEASURES VARIABLES
% AlphaMin = 999;
% QAlphaMin = 999;
% Fmn = 999;
% Dqmn = 999;
% AlphaMax =  -999.9;
% QAlphaMax =  -999.9;
% Fmx =  -999.9;
% Dqmx = -999.9;
% qMin = 0;
% EDqmn = 0;
% RDqmn = 0;
% EAlphaMin = 0;
% RAlphaMin = 0;	% Alfa minimo, erro e r2
% qMax = 0;
% EDqmx = 0;
% RDqmx = 0;
% EAlphaMax = 0;
% RAlphaMax = 0;	% Alfa maximo, erro e r2
% Alpha0 = 0;
% EAlpha0 = 0;
% RAlpha0 = 0;
% D0 = 0;
% RD0 = 0;
% ED0 = 0;
% D2 = -1;
% D1 = -1;
% RD1 = -1;
% RD2 = -1;
% ED1 = -1;
% ED2 = -1;	 %-1 indicates that for the especific q (2 or 1) the R was not calculated
% %END OF VARIABLE INITIALISATION

%% ESTIMATING THE SUM OF ALL ELEMENTS IN THE TIME SERIES SEGMENT
SumY = sum(y);


%% THIS VARIABLE INDICATES THE NUMBER OF SCALES WHICH WILL BE REMOVED FROM THE PARTITION FUNCTION DURING THE CALCULUS
% THIS IS MADE IN ORDER TO REMOVE CERTAIN SCALES THAT MIGHT NOT PRESENT
% FOLLOW THE SCALING PATTERN

I=Io+1;

%% LOOP OVER ALL THE Q VALUES, FROM THE INTIAL Q (qi) TO THE FINAL ONE (qf) WITH INCREASES OF (dq).
% THIS LOOP IS INTENDED TO REALISE THE CALCULATIONS FOR ALL THE Q VALUES IN
% ORDER TO DERIVE THE SPECTRA
qix=((qf-qi)/dq)+1;
Mq = zeros(qix,Np);
Md = zeros(qix,Np);
spectr = zeros(qix,6);
qDq = zeros(qix,5);
for q=qi:dq:qf
    
    %% ALOCATING VARIABLES
    Ma = zeros(Np,1);
    Mf = zeros(Np,1);
    %mye = zeros(Np,1);
    %     for k=1:Np
    %         Ma(k)=0;
    %         Mf(k)=0;
    %         qix=((q-qi)/dq)+1;
    %         Md(qix,k)=0;
    %     end
    
    %% LOOP FOR ALL PARTITION SIZES
    for k=I:Np
        
        Nor=0;
        p=0;
        
        Pr = 2^k;                   % MAXIMUM NUMBER OF POINTS (DIATIC SCALE)
        E = 1/Pr;                       % SIZE OF EACH PARTITION
        pos = k-I+1;
        mye(pos,1) = log10(E); % para optimizar
        val = mye(pos);
        
        for i=1:Pr
            
            %% ESTIMATING m(epsilon,i) AND p(epsilon)
            
            m = calcSumM(x,y,(i-1)*E,i*E);
            p = m/SumY;
            
            
            %% ESTIMATING THE GENERIC MEASURES FAMILY (mu(q,episilon))
            if(p~=0)
                
                Nor = Nor + p^q;
                
            end
            
        end
        
        for i=1:Pr % loop for scan over the segments
            
            p = calcSumM(x,y,(i-1)*E,i*E)/SumY;
            
            %% IF TO AVOID DIVERGENCE DUE TO NULL MEASURES
            
            if(p~=0)
                
                if((1-dq/2) < q < (1+dq/2))
                    
                    Md(((q-qi)/dq)+1,k-I+1) = Md(((q-qi)/dq)+1,k-I+1) + ((p*log10(p))/Nor);
                    
                else
                    
                    Md(((q-qi)/dq)+1,k-I+1)= Md(((q-qi)/dq)+1,k-I+1) + p^q;
                    pq = p^q;					%To estimate f(alfa)
                    mu= pq/Nor;
                    
                    Ma(k-I+1,1) = Ma(k-I+1,1) + mu*log10(p);        %STEP 1-B-B
                    Mf(k-I+1) = Mf(k-I+1) + mu*log10(mu);       %STEP 1-B-A
                    
                end
                
                mu = (p^q)/Nor;					% To estimate f(alfa)
                Ma(k-I+1,1) = Ma(k-I+1,1) + mu*log10(m);
                Mf(k-I+1) = Mf(k-I+1) + mu*log10(mu);
                
            end
            
            % ENDIF
            
        end
        
        if(~((1-dq/2) < q < (1+dq/2)))
            
            Md(((q-qi)/dq)+1,k-I+1)= log10(Md(((q-qi)/dq)+1,k-I+1));  %if q!=1
            
        end
    end
    
    FAq = fitting(mye,Ma,Np);
    FFq = fitting(mye,Mf,Np);
    FDq = fitting(mye',Md((((q-qi)/dq)+1),:),Np);
    
    if((q>(1-dq/2) && q<(1+dq/2)))
        
        Dq = FDq.sl;
        
    else
        
        Dq = FDq.sl/(q-1);
        FDq.sd = FDq.sd/round(q-1); %***
        
    end
    
    if(FAq.r>=RmFa && FFq.r>=RmFa)
        
        spectr((q-qi)/dq+1,1) = FAq.sl;
        spectr((q-qi)/dq+1,2) = FAq.sd;
        spectr((q-qi)/dq+1,3) = FAq.r;
        spectr((q-qi)/dq+1,4) = FFq.sl;
        spectr((q-qi)/dq+1,5) = FFq.sd;
        spectr((q-qi)/dq+1,6) = FFq.r;
        
        %         if(FAq.sl>AlphaMax)
        %             AlphaMax = FAq.sl;
        %             EAlphaMax = FAq.sd;
        %             RAlphaMax = FAq.r;
        %             qAlphaMax = q;
        %         end
        %
        %         if(FAq.sl<AlphaMin)
        %             AlphaMin = FAq.sl;
        %             EAlphaMin = FAq.sd;
        %             RAlphaMin = FAq.r;
        %             qAlphaMin = q;
        %         end
        %
        %         if(FFq.sl<Fmn)
        %             Fmn = FFq.sl;
        %         end
        %
        %         if(FFq.sl>Fmx)
        %             Fmx = FFq.sl;
        %         end
        %
        %         if((q>(0-dq/2) && q<(0+dq/2)))
        %             ao = FAq.sl;
        %             EAo = FAq.sd;
        %             RAo = FAq.r;
        %         end
        
    end
    
    if(FDq.r >= RmDq)
        
        qDq((q-qi)/dq+1,1) = q;
        qDq((q-qi)/dq+1,2) = Dq;
        qDq((q-qi)/dq+1,3) = Dq*(q-1);
        qDq((q-qi)/dq+1,4) = FDq.sd;
        qDq((q-qi)/dq+1,5) = FDq.r;
        
        
        %         if (q>(1-dq/2) && q<(1+dq/2))
        %
        %             EDq = FDq.ea;
        %
        %         else
        %
        %             EDq = round(FDq.ea/(q-1)); %*****
        %
        %         end
        %
        %         if(Dq>Dqmx)
        %             Dqmx = Dq;
        %             qMax = q;
        %             EDqmx = EDq;
        %             RDqmx = FDq.r;
        %         end
        %
        %         if(Dq<Dqmn)
        %             Dqmn = Dq;
        %             qMin = q;
        %             EDqmn = EDq;
        %             RDqmn = FDq.r;
        %         end
        %
        %         if((q>(0-dq/2) && q<(0+dq/2)))
        %             Do = Dq;
        %             RDo = FDq.r;
        %             EDo = EDq;
        %         end
        %
        %         if((q>(1-dq/2) && q<(1+dq/2)))
        %             D1 = Dq;
        %             RD1 = FDq.r;
        %             ED1 = EDq;
        %         end
%         
%         if((q>(2-dq/2) && q<(2+dq/2)))
%             D2 = Dq;
%             RD2 = FDq.r;
%             ED2 = EDq;
%         end
        
    end
    end
    % END OF THE Q LOOP