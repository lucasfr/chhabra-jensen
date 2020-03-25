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


import numpy as np
import matplotlib.pyplot as plt
import chhabrajensen as chj

qi=-15
qf=15
dq=1
Io=2
Np=8
Ra=0.9
qValues = np.arange(qi,qf + 1)
scales = np.arange(Io,Np + 1)

with open('../data/series.txt', 'r') as f:
    x = f.readlines()
    
x = np.genfromtxt(x, delimiter='\t')
Timeseries = x[:,1]
Timeseries

with open('../data/out.txt', 'r') as f:
    y = f.readlines()
out = np.genfromtxt(y, delimiter=',')

alpha,falpha,Dq,Rsqr_alpha,Rsqr_falpha,Rsqr_Dq,muScale,Md,Ma,Mf = chj.getSpectrum(Timeseries,qValues,scales)

fig = plt.figure()
ax = fig.add_axes([0.1,0.1,0.9,0.9])
ax.plot(alpha, falpha, label = 'Python')
ax.scatter(out[:,0],out[:,1], color = 'r', label = 'Matlab')
ax.set_xlabel(r'$\alpha$')
ax.set_ylabel(r'$f(\alpha$)')
leg = ax.legend(shadow = True)
plt.savefig("test.pdf", dpi=300)