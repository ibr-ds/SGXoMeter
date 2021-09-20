#!/bin/bash
for (( c=16; c<=1048576; c=c*2 )) # 1 MiB of Data
do
   ./BaselineApp -w 10 -R 60 -s$c
done

for (( c=16; c<=1048576; c=c*2 ))
do
   ./BenchApp -w 10 -R 60 -s$c
done

for (( c=16; c<=1048576; c=c*2 ))
do
   ./BenchAppSim -w 10 -R 60 -s$c
done
                          