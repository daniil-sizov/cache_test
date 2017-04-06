#!/bin/bash
test_seqs=( "./data/test_ls.rws" )
bs=( 8, 16, 32 )
as=( 1, 4, 16, 64 )
wps=( "write-through" "write-back" )
legend="-l"

for b in "${bs[@]}"
do 
    for a in "${as[@]}"
    do
        for w in "${wps[@]}"
        do
            for f in "${test_seqs[@]}"
            do
                ./cache_test -v ${legend} -b ${b} -a ${a} -w ${w} -r LRU ${f}
                legend=""
            done
        done
    done
done