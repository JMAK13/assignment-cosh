#!/bin/sh

cd ..

IFS=
OUTPUT1=$(./rshell echo "Hello World")
OUTPUT2=$(./rshell ls -a)


echo ${OUTPUT1}
echo ${OUTPUT2}
