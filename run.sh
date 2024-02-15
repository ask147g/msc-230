#!/bin/bash

OUTPUT_DIR=/eos/user/k/kuzmenko/msc-230/

mkdir $OUTPUT_DIR/tmp

for (( i=0; i<$1; i++ ))
do
sbatch msc.sbatch $OUTPUT_DIR
sleep 5s
done