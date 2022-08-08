#!/bin/sh

work_dir=$(pwd)

# first, compile protobuf
protobuf="./3rd/protobuf/cmake"
protobuf_tmp_build_dir=".protobuf_build" 

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

if [ ! -f $work_dir/libs/protos/protoc ]; then
  cp $work_dir/$protobuf_tmp_build_dir/protoc $work_dir/libs/protos/
fi

if [ ! -f $work_dir/libs/protos/libprotobuf.a ]; then
  cp $work_dir/$protobuf_tmp_build_dir/libprotobuf.a $work_dir/libs/protos
fi

#second, generate pb code from proto files
function MakeProto()
{
  cd $work_dir
  proto_cs_dir="libs/protos/cs"
  proto_ss_dir="libs/protos/ss"
  proto_output_dir="libs/protos/include"
  proto_common_head_file="libs/protos/commonprotobuf.h"
    
	if [ ! -d $proto_cs_dir ]; then
    mkdir $proto_cs_dir
	fi
	
  if [ ! -d $proto_ss_dir ]; then
    mkdir proto_ss_dir
	fi

  if [ ! -d $proto_output_dir ]; then
    mkdir $proto_output_dir
    mkdir $proto_output_dir/cs
    mkdir $proto_output_dir/ss
	fi

  $work_dir/libs/protos/protoc  $(ls $proto_cs_dir/*.proto) -I=$proto_cs_dir --cpp_out=$proto_output_dir/cs

  $work_dir/libs/protos/protoc  $(ls $proto_ss_dir/*.proto) -I=$proto_ss_dir --cpp_out=$proto_output_dir/ss
  
  if [ -f $proto_common_head_file ]; then
    rm $proto_common_head_file
	fi

  # cs_head=$(cd $proto_output_dir/.. && ls cs/*.h)
  # ss_head=$(cd $proto_output_dir/.. && ls ss/*.h)

  # echo -e "#pragma once\n""#include" \
  #         > $proto_common_head_file
}

if [ "$1" == proto ] ; then
  MakeProto
fi

proj_build_dir="proj_build"
cmake . -B$proj_build_dir -Dlibprotobuf=$work_dir/$protobuf_tmp_build_dir/libprotobuf.a && cd proj_build && make -j$(nproc --all)
