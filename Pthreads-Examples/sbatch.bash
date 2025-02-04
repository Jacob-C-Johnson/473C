#!/bin/bash
#SBATCH --job-name="pth_mutex_modified"
#SBATCH --output="pth_mutex_modified.%j.%N.out"
#SBATCH --partition=compute
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=4
#SBATCH --mem=1GB
#SBATCH --account=ccu108
#SBATCH --export=ALL
#SBATCH -t 00:5:00

module purge
module load cpu
module load slurm
module load gcc

for ((N=100; N<=1000; N*=10))
do
    for ((P=1; P<=256; P*=2)) # number of threads
    # we only have 128 cores on this node
    # what will happen if we try to run on 256 threads?
    do
        # run the job with some outputs
        echo "running program on $P threads"
        ./pth_pi_mutex_modified $P $N
    done
    echo "-----------------------------------------"
done


# A bash script to run your experiments on the HPC
# This script provides an output file name
# runs on the compute nodes of the cluster (see the user guide)
# uses a single node
# has a single process on that node
# but we have 4 cpus available to run this task
# uses the ccu108 account number (it gets charged to this account)
# copy all environment variables over
# -t is the amount of time at most to run this job hours:minutes:seconds
# time is important so it kills the program if it accidentally breaks and keeps running
# time is also important because this program will be queued but will not run right away 
# because other people are running things right now (its busy)
# so the time you put helps the schedulder know when to start your script

# submit this job using the command: $ sbatch sbatch.bash
# it will reutrn the job id

# to know how long the job has been running: $ squeue -u <username> 
# and you can keep calling that command to see when it's done

# alternatively, use: $ watch squeue -u <username>
# for it to automatically refresh every 2 seconds

# when it's done running, it will create a .out file
# this file contains all of the print output (instead of it going to the screen)