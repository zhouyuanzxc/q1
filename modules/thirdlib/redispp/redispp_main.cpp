#include "redis++.h"
#include <iostream>
#include <cstdio>
#include <unordered_set>
#include <queue>

//#include "../base/yx01_log.h"
#include "redispp_main.h" 

using namespace sw::redis;

char RS::ip[LEN_ITEM] = "127.0.0.1";  //192.168.137.199
int  RS::port = 6379;
char RS::tcpipport[LEN_ITEM] = "tcp://127.0.0.1:6379";		//such as "tcp://127.0.0.1:6379"

//Redis缓存Object，List对象  https://www.cnblogs.com/firstdream/p/7802295.html  
//结构化存储 http://www.doc88.com/p-7466440106885.html  

void RS::config(const char* tcpipport_ext)
{
	strcpy(tcpipport, tcpipport_ext);
}

bool RS::log(std::string value)
{
	try {
		auto redis = Redis(tcpipport);
		redis.rpush("log", { value });
	}
	catch (const sw::redis::Error& e) {// Error handling.
		std::string msg = e.what();
		if (msg.find("Failed to connect to Redis") != std::string::npos) { //Failed to connect to Redis : 套接字操作尝试一个无法连接的主机。
			printf("%s\n", value.c_str());
			printf("system exit by error : Failed to connect to Redis : 套接字操作尝试一个无法连接的主机。\n");
			exit(-1);
		}
		////CLog::rec(CPPFILE, e.what());  //不做嵌套调用 
		return false;
	}
	return true;
}

//bool RS::empty_pars()	//清空内存pars 
//{
//	std::vector<ITEM>().swap(pars);//最简单的使用swap,清除元素并回收内存//pars.swap(std::vector<ITEM>());   
//	return true;
//}

bool RS::empty_db()	//清空内存pars 
{
	try {
		auto redis = Redis(tcpipport);
		redis.command("flushall");//把M值也清除了
	}
	catch (const sw::redis::Error& e) {// Error handling.
		////CLog::rec(CPPFILE, e.what());
		return false;
	}
	return true;
}

bool RS::empty_m(const std::string mkey_pattern, std::string& report)
{
	try {
		auto redis = Redis(tcpipport);
		//redis.command("flushall");//把M值也清除了

		auto cursor = 0LL;
		//auto mkey_pattern = "M*";		//只清除P*
		auto count = 5;
		std::unordered_set<std::string> keys;
		while (true) {
			cursor = redis.scan(cursor, mkey_pattern, count, std::inserter(keys, keys.begin()));
			// Default pattern is "*", and default count is 10
			// cursor = redis.scan(cursor, std::inserter(keys, keys.begin()));
			if (cursor == 0) {
				break;
			}
		}
		if (!keys.empty())
			redis.del(keys.begin(), keys.end()); //清除P*
		report = "{\"success\":true,\"message\":\"success\",\"code\":200}";
	}
	catch (const sw::redis::Error& e) {// Error handling.
		////CLog::rec(CPPFILE, e.what());
		report = "{\"success\":false,\"message\":\"";
		report += e.what();
		report += "\",\"code\":500}";
		return false;
	}
	return true;
}

bool RS::empty_p()
{
	try {
		auto redis = Redis(tcpipport);
		//		redis.command("flushall");//把M值也清除了

		auto cursor = 0LL;
		auto pattern = "P*";		//只清除P*
		auto count = 5;
		std::unordered_set<std::string> keys;
		while (true) {
			cursor = redis.scan(cursor, pattern, count, std::inserter(keys, keys.begin()));
			// Default pattern is "*", and default count is 10
			// cursor = redis.scan(cursor, std::inserter(keys, keys.begin()));
			if (cursor == 0) {
				break;
			}
		}
		if (!keys.empty())
			redis.del(keys.begin(), keys.end()); //清除P*
	}
	catch (const sw::redis::Error& e) {// Error handling.
		//RS::log(e.what());
		//AfxMessageBox(e.what());
//		//CLog::rec(CPPFILE,e.what());
		////CLog::rec(CPPFILE, e.what());
		return false;
	}
	return true;
}

bool RS::get_hash_all2(std::unordered_set<std::string> keys,std::initializer_list<std::string>fields,std::vector<std::vector<std::string>>& valss)		// 
{
	try {
		auto redis = Redis(tcpipport);
		//		redis.command("select 0");
		//		redis.command("flushall");	
		std::vector<std::string> line;
		std::vector<OptionalString> line_vals;
		for (auto it = keys.begin(); it != keys.end(); ++it) {
			std::vector<std::string>().swap(line);//line.swap(vector<std::string>());
			std::vector<OptionalString>().swap(line_vals);
			redis.hmget(it->c_str(), fields, std::back_inserter(line_vals));
			size_t len = line_vals.size();
			for (size_t i = 0; i < len; i++) {
				line.push_back(line_vals[i].value());
			}
			valss.push_back(line);
		}
	}
	catch (const sw::redis::Error& e) {// Error handling.
		//RS::log(e.what());
		//AfxMessageBox(e.what());
		////CLog::rec(CPPFILE, e.what());
		return false;
	}
	return true;
}

bool RS::get_hash_all3(std::vector<std::string> keys, std::initializer_list<std::string>fields, std::vector<std::vector<std::string>>& valss)		// 
{
	try {
		auto redis = Redis(tcpipport);
//		redis.command("select 0");
//		redis.command("flushall");	
		std::vector<std::string> line;
		std::vector<OptionalString> line_vals;
		for (auto it = keys.begin(); it != keys.end(); ++it) {
			std::vector<std::string>().swap(line);//line.swap(vector<std::string>());
			std::vector<OptionalString>().swap(line_vals);
			redis.hmget(it->c_str(), fields, std::back_inserter(line_vals));
			size_t len = line_vals.size();
			for (size_t i = 0; i < len; i++) {
				line.push_back(line_vals[i].value());
			}
			valss.push_back(line);
		}
	}
	catch (const sw::redis::Error& e) {// Error handling.
		//RS::log(e.what());
		//AfxMessageBox(e.what());
		////CLog::rec(CPPFILE, e.what());
		return false;
	}
	return true;
}

