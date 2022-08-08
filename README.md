## mosquitto_test_arm

```
本地编译
source env_linux.sh 
./build_project.sh 


交叉编译
source env_linux.sh 
./build_project.sh 

arm平台 i.mx6ull
```

./mosquitto_pub -t 'DatabaseCenter/Table_XPRO_ALL_DEVINFO/Rsp_for_cli
' -m '腰疼不加班'

./mosquitto_sub  -t 'DatabaseCenter/Table_XPRO_ALL_DEVINFO/Rsp_for_cli' -v