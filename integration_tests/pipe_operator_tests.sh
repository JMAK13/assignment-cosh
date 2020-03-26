#!/bin/sh

cd ..


IFS=
OUTPUT=$(./rshell 'fail || (ls | grep .txt | cat && echo success)')

echo ${OUTPUT}
