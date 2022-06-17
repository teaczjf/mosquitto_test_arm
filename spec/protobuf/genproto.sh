#!/bin/bash

../../thirdparty/libprotobuf/bin/protoc --experimental_allow_proto3_optional ./datastruct.proto --cpp_out=../protobuf
mv *.h ./inc/
mv *.cc ./src/

