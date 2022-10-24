#!/bin/bash

mkdir Release
mkdir Debug

cp -r ../resources/* Release/
cp -r ../resources/* Debug/
cp -r ../resources/* ./

cp libs/DLLs/* Release/
cp libs/DLLs/* Debug/
cp libs/DLLs/* ./