bool RS::get_hash_all(const std::string pattern, std::initializer_list<std::string>fields, std::vector<std::vector<std::string>>& valss)		//从redis库中获取M表，用于管理
{
	try {
		auto redis = Redis(tcpipport);
		//		redis.command("select 0");
		//		redis.command("flushall");
		auto cursor = 0LL;
		//auto pattern = "M*";
		auto count = 5;
		std::unordered_set<std::string> keys;
		while (true) {
			cursor = redis.scan(cursor, pattern, count, std::inserter(keys, keys.begin()));
			// Default pattern is "*", and default count is 10
			// cursor = redis.scan(cursor, std::inserter(keys, keys.begin()));
			if (cursor == 0) {
				break;
			}
		}
		std::vector<OptionalString> line_vals;
		std::vector<std::string> line;

		for (auto it = keys.begin(); it != keys.end(); ++it) {
			std::vector<std::string>().swap(line);//line.swap(vector<std::string>());
			std::vector<OptionalString>().swap(line_vals);
			redis.hmget(it->c_str(), fields, std::back_inserter(line_vals));
			size_t len = line_vals.size();
			for (size_t i = 0; i < len; i++) {
				line.push_back(line_vals[i].value());
			}
			valss.push_back(line);
		}


	}
	catch (const sw::redis::Error& e) {// Error handling.
		//RS::log(e.what());
		//AfxMessageBox(e.what());
		////CLog::rec(CPPFILE, e.what());
		return false;
	}
	return true;
}

bool RS::set_m(ITEM* itemp)
{
	if (itemp == nullptr)
		return false;
	char itemkey[LEN_ITEM], itemval[LEN_ITEM];

	try {
		auto redis = Redis(tcpipport);
		sprintf(itemkey, "M%02d%04d%02d%s", itemp->devno, itemp->modno, itemp->partno, itemp->key);
		strcpy(itemp->mkey, itemkey);				redis.hset(itemkey, "mkey", itemp->mkey);
		sprintf(itemp->pkey, "P%02d%04d%02d%s", itemp->devno, itemp->modno, itemp->partno, itemp->key);
		redis.hset(itemkey, "pkey", itemp->pkey);
		sprintf(itemval, "%d", itemp->devno);		redis.hset(itemkey, "devno", itemval);			//redis.hset(itemkey, std::make_pair("devno", itemval));
		sprintf(itemval, "%d", itemp->modno);		redis.hset(itemkey, "modno", itemval);
		sprintf(itemval, "%d", itemp->partno);		redis.hset(itemkey, "partno", itemval);
		redis.hset(itemkey, "key", itemp->key);
		sprintf(itemval, "%d", itemp->ifvar);		redis.hset(itemkey, "ifvar", itemval);			//redis.hset(itemkey, std::make_pair("devno", itemval));
		sprintf(itemval, "%d", itemp->datatype);	redis.hset(itemkey, "datatype", itemval);
		sprintf(itemval, "%d", itemp->datalen);		redis.hset(itemkey, "datalen", itemval);
		redis.hset(itemkey, "value", itemp->value);
		redis.hset(itemkey, "valdef", itemp->valdef);
		redis.hset(itemkey, "valall", itemp->valall);
		redis.hset(itemkey, "style", itemp->style);
	}
	catch (const sw::redis::Error& e) {// Error handling.
		////CLog::rec(CPPFILE, e.what());
		return false;
	}

	return true;
}

bool RS::set_m_all(std::vector<ITEM> pars)		//向redis库中设置所有参量表，用于管理
{
	char itemkey[LEN_ITEM], itemval[LEN_ITEM];
	try {
		auto redis = Redis(tcpipport);
		for (auto item : pars) {
			sprintf(itemkey, "M%02d%04d%02d%s", item.devno, item.modno, item.partno, item.key);
			strcpy(item.mkey, itemkey);				redis.hset(itemkey, "mkey", item.mkey);
			sprintf(item.pkey, "P%02d%04d%02d%s", item.devno, item.modno, item.partno, item.key);
			redis.hset(itemkey, "pkey", item.pkey);
			sprintf(itemval, "%d", item.devno);		redis.hset(itemkey, "devno", itemval);			//redis.hset(itemkey, std::make_pair("devno", itemval));
			sprintf(itemval, "%d", item.modno);		redis.hset(itemkey, "modno", itemval);
			sprintf(itemval, "%d", item.partno);	redis.hset(itemkey, "partno", itemval);
			redis.hset(itemkey, "key", item.key);
			sprintf(itemval, "%d", item.ifvar);		redis.hset(itemkey, "ifvar", itemval);
			sprintf(itemval, "%d", item.datatype);	redis.hset(itemkey, "datatype", itemval);
			sprintf(itemval, "%d", item.datalen);	redis.hset(itemkey, "datalen", itemval);
			redis.hset(itemkey, "value", item.value);
			redis.hset(itemkey, "valdef", item.valdef);
			redis.hset(itemkey, "valall", item.valall);
			redis.hset(itemkey, "style", item.style);
		}
	}
	catch (const sw::redis::Error& e) {// Error handling.
		////CLog::rec(CPPFILE, e.what());
		return false;
	}
	return true;

}
bool RS::get_p(std::string key, ITEM* item)		//获取P参数
{
	if (key.size() <= 9)
		return false;
	try {
		auto redis = Redis(tcpipport);
		auto val = redis.get(key);
		if (!val)
			return false;
		strcpy(item->value, (*val).c_str());
	}
	catch (const sw::redis::Error& e) {// Error handling.
		////CLog::rec(CPPFILE, e.what());
		return false;
	}
	return true;
}

