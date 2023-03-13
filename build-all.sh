#!/bin/bash

SOURCE_FILES="insert find bcon list_collections hello_mongoc delete"

mkdir output

echo COMPILING ALL EXAMPLES!

for file in $SOURCE_FILES
do 

echo "Compiling $file"

gcc -o output/$file $file.c \
    -I/usr/local/include/libbson-1.0 -I/usr/local/include/libmongoc-1.0 \
    -lmongoc-1.0 -lbson-1.0 -Wdeprecated-declarations -w

done

echo RUNNING ALL EXAMPLES! 🚀

for file in $SOURCE_FILES
do 

echo "Running $file"
echo "-------------"

./output/$file

done