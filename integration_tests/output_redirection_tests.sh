#!/bin/sh

cd ..


IFS=
OUTPUT=$(./rshell 'fail || (ls > filelist.txt && echo success)')

echo ${OUTPUT}
