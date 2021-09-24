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


plt.figure(figsize=(5,3))
plt.semilogy(basey=10)
plt.xscale('log', basex=2)
plt.plot(x,baseline,'r',label='Baseline')
plt.plot(x,sgx,'b--',label='SGX SDK')
plt.plot(x,oe,'g:',label='OE SDK')
plt.plot(x,graphene,'m-.',label='GrapheneSGX')
plt.xlabel('Length of the examined DNA string')
plt.xticks(x)
#plt.set_minor_formatter(FormatStrFormatter('%d'))
plt.ylabel('#Operations Per Sec')
#plt.title('Plot of the benchmark DNA pattern matching of Seeq without ocalls')
plt.legend(fontsize=9)
plt.tight_layout()
plt.savefig("DNA_DSGX4.pdf")
#plt.show()
