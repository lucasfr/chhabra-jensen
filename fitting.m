%%FITTING FUNCTION
function [fit] = fitting(vx, vy, N)

%x = [s,sx,sy,sx2,sxy,sy2,a,b,r,rx,ry,w,sa,sb]
vxt=vx';
vyt=vy';

%CALCULATE THE SUM

sumX = sum(vx);
sumY = sum(vy);
sumXY = sum(sum(vx*vyt));
sumX2 = sum(sum(vx*vxt));
sumY2 = sum(sum(vy*vyt));

%DETERMINE THE COEFICIENTS

s = sumX2 - sumX*sumX/N;
a = (sumXY - sumX*sumY/N)/s;
b = (sumY - a*sumX)/N;
w = sumY2 + a*a*sumX2 + N*b*b;
w = w - 2*a*sumXY - 2*b*sumY + 2*a*b*sumX;

if (w < 0)
    w = 0;
else
    w = sqrt(w/(N-2));
end

rx = sumX2-sumX2/N;
ry = sumY2-sumY2/N;

% Slope error
sa = (sumY2 + N*b*b + a*a*sumX2 - 2*(b*sumY-a*b*sumX+a*sumXY))/(N-2);
sb = sqrt((sumX2*sa)/(N*sumX2-sumX*sumX));
sa = sqrt((N*sa)/(N*sumX2-sumX*sumX));

if(abs(ry)<1.0e-10)
    
    if(abs(a)<1.0e-10)
        r = 1;
    else
        r = 30000;
    end
    
else
    
    r = a*a*rx/ry;
    
end

fit = struct('sl',a,'sd',w,'r',r,'in',b,'ea',sa,'eb',sb);

end
%END OF FITTING FUNCTION
