#!/bin/bash

# Compile with debug using ninja
D=build_debug_ninja
#mkdir -p $D
#cd $D
#cmake -GNinja -DCMAKE_BUILD_TYPE=Debug ..
#cd ..
ninja -C $D
