#include <stdio.h>
#include <iostream>
#include "my_easylogging.h"

#include <mosquitto.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mosquittopp.h"
// #include "./spec/protobuf/inc/datastruct.pb.h"
// #include <google/protobuf/util/json_util.h>

using namespace std;
// using google::protobuf::util::JsonStringToMessage;

#define MODULE_NAME_STR (" [" + (this->GetModuleName()) + "] ")

/// init status
#define MOSQUITTO_INTI_SUCCESS 0
#define MOSQUITTO_INTI_FAIL 1

/// connect status
#define MOSQUITTO_CONNECT_SUCCESS 0
#define MOSQUITTO_CONNECT_FAIL 1

class Pub_test : public mosqpp::mosquittopp
{
private:
    string m_module_name;
    /// record module number
    static INT32 m_mqtt_module_num;
    /// mqtt broker
    string m_host;
    int m_port;
    /// broker init status
    static BOOLEAN m_mosquitto_init_status;

    /// connect status
    BOOLEAN m_mosquitto_connect_status;

public:
    Pub_test(const char *moduleName, const char *host, int port);
    ~Pub_test();

    void pub_message(string dev_name, string cmd_name);
    inline string GetModuleName()
    {
        return m_module_name;
    }
};

Pub_test::Pub_test(const char *moduleName, const char *host, int port) : mosquittopp(moduleName)
{

    INT32 ret = Lret_success;

    m_module_name = moduleName;
    m_host = host;
    m_port = port;

    if (0 == m_mqtt_module_num)
    {
        ret = mosqpp::lib_init();
        if (MOSQ_ERR_SUCCESS == ret)
        {
            LOG(INFO) << MODULE_NAME_STR << "mosquitto library init success!";
            m_mosquitto_init_status = MOSQUITTO_INTI_SUCCESS;
        }
        else
        {
            LOG(ERROR) << MODULE_NAME_STR << "mosquitto library init fail!";
        }
    }
    /// add module number
    m_mqtt_module_num++;
    /// connect broker
    ret = connect(host, port, 60);

    if (MOSQ_ERR_SUCCESS == ret)
    {
        LOG(INFO) << MODULE_NAME_STR << "mosquitto connect success!";
        m_mosquitto_connect_status = MOSQUITTO_CONNECT_SUCCESS;
    }
    else
    {
        LOG(ERROR) << MODULE_NAME_STR << "mosquitto connect fail!";
    }
}

Pub_test::~Pub_test() {}

void Pub_test::pub_message(string dev_name, string cmd_name)
{

    //     google::protobuf::util::JsonPrintOptions options;
    //     if (1)
    //     {
    //         options.add_whitespace = true;
    //         options.always_print_primitive_fields = true;
    //         options.preserve_proto_field_names = true;
    //     }
    //     else
    //     {
    //         options.add_whitespace = false;
    //         options.always_print_primitive_fields = false;
    //         options.preserve_proto_field_names = false;
    //     }

    //     Proto3DeviceAllCMD device_packet;
    //     Proto3DeviceCMDDefine *payload_CMD = device_packet.add_cmds();

    //     device_packet.set_dev_name(dev_name);
    //     payload_CMD->set_cmd_name(cmd_name);
    //     int message_len = device_packet.ByteSizeLong();
    //     char cmd_buffer[message_len];
    // #if 0 // JSON格式打印即将发出的数据报
    //     string json_string;
    //     MessageToJsonString(device_packet, &json_string, options);
    //     LOG(INFO) << MODULE_NAME_STR
    //               << "size = " << json_string.size() << " publish data " << json_string;
    // #endif
    //     memset(cmd_buffer, 0, message_len);
    //     device_packet.SerializeToArray(cmd_buffer, message_len);
    //     string topic = "CliCmdAdapter/" + dev_name + "/TX_Send_Cmd_cli";
    //     publish(NULL, topic.data(), message_len, cmd_buffer);
    //     usleep(1000 * 20);
}

INT32 Pub_test::m_mqtt_module_num = 0;
BOOLEAN Pub_test::m_mosquitto_init_status = 0;

int main(int argc, char *argv[])
{
    // Pub_test *dev_pub = new Pub_test("CliCmdAdapter", "localhost", 1883);
    Pub_test *dev_pub = new Pub_test("CliCmdAdapter", "192.168.2.133", 6000);
    string message = "SendCmd PH_ACU1 PH_ACU_AntStatus_Format1";

    // Proto3DeviceAllCMD device_packet;
    // Proto3DeviceCMDDefine *payload_CMD = device_packet.add_cmds();
    int cnt = 0;
    int packet_num = 1000;
    string topic = "zjf/topic";
    while (packet_num--)
        while (1)
        {
            dev_pub->publish(NULL, topic.data(), 5, "12345");

            // usleep(1000 * 1);
            // dev_pub->pub_message("PH_ACU1", "PH_ACU_AntStatus_Format1");
            // dev_pub->pub_message("PH_ACU2", "PH_ACU_AntStatus_Format1");
            // dev_pub->pub_message("PH_ACU3", "PH_ACU_AntStatus_Format1");
            // dev_pub->pub_message("PH_ACU4", "PH_ACU_AntStatus_Format1");
            // dev_pub->pub_message("PH_ACU6", "PH_ACU_AntStatus_Format1");
            // dev_pub->pub_message("PH_ACU7", "PH_ACU_AntStatus_Format1");
            // dev_pub->pub_message("PH_ACU8", "PH_ACU_AntStatus_Format1");
            // dev_pub->pub_message("PH_ACU9", "PH_ACU_AntStatus_Format1");
            // dev_pub->pub_message("PH_ACU10", "PH_ACU_AntStatus_Format1");
            // dev_pub->pub_message("PH_ACU11", "PH_ACU_AntStatus_Format1");
            // dev_pub->pub_message("PH_ACU12", "PH_ACU_AntStatus_Format2");
            // dev_pub->publish(NULL, "DatabaseCenter/Table_XPRO_ALL_DEVINFO/Rsp_for_cli", 1, to_string(cnt).data());
            usleep(1000 * 1000);

            LOG(INFO) << "cnt = " << ++cnt;
        }
    usleep(1000 * 10);

    return 0;
}
// command = r'SendCmd PH_ACU1 PH_ACU_AntStatus_Format1'
// .\mosquitto_sub.exe -t 'roger/topic' -v
