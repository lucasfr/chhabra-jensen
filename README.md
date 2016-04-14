# chhabra-jensen
Multifractal analysis in Matlab based on the CHhabra-Jensen method.

Chhabra, A. & Jensen, R., 1989. Direct determination of the f(α) singularity spectrum. Physical Review Letters, 62(12), pp.1327–1330. Available at: http://link.aps.org/doi/10.1103/PhysRevA.40.5284.

Function:

function [qDq,spectr,partFunc] = ChhabraJensen(x, y, qi, qf, dq, Np, Ra, Rq, Io)

%% The variables of the function chj correspond to:

qi - initial value of q

qf - final value of q

dq - increment to made on the q value at each iteration

rq and ra - minimum r2 value for q and alpha, respectively

io - initial scale (dyadic)

x and y - x and y coordinates of the input time series

