#!/bin/sh

cd ..


IFS=
OUTPUT=$(./rshell 'fail || (grep ucr < names.txt && echo success)')

echo ${OUTPUT}
