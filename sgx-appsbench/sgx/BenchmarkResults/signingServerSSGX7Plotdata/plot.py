import matplotlib.pyplot as plt
import csv

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
ax.plot(x,sim,'g:',label='SGX Simulation Mode')
ax.plot(x,sgx,'b--',label='SGX Hardware Mode')
plt.xlabel('RSA bit size')
plt.xticks(x)
#plt.set_minor_formatter(FormatStrFormatter('%d'))
plt.ylabel('#Signing-verification Per Sec')
plt.title('Plot of the benchmark signing and verification using RSA')
plt.tight_layout()
plt.legend()

#plt.savefig("signVerification.pdf")
#plt.show()


from mpl_toolkits.axes_grid1.inset_locator import zoomed_inset_axes
axins = zoomed_inset_axes(ax, 2,loc=7) # zoom-factor: 1.8, location: center-right
axins.plot(x,baseline,'r',label='Baseline')
axins.plot(x,sim,'g:',label='SGX Simulation Mode')
axins.plot(x,sgx,'b--',label='SGX Hardware Mode')
x1, x2, y1, y2 = 2500, 4000, 256, 1000 # specify the limits
axins.set_xlim(x1, x2) # apply the x-limits
axins.set_ylim(y1, y2) # apply the y-limits
axins.tick_params(axis='both', which='both', length=0)
plt.yticks(visible=False)
plt.xticks(visible=False)
ax.xaxis.set_visible('False')
ax.yaxis.set_visible('False')
from mpl_toolkits.axes_grid1.inset_locator import mark_inset
mark_inset(ax, axins, loc1=1, loc2=4, fc="none", ec="0.5")


plt.savefig("signVerification.pdf")
plt.show()
