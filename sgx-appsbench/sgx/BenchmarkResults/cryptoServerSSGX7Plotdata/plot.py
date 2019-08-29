import numpy as np
import matplotlib.pyplot as plt
import csv


def f(theList):
    result = []
    for t in theList:
        result.append(t)
	print(np.exp(-t) * np.cos(2*np.pi*t))
    return result	 


t1 = np.arange(0.0, 3.0, 0.01)
fn_sgx = 'plotdata.txt'
fn_sim = 'plotdata_sim.txt'
fn_base = 'BaselineData.txt'
x = []
sgx = []
sim = []
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

with open(fn_base,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        baseline.append(float(row[6]))

plt.semilogy(basey=2)
#plt.xscale('log', basex=2)
ax = plt.subplot() # create a new figure with a default 111 subplot
ax.semilogy(basey=2)
ax.plot(x,baseline,'r',label='Baseline')
ax.plot(x,sim,'g',label='SGX Simulation Mode')
ax.plot(x,sgx,'b',label='SGX Hardware Mode')
plt.xlabel('RSA bit size')
plt.xticks(x)
#plt.set_minor_formatter(FormatStrFormatter('%d'))
plt.ylabel('#En-decryption Per Sec')
plt.title('Plot of the benchmark en-decryption using RSA')
plt.legend()



from mpl_toolkits.axes_grid1.inset_locator import zoomed_inset_axes
axins = zoomed_inset_axes(ax, 1.8 , loc=7) # zoom-factor: 2.5, location: upper-left
axins.plot(x,f(baseline),'r',label='Baseline')
axins.plot(x,f(sim),'g',label='SGX Simulation Mode')
axins.plot(x,f(sgx),'b',label='SGX Hardware Mode')
x1, x2, y1, y2 = 1500, 3000, 500, 3000 # specify the limits
axins.set_xlim(x1, x2) # apply the x-limits
axins.set_ylim(y1, y2) # apply the y-limits
axins.tick_params(axis='both', which='both', length=0)
plt.yticks(visible=False)
plt.xticks(visible=False)
ax.xaxis.set_visible('False')
ax.yaxis.set_visible('False')
from mpl_toolkits.axes_grid1.inset_locator import mark_inset
mark_inset(ax, axins, loc1=3, loc2=4, fc="none", ec="0.5")

plt.tight_layout()
plt.savefig("en-decryptionRsa.pdf")
plt.show()
