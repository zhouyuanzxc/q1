#ifndef REDISPP_MAIN
#define REDISPP_MAIN


#include <iostream>
#include <vector>
#include <map>

//#include "../base/yx00_macro.h"
//#include "../base/yx00_type.h"

#include <yx00_macro.h>
#include <yx00_type.h>

#define LEN_ITEM 512

#include <unordered_set>

//https://www.cnblogs.com/firstdream/p/7802295.html

class RS {
public:
	static char ip[LEN_ITEM];
	static int  port;
	static char tcpipport[LEN_ITEM];		//such as "tcp://127.0.0.1:6379"

public:
	static void config(const char* tcpiport);
public:
	static bool log(std::string value);
	static bool empty_db();	//����ڴ�pars 
//	static bool empty_pars();	//����ڴ�pars 
	static bool empty_m(const std::string mkey_pattern, std::string& report);	// RS ���m key ��������
	static bool empty_p();	// RS ���p key ��������

	static bool get_hash_all(const std::string pattern, std::initializer_list<std::string>fields, std::vector<std::vector<std::string>>& valss);		//��redis���л�ȡM�����ڹ���

	static bool get_hash_all2(std::unordered_set<std::string> keys,std::initializer_list<std::string>fields, std::vector<std::vector<std::string>>& valss);		//��redis���л�ȡM�����ڹ���
	static bool get_hash_all3(std::vector<std::string> keys, std::initializer_list<std::string>fields, std::vector<std::vector<std::string>>& valss);		//��redis���л�ȡM�����ڹ���


	static bool get_p(std::string key, ITEM* item);		//��ȡp��������д��item��value
	static bool get_p(std::string key, int& intvalue);		//��ȡp��������д��int��value
	static bool get_p(const char* key, int& intvalue);		//��ȡp��������д��int��value
	static bool get_p(std::string key, std::string& strvalue);		//��ȡp��������д��int��value
	static bool get_p(const char* key, char* strvalue);		// 

	static bool get_m(std::string key, ITEM& item);		//��ȡm��������д����item
	static bool get_m(std::string key, std::string& itemstring);		//��ȡm��������д����item
	static bool set_m(ITEM* itemp);
	static bool set_m_all(std::vector<ITEM> pars);		//��redis��������M�����ڹ���
	static bool get_m_all(std::vector<ITEM>& pars);		//��redis���л�ȡM�����ڹ���
	static bool get_m_all(const std::string pattern, std::string& report);		//��redis���л�ȡM�����ڹ���

	static bool get_chn(std::string key, std::string& itemstring);
	static bool get_chn_all(const std::string pattern, std::string& report);		//��redis���л�ȡM�����ڹ���

	static bool get_pro(std::string key, std::string& itemstring);
	static bool get_pro_all(const std::string pattern, std::string& report);		//��redis���л�ȡM�����ڹ���

	static bool set_p(const std::string key, const std::string value, std::string excepcontent);		//��redis��������P�����ڼ�غͲ���
	static bool set_p_all(std::vector<ITEM> pars);		//��redis��������P�����ڼ�غͲ���
	static bool set_p_kvs(std::vector<std::pair<std::string, std::string>>  pars);
	static bool get_p_all(std::vector<ITEM>& pars);		//��redis��������P�����ڼ�غͲ���
	static bool get_p_keys(std::map<std::string, std::string>& maps);
	static bool set_chn(const char* name, const int type, const bool issvr, const char* addr, const int port, const int timeout, const int speed, const bool openkeep, const bool byrecv, const bool connected, const bool flag_task_run, const time_t recvtime, const int cmdid, const int tasknum, const int cur);
	static bool set_pro(const char* name, const jlong id, const int type, const char* chn, const char* sendbuf, const int sendbuflen_must, const int sendbuflen_act, const int sendtime, const char* recvbuf, const int recvbuflen_must, const int recvbuflen_act, const int recvtime, const char* ecpttext, const int status);

	static bool get_CMD(std::string key, std::string& itemstring);
	static bool get_CMD_All(const std::string pattern, std::string& report);
//	static int init();

//	static bool set_p(const char* item, char* val);		//��ȡ����
//	static bool get_p(const char* item, char* val);		//��ȡ����
//	static bool getp(const int devno, const int modno, const int partno, const char* item, char* val);//��ȡ����
//	
//	static bool setvall(std::vector<ITEM> vars);		//��redis���л�ȡ���еı��������ڹ���
//	static bool setv(const char* item, char* val);		//��ȡ����
//	static bool getv(const char* item, char* val);		//��ȡ����
};



#endif