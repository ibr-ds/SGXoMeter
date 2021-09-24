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

#plt.semilogy()
plt.semilogx(basex=2)
#plt.xscale('log', basex=2)
plt.plot(x,baseline,'r',label='Baseline')
plt.plot(x,sgx,'b--',label='SGX SDK')
plt.plot(x,oe,'g:',label='OE SDK')
plt.plot(x,graphene,'purple',label='GrapheneSGX')
plt.xlabel('Decrypted Buffer Size')
plt.xticks(x,('16 B','32 B','64 B','128 B','256 B','512 B','1 KiB','2 KiB','4 KiB','8 KiB','16 KiB','32 KiB','64 KiB','128 KiB','256 KiB','512 KiB','1 MiB'), rotation='vertical')
#plt.vlines(32, ymin=0, ymax=baseline[0], color='0.55', linestyles='dashed',linewidth=1)
#text(32, (10000), "optimisations", rotation=90, verticalalignment='center', size='large')
#plt.set_minor_formatter(FormatStrFormatter('%d'))
plt.ylabel('#Operation Per Sec')
#plt.title('AES256 GCM encryption on in-enclave Buffers Benchmark')
plt.legend()
plt.tight_layout()
plt.savefig("AES256encrypt_Ice1.pdf")
#plt.show()