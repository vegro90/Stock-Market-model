import numpy as np
import matplotlib.pyplot as plt

fileName = "../release/src/testHist.txt"
file = np.loadtxt(fileName,dtype = float)
step = 0.01
x = np.linspace(0,len(file)*step,len(file))

plt.style.use("ggplot")
fig = plt.figure(figsize=(15,10))
fig.suptitle("Distribution",size=20)

ax1 = fig.add_subplot(1,1,1)

y1 = 0;
y2 = file;

ax1.fill_between(x, y1, y2, where=y2 >= y1, interpolate=True)    


ax1.set_yscale('log')
#ax1.plot(x,file)