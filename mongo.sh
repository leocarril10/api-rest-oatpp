#!/bin/sh

rm -rf tmp

mkdir tmp
cd tmp

sudo apt-get install libmongoc-dev
sudo apt-get install libbson-dev
sudo apt-get install curl
sudo apt-get install cmake
sudo apt-get install g++
sudo apt-get install pkg-config
##########################################################
## install oatpp

MODULE_NAME="oatpp"

git clone --depth=1 https://github.com/oatpp/$MODULE_NAME

cd $MODULE_NAME
mkdir build
cd build

cmake ..
sudo make install

cd ../../

##########################################################
## install mongo driver cxx
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

##########################################################
## install oatpp-mongo
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

##########################################################
## install openssl
clear
sudo apt update
sudo apt install build-essential checkinstall zlib1g-dev -y

sudo cd /usr/local/src/
sudo wget https://www.openssl.org/source/openssl-3.1.0.tar.gz

sudo tar -xf openssl-3.1.0.tar.gz
sudo cd openssl-3.1.0

sudo cd /usr/local/src/openssl-3.1.0

sudo ./config --prefix=/usr/local/ssl --openssldir=/usr/local/ssl shared zlib

sudo make
sudo make test

echo "Make test completo"

sudo make install

echo "Make install completo"

##Configure Link Libraries

sudo echo "/usr/local/ssl/lib64"> /etc/ld.so.conf.d/openssl-3.1.0.conf

sudo ldconfig -v

sudo mv /usr/bin/c_rehash /usr/bin/c_rehash.bak
sudo mv /usr/bin/openssl /usr/bin/openssl.bak

sudo echo "PATH=\"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/usr/local/ssl/bin\""> /etc/environment

sudo source /etc/environment
sudo echo $PATH

sudo which openssl
exit

##########################################################
## install oatpp-openssl
cd ../

rm -rf tmp

MODULE_NAME="oatpp-openssl"
git clone --depth=1 https://github.com/oatpp/$MODULE_NAME

cd $MODULE_NAME
mkdir build
cd build

cmake ..
sudo make install

cd ../../

##########################################################

cd ../

rm -rf tmp
