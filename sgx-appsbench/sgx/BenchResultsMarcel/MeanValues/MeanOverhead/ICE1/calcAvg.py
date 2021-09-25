import numpy as np
import matplotlib.pyplot as plt
import csv


fn_sgx = 'SGXData.txt'
fn_oe = 'OEData.txt'
fn_graphene = 'GrapheneData.txt'
sgx = []
baseline = []
oe = []
graphene = []

with open(fn_sgx,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        sgx.append(float(row[0]))

with open(fn_oe,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        oe.append(float(row[0]))

with open(fn_graphene,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        graphene.append(float(row[0]))

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

print (len(sgx))

f= open("Mean_Overhead_DSGX4.txt","w+")
f.write("SGX: %f \n OE: %f \n Graphene: %f" % ((resultSGX/6), (resultOE/6), (resultGraphene/6) ))
f.close()
