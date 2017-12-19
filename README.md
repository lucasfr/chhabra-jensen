# chhabra-jensen

Multifractal analysis in Matlab based on the Chhabra-Jensen method. 

[PAPER TO CITE SOON!]

Chhabra, A. & Jensen, R., 1989. [Direct determination of the f(α) singularity spectrum](http://link.aps.org/doi/10.1103/PhysRevA.40.5284). Physical Review Letters, 62(12), pp.1327–1330.

## Download

Please, clone the repository with the following command.

```
git clone https://github.com/lucasfr/chhabra-jensen
```

## Function:

The function runs on Matlab with the following command: 

```
function [alpha,falpha,Dq,Rsqr_alpha,Rsqr_falpha,Rsqr_Dq,muScale,Md,Ma,Mf]=ChhabraJensen_Yuj_w0(Timeseries,qValues,scales)
```

### INPUT:

Timeseries, qValues, and scales are all row vectors 

(This function assumes that your time series is all positive values.) 
(None of the qValue can be between 0 and 1.)

### OUTPUT:

alpha and falpha scattered against each other give the multifractal spectrum. 
qValues and Dq scattered against each other give the generalised dimensions spectrum. 
Rsqr_alpha, Rsqr_falpha, and Rsqr_Dq are the R^2 values for each of the values in alpha, falpha, and Dq respectively. 

:warning: It is recommended to run the following code outside of the function: 

Rrej=0.9; %R^2 value below which values are rejected. 

```
kid=Rsqr_alpha>Rrej & Rsqr_falpha>Rrej; 
alpha=alpha(kid);
falpha=falpha(kid);
```

muScale, Md, Ma, and Mf are the basic matricies from which alpha, falpha, and Dq can be constructed by linear regression (see code below line 81 - 92 for details). They are included in the output mainly for completeness.

## LICENSE

This software is licensed under an MIT License. 

Copyright (c) 2017 [Lucas G S França](https://lucasfr.github.io/), [Yujiang Wang](http://xaphire.de/), José G V Miranda. 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
