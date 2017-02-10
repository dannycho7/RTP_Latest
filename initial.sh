#!/bin/bash

cd ./phase2
./gen_cluster ../$1
python gen_forward.py
cd lucene_step
python runjob_index_new.py
cd ../../phase1_latest/lucene_step
./latest_index.sh
