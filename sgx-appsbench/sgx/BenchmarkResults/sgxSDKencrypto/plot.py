import matplotlib.pyplot as plt
from matplotlib.pyplot import text
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
        sgx.append(float(row[5]))

with open(fn_sim,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        sim.append(float(row[5]))

with open(fn_base,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        baseline.append(float(row[5]))

plt.semilogy()
plt.semilogx(basex=2)
#plt.xscale('log', basex=2)
plt.plot(x,baseline,'r',label='Baseline')
plt.plot(x,sim,'g:',label='SGX Simulation Mode')
plt.plot(x,sgx,'b--',label='SGX Hardware Mode')
plt.xlabel('Encrypted Buffer Size')
plt.xticks(x,('16 B','32 B','64 B','128 B','256 B','512 B','1 KiB','2 KiB','4 KiB','8 KiB','16 KiB','32 KiB','64 KiB','128 KiB','256 KiB','512 KiB','1 MiB'), rotation='vertical')
#plt.vlines(32, ymin=0, ymax=baseline[0], color='0.55', linestyles='dashed',linewidth=1)
#text(32, (10000), "optimisations", rotation=90, verticalalignment='center', size='large')
#plt.set_minor_formatter(FormatStrFormatter('%d'))
plt.ylabel('#Operation Per Sec')
plt.title('Plot of the SGXSDK AES GCM Encryption Benchmark')
plt.legend()
plt.tight_layout()
plt.savefig("encrypto.pdf")
plt.show()
