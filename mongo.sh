#!/bin/sh

MODULE_NAME="oatpp"

git clone --depth=1 https://github.com/oatpp/$MODULE_NAME

cd $MODULE_NAME
mkdir build
cd build

cmake ..
sudo make install

cd ../../
