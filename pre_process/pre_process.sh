#!/bin/bash

# $1 -> file_path


./stem $1 $1'.stem'
python clean_up.py $1'.stem' $1'.stem''.clean'
rm $1'.stem'
