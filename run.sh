#!/bin/bash

set -e

executable_name=Snake

cmake -B build
cmake --build build -j$(nproc)

for file in build/$executable_name build/Debug/$executable_name build/Release/$executable_name; do
    if [ -f $file ]; then
        ./$file
        break
    fi
done
