FROM gcc:10

COPY ./install-dependencies.sh .
RUN bash ./install-dependencies.sh

ENV LD_LIBRARY_PATH=/usr/local/bin:./bin
