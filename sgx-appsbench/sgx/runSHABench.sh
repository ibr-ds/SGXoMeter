#!/bin/bash
for (( c=2; c<=16777216; c=c*2 ))
do  
   ./BaselineApp -w 10 -R 60 -L$c
done

for (( c=2; c<=16777216; c=c*2 ))
do  
   ./BenchApp -w 10 -R 60 -L$c
done

for (( c=2; c<=16777216; c=c*2 ))
do  
   ./BenchAppSim -w 10 -R 60 -L$c
done
