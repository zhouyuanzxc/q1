#pragma once
#include "ZMCard.h"
#include "windows.h"
#define Max_Strlen 256
class CIniFile
{
private:
	int len;
	char cstr[Max_Strlen];
	bool isreaddta();
public:
	bool isiniExists(string filepath);
	void read_fromini(DEVSpeedSet* devspeedSet);
	void save_toini(DEVSpeedSet* devspeedSet);
};

