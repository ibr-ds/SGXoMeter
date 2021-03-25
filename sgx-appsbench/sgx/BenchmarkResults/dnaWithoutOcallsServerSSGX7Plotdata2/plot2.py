import matplotlib.pyplot as plt
from matplotlib.lines import Line2D
import csv

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
plt.title("simulation mode [....] , hardware mode [----]", fontsize=10)
plt.semilogy(basey=10)
plt.semilogx(basex=10)
#plt.xscale('log', basex=2)
plt.plot(x,baseline,'r')
plt.plot(x,sim,'g:')
plt.plot(x,sgx,'g--')
plt.plot(x,sim_old,'b:')
plt.plot(x,sgx_old,'b--')
plt.xlabel('DNA String Size [Bytes]')

colors = ['red', 'blue', 'green']
lines = [Line2D([0], [0], color=c, linewidth=1, linestyle='solid') for c in colors]
labels = ['Baseline', 'SGX-SDK 2.7', 'SGX-SDK 2.12']

plt.xticks(x,fontsize=8)
plt.yticks(fontsize=8)
#plt.set_minor_formatter(FormatStrFormatter('%d'))
plt.ylabel('#Operations Per Sec')
#plt.title('Plot of the benchmark DNA pattern matching of Seeq without ocalls')
plt.legend(lines,labels,fontsize=9)
plt.tight_layout()
plt.savefig("dnaWithoutOcalls2SDKs.pdf")
plt.show()
