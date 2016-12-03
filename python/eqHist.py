# -*- coding: utf-8 -*-
"""
Created on Sat Dec  3 13:29:07 2016

@author: sindrerb
"""

import numpy as np
import matplotlib.pyplot as plt

fileName = "../release/src/runA_EqHist.txt"
file = np.loadtxt(fileName,dtype = float, skiprows = 2)
file = file[:]
    
plt.hist(file,10,alpha=0.3);
plt.legend()