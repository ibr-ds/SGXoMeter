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

# with open(fn_graphene,'r') as csvfile:
#     plots = csv.reader(csvfile, delimiter=',')
#     for row in plots:
#         graphene.append(float(row[5]))

plt.semilogy()
plt.semilogx(basex=2)
#plt.xscale('log', basex=2)
plt.plot(x,baseline,'r',label='Baseline')
plt.plot(x,sgx,'b--',label='SGX SDK')
plt.plot(x,oe,'g:',label='OE SDK')
#plt.plot(x,graphene,'m-.',label='GrapheneSGX')
plt.xlabel('Read buffer size')
plt.xticks(x,('1 MiB','2 MiB','4 MiB','8 MiB','16 MiB','32 MiB','64 MiB','128 MiB','256 MiB','512 MiB'), rotation='vertical')
#plt.vlines(32, ymin=0, ymax=baseline[0], color='0.55', linestyles='dashed',linewidth=1)
#text(32, (10000), "optimisations", rotation=90, verticalalignment='center', size='large')
#plt.set_minor_formatter(FormatStrFormatter('%d'))
plt.ylabel('#Operation Per Sec')
plt.title('Sequential read in-enclave buffers Benchmark')
plt.legend()
plt.tight_layout()
plt.savefig("EPC_RAND_SSGX8.pdf")
#plt.show()
