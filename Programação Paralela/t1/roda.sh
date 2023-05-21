#!/bin/bash
for nt in {1..8}
do
    echo "Executando 10 vezes com [$1] elementos e [$nt] threads:"
    #for vez in {1..1}   # 1 vez
    for vez in {1..10}  # 10 vezes
    do
        ./prefixSumPth-v1 $1 $nt | grep -oP '(?<=total_time_in_seconds: )[^ ]*'
    done
done