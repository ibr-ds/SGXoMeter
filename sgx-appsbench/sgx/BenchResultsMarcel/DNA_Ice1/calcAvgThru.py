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
    resultSGX += sgxValue
    print(resultSGX)

resultOE = 0
for num, oeValue in enumerate(oe, start=0):
    resultOE += oeValue
    print(resultOE)

resultGraphene = 0
for num, grapheneValue in enumerate(graphene, start=0):
    resultGraphene += grapheneValue
    print(resultGraphene)

resultBaseline = 0
for num, baselineValue in enumerate(baseline, start=0):
    resultBaseline += baselineValue
    print(resultBaseline)

print (len(sgx))

f= open("AESdecryptThroughput_ICE1.txt","w+")
f.write("SGX: %f \n OE: %f \n Graphene: %f \n Baseline: %f" % ((resultSGX/len(sgx)), (resultOE/len(oe)), (resultGraphene/len(graphene)), (resultBaseline/len(baseline)) ))
f.close()
