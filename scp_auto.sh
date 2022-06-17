#! /bin/sh
project_path=$(
    cd $(dirname $0)
    pwd
)
project_name="${project_path##*/}"

# #存放要传输目标文件的路径
# cd $project_path/Build/bin  
# #配置目标设备的地址和文件还有密码
# expect -c "
#     spawn scp -r xDC root@192.168.0.139:/opt/FCIMS/
#     expect {
#         \"*assword\" {set timeout 300; send \"hzxy123\r\"; exp_continue;}
#         \"yes/no\" {send \"yes\r\";}
#     }
# expect eof"


#存放要传输目标文件的路径
cd $project_path
#配置目标设备的地址和文件还有密码
expect -c "
    spawn scp -r Build/bin/helloworld root@192.168.0.115:/home/root/zjftest
    expect {
        \"yes/no\" {send \"yes\r\";}
    }
expect eof"


# expect -c "
#     spawn scp -r FCIMS root@192.168.0.115:/home/root/zjftest
#     expect {
#         \"*assword\" {set timeout 300; send \"hzxy123\r\"; exp_continue;}
#         \"yes/no\" {send \"yes\r\";}
#     }
# expect eof"

