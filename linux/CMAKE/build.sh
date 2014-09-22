#!/bin/bash
mkdir build
cd build
cmake ../src/.
make -j 2
cp ../src/filecache.dat .
cp ../src/inject.htx .
cp ../src/monitor.htx .
cp ../src/input.html .
