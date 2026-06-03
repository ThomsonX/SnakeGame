#!/bin/bash

set -e

executable_name=main

cmake -B build
cmake --build build -j$(nproc)

# Assert dominanace on Visual St*dio
for file in build/Debug/$executable_name build/Release/$executable_name; do
    if [ -f $file ]; then
        mv $file ./build/$executable_name
    fi
done

./build/$executable_name
