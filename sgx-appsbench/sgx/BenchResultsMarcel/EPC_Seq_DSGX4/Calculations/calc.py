import matplotlib.pyplot as plt
import csv

fn_sgx = 'sgxsdk.txt'
fn_oe = 'oe.txt'
fn_base = 'baseline.txt'
fn_graphene = 'graphene.txt'
valueSGX = []
valueBL = []
diff = []
count = 0

with open(fn_sgx,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        count = count + 1
        valueSGX.append(float(row[5]))

with open(fn_oe,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        valueSGX[row.index] += float(row[5])

with open(fn_graphene,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        valueSGX[row.index] += float(row[5])


with open(fn_base,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        valueBL.append(float(row[5]))

for v in valueSGX:
    v = v/float(3)

for v in valueSGX:
    diff.append(valueBL[v.index] - v)


