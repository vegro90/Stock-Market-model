import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure(figsize=(15,10))
fig.suptitle("Distribution",size=20)

ax1 = fig.add_subplot(1,1,1)

hists = [0,10]

step = 0.01

fileName = "../release/src/runA_CapitalDistribution.txt"
file = np.loadtxt(fileName,dtype = float,skiprows=7)

x = np.linspace(0,len(file)*step,len(file))

y1 = 0;
y2 = file;

file = file/np.trapz(file,dx=0.01)

#ax1.fill_between(x, y1, y2, where=y2 >= y1, interpolate=True)    
ax1.plot(x,file)
x = x[60:]
"""
    for i in np.linspace(0.5,2,4):
    norm = np.trapz(x**(-1-i),x)
    ax1.plot(x,x**(-1-i)/norm,label='alpha=%f'%i)
    """
#ax1.plot(x, np.exp(-x))
#ax1.set_ylim(1e-6,2.5e0)
ax1.set_xlim(0,2)
ax1.legend()
#ax1.set_yscale('log')

#ax1.plot(x,file)