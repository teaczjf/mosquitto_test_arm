#!/bin/bash
if [[ "$#" =~ "0" ]]
then
	echo "没有注释信息,git commit 失败"
else
    echo $1
    git add . 
    git commit -m "update:$1"
    git push
fi  
