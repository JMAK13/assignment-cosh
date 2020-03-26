#!/bin/sh

cd ..


IFS=
OUTPUT=$(./rshell echo success \#'ignore && the || text')

echo ${OUTPUT}
