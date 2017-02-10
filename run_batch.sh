#!/bin/bash

# $1 -> all queries

cd ./pre_process
./pre_process.sh ../$1
FILE_PATH=$1'.stem.clean'

cd ..
python batch_optionTestCluster_vector_new.py $FILE_PATH