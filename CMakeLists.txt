#cmake version
cmake_minimum_required ( VERSION 3.10 )

project ( helloworld CXX C)


#判断是不是交叉编译环境
if($ENV{XPL_OBJECT_TYPE} STREQUAL ARM) 
	# 指定交叉编译的目标系统，此处为arm-linux-gnueabihf，依情形设置
	SET(CMAKE_SYSTEM_NAME arm-linux-gnueabihf)
	SET(TOOL_ADD "/home/lkt/Soft_packet/gcc-linaro-arm-linux-gnueabihf-4.9-2014.09_linux")
	set(triple arm-linux-gnueabihf)
	# 指定C编译器
	set(CMAKE_C_COMPILER "${TOOL_ADD}/bin/arm-linux-gnueabihf-gcc")
	set(CMAKE_C_COMPILER_TARGET ${triple})

	# 指定C++编译器
	set(CMAKE_CXX_COMPILER "${TOOL_ADD}/bin/arm-linux-gnueabihf-g++")
	set(CMAKE_CXX_COMPILER_TARGET ${triple})	
endif( )
#reset output path
set ( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin )
set ( LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib )
set (CMAKE_PREFIX_PATH $ENV{XPL_THIRDPARTY_DIR})

set ( CMAKE_SHARED_LIBRARY_LINK_C_FLAGS )

message(STATUS "CMake Info")
message(STATUS "=======================================================")
message(STATUS "    Operation System :  ${CMAKE_SYSTEM}")
message(STATUS "    CPU Architecture : ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "    Build Type : ${CMAKE_BUILD_TYPE}${CMAKE_CONFIGURATION_TYPES}")
message(STATUS "    Shared Library  : ${BUILD_SHARED_LIBS}")
message(STATUS "    Build Examples  : ${CSERIALPORT_BUILD_EXAMPLES}")
message(STATUS "    Build Test  : ${CSERIALPORT_BUILD_TEST}")
message(STATUS "=======================================================")
#set include file
include_directories (./inc)
include_directories ( $ENV{XPL_FEATURE_DIR}/easylogging)
include_directories ( $ENV{XPL_FEATURE_DIR}/easylogging/inc)
include_directories ( ${CMAKE_PREFIX_PATH}/libmosquitto/include)
# include_directories ( ${CMAKE_PREFIX_PATH}/libprotobuf/include)
# include_directories (./spec/protobuf/inc)

#set source file
aux_source_directory ( . DIR_USR_SOURCE )
aux_source_directory ( $ENV{XPL_FEATURE_DIR}/easylogging/src DIR_USR_SOURCE )
aux_source_directory ( $ENV{XPL_FEATURE_DIR}/easylogging DIR_USR_SOURCE )
# aux_source_directory ( ./src DIR_USR_SOURCE )
# aux_source_directory ( ./spec/protobuf/src DIR_USR_SOURCE )

#set CC AR LD AS
set ( CMAKE_C_COMPILER $ENV{CC} )
set ( CMAKE_C_AR $ENV{AR} )
set ( CMAKE_C_LD $ENV{LD} )

#CFLAGS
set ( CMAKE_C_FLAGS "-g -std=c11" )
set ( CMAKE_CXX_FLAGS "-g -std=c++14" )

add_definitions (
	-DELPP_FEATURE_ALL
	-DELPP_FEATURE_CRASH_LOG
	#-DELPP_NO_DEFAULT_LOG_FILE
	-DELPP_THREAD_SAFE
	-DELPP_OS_UNIX
	#-DELPP_SYSLOG
)

#set debug
if(CMAKE_BUILD_TYPE STREQUAL Debug)
	add_definitions (
		-DPRINT_DEBUG_INFO
	)
endif()


#添加静态库
#静态库的路径

# add_library ( protobuf  STATIC IMPORTED )
# set_property (TARGET protobuf PROPERTY IMPORTED_LOCATION ${CMAKE_PREFIX_PATH}/libprotobuf/lib/libprotobuf.a)
if($ENV{XPL_OBJECT_TYPE} STREQUAL ARM) #交叉编译
add_library ( mosquittopp SHARED IMPORTED )
set_property (TARGET mosquittopp PROPERTY IMPORTED_LOCATION ${CMAKE_PREFIX_PATH}/libmosquitto_arm_a7/lib/libmosquittopp.so.2.0.14)
add_library ( mosquitto SHARED IMPORTED )
set_property (TARGET mosquitto PROPERTY IMPORTED_LOCATION ${CMAKE_PREFIX_PATH}/libmosquitto_arm_a7/lib/libmosquitto.so.2.0.14)
else()#本地编译
add_library ( mosquittopp  STATIC IMPORTED )
set_property (TARGET mosquittopp PROPERTY IMPORTED_LOCATION ${CMAKE_PREFIX_PATH}/libmosquitto/lib/libmosquittopp_static.a)
add_library ( mosquitto  STATIC IMPORTED )
set_property (TARGET mosquitto PROPERTY IMPORTED_LOCATION ${CMAKE_PREFIX_PATH}/libmosquitto/lib/libmosquitto_static.a)
endif()


MESSAGE( STATUS "There are source files : ${DIR_USR_SOURCE}.")
#generate target
add_executable ( ${CMAKE_PROJECT_NAME} ${DIR_USR_SOURCE} )
target_link_libraries ( ${CMAKE_PROJECT_NAME} pthread  mosquittopp mosquitto)  

#add custom
add_custom_target ( clean-all COMMAND rm -rf {CMAKE_BINARY_DIR}/* )
