#!/bin/bash

# $1 -> query
# $2 -> top_k

QUERY=$1
TOP_K=${2:-1} # sets default value of TOP_K to value 1 if not set in arguments

cd target/
./single_query_search $TOP_K $QUERY
cd ..