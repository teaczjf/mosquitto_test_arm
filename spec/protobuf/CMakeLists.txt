#set version
cmake_minimum_required ( VERSION 3.10 )

#project
project ( datastruct )

set ( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin )
set ( LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib )

set (CMAKE_PREFIX_PATH $ENV{XDC_THIRDPARTY_DIR})

#set include 
include_directories ( ./inc )
include_directories ( ${CMAKE_PREFIX_PATH}/libprotobuf/include)

#set source file
aux_source_directory ( ./src DIR_DATASTRUCT_SRC )

#set CC AR LD AS
set ( CMAKE_C_COMPILER $ENV{CC} )
set ( CMAKE_C_AR $ENV{AR} )


set ( CMAKE_C_FLAGS "-g -pthread" )
set ( CMAKE_CXX_FLAGS "-g -std=c++11 -pthread" )

add_library ( protobuf  STATIC IMPORTED )
set_property (TARGET protobuf PROPERTY IMPORTED_LOCATION ${CMAKE_PREFIX_PATH}/libprotobuf/lib/libprotobuf.a)

#generate target
add_library ( datastruct ${DIR_DATASTRUCT_SRC} )

#add custom 
add_custom_target ( clean-all COMMAND rm -rf ${CMAKE_BINARY_DIR}/* )

target_link_libraries ( datastruct PRIVATE  protobuf pthread )
