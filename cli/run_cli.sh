#!/bin/bash

# CLI Build script based off of the Makefile

GCC=g++
CXXFLAGS="-std=c++17"
SRC_DIR="./src"
SRC_FILES=("$SRC_DIR"/*.cpp)
INCLUDE_DIR="-Iinclude"
EXEC="test"

echo "Building..."
$GCC $CXXFLAGS $INCLUDE_DIR "${SRC_FILES[@]}" -o "$EXEC"

if [[ $? -eq 0 ]]; then
    echo "Build successful: ./$EXEC"
    echo
    ./$EXEC
    echo
    echo "Cleaning up..."
    echo
    rm -f $EXEC
else
    echo "Build failed!"
    echo
    exit 1
fi