#!/bin/sh

MODULE_NAME="oatpp-mongo"
git clone --depth=1 https://github.com/oatpp/$MODULE_NAME

cd $MODULE_NAME
mkdir build
cd build

cmake ..
make
sudo make install

cd ../../
