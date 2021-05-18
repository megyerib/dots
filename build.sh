#!/bin/bash

build_dir=build_linux
mkdir -p $build_dir
cp data/settings.dat $build_dir/settings.dat
cd $build_dir
cmake ..
make
