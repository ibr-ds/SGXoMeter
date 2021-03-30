import matplotlib.pyplot as plt
from matplotlib.pyplot import text
from matplotlib.lines import Line2D
import csv
plt.rc('text', usetex=True)

fn_sgx = 'plotdata.txt'
fn_sim = 'plotdata_sim.txt'
fn_base = 'BaselineData.txt'
fn_sgx_old = 'plotdataOld.txt'
fn_sim_old = 'plotdata_simOld.txt'
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
        sgx.append(float(row[5]))

with open(fn_sim,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        sim.append(float(row[5]))

with open(fn_sgx_old,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        sgx_old.append(float(row[5]))

with open(fn_sim_old,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        sim_old.append(float(row[5]))  
        
with open(fn_base,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        baseline.append(float(row[5]))

plt.figure(figsize=(5,3))
plt.semilogy()
ax = plt.subplot()
plt.semilogx(basex=2)
#plt.xscale('log', basex=2)
plt.plot(x,baseline,'r')
plt.plot(x,sim,'g:')
plt.plot(x,sgx,'g--')
plt.plot(x,sim_old,'b:')
plt.plot(x,sgx_old,'b--')
plt.xlabel('Hashed String Size [Bytes]')
plt.xticks(x,fontsize=8)
plt.yticks(fontsize=8)
#plt.xticks(x,('2 B','4 B','8 B','16 B','32 B','64 B','128 B','256 B','512 B','1 KiB','2 KiB','4 KiB','8 KiB','16 KiB','32 KiB','64 KiB','128 KiB','256 KiB','512 KiB','1 MiB','2 MiB','4 MiB','8 MiB','16 MiB'), rotation='vertical')
plt.vlines(32, ymin=0, ymax=baseline[0], color='0.55', linestyles='dashed',linewidth=1)
#text(32, (10000), "optimisations", rotation=90, verticalalignment='center', size='large')
#plt.set_minor_formatter(FormatStrFormatter('%d'))
plt.ylabel('Operations Per Sec')

#plt.title("simulation mode [....] , hardware mode [----]", fontsize=10)
cnt=[0,1,2,3,4]
colors = ['red', 'blue', 'green','black','black']
styles = ['solid','solid','solid','dotted','dashed']
lines = [Line2D([0], [0], color=colors[c], linewidth=1, linestyle=styles[c]) for c in cnt]
labels = ['Baseline', 'SGX-SDK 2.7', 'SGX-SDK 2.12', 'Simulation Mode' , 'Hardware Mode']



plt.legend(lines,labels,fontsize=9)
plt.tight_layout()

from mpl_toolkits.axes_grid1.inset_locator import zoomed_inset_axes
axins = zoomed_inset_axes(ax, 2.3,loc=6) # zoom-factor: 1.8, location: center-right
axins.plot(x,baseline,'r')
axins.plot(x,sim,'g:')
axins.plot(x,sgx,'g--')
axins.plot(x,sim_old,'b:')
axins.plot(x,sgx_old,'b--')
x1, x2, y1, y2 = 2, 64, 1000000, 5000000 # specify the limits
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


plt.savefig("sha256new2SDKs.pdf")
plt.show()
