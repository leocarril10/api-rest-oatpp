#!/bin/sh

curl -OL https://github.com/mongodb/mongo-cxx-driver/releases/download/r3.6.7/mongo-cxx-driver-r3.6.7.tar.gz
tar -xzf mongo-cxx-driver-r3.6.7.tar.gz
cd mongo-cxx-driver-r3.6.7/build

cmake ..                                \
    -DCMAKE_BUILD_TYPE=Release          \
    -DCMAKE_INSTALL_PREFIX=/usr/local

sudo cmake --build . --target EP_mnmlstc_core

cmake --build .
sudo cmake --build . --target install
ls
