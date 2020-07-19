#!/bin/bash

SRC_DIR = $(dirname "$0")

cd "$SRC_DIR"
mkdir vendor
cd vendor

# Boost library
echo "Installing Boost library (https://www.boost.org) ..."
wget https://dl.bintray.com/boostorg/release/1.73.0/source/boost_1_73_0.tar.bz2
tar --bzip2 -xf boost_1_73_0.tar.bz2
rm -rf boost_1_73_0.tar.bz2
echo "... Boost library installed successfully!"

cd ..
chown -R vendor --reference=test
