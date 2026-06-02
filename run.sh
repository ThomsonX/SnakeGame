#!/bin/bash

set -e

cmake -B build
cmake --build build -j$(nproc)
./build/Debug/main.exe
