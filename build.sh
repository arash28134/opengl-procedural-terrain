#!/bin/bash

mkdir build

cp -r resources/* build/

cmake -S . -B build
cd build/
make

if [[ $* == *-r* ]] || [[ $* == *--run* ]]
then
    ./opengl_example
fi

if [[ $* == *-p* ]] || [[ $* == *--pack* ]]
then
    # delete makefile
    rm Makefile

    # delete cmake output
    find . -iwholename '*cmake*' -delete

    cd ../
    tar -czvf build.tar.gz build
    cd build/
fi
