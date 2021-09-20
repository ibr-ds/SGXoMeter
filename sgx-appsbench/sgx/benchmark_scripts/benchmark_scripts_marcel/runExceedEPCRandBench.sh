#!/bin/bash
for (( m=1; m<=512; m=m*2 ))
do  
   ./BaselineApp -w 10 -R 60 -S$m    
done

for (( m=1; m<=512; m=m*2 ))
do  
   ./BenchApp -w 10 -R 60 -S$m    
done

for (( m=1; m<=512; m=m*2 ))
do  
   ./OEBenchApp -w 10 -R 60 -S$m     
done

# for (( m=1; m<=4096; m=m*2 ))
# do  
#    graphene-sgx GrapheneBench -w 10 -R 60 -M$((1<<$m))    #DNA Pattern Multiplicator Value (default 1)
# done
