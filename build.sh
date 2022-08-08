#!/bin/sh

work_dir=($pwd)

# first, protobuf
protobuf="./3rd/protobuf/cmake"
protobuf_tmp_build_dir="protobuf_build" 

if [ ! -d $protobuf_tmp_build_dir ]; then
  echo "cant find protobuf project, pulling"
  git submodule update --init
  cmake 3rd/protobuf/cmake -B$protobuf_tmp_build_dir -Dprotobuf_BUILD_TESTS=OFF
  echo "cmake done"  
fi

if [ ! -f $protobuf_tmp_build_dir/protoc ]; then
  echo "protoc not exist, making"
  cd $protobuf_tmp_build_dir && make -j$(nproc --all)
  echo "make done"
fi
