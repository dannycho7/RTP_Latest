#!/bin/bash

cd ./phase2/create_clusters
make
cd ../lucene_step
make
cd ../search_doc
make
cd ../../phase1/search_doc
make

