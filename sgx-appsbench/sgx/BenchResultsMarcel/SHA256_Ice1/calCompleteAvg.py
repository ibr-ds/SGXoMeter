import numpy as np
import matplotlib.pyplot as plt
import csv


fn_sgx = 'plotdata.txt'
fn_oe = 'OpenEnclaveData.txt'
fn_base = 'BaselineData.txt'
fn_graphene = 'GrapheneData.txt'
sgx = []
baseline = []
oe = []
graphene = []

with open(fn_sgx,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        sgx.append(float(row[5]))

with open(fn_base,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        baseline.append(float(row[5]))

with open(fn_oe,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        oe.append(float(row[5]))

with open(fn_graphene,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        graphene.append(float(row[5]))

resultSGX = 0
for num, sgxValue in enumerate(sgx, start=0):
    resultSGX += (sgxValue/baseline[num])
    print(resultSGX)

resultOE = 0
for num, oeValue in enumerate(oe, start=0):
    resultOE += (oeValue/baseline[num])
    print(resultOE)

resultGraphene = 0
for num, grapheneValue in enumerate(graphene, start=0):
    resultGraphene += (grapheneValue/baseline[num])
    print(resultGraphene)

print (len(sgx))

f= open("SHA_COMPLETE_ICE1.txt","w+")
f.write("SGX: %f \n OE: %f \n Graphene: %f" % (1-(resultSGX/len(sgx)), 1-(resultOE/len(oe)), 1-(resultGraphene/len(graphene)) ))
f.close()
