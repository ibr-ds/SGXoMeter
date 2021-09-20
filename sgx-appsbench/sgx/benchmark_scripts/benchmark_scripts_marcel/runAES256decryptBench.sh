#!/bin/bash
for (( c=16; c<=1048576; c=c*2 ))
do
   ./BaselineApp -w 10 -R 60 -s$c
done

for (( c=16; c<=1048576; c=c*2 ))
do
   ./BenchApp -w 10 -R 60 -s$c
done

for (( c=16; c<=1048576; c=c*2 ))
do
   ./OEBenchApp -w 10 -R 60 -s$c
done
                          