#pragma once
//#include <vector>
//#include <string>
//#include <windef.h>
//using namespace std;
#ifdef DXWEBSOCKSERVER_EXPORTS
#define WEBSOCKSVRDLL_API __declspec(dllexport)
#else
#define WEBSOCKSVRDLL_API __declspec(dllimport)
#include <vector>
#include <string>
#include <functional>
#endif
typedef std::function<void(std::string, std::string)> webstrRecv;
typedef std::function<void(std::string, void*, unsigned int slen)> webdataRecv;
typedef std::function<void(std::string)> webopen;
typedef std::function<void(std::string)> webclose;
extern "C"
{

	WEBSOCKSVRDLL_API void* __stdcall  CreateWebsockServer(const int svport);	
	WEBSOCKSVRDLL_API void __stdcall setWebsockObsrv(void* mserver, webstrRecv webTxtCallback,
		webdataRecv webDataCallback, webopen funopen,webclose funclose);
	WEBSOCKSVRDLL_API int  __stdcall getwebserverConnected_number(void* mserver);
	WEBSOCKSVRDLL_API void __stdcall startwebserver(void* mserver);
	WEBSOCKSVRDLL_API void __stdcall stop_WebsockObsrv(void* mserver);
	WEBSOCKSVRDLL_API void __stdcall getClientList(void* mserver, std::vector<std::string>* vcelist);	
	WEBSOCKSVRDLL_API void __stdcall broadcastString(void* mserver, const std::string msg);	
	WEBSOCKSVRDLL_API void __stdcall broadcastbuffer(void* mserver, const void* data, size_t slen);
	WEBSOCKSVRDLL_API void __stdcall sendString_withEndpoint(void* mserver, const std::string endpoint, std::string msg);
	WEBSOCKSVRDLL_API void __stdcall sendbuffer_withEndpoint(void* mserver, const std::string endpoint, const void* data, size_t slen);


}