bool RS::get_p(std::string key, int& intvalue)		//获取p参数，填写到int的value
{
	if (key.size() <= 9)
		return false;
	try {
		auto redis = Redis(tcpipport);
		auto val = redis.get(key);
		if (!val)
			return false;
		intvalue = atoi((*val).c_str());
		return true;
	}
	catch (const sw::redis::Error& e) {// Error handling.
		////CLog::rec(CPPFILE, e.what());
		return false;
	}
	return false;
}

bool RS::get_p(const char* key, int& intvalue)		//获取p参数，填写到int的value
{
	if (strlen(key) <= 9)
		return false;
	try {
		auto redis = Redis(tcpipport);
		auto val = redis.get(key);
		if (!val)
			return false;
		intvalue = atoi((*val).c_str());
		return true;
	}
	catch (const sw::redis::Error& e) {// Error handling.
		////CLog::rec(CPPFILE, e.what());
		return false;
	}
	return false;
}

bool RS::get_p(std::string key, std::string& strvalue)		//获取p参数，填写到string的value
{
	if (key.size() <= 9)
		return false;
	try {
		auto redis = Redis(tcpipport);
		auto val = redis.get(key);
		if (!val)
			return false;
		strvalue = *val;
		return true;
	}
	catch (const sw::redis::Error& e) {// Error handling.
		////CLog::rec(CPPFILE, e.what());
		return false;
	}
	return false;
}

bool RS::get_p(const char* key, char* strvalue)		// 
{
	if (strlen(key) <= 9)
		return false;
	try {
		auto redis = Redis(tcpipport);
		auto val = redis.get(key);
		if (!val)
			return false;
		strcpy(strvalue, (*val).c_str());
		return true;
	}
	catch (const sw::redis::Error& e) {// Error handling.
		////CLog::rec(CPPFILE, e.what());
		return false;
	}
	return false;
}

bool RS::get_m(std::string  key, ITEM& item)		//获取M参数
{
	if (key.size() <= 9)
		return false;
	try {
		auto redis = Redis(tcpipport);
		//	std::unordered_map<std::string, std::string> m;
		//	m.clear();
		//	redis.hgetall(key, std::inserter(m, m.begin()));
			// Get value only.
			// NOTE: since field might NOT exist, so we need to parse it to OptionalString.
		std::vector<OptionalString> vals;
		redis.hmget(key, { "mkey","pkey","devno","modno","partno","key","ifvar","datatype","datalen","value","valdef","valall","style" }, std::back_inserter(vals));
		strcpy(item.mkey, vals[0].value().c_str());
		strcpy(item.pkey, vals[1].value().c_str());
		item.devno = atoi(vals[2].value().c_str());
		item.modno = atoi(vals[3].value().c_str());
		item.partno = atoi(vals[4].value().c_str());
		strcpy(item.key, vals[5].value().c_str());
		item.ifvar = atoi(vals[6].value().c_str());
		item.datatype = atoi(vals[7].value().c_str());
		item.datalen = atoi(vals[8].value().c_str());
		strcpy(item.value, vals[9].value().c_str());
		strcpy(item.valdef, vals[10].value().c_str());
		strcpy(item.valall, vals[11].value().c_str());
		strcpy(item.style, vals[12].value().c_str());
	}
	catch (const sw::redis::Error& e) {// Error handling.
		////CLog::rec(CPPFILE, e.what());
		return false;
	}
	return true;
}

bool RS::get_m(std::string key, std::string& itemstring)		//获取m参数，填写整个item
{
	if (key.size() <= 9)
		return false;
	try {
		auto redis = Redis(tcpipport);
		//	std::unordered_map<std::string, std::string> m;
		//	m.clear();
		//	redis.hgetall(key, std::inserter(m, m.begin()));
			// Get value only.
			// NOTE: since field might NOT exist, so we need to parse it to OptionalString.
		std::vector<OptionalString> vals;
		redis.hmget(key, { "mkey","pkey","devno","modno","partno","key","ifvar","datatype","datalen","value","valdef","valall","style" }, std::back_inserter(vals));
		itemstring = "{";
		itemstring += ("\"mkey\":\"" + vals[0].value() + "\",");
		itemstring += ("\"pkey\":\"" + vals[1].value() + "\",");
		itemstring += ("\"devno\":" + vals[2].value() + ",");
		itemstring += ("\"modno\":" + vals[3].value() + ",");
		itemstring += ("\"partno\":" + vals[4].value() + ",");
		itemstring += ("\"key\":\"" + vals[5].value() + "\",");
		itemstring += ("\"ifvar\":" + vals[6].value() + ",");
		itemstring += ("\"datatype\":" + vals[7].value() + ",");
		itemstring += ("\"datalen\":" + vals[8].value() + ",");
		itemstring += ("\"value\":\"" + vals[9].value() + "\",");
		itemstring += ("\"valdef\":\"" + vals[10].value() + "\",");
		itemstring += ("\"valall\":\"" + vals[11].value() + "\",");
		itemstring += ("\"style\":\"" + vals[12].value() + "\"");
		itemstring += "}";

	}
	catch (const sw::redis::Error& e) {// Error handling.
		////CLog::rec(CPPFILE, e.what());
		return false;
	}
	return true;
}

bool RS::get_m_all(std::vector<ITEM>& pars)		//从redis库中获取所有参量表，用于管理
{
	//char itemkey[LEN_ITEM], itemval[LEN_ITEM];
	try {
		auto redis = Redis(tcpipport);
//		redis.command("select 0");
//		redis.command("flushall");

		auto cursor = 0LL;
		auto pattern = "M*";
		auto count = 5;
		std::unordered_set<std::string> keys;
		while (true) {
			cursor = redis.scan(cursor, pattern, count, std::inserter(keys, keys.begin()));
			// Default pattern is "*", and default count is 10
			// cursor = redis.scan(cursor, std::inserter(keys, keys.begin()));
			if (cursor == 0) {
				break;
			}
		}
		ITEM item;
		for (auto it = keys.begin(); it != keys.end(); ++it) {
			get_m(it->c_str(), item);
			pars.push_back(item);
		}
	}
	catch (const sw::redis::Error& e) {// Error handling.
		//RS::log(e.what());
		//AfxMessageBox(e.what());
		////CLog::rec(CPPFILE, e.what());
		return false;
	}
	return true;
}

