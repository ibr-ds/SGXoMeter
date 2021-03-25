import numpy as np
import matplotlib.pyplot as plt
from matplotlib.lines import Line2D
import csv


t1 = np.arange(0.0, 3.0, 0.01)
fn_sgx = 'plotdata.txt'
fn_sim = 'plotdata_sim.txt'
fn_sgx_old = 'plotdataOld.txt'
fn_sim_old = 'plotdata_simOld.txt'
fn_base = 'BaselineData.txt'
x = []
sgx = []
sim = []
sgx_old = []
sim_old = []
baseline = []

with open(fn_sgx,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        x.append(int(row[1]))
        sgx.append(float(row[6]))

with open(fn_sim,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        sim.append(float(row[6]))

with open(fn_sgx_old,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        sgx_old.append(float(row[6]))

with open(fn_sim_old,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        sim_old.append(float(row[6])) 
        
with open(fn_base,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        baseline.append(float(row[6]))
        
        

#plt.semilogy(basey=2)
plt.figure(figsize=(5,3))
plt.title("simulation mode [....] , hardware mode [----]", fontsize=10)
#plt.xscale('log', basex=2)
ax = plt.subplot() # create a new figure with a default 111 subplot
ax.semilogy(basey=10)
ax.plot(x,baseline,'r')
ax.plot(x,sim,'g:')
ax.plot(x,sgx,'g--')
ax.plot(x,sim_old,'b:')
ax.plot(x,sgx_old,'b--')
plt.xlabel('RSA Bit Size')
plt.xticks(x,fontsize=8)
plt.yticks(fontsize=8)
#plt.set_minor_formatter(FormatStrFormatter('%d'))
plt.ylabel('#Operations Per Sec')
plt.tight_layout()

colors = ['red', 'blue', 'green']
lines = [Line2D([0], [0], color=c, linewidth=1, linestyle='solid') for c in colors]
labels = ['Baseline', 'SGX-SDK 2.7', 'SGX-SDK 2.12']
plt.legend(lines,labels)


from mpl_toolkits.axes_grid1.inset_locator import zoomed_inset_axes
axins = zoomed_inset_axes(ax, 1.45,loc=3) # zoom-factor: 1.8, location: Center-Left
axins.plot(x,baseline,'r')
axins.plot(x,sim,'g:')
axins.plot(x,sgx,'g--')
axins.plot(x,sim_old,'b:')
axins.plot(x,sgx_old,'b--')
x1, x2, y1, y2 = 1024, 2500, 2048, 16384 # specify the limits
axins.set_xlim(x1, x2) # apply the x-limits
axins.set_ylim(y1, y2) # apply the y-limits
axins.tick_params(axis='both', which='both', length=0)
plt.yticks(visible=False)
plt.xticks(visible=False)
axins.set_xticklabels('')
axins.set_yticklabels('')
ax.xaxis.set_visible('False')
ax.yaxis.set_visible('False')
from mpl_toolkits.axes_grid1.inset_locator import mark_inset
mark_inset(ax, axins, loc1=1, loc2=2, fc="none", ec="0.5")

#plt.tight_layout()
plt.savefig("en-decryptionRsa2SDKs.pdf")
plt.show()
