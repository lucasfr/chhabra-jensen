clear 

addpath('../data/')

series = load('series.txt');
Timeseries = series(:,2);

scales = 2:8;
qValues = -15:15;

[alpha,falpha,Dq,Rsqr_alpha,Rsqr_falpha,Rsqr_Dq,muScale,Md,Ma,Mf]=...
    ChhabraJensen_Yuj_w0(Timeseries,qValues,scales);

out = horzcat(alpha,falpha);

csvwrite('../data/out.txt',out)