bool RS::get_m_all(const std::string pattern, std::string& report)		//从redis库中获取M表，用于管理
{
	try {
		auto redis = Redis(tcpipport);
//		redis.command("select 0");
//		redis.command("flushall");

		auto cursor = 0LL;
		//auto pattern = "M*";
		auto count = 5;
		std::unordered_set<std::string> keys;
		while (true) {
			cursor = redis.scan(cursor, pattern, count, std::inserter(keys, keys.begin()));
			// Default pattern is "*", and default count is 10
			// cursor = redis.scan(cursor, std::inserter(keys, keys.begin()));
			if (cursor == 0) {
				break;
			}
		}
		//ITEM item;
		std::string itemstring = "";
		report = "[";
		for (auto it = keys.begin(); it != keys.end(); ++it) {
			get_m(it->c_str(), itemstring);//
			//pars.push_back(item);
			report += (itemstring + ",");
		}
		if (report.length() != 1)
			report.pop_back();
		report += "]";
	}
	catch (const sw::redis::Error& e) {// Error handling.
		//RS::log(e.what());
		//AfxMessageBox(e.what());
		////CLog::rec(CPPFILE, e.what());
		return false;
	}
	return true;
}

bool RS::get_chn(std::string key, std::string& itemstring)		//获取m参数，填写整个item
{
	try {
		auto redis = Redis(tcpipport);
		//	std::unordered_map<std::string, std::string> m;
		//	m.clear();
		//	redis.hgetall(key, std::inserter(m, m.begin()));
			// Get value only.
			// NOTE: since field might NOT exist, so we need to parse it to OptionalString.
		std::vector<OptionalString> vals;
		//const char* name, const int type, const bool issvr, const char* addr, const int port, const int timeout, const int speed, const bool openkeep, const bool byrecv, const bool connected, const bool flag_task_run, const time_t recvtime, const int cmdid, const int tasknum, const int cur

		redis.hmget(key, { "name","type","issvr","addr","port","timeout","speed","openkeep","byrecv","connected","flag_task_run","recvtime","cmdid","tasknum","cur" }, std::back_inserter(vals));
		itemstring = "{";
		itemstring += ("\"name\":\"" + vals[0].value() + "\",");
		itemstring += ("\"type\":" + vals[1].value() + ",");
		itemstring += ("\"issvr\":" + vals[2].value() + ",");
		itemstring += ("\"addr\":\"" + vals[3].value() + "\",");
		itemstring += ("\"port\":" + vals[4].value() + ",");
		itemstring += ("\"timeout\":" + vals[5].value() + ",");
		itemstring += ("\"speed\":" + vals[6].value() + ",");
		itemstring += ("\"openkeep\":" + vals[7].value() + ",");
		itemstring += ("\"byrecv\":" + vals[8].value() + ",");
		itemstring += ("\"connected\":" + vals[9].value() + ",");
		itemstring += ("\"flag_task_run\":" + vals[10].value() + ",");
		itemstring += ("\"recvtime\":" + vals[11].value() + ",");
		itemstring += ("\"cmdid\":" + vals[12].value() + ",");
		itemstring += ("\"tasknum\":" + vals[13].value() + ",");
		itemstring += ("\"cur\":" + vals[14].value() + "");
		itemstring += "}";
	}
	catch (const sw::redis::Error& e) {// Error handling.
		////CLog::rec(CPPFILE, e.what());
		return false;
	}
	return true;
}

bool RS::get_chn_all(const std::string pattern, std::string& report)		//从redis库中获取M表，用于管理
{
	try {
		auto redis = Redis(tcpipport);
//		redis.command("select 0");
//		redis.command("flushall");

		auto cursor = 0LL;
		//auto pattern = "M*";
		auto count = 5;
		std::unordered_set<std::string> keys;
		while (true) {
			cursor = redis.scan(cursor, pattern, count, std::inserter(keys, keys.begin()));
			// Default pattern is "*", and default count is 10
			// cursor = redis.scan(cursor, std::inserter(keys, keys.begin()));
			if (cursor == 0) {
				break;
			}
		}
		//ITEM item;
		std::string itemstring = "";
		report = "[";
		for (auto it = keys.begin(); it != keys.end(); ++it) {
			get_chn(it->c_str(), itemstring);//
			//pars.push_back(item);
			report += (itemstring + ",");
		}
		if (report.length() != 1)
			report.pop_back();
		report += "]";
	}
	catch (const sw::redis::Error& e) {// Error handling.
		//RS::log(e.what());
		//AfxMessageBox(e.what());
	//	//CLog::rec(CPPFILE, e.what());
		return false;
	}
	return true;
}


