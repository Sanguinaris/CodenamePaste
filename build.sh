#!/bin/bash

source /etc/profile

mkdir bld
cd bld
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_FLAGS="-g -O0 -fprofile-instr-generate -fcoverage-mapping" -DENABLE_TESTING=1 ..
make -j16
