import numpy as np
import matplotlib.pyplot as plt
import csv


fn_sgx = 'plotdata.txt'
fn_sim = 'plotdata_sim.txt'
fn_base = 'BaselineData.txt'
sgx = []
baseline = []

with open(fn_sgx,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        sgx.append(float(row[6]))

with open(fn_base,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        baseline.append(float(row[6]))

result = 0;
for num, sgxValue in enumerate(sgx, start=0):
    result += (sgxValue/baseline[num]);
    print(result)

print len(sgx)

f= open("cryptoAvg.txt","w+")
f.write("%f" % (result/len(sgx)))
f.close()
