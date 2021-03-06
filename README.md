# Chhabra-Jensen

Multifractal analysis based on the Chhabra-Jensen method.

:warning: Please, use the following article for references:

França, L.G.S., Miranda, J.G.V., Leite, M., Sharma, N.K., Walker, M.C., Lemieux, L. and Wang, Y., 2018. [Fractal and Multifractal Properties of Electrographic Recordings of Human Brain Activity: Towards its Use as a Signal Feature for Machine Learning in Clinical Applications](https://www.frontiersin.org/articles/10.3389/fphys.2018.01767/). Frontiers in Physiology, 9, p.1767. DOI: 10.3389/fphys.2018.01767

The code was developed based on the method described in:

Chhabra, A. & Jensen, R., 1989. [Direct determination of the f(α) singularity spectrum](http://link.aps.org/doi/10.1103/PhysRevA.40.5284). Physical Review Letters, 62(12), pp.1327–1330.

:warning: A Python version is also included.

## Download

Please, clone the repository with the following command.

```
git clone https://github.com/lucasfr/chhabra-jensen
```

## Function:

The function runs on Matlab with the following command: 

```
[alpha,falpha,Dq,Rsqr_alpha,Rsqr_falpha,Rsqr_Dq,muScale,Md,Ma,Mf] = ...
ChhabraJensen_Yuj_w0(Timeseries,qValues,scales)
```

An alternative Python version can be called with the following command:

```
alpha,falpha,Dq,Rsqr_alpha,Rsqr_falpha,Rsqr_Dq,muScale,Md,Ma,Mf = getSpectrum(Timeseries,qValues,scales)
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

### Docker

To guarantee reproducibility and reduce issues involved in solving dependencies, the Python routine available here runs in a Docker container. Please download the last version of the software at their website: https://www.docker.com/

To execute the Docker container with the defined settings, please run:

```
docker-compose up -d
```

The demo script can then be executed with the following command:

```
docker-compose exec jupyter /bin/sh -c "python /src/chj_demo.py"
```

After finishing the execution you can stop the Docker container with:

```
docker-compose down
```

## LICENSE

This software is licensed under an MIT License. 

Copyright (c) 2020 [Lucas G S França](https://lucasfr.github.io/), [Yujiang Wang](http://xaphire.de/), José G V Miranda. 

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
