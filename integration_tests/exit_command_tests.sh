#!/bin/sh

cd ..


IFS=
OUTPUT=$(./rshell exit)

echo ${OUTPUT}
