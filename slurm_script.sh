#!/bin/bash
#SBATCH --job-name=chuntering_from_a_sedentary_position
#SBATCH --cpus-per-task=1
#SBATCH -N 1
#SBATCH --mem=24GB
./abqs_benchmark
./bqs_benchmark
./ninther_benchmark
./std_benchmark