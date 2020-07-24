FROM gcc:10

ENV LD_LIBRARY_PATH=/usr/local/bin:/oregex/bin/:./bin

RUN apt-get update -y

# Compile dependencies
RUN apt-get install -y clang

# Valgrind dependencies
RUN apt-get install -y valgrind

# Boost library
RUN echo "Installing Boost library (https://www.boost.org) ..." && \
    mkdir -p /vendor && \
    cd /vendor && \
    wget https://dl.bintray.com/boostorg/release/1.73.0/source/boost_1_73_0.tar.bz2 && \
    tar --bzip2 -xf boost_1_73_0.tar.bz2 && \
    rm -rf boost_1_73_0.tar.bz2 && \
    echo "... Boost library installed successfully in /vendor!"