bool RS::get_pro(std::string key, std::string& itemstring)		//获取m参数，填写整个item
{
	try {
		auto redis = Redis(tcpipport);
		//	std::unordered_map<std::string, std::string> m;
		//	m.clear();
		//	redis.hgetall(key, std::inserter(m, m.begin()));
			// Get value only.
			// NOTE: since field might NOT exist, so we need to parse it to OptionalString.
		std::vector<OptionalString> vals;
		//const char* name, const jlong id, const int type, const char* sendbuf, const int sendbuflen_must, const int sendbuflen_act, const int sendtime, const char* recvbuf, const int recvbuflen_must, const int recvbuflen_act, const int recvtime, const char* ecpttext, const int status

		redis.hmget(key, { "name","id","type","chn","sendbuf","sendbuflen_must","sendbuflen_act","sendtime","recvbuf","recvbuflen_must","recvbuflen_act","recvtime","ecpttext","status" }, std::back_inserter(vals));
		itemstring = "{";
		itemstring += ("\"name\":\"" + vals[0].value() + "\",");
		itemstring += ("\"id\":" + vals[1].value() + ",");
		itemstring += ("\"type\":" + vals[2].value() + ",");
		itemstring += ("\"chn\":\"" + vals[3].value() + "\",");
		itemstring += ("\"sendbuf\":\"" + vals[4].value() + "\",");
		itemstring += ("\"sendbuflen_must\":" + vals[5].value() + ",");
		itemstring += ("\"sendbuflen_act\":" + vals[6].value() + ",");
		itemstring += ("\"sendtime\":" + vals[7].value() + ",");
		itemstring += ("\"recvbuf\":\"" + vals[8].value() + "\",");
		itemstring += ("\"recvbuflen_must\":" + vals[9].value() + ",");
		itemstring += ("\"recvbuflen_act\":" + vals[10].value() + ",");
		itemstring += ("\"recvtime\":" + vals[11].value() + ",");
		itemstring += ("\"ecpttext\":\"" + vals[12].value() + "\",");
		itemstring += ("\"status\":" + vals[13].value() + "");
		itemstring += "}";
	}
	catch (const sw::redis::Error& e) {// Error handling.
		////CLog::rec(CPPFILE, e.what());
		return false;
	}
	return true;
}


bool RS::get_pro_all(const std::string pattern, std::string& report)		//从redis库中获取M表，用于管理
{
	try {
		auto redis = Redis(tcpipport);
//		redis.command("select 0");
//		redis.command("flushall");

		auto cursor = 0LL;
		//auto pattern = "M*";
		auto count = 5;
		std::unordered_set<std::string> keys;
		while (true) {
			cursor = redis.scan(cursor, pattern, count, std::inserter(keys, keys.begin()));
			// Default pattern is "*", and default count is 10
			// cursor = redis.scan(cursor, std::inserter(keys, keys.begin()));
			if (cursor == 0) {
				break;
			}
		}
		//ITEM item;
		std::string itemstring = "";
		report = "[";
		for (auto it = keys.begin(); it != keys.end(); ++it) {
			get_pro(it->c_str(), itemstring);//
			//pars.push_back(item);
			report += (itemstring + ",");
		}
		if (report.length() != 1)
			report.pop_back();
		report += "]";
	}
	catch (const sw::redis::Error& e) {// Error handling.
		//RS::log(e.what());
		//AfxMessageBox(e.what());
		////CLog::rec(CPPFILE, e.what());
		return false;
	}
	return true;
}

bool RS::set_p(const std::string key, const std::string value, std::string excepcontent)		//向redis库中设置P表，用于监控和操作
{
	try {
		auto redis = Redis(tcpipport);
		//itemkey=myprintf("P%02d%04d%02d%s", item.devno, item.modno, item.partno, item.keyname);
		redis.set(key, value);
	}
	catch (const sw::redis::Error& e) {// Error handling.
		//RS::log(e.what());
		//AfxMessageBox(e.what());
		////CLog::rec(CPPFILE, e.what());
		excepcontent = e.what();
		return false;
	}
	return true;
}
/// std::vector<std::pair<std::string, std::string>> kvs1 = {{"k1", "v1"}, {"k2", "v2"}};
/// redis.mset(kvs1.begin(), kvs1.end());
/// std::unordered_map<std::string, std::string> kvs2 = {{"k3", "v3"}, {"k4", "v4"}};
/// redis.mset(kvs2.begin(), kvs2.end());
/// 

bool RS::set_p_kvs(std::vector<std::pair<std::string, std::string>> pars)
{
	try {
		auto redis = Redis(tcpipport);
		redis.mset(pars.begin(), pars.end());
		//itemkey=myprintf("P%02d%04d%02d%s", item.devno, item.modno, item.partno, item.keyname);
		//redis.set(key, value);
	}
	catch (const sw::redis::Error& e) {// Error handling.
		//RS::log(e.what());
		//AfxMessageBox(e.what());
		////CLog::rec(CPPFILE, e.what());
		//excepcontent = e.what();
		return false;
	}
	return true;
}

bool RS::set_p_all(std::vector<ITEM> pars)		//向redis库中设置P表，用于监控和操作
{
	//	redis.command("flushall");//把P值也清除了
	empty_p();

	char itemkey[LEN_ITEM];
	try {
		auto redis = Redis(tcpipport);
		for (auto item : pars) {
			//itemkey=myprintf("P%02d%04d%02d%s", item.devno, item.modno, item.partno, item.keyname);
			sprintf(itemkey, "P%02d%04d%02d%s", item.devno, item.modno, item.partno, item.key);
			redis.set(itemkey, item.value);
		}
	}
	catch (const sw::redis::Error& e) {// Error handling.
		//RS::log(e.what());
		//AfxMessageBox(e.what());
		////CLog::rec(CPPFILE, e.what());
		return false;
	}
	return true;
}

ITEM* getitem(std::vector<ITEM> pars, std::string key)
{
	for (auto item : pars)
		if (key == item.mkey)
			return &item;
	return nullptr;
	//	std::vector<ITEM>::iterator it = std::find_if(pars.begin(), pars.end(), ((ITEM)(*it)).mkey==key);
	//	if (it == pars.end())
	//		return nullptr;
	//	else
	//		return &(*it);
}

