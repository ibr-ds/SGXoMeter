import numpy as np
import matplotlib.pyplot as plt
import csv


fn_crypto = 'cryptoAvg.txt'
fn_rsaGen = 'rsaKeyGenAvg.txt'
fn_sgnver = 'signAndverifAvg.txt'
fn_sha256 = 'sha256Avg.txt'
fn_dnaWoc = 'dnaWithOcallAvg.txt'
fn_dnaNOc = 'dnaWithoutOcallAvg.txt'

files = ["cryptoAvg.txt","rsaKeyGenAvg.txt","signAndverifAvg.txt","sha256Avg.txt","dnaWithOcallAvg.txt","dnaWithoutOcallAvg.txt"]

result = 0;

for f in files:
    with open(f,'r') as csvfile:
        plots = csv.reader(csvfile, delimiter=' ')
        for row in plots:
            result += float(row[0])

overheadAvg = (1-(result/len(files)));
overheadAvgPercent = overheadAvg * 100;
f= open("totalAvg.txt","w+")
f.write("The total overhead average is %f ~ %f%%" % (overheadAvg , overheadAvgPercent))
f.close()
