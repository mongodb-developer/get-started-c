#!/bin/bash

# Bash script to build and run all sample code

if [ ! -f "URI.h" ]; then
cat << EOF
Error: You need to create a URI.h file containing the Connection String URI of your MongoDB instance.

Sample URI.h file:

// Start URI.h
#define MY_MONGODB_URI "mongodb+srv://YOUR-MONGODB-CONNECTION-STRING-URI"
// End URI.h

To get your connection string please read: https://www.mongodb.com/basics/mongodb-connection-string
EOF
exit
fi

# list of files to be compiled and run
SOURCE_FILES="insert find bcon list_collections hello_mongoc delete update"

if [ ! -d "output" ]; then  
mkdir output
else
rm output/*
fi

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