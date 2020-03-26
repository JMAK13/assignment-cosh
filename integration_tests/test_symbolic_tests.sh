#!/bin/sh

cd ..


IFS=
OUTPUT=$(./rshell '[ -f rshell ] && echo exists!')

echo ${OUTPUT}
