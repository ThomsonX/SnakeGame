#!/bin/bash

set -e

cmake -B build
cmake --build build -j$(nproc)

# Find a file to execute
for file in build/main build/Debug/main build/Release/main; do
    if [ -f $file ]; then
        ./$file
        break
    fi
done
