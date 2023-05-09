#!/bin/sh

sudo apt-get install libmongoc-1.0-0
cd

wget https://github.com/mongodb/libbson/releases/download/1.9.5/libbson-1.9.5.tar.gz
cd libbson-1.9.5/build
cmake ..
make 
sudo make install

curl -OL https://github.com/mongodb/mongo-cxx-driver/releases/download/r3.6.7/mongo-cxx-driver-r3.6.7.tar.gz
tar -xzf mongo-cxx-driver-r3.6.7.tar.gz
cd mongo-cxx-driver-r3.6.7/build

cmake ..                                \
    -DCMAKE_BUILD_TYPE=Release          \
    -DCMAKE_INSTALL_PREFIX=/usr/local

cmake ..                                \
    -DCMAKE_BUILD_TYPE=Release          \
    -DCMAKE_INSTALL_PREFIX=/opt/mongo   \
    -DCMAKE_INSTALL_RPATH=/opt/mongo

sudo cmake --build . --target EP_mnmlstc_core

cmake --build .
sudo cmake --build . --target install
ls
