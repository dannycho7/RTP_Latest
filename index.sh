#!/bin/bash

# $1 -> path_to_data_file
# $2 -> representative_choice (Optional. If not given, 1 is chosen by default.)

if [ $# -eq 0 ]; then
	echo "Illegal number of arguments. Should be of format: ./index.sh <path_to_data_file> <representative_choice>"
fi

DATA_FILE_PATH=$1
REP_CHOICE=${2:-1} # representative choice is set to $2 arg or set to the value 1 if not


if [ "$#" -gt 0 ]; then
	./src/pre_process_data/pre_process.sh $DATA_FILE_PATH
	./target/gen_cluster ./target/data.stem.clean $REP_CHOICE
	python ./src/phase2/gen_representative_index/gen_super.py ./target/data.stem.clean
	python ./src/phase2/index_step/runjob_index.py
	./src/phase1/index_step/run_phase1_index.sh $REP_CHOICE

	cp src/phase1/search_step/lucene_search.jar ./target/
fi
