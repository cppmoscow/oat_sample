FROM alpine:latest

RUN apk update \
    && apk upgrade \
    && apk add --no-cache \
    clang \
    clang-dev \
    alpine-sdk \
    dpkg \
    cmake \
    ccache \
    python3

RUN ln -sf /usr/bin/clang /usr/bin/cc \
    && ln -sf /usr/bin/clang++ /usr/bin/c++ \
    && update-alternatives --install /usr/bin/cc cc /usr/bin/clang 10\
    && update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++ 10\
    && update-alternatives --auto cc \
    && update-alternatives --auto c++ \
    && update-alternatives --display cc \
    && update-alternatives --display c++ \
    && ls -l /usr/bin/cc /usr/bin/c++ \
    && cc --version \
    && c++ --version

RUN apk add postgresql-dev

ADD . /service

WORKDIR /service/utility

RUN ./install-oatpp-modules.sh

WORKDIR /service/build

RUN cmake ..
RUN make

EXPOSE 8000 8000

ENTRYPOINT ["./example-postgresql-exe"]