bool RS::get_p_all(std::vector<ITEM>& pars)		// 
{
	//std::vector<ITEM>().swap(pars);//最简单的使用swap,清除元素并回收内存//pars.swap(std::vector<ITEM>());   
	try {
		auto redis = Redis(tcpipport);
		//		redis.command("select 0");
		//		redis.command("flushall");

		auto cursor = 0LL;
		auto pattern = "P*";
		auto count = 5;
		std::unordered_set<std::string> keys;
		while (true) {
			cursor = redis.scan(cursor, pattern, count, std::inserter(keys, keys.begin()));
			// Default pattern is "*", and default count is 10
			// cursor = redis.scan(cursor, std::inserter(keys, keys.begin()));
			if (cursor == 0) {
				break;
			}
		}
		ITEM* pitem = nullptr;
		for (auto it = keys.begin(); it != keys.end(); ++it) {
			if ((pitem = getitem(pars, it->c_str())) != nullptr)
				get_p(it->c_str(), pitem);
		}
	}
	catch (const sw::redis::Error& e) {// Error handling.
		//RS::log(e.what());
		//AfxMessageBox(e.what());
		////CLog::rec(CPPFILE, e.what());
		return false;
	}
	return true;
}

bool RS::get_p_keys(std::map<std::string, std::string>& maps) {
	if (maps.size() > 0)
		try {
		auto redis = Redis(tcpipport);
		auto tx = redis.transaction();
		std::vector<std::string > keys;
		std::map<std::string, std::string>::iterator iter;
		for (iter = maps.begin(); iter != maps.end(); iter++)
			keys.push_back(iter->first);
		std::vector<OptionalString> vals;
		redis.mget(keys.begin(), keys.end(), std::back_inserter(vals));
		iter = maps.begin();
		for (const auto& val : vals) {
			if (val)
				iter->second = *val;// std::cout << *val << std::endl;
			else
				iter->second = ""; //std::cout << "key does not exist" << std::endl;
			iter++;
		}
	}
	catch (const sw::redis::Error& e) {// Error handling.
		////CLog::rec(CPPFILE, e.what());
		return false;
	}
	return true;
}
//name,type,issvr,addr,port,timeout,speed,openkeep,byrecv,connected,flag_task_run, recvtime, cmdid,tasknum,cur
bool RS::set_chn(const char* name, const int type, const bool issvr, const char* addr, const int port, const int timeout, const int speed, const bool openkeep, const bool byrecv, const bool connected, const bool flag_task_run, const time_t recvtime, const int cmdid, const int tasknum, const int cur)
{
	char itemkey[LEN_ITEM], itemval[LEN_ITEM];

	try {
		auto redis = Redis(tcpipport);
		sprintf(itemkey, "chn%s", name);

		redis.hset(itemkey, "name", name);
		sprintf(itemval, "%d", type);			redis.hset(itemkey, "type", itemval);
		sprintf(itemval, "%d", issvr);			redis.hset(itemkey, "issvr", itemval);
		redis.hset(itemkey, "addr", addr);
		sprintf(itemval, "%d", port);			redis.hset(itemkey, "port", itemval);
		sprintf(itemval, "%d", timeout);		redis.hset(itemkey, "timeout", itemval);
		sprintf(itemval, "%d", speed);			redis.hset(itemkey, "speed", itemval);
		sprintf(itemval, "%d", openkeep);		redis.hset(itemkey, "openkeep", itemval);
		sprintf(itemval, "%d", byrecv);			redis.hset(itemkey, "byrecv", itemval);
		sprintf(itemval, "%d", connected);		redis.hset(itemkey, "connected", itemval);
		sprintf(itemval, "%d", flag_task_run);	redis.hset(itemkey, "flag_task_run", itemval);
#ifdef _MSC_VER
		sprintf(itemval, "%I64d", recvtime);	redis.hset(itemkey, "recvtime", itemval);
#else
		sprintf(itemval, "%lld", recvtime);	redis.hset(itemkey, "recvtime", itemval);
#endif
		sprintf(itemval, "%d", cmdid);			redis.hset(itemkey, "cmdid", itemval);
		sprintf(itemval, "%d", tasknum);		redis.hset(itemkey, "tasknum", itemval);
		sprintf(itemval, "%d", cur);			redis.hset(itemkey, "cur", itemval);
	}
	catch (const sw::redis::Error& e) {// Error handling.
		//CLog::rec(CPPFILE, e.what());
		return false;
	}

	return true;

}

bool RS::get_CMD(std::string key, std::string& itemstring)		//获取m参数，填写整个item
{
	try {
		auto redis = Redis(tcpipport);
		//	std::unordered_map<std::string, std::string> m;
		//	m.clear();
		//	redis.hgetall(key, std::inserter(m, m.begin()));
			// Get value only.
			// NOTE: since field might NOT exist, so we need to parse it to OptionalString.
		std::vector<OptionalString> vals;
		redis.hmget(key, {
		"sendbuflen_must","recvbuf","chn",
		"sendbuf","title","type","sendbuflen_act",
		"recvtime","name","recvbuflen_act",
		"ecpttext","id","sendtime",
		"recvbuflen_must","status",
			}, std::back_inserter(vals));
		itemstring = "{";
		itemstring += ("\"sendbuflen_must\":" + vals[0].value() + ",");
		itemstring += ("\"recvbuf\":\"" + vals[1].value() + "\",");
		itemstring += ("\"chn\":\"" + vals[2].value() + "\",");

		itemstring += ("\"sendbuf\":\"" + vals[3].value() + "\",");
		itemstring += ("\"title\":\"" + vals[4].value() + "\",");
		itemstring += ("\"type\":" + vals[5].value() + ",");
		itemstring += ("\"sendbuflen_act\":" + vals[6].value() + ",");

		itemstring += ("\"recvtime\":" + vals[7].value() + ",");
		itemstring += ("\"name\":\"" + vals[8].value() + "\",");
		itemstring += ("\"recvbuflen_act\":" + vals[9].value() + ",");

		itemstring += ("\"ecpttext\":\"" + vals[10].value() + "\",");
		itemstring += ("\"id\":" + vals[11].value() + ",");
		itemstring += ("\"sendtime\":" + vals[12].value() + ",");
		itemstring += ("\"recvbuflen_must\":" + vals[13].value() + ",");
		itemstring += ("\"status\":" + vals[14].value() + "");
		itemstring += "}";
	}
	catch (const sw::redis::Error& e) {// Error handling.
		//CLog::rec(CPPFILE, e.what());
		return false;
	}
	return true;

}
bool RS::get_CMD_All(const std::string pattern, std::string& report)		//从redis库中获取M表，用于管理
{
	try {
		auto redis = Redis(tcpipport);
//		redis.command("select 0");
//		redis.command("flushall");
		auto cursor = 0LL;
		//auto pattern = "M*";
		auto count = 5;
		std::unordered_set<std::string> keys;
		while (true) {
			cursor = redis.scan(cursor, pattern, count, std::inserter(keys, keys.begin()));
			// Default pattern is "*", and default count is 10
			// cursor = redis.scan(cursor, std::inserter(keys, keys.begin()));
			if (cursor == 0) {
				break;
			}
		}
		//ITEM item;
		std::string itemstring = "";
		report = "[";
		for (auto it = keys.begin(); it != keys.end(); ++it) {
			if (strlen(it->c_str()) > 15)
			{
				get_CMD(it->c_str(), itemstring);//
				//pars.push_back(item);
				if (!itemstring.empty() && itemstring.length() > 15)
					report += (itemstring + ",");
			}
		}
		if (report.length() != 1)
			report.pop_back();
		report += "]";
	}
	catch (const sw::redis::Error& e) {// Error handling.
		//RS::log(e.what());
		//AfxMessageBox(e.what());
		//CLog::rec(CPPFILE, e.what());
		return false;
	}
	return true;
}

