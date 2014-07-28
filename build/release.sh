#!/bin/sh

if [ ! -d build.release ] ; then 
    mkdir build.release
fi

cd build.release
cmake -DCMAKE_BUILD_TYPE=Release ../ 
cmake --build . --target install
cd ./../../install/mac-clang-x86_64/bin/
./test_sdp_parser
