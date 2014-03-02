#!/bin/bash
# The #PBS directives are the equivalent of passing the same argument on 
# the qsub command line.

#PBS -N geneticBuddha

#PBS -l nodes=2:ppn=1
#PBS -l walltime=01:00:00

#PBS -j oe

#PBS -M ethanjbirch@gmail.com

#PBS -m abe
. /rc/tools/utils/dkinit
use OpenMPI-GCC-4.8

mpirun -np $PBS_NP /home/A01514050/geneticBuddha/geneticBuddha
