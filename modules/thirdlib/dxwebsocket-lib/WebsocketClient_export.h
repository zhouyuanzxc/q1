#pragma once
#ifdef DXWEBSOCKCLIENT_EXPORTS
#define WEBSOCKCLIENT_API __declspec(dllexport)
#else
#define  WEBSOCKCLIENT_API __declspec(dllimport)
#include <vector>

#endif
#include <functional>
#include <string>
typedef std::function<void(const int id, std::string, std::string)> swebstrRecv;
typedef std::function<void(const int id, std::string, void*, unsigned int slen)> swebdataRecv;
typedef std::function<void(const int id, std::string)> swebfailer;
typedef std::function<void(const int id, std::string)> swebclose;
typedef std::function<void(const int id, std::string)> swebopen;
extern "C"
{
	WEBSOCKCLIENT_API void* __stdcall  CreateWebsockClient();
	WEBSOCKCLIENT_API void __stdcall  setWebsockObsrvs(void* mclient, swebstrRecv webTxtCallback,
		swebdataRecv webDataCallback, swebopen funopen, swebclose funclose);
	WEBSOCKCLIENT_API void __stdcall setWebsockObsvr_failer(void* mclient, swebfailer webfailer);
	//
	WEBSOCKCLIENT_API int  __stdcall connect_ws(void* mclient,std::string urls);
	WEBSOCKCLIENT_API int __stdcall isidconnect(void* mclient,const int id);
	WEBSOCKCLIENT_API bool __stdcall close_connect(void* mclient, const int id);
	//
	WEBSOCKCLIENT_API bool __stdcall sendstring(void* mclient, int id, std::string message);
	WEBSOCKCLIENT_API bool __stdcall sendbuffer(void* mclient, int id, const void* data, size_t slen);

}