#pragma once

#include <iostream>
#include <vector>
//#include <string>
//#include <string.h>
#ifdef SFILELIBRARY_EXPORTS
#define SFILELIBRARY_API __declspec(dllexport)
#else
#define SFILELIBRARY_API __declspec(dllimport)
#endif

extern "C"
{
	SFILELIBRARY_API bool __stdcall rawdata_toBmpFile(unsigned char* pImg, int width, int height, const char* filename);
	SFILELIBRARY_API bool __stdcall rawdata_toImageBuffer(unsigned char* rawData, int width, int height, unsigned char* sImgBuffer);
	SFILELIBRARY_API bool  __stdcall isFileExis(std::string strFile);
	SFILELIBRARY_API void  __stdcall searchFileInfolder(std::string tempFolder, std::string tailF, std::vector<std::string>* inputfiles);
}



