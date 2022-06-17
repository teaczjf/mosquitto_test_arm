#!/bin/bash

echo "=======================Bulid helloworld Test================="

echo "$1"
echo "$2"
echo "$3"

project_path=$(cd `dirname $0`; pwd)
project_name="${project_path##*/}"

echo $project_path
echo $project_name

check_build_dir=`ls -l |grep "build"`

echo $check_build_dir

if [[ $check_build_dir =~ "Build/" ]]
then
	echo "Has bulid Directroy!"
else
	echo "Create Build Directory!"
	mkdir -p Build
fi






#app build
cd $project_path/Build/
cmake -D CMAKE_BUILD_TYPE=$2 ..

if [[ "$1" =~ "clean" ]]
then
	make clean-all
	rm -rf ./*
	#clear swp
	cd $project_path 

	#python version
	python -V
	rtn="$?"
	if [[ $rtn == "0" ]]
	then
		echo "python"
		python cleartmp.py
	else
		echo "python3"
		python3 cleartmp.py
	fi

	echo $check_python_ver
	echo "====================================....clean Success....========================================="
else
	echo "====================================....Build start....==============================================="
	make -j8
	echo "generate helloworld at ./Build/bin/"
	echo "====================================....Build Success....========================================="
	echo "press anykey to running helloworld!"
	read input

	cd $project_path

	./Build/bin/helloworld 
fi
