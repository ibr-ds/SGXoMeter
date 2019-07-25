#!/bin/bash
for (( m=0; m<=10; m++ ))
do  
   ./BaselineApp -w 10 -R 60 -M$((1<<$m))    
done

for (( m=0; m<=10; m++ ))
do  
   ./BenchApp -w 10 -R 60 -M$((1<<$m))    
done

for (( m=0; m<=10; m++ ))
do  
   ./BenchAppSim -w 10 -R 60 -M$((1<<$m))    
done

