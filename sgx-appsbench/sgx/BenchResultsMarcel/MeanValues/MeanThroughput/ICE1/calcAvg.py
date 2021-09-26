import numpy as np
import matplotlib.pyplot as plt
import csv


fn_sgx = 'SGXData.txt'
fn_oe = 'OEData.txt'
fn_graphene = 'GrapheneData.txt'
fn_baseline = "BaselineData.txt"
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

with open(fn_baseline,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        baseline.append(float(row[0]))

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

resultSGX /= 6
resultOE /= 6
resultGraphene /= 6
resultBaseline /= 6


context = ['Baseline', 'SGX SDK', 'OE SDK' , 'GrapheneSGX']
avgThroughput = [resultBaseline, resultSGX, resultOE, resultGraphene]
plt.bar(context ,avgThroughput, color=['red', 'blue', 'green', 'purple'])
plt.ylabel('#Operation Per Sec')
plt.savefig("MeanThroughput_ICE1.pdf", bbox_inches='tight')


