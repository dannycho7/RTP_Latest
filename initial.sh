#!/bin/bash

cd ./phase2/create_clusters
./gen_cluster ../../$1 $2
python gen_forward.py
cd ../lucene_step
python runjob_index_new.py
cd ../../phase1/lucene_step
./latest_index.sh $2
