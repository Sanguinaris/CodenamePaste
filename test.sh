#!/bin/bash

cd bld
LLVM_PROFILE_FILE="CTRLV.profraw" test/CTRLV -o report.xml -r junit
