#!/bin/bash

# $1 -> all queries

./src/pre_process_query/pre_process.sh $1
FILE_PATH='query.stem.clean'

python ./src/search_scripts/batch_optionTestCluster_vector_new.py $FILE_PATH