#include <mosquittopp.h>
#include "feature/easylogging/my_easylogging.h"

static int run = -1;
using namespace std;
class mosquittopp_test : public mosqpp::mosquittopp
{
public:
    mosquittopp_test(const char *id);

    void on_connect(int rc);
    void on_disconnect(int rc);
    void on_subscribe(int mid, int qos_count, const int *granted_qos);
    void on_message(const struct mosquitto_message *message);
};

void mosquittopp_test::on_message(const struct mosquitto_message *message)
{
    char buf[message->payloadlen + 1];                                 //根据收到的数据长度来灵活申请内存。 因为数据库中查处理的信息长度不可预知
    memset(buf, 0, message->payloadlen * sizeof(char));                //清空数组
    memcpy(buf, message->payload, message->payloadlen * sizeof(char)); //获取payload内容

    LOG(INFO) << "##################rev::message->topic = " << message->topic;
    cout << "##################rev::message->topic = " << buf << endl;
}

mosquittopp_test::mosquittopp_test(const char *id) : mosqpp::mosquittopp(id)
{
}

void mosquittopp_test::on_connect(int rc)
{
    if (rc)
    {
        LOG(INFO) << "exit = " << rc;

        exit(1);
    }
    else
    {
        LOG(INFO) << "subscribe ";

        subscribe(NULL, "xprotocol/1111", 0); //这里订阅主题的
    }
}

void mosquittopp_test::on_disconnect(int rc)
{
    LOG(INFO) << "on_disconnect ";

    run = rc;
}

void mosquittopp_test::on_subscribe(int mid, int qos_count, const int *granted_qos)
{
    LOG(INFO) << "on_subscribe succeeded111";

    // disconnect();
}

int main(int argc, char *argv[])
{

    easylogginginit(); //初始化easylogging
    En_G_DEBUG_TERMINAL_LOG(0);
    En_G_LOG_DEBUG_INFO(0);

    struct mosquittopp_test *mosq;

    // int port = atoi(argv[1]);

    mosqpp::lib_init();

    mosq = new mosquittopp_test("DatabaseCenter/Table_XPRO_ALL_DEVINFO/Rsp_for_cli");

    mosq->connect("localhost", 1883, 60);
    mosq->subscribe(NULL, "test", 0);

    LOG(INFO) << "run1 = " << run;
    while (run == -1)
    {
        mosq->loop();
    }

    delete mosq;

    mosqpp::lib_cleanup();

    return run;
}
