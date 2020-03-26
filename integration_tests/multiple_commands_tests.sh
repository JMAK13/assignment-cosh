#!/bin/sh

cd ..


IFS=
OUTPUT=$(./rshell 'failhere || echo success && ls -a; git status')

echo ${OUTPUT}
