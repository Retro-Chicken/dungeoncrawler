#!/bin/sh

make -f makefile-linux.mk linux-build
export LD_LIBRARY_PATH="sfml-linux/lib" && builds/linux-build
