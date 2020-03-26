#!/bin/sh

cd ..


IFS=
OUTPUT=$(./rshell '(echo A && echo B) || (echo C && echo D)')

echo ${OUTPUT}
