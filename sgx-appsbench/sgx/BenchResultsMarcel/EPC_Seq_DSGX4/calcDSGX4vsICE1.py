from io import IncrementalNewlineDecoder
import numpy as np
import matplotlib.pyplot as plt
import csv


fn_ice = 'EPC_SEQ_ICE1.txt'
fn_dsgx4 = 'EPC_SEQ_DSGX4v.txt'
ice1 = []
dsgx4 = []

with open(fn_ice,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        ice1.append(float(row[0]))

with open(fn_dsgx4,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        dsgx4.append(float(row[0]))

iceValue = np.mean(ice1)
dsgx4Value = np.mean(dsgx4)

# resultOE = 0
# for num, oeValue in enumerate(oe, start=0):
#     resultOE += (oeValue/baseline[num])
#     print(resultOE)

# resultGraphene = 0
# for num, grapheneValue in enumerate(graphene, start=0):
#     resultGraphene += (grapheneValue/baseline[num])
#     print(resultGraphene)

avg = (dsgx4Value / iceValue)

f= open("EPC_SEQ_DSGX4vsICE1.txt","w+")
f.write("Ice is: %f faster than DSGX4 " % (avg))
f.close()
