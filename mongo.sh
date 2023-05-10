#!/bin/sh
cd ../../

rm -rf tmp

MODULE_NAME="oatpp-mongo"
git clone --depth=1 https://github.com/oatpp/$MODULE_NAME

cd $MODULE_NAME
mkdir build
cd build

cmake ..
sudo make install

cd ../../
