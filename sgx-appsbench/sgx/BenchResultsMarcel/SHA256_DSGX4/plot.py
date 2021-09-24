import matplotlib.pyplot as plt
import csv

fn_sgx = 'plotdata.txt'
fn_oe = 'OpenEnclaveData.txt'
fn_base = 'BaselineData.txt'
fn_graphene = 'GrapheneData.txt'
x = []
sgx = []
oe = []
baseline = []
graphene = []

with open(fn_sgx,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        x.append(int(row[1]))
        sgx.append(float(row[5]))

with open(fn_oe,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        oe.append(float(row[5]))

with open(fn_base,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        baseline.append(float(row[5]))

with open(fn_graphene,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        graphene.append(float(row[5]))

plt.semilogy()
plt.semilogx(basex=2)
ax = plt.subplot()
#plt.xscale('log', basex=2)
plt.plot(x,baseline,'r',label='Baseline')
plt.plot(x,sgx,'b--',label='SGX SDK')
plt.plot(x,oe,'g:',label='OE SDK')
plt.plot(x,graphene,'m-.',label='GrapheneSGX')
plt.xlabel('Hashed String Length')
plt.xticks(x,('2 B','4 B','8 B','16 B','32 B','64 B','128 B','256 B','512 B','1 KiB','2 KiB','4 KiB','8 KiB','16 KiB','32 KiB','64 KiB','128 KiB','256 KiB','512 KiB','1 MiB','2 MiB','4 MiB','8 MiB','16 MiB'), rotation='vertical')
plt.vlines(32, ymin=0, ymax=baseline[0], color='0.55', linestyles='dashed',linewidth=1)
#text(32, (10000), "optimisations", rotation=90, verticalalignment='center', size='large')
#plt.set_minor_formatter(FormatStrFormatter('%d'))
plt.ylabel('#Operation Per Sec')
#plt.title('Plot of the benchmark Hashing Using SHA256')
plt.legend()
plt.tight_layout()
#plt.show()
from mpl_toolkits.axes_grid1.inset_locator import zoomed_inset_axes
axins = zoomed_inset_axes(ax, 2.3,loc=6) # zoom-factor: 1.8, location: center-right
axins.plot(x,baseline,'r')
axins.plot(x,sgx,'b--')
axins.plot(x,oe,'g:')
axins.plot(x,graphene,'m-.')
x1, x2, y1, y2 = 2, 64, 1000000, 4000000 # specify the limits
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
plt.savefig("sha256_DSGX4.pdf")
