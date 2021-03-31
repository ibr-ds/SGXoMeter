#!/bin/bash
for (( c=1; c<=8; c++ ))
do  
   ./BaselineApp -w 10 -R 60 -B$((1024*$c))    
done

for (( c=1; c<=8; c++ ))
do  
   ./BenchApp -w 10 -R 60 -B$((1024*$c))
done

for (( c=1; c<=8; c++ ))
do  
   ./BenchAppSim -w 10 -R 60 -B$((1024*$c))
done
