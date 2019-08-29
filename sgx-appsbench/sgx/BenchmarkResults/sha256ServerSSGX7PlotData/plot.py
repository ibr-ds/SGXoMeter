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
plt.plot(x,sim,'g',label='SGX Simulation Mode')
plt.plot(x,sgx,'b',label='SGX Hardware Mode')
plt.xlabel('Hashed String Length')
plt.xticks(x)
#plt.set_minor_formatter(FormatStrFormatter('%d'))
plt.ylabel('#Operation Per Sec')
plt.title('Plot of the benchmark Hashing Using SHA256')
plt.legend()
plt.tight_layout()
plt.savefig("sha256.pdf")
plt.show()
