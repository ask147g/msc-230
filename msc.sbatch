#!/bin/bash
#SBATCH -J msc-230
#SBATCH -n 1

#ARGC=$#
OUTPUT_FILE=msc-230.root

./msc-230 beam.in
cp $TMPDIR/$OUTPUT_FILE /eos/user/k/kuzmenko/msc-230/tmp/$SLURM_JOB_ID.root
rm $TMPDIR/$OUTPUT_FILE