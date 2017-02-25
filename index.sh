#!/bin/bash

#command to run: ./index.sh <path_to_data_file> <representative_choice>


./src/pre_process_data/pre_process.sh $1
./target/gen_cluster ./target/data.stem.clean $2
python ./src/phase2/create_clusters/gen_forward.py
python ./src/phase2/create_clusters/gen_super.py ./target/data.stem.clean
python ./src/phase2/index_doc/runjob_index.py
./src/phase1/index_doc/phase1_index.sh $2