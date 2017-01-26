#!/bin/bash

cd ./phase2/create_clusters
make clean
cd ../lucene_step
make clean
cd ../search_doc
make clean
cd ../../phase1/search_doc
make clean

#delete all files generated during search phase
#navigate to root directory
cd ../../
rm -f ./phase2/vidlistC.txt ./outputTestCluster


