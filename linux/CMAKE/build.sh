#!/bin/bash
mkdir build
cd build
cmake ../src/.
make -j 2
cp ../src/filecache.dat .
cp -r ../src/res .
