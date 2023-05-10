#!/bin/sh

sudo apt-get install libmongoc-1.0-0
cd

wget http://ports.ubuntu.com/pool/universe/m/mongo-c-driver/libbson-dev_1.21.0-1build1_arm64.deb --no-check-certificate
sudo apt install ./libbson-dev_1.21.0-1build1_arm64.deb

cd

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