bool RS::set_pro(const char* name, const jlong id, const int type, const char* chn, const char* sendbuf, const int sendbuflen_must, const int sendbuflen_act, const int sendtime,
	const char* recvbuf, const int recvbuflen_must, const int recvbuflen_act, const int recvtime, const char* ecpttext, const int status)
{
	char itemkey[LEN_ITEM], itemval[LEN_ITEM];

	try {
		auto redis = Redis(tcpipport);
		sprintf(itemkey, "pro%s", name);

		redis.hset(itemkey, "name", name);
#ifdef _MSC_VER
		sprintf(itemval, "%I64d", id);				redis.hset(itemkey, "id", itemval);
#else
		sprintf(itemval, "%lld", id);				redis.hset(itemkey, "id", itemval);
#endif
		sprintf(itemval, "%d", type);				redis.hset(itemkey, "type", itemval);
		redis.hset(itemkey, "chn", chn);

		redis.hset(itemkey, "sendbuf", sendbuf);
		sprintf(itemval, "%d", sendbuflen_must);	redis.hset(itemkey, "sendbuflen_must", itemval);
		sprintf(itemval, "%d", sendbuflen_act);		redis.hset(itemkey, "sendbuflen_act", itemval);
		sprintf(itemval, "%d", sendtime * 1);		redis.hset(itemkey, "sendtime", itemval);

		redis.hset(itemkey, "recvbuf", recvbuf);
		sprintf(itemval, "%d", recvbuflen_must);	redis.hset(itemkey, "recvbuflen_must", itemval);
		sprintf(itemval, "%d", recvbuflen_act);		redis.hset(itemkey, "recvbuflen_act", itemval);
		sprintf(itemval, "%d", recvtime * 1);		redis.hset(itemkey, "recvtime", itemval);

		redis.hset(itemkey, "ecpttext", ecpttext);
		sprintf(itemval, "%d", status);				redis.hset(itemkey, "status", itemval);
	}
	catch (const sw::redis::Error& e) {// Error handling.
		//CLog::rec(CPPFILE, e.what());
		return false;
	}

	return true;
}



//bool RS::getmodpar(std::string mod, std::string item, int defval, std::string path)
//{
//	//从 redis 获取分类配置的int值，如果没有，则新增并设置缺省值
//	if(true)
//		return true;
//	return false;
//};
//
//bool RS::getp(const int devno, const int modno, const int partno, const char* item, char *val)//获取参数
//{
//	//获取类型，返回
//	return true;
//}
//
//int RS::init()
//{
//	//	empty_db();
//
//	//	empty_m();
//	//	set_m_all(pars);
//	//	
//	empty_pars();
//	get_m_all(pars);
//	//	
//	set_p_all(pars);
//	//	
//	//	empty_p();
//	//	get_p_all(pars);
//
//	return 0;
//}
//


