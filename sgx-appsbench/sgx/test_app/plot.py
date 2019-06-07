import matplotlib.pyplot as plt
import csv
import os
import sys

argc = len (sys.argv)
if argc != 2 :
    fn = 'plotdata.txt'
else: 
    fn = sys.argv[1] 

x = []
y = []

with open(fn,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        x.append(int(row[0]))
        y.append(int(row[1]))

plt.semilogx()
plt.plot(x,y,'b.',label='Occurrence Count with 1M Cycles Rate')
plt.xlabel('Cycles')
#plt.set_minor_formatter(FormatStrFormatter('%d'))
plt.ylabel('Occurrence Frequency')
plt.title('Plot of the benchmark result of ' + fn)
plt.legend()
plt.show()
