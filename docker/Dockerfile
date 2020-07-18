FROM gcc:10

ENV LD_LIBRARY_PATH=/usr/local/bin:/oregex/bin/:./bin

RUN apt-get update -y

# Compile dependencies
RUN apt-get install -y clang

# Valgrind dependencies
RUN apt-get install -y valgrind
