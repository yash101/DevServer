#!/bin/bash
sudo apt-get install git cmake build-essential
git clone https://github.com/yash101/devserver.git
mkdir DevServer
cd devserver/linux/CMAKE
cp -r * ../../../DevServer/.
cd ../../../DevServer
rm -rf ../devserver
./build.sh
cd build
./DevServer
