#!/bin/bash

cd ./pre_process
make
cd ../phase2
make
cd lucene_step
make
cd ../search_doc
make
cd ../../phase1_latest/search_doc
make

