#  LICENSE
 
#  This software is licensed under an MIT License.
 
#  Copyright (c) 2020 Lucas G S França, Yujiang Wang, José Miranda.
 
#  Permission is hereby granted, free of charge, to any person obtaining a 
#  copy of this software and associated documentation files (the "Software"), 
#  to deal in the Software without restriction, including without limitation 
#  the rights to use, copy, modify, merge, publish, distribute, sublicense, 
#  and/or sell copies of the Software, and to permit persons to whom the 
#  Software is furnished to do so, subject to the following conditions:
 
#  The above copyright notice and this permission notice shall be included 
#  in all copies or substantial portions of the Software.
 
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
#  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
#  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
#  DEALINGS IN THE SOFTWARE.
 
#  Authors: Lucas França(1), Yujiang Wang(1,2,3), José Miranda (4)
 
#  1 Department of Clinical and Experimental Epilepsy, UCL Institute of Neurology,
#  University College London, London, United Kingdom
 
#  2 Interdisciplinary Computing and Complex BioSystems (ICOS) research group,
#  School of Computing Science, Newcastle University, Newcastle upon Tyne,
#  United Kingdom
 
#  3 Institute of Neuroscience, Newcastle University, Newcastle upon Tyne,
#  United Kingdom

#  4 Institute of Physics, Federal University of Bahia, Salvador, Bahia,
#  Brazil
 
#  email address: lucas.franca.14@ucl.ac.uk, Yujiang.Wang@newcastle.ac.uk
#  Website: https://lucasfr.github.io/, http://xaphire.de/

#  THIS FUNCTION WAS DEVELOPED IN ORDER TO ESTIMATE THE MULTIFRACTAL SPECTRA 
#  FROM TIME SERIES AND WAS DEVOLEP BASED ON A CODE ORIGINALLY WRITTEN BY
#  J. G. V. MIRANDA, modified by L. G. S. FRANCA. It is based on the
#  publication by Chhabra & Jensen 1989 PRL.


#[alpha,falpha,Dq,Rsqr_alpha,Rsqr_falpha,Rsqr_Dq,muScale,Md,Ma,Mf]

import numpy as np
from scipy import stats

def getSpectrum(Timeseries,qValues,scales):

# INPUT:
# Timeseries, qValues, and scales are all row vectors
# This function assumes that your time series is all positive values (sigm transform it if needed) 
# None of the qValue can be between 0 and 1.

# OUTPUT:
# alpha and falpha scattered against each other give the multifractal spectrum
# qValues and Dq scattered against each other give the generalised dimensions spectrum
# Rsqr_alpha, Rsqr_falpha, and Rsqr_Dq are the R^2 values for each of the values in alpha, falpha, and Dq respectively. It is recommended to run the following code outside of the function:
#  Rrej=0.9; %R^2 value below which values are rejected
#  kid=Rsqr_alpha>Rrej & Rsqr_falpha>Rrej;
#  alpha=alpha(kid);
#  falpha=falpha(kid);
# muScale, Md, Ma, and Mf are the basic matricies from which alpha, falpha, and Dq can be constructed by linear regression (see code below line 81 - 92 for details). They are included in the output mainly for completeness.

    ## initialise
    nq = qValues.shape[0]
    ns = scales.shape[0]
    Ma = np.zeros([nq,ns])
    Mf = np.zeros([nq,ns])
    Md = np.zeros([nq,ns])
        
    muScale = -np.log10(np.power(2,scales))
    #muScale=[muScale 0]
        
    alpha = np.zeros([nq,1])
    falpha = np.zeros([nq,1])
    Dq = np.zeros([nq,1])
        
    Rsqr_alpha = np.zeros([nq,1])
    Rsqr_falpha = np.zeros([nq,1])
    Rsqr_Dq = np.zeros([nq,1])

    ## calculating Ma_ij Mf_ij Md_ij
    for i in range(nq):
        
        q = qValues[i]

        for j in range(ns):
                
            # determine how many windows we will have at this scale
            window = 2**scales[j]
                
            # break the time series into windows & sum
            TimeseriesReshaped = np.reshape(Timeseries, (-1, window), order="F")
            TimeseriesSummed = np.sum(Timeseries)
                
            # calculate p
            ps = np.sum(TimeseriesReshaped, axis = 0)
            p = np.divide(ps,TimeseriesSummed)
                
                
            Nor = sum(np.power(p,q))
                
                
            # calculation of Md
            Md[i,j] = np.log10(Nor); # not accounting for q between 0 and 1
            
            if q<=1 and q>0:
                Md[i,j] = np.divide(sum(np.multiply(p,np.log10(p))),Nor)
                
                
            # Ma & Mf
            mu = np.divide((np.power(p,q)),Nor)
            Ma[i,j] = np.sum(np.multiply(mu,np.log10(p)))
            Mf[i,j] = np.sum(np.multiply(mu,np.log10(mu)))
            
            #looping through scales
            
            
        ## regression part
        slope, intercept, r_value, p_value, std_err = stats.linregress(muScale,Ma[i,:])
        b_Ma = slope
        R2_Ma = r_value
        slope, intercept, r_value, p_value, std_err = stats.linregress(muScale,Mf[i,:])
        b_Mf = slope
        R2_Mf = r_value
        slope, intercept, r_value, p_value, std_err = stats.linregress(muScale,Md[i,:])
        b_Md = slope
        R2_Md = r_value
            
        alpha[i] = b_Ma
        falpha[i] = b_Mf
        Dq[i] = np.divide(b_Md,(q - 1))
            
        if q<=1 and q>0: 
            Dq[i] = b_Md
            
            
        Rsqr_alpha[i] = R2_Ma
        Rsqr_falpha[i] = R2_Mf
        Rsqr_Dq[i] = R2_Md
    return alpha,falpha,Dq,Rsqr_alpha,Rsqr_falpha,Rsqr_Dq,muScale,Md,Ma,Mf
            
    #looping through qValues