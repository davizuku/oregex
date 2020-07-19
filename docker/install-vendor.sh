#!/bin/bash

BASEPATH = $(dirname "${BASH_SOURCE[0]}")

cd BASEPATH/..
mkdir vendor
cd vendor

# Boost library
echo "Installing Boost library (https://www.boost.org) ..."
wget https://dl.bintray.com/boostorg/release/1.73.0/source/boost_1_73_0.tar.bz2
tar --bzip2 -xvf boost_1_73_0.tar.bz2
rm -rf boost_1_73_0.tar.bz2
chown -R boost_1_73_0 --reference=test
apt-get install -y dladdr
echo "... Boost library installed successfully!"
