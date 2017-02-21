#!/bin/bash

cd ./pre_process
./pre_process.sh ../$1
cd ../phase2
./gen_cluster ../$1.stem.clean
python gen_forward.py
python gen_super.py ../$1.stem.clean
cd lucene_step
python runjob_index_new.py
cd ../../phase1_super/lucene_step
./latest_index.sh
cd ../
./gen_title_len latest.txt