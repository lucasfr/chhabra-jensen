# chhabra-jensen
Multifractal analysis in Matlab based on the Chhabra-Jensen method.

Chhabra, A. & Jensen, R., 1989. Direct determination of the f(α) singularity spectrum. Physical Review Letters, 62(12), pp.1327–1330. Available at: http://link.aps.org/doi/10.1103/PhysRevA.40.5284.

Function:

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


