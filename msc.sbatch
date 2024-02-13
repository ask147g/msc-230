#!/bin/bash
#SBATCH -J msc-230
#SBATCH -n 1

./msc-230 beam.in
cp $TMPDIR/msc-230.root /eos/user/k/kuzmenko/msc-230/$SLURM_JOB_ID.root
