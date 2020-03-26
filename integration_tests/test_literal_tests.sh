#!/bin/sh

cd ..


IFS=
OUTPUT=$(./rshell 'test -d header && echo exists!')

echo ${OUTPUT}
