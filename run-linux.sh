#!/bin/sh

make -f makefile.mk linux-build
export LD_LIBRARY_PATH="sfml/lib-linux" && builds/linux-build