static int  basedemo()//int argc, char** argv
{
	try {
		// Create an Redis object, which is movable but NOT copyable.
		auto redis = Redis(RS::tcpipport);

		// ***** STRING commands *****

		redis.set("key", "val");
		auto val = redis.get("key");    // val is of type OptionalString. See 'API Reference' section for details.
		if (val) {
			// Dereference val to get the returned value of std::string type.
			std::cout << *val << std::endl;
		}   // else key doesn't exist.

		// ***** LIST commands *****

		// std::vector<std::string> to Redis LIST.
		std::vector<std::string> vec = { "a", "b", "c" };
		redis.rpush("list", vec.begin(), vec.end());

		// std::initializer_list to Redis LIST.
		redis.rpush("list", { "a", "b", "c" });

		// Redis LIST to std::vector<std::string>.
		vec.clear();
		redis.lrange("list", 0, -1, std::back_inserter(vec));

		// ***** HASH commands *****

		redis.hset("hash", "field", "val");

		// Another way to do the same job.
		redis.hset("hash", std::make_pair("field", "val"));

		// std::unordered_map<std::string, std::string> to Redis HASH.
		std::unordered_map<std::string, std::string> m = {
			{"field1", "val1"},
			{"field2", "val2"}
		};
		redis.hmset("hash", m.begin(), m.end());

		// Redis HASH to std::unordered_map<std::string, std::string>.
		m.clear();
		redis.hgetall("hash", std::inserter(m, m.begin()));

		// Get value only.
		// NOTE: since field might NOT exist, so we need to parse it to OptionalString.
		std::vector<OptionalString> vals;
		redis.hmget("hash", { "field1", "field2" }, std::back_inserter(vals));

		// ***** SET commands *****

		redis.sadd("set", "m1");

		// std::unordered_set<std::string> to Redis SET.
		std::unordered_set<std::string> set = { "m2", "m3" };
		redis.sadd("set", set.begin(), set.end());

		// std::initializer_list to Redis SET.
		redis.sadd("set", { "m2", "m3" });

		// Redis SET to std::unordered_set<std::string>.
		set.clear();
		redis.smembers("set", std::inserter(set, set.begin()));

		if (redis.sismember("set", "m1")) {
			std::cout << "m1 exists" << std::endl;
		}   // else NOT exist.

		// ***** SORTED SET commands *****

		redis.zadd("sorted_set", "m1", 1.3);

		// std::unordered_map<std::string, double> to Redis SORTED SET.
		std::unordered_map<std::string, double> scores = {
			{"m2", 2.3},
			{"m3", 4.5}
		};
		redis.zadd("sorted_set", scores.begin(), scores.end());

		// Redis SORTED SET to std::unordered_map<std::string, double>.
		scores.clear();
		redis.zrangebyscore("sorted_set",
			UnboundedInterval<double>{},            // (-inf, +inf)
			std::inserter(scores, scores.begin()));

		// Only get member names:
		// pass an inserter of std::vector<std::string> type as output parameter.
		std::vector<std::string> without_score;
		redis.zrangebyscore("sorted_set",
			BoundedInterval<double>(1.5, 3.4, BoundType::CLOSED),   // [1.5, 3.4]
			std::back_inserter(without_score));

		// Get both member names and scores:
		// pass an inserter of std::unordered_map<std::string, double> as output parameter.
		std::unordered_map<std::string, double> with_score;
		redis.zrangebyscore("sorted_set",
			BoundedInterval<double>(1.5, 3.4, BoundType::LEFT_OPEN),    // (1.5, 3.4]
			std::inserter(with_score, with_score.end()));

		// ***** SCRIPTING commands *****

		// Script returns a single element.
		auto num = redis.eval<long long>("return 1", {}, {});

		// Script returns an array of elements.
		std::vector<long long> nums;
		redis.eval("return {ARGV[1], ARGV[2]}", {}, { "1", "2" }, std::back_inserter(nums));

		// ***** Pipeline *****

		// Create a pipeline.
		auto pipe = redis.pipeline();

		// Send mulitple commands and get all replies.
		auto pipe_replies = pipe.set("key", "value")
			.get("key")
			.rename("key", "new-key")
			.rpush("list", { "a", "b", "c" })
			.lrange("list", 0, -1)
			.exec();

		// Parse reply with reply type and index.
		auto set_cmd_result = pipe_replies.get<bool>(0);

		auto get_cmd_result = pipe_replies.get<OptionalString>(1);

		// rename command result
		pipe_replies.get<void>(2);

		auto rpush_cmd_result = pipe_replies.get<long long>(3);

		std::vector<std::string> lrange_cmd_result;
		pipe_replies.get(4, back_inserter(lrange_cmd_result));

		// ***** Transaction *****

		// Create a transaction.
		auto tx = redis.transaction();

		// Run multiple commands in a transaction, and get all replies.
		auto tx_replies = tx.incr("num0")
			.incr("num1")
			.mget({ "num0", "num1" })
			.exec();

		// Parse reply with reply type and index.
		auto incr_result0 = tx_replies.get<long long>(0);

		auto incr_result1 = tx_replies.get<long long>(1);

		std::vector<OptionalString> mget_cmd_result;
		tx_replies.get(2, back_inserter(mget_cmd_result));

		// ***** Generic Command Interface *****

		// There's no *Redis::client_getname* interface.
		// But you can use *Redis::command* to get the client name.
		val = redis.command<OptionalString>("client", "getname");
		if (val) {
			std::cout << *val << std::endl;
		}

		// Same as above.
		auto getname_cmd_str = { "client", "getname" };
		val = redis.command<OptionalString>(getname_cmd_str.begin(), getname_cmd_str.end());

		// There's no *Redis::sort* interface.
		// But you can use *Redis::command* to send sort the list.
		std::vector<std::string> sorted_list;
		redis.command("sort", "list", "ALPHA", std::back_inserter(sorted_list));

		// Another *Redis::command* to do the same work.
		auto sort_cmd_str = { "sort", "list", "ALPHA" };
		redis.command(sort_cmd_str.begin(), sort_cmd_str.end(), std::back_inserter(sorted_list));

		// ***** Redis Cluster *****

		// Create a RedisCluster object, which is movable but NOT copyable.
		auto redis_cluster = RedisCluster("tcp://192.168.137.100:7000");

		// RedisCluster has similar interfaces as Redis.
		redis_cluster.set("key", "value");
		val = redis_cluster.get("key");
		if (val) {
			std::cout << *val << std::endl;
		}   // else key doesn't exist.

		// Keys with hash-tag.
		redis_cluster.set("key{tag}1", "val1");
		redis_cluster.set("key{tag}2", "val2");
		redis_cluster.set("key{tag}3", "val3");

		std::vector<OptionalString> hash_tag_res;
		redis_cluster.mget({ "key{tag}1", "key{tag}2", "key{tag}3" },
			std::back_inserter(hash_tag_res));

	}
	catch (const sw::redis::Error& e) {
		// Error handling.
		//CLog::rec(CPPFILE, e.what());
	}
	return 0;
}

int redispp_main_test()
{
	try {
		Redis redis = Redis(RS::tcpipport);

		redis.set("key", "Test redis-cplus-cplus");
		OptionalString val = redis.get("key");
		if (val) {
			std::cout << *val << std::endl;
		}
		basedemo();
	}
	catch (const sw::redis::Error& e) {
		//CLog::rec(CPPFILE, e.what());
	}
	return 0;
}

