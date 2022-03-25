#include "cinifile.h"
#include <io.h>
#define DEVCONFIG "Dev-config"
#define XY_SPEED "xy_speed"
#define XY_HOMESPEED "xy_ghome_speed"
#define Z_SPEED "z_speed"
#define z_HOMESPEED "z_gohome_speed"

#define XY_AccNormal "xynormal_accspeed"
#define XY_DAccNormal "xynormal_daccspeed"
#define mxy_unitc "xy_unit"
#define mz_unitc "z_unit"
#define z_AccNormal "znormal_accspeed"
#define z_DAccNormal "znormal_daccspeed"
#define MAP_AXIDHeader "Axid_MAP"
#define MAP_AXIDUP  "axid_plaptup"
#define MAP_AXIDDown  "axid_plaptdown"
#define ISNEWLight  "Isnew_Light"
#define Quadrant   "Dev_quadrant"
//---
#define APPCONFIG   "App-Config"
#define DEVNAME    "DeviceName"
#define APPNAME   "AppVer"
#define DATABASE "Database-Config"
#define  RedisServerAddr "Redis_server"
#define  DBINDEX "dbindex" 
#define  DEVType "devtype"
#define DBStart "db-save"


#define FilePath "E:\\work_cpp\\adam\\sysconfig.ini"



bool CIniFile::isiniExists(string filepath) {
	//_access();
	int iRtn = _access(filepath.c_str(), 0);// 这个文件夹是 存在的
	return (iRtn == 0);
}

//bool CIniFile::isreaddta() {
//	if (strcmp(cstr, "999999") == 0)
//	{
//		cout << "读取ini出错";
//	}
//}

void CIniFile::read_fromini(DEVSpeedSet* devspeedSet) {




	//节名1    [Database-Config] (DATABASE)  

	len = GetPrivateProfileString(DATABASE, RedisServerAddr, "999999", cstr, Max_Strlen, FilePath);
	devspeedSet->redisSerAddr = cstr;
	len = GetPrivateProfileString(DATABASE, DBINDEX, "999999", cstr, Max_Strlen, FilePath);
	devspeedSet->dbindex = atoi(cstr);
	len = GetPrivateProfileString(DATABASE, DEVType, "999999", cstr, Max_Strlen, FilePath);
	devspeedSet->devtype = atoi(cstr);
		
	bool b;
	std::istringstream(cstr) >> std::boolalpha >> b;
	devspeedSet->dbWriter = 
	

	_IniHandle->beginGroup(DATABASE);
	//devspeedSet->redisSerAddr = _IniHandle->value(RedisServerAddr).toString();
	//devspeedSet->dbindex = _IniHandle->value(DBINDEX).toInt();
	//devspeedSet->devtype = _IniHandle->value(DEVType).toInt();
	devspeedSet->dbWriter = _IniHandle->value(DBStart).toBool();
	_IniHandle->endGroup();

	_IniHandle->beginGroup(APPCONFIG);
	devspeedSet->deviceName = _IniHandle->value(DEVNAME).toString();
	devspeedSet->appName = _IniHandle->value(APPNAME).toString();
	_IniHandle->endGroup();
	_IniHandle->beginGroup(DEVCONFIG);
	devspeedSet->xynormal_speed = _IniHandle->value(XY_SPEED).toInt();
	devspeedSet->xyhome_speed = _IniHandle->value(XY_HOMESPEED).toInt();

	devspeedSet->xynormal_accspeed = _IniHandle->value(XY_AccNormal).toInt();
	devspeedSet->xynormal_daccspeed = _IniHandle->value(XY_DAccNormal).toInt();

	devspeedSet->zhome_speed = _IniHandle->value(z_HOMESPEED).toInt();
	devspeedSet->znormal_speed = _IniHandle->value(Z_SPEED).toInt();
	devspeedSet->znormal_accspeed = _IniHandle->value(z_AccNormal).toInt();
	devspeedSet->znormal_daccspeed = _IniHandle->value(z_DAccNormal).toInt();
	//-----

	devspeedSet->xy_unitc = _IniHandle->value(mxy_unitc).toInt();
	devspeedSet->z_unitc = _IniHandle->value(mz_unitc).toInt();
	devspeedSet->islightNew = _IniHandle->value(ISNEWLight).toBool();
	devspeedSet->dev_quadrant = _IniHandle->value(Quadrant).toInt();

	_IniHandle->endGroup();

	_IniHandle->beginReadArray(MAP_AXIDHeader);
	for (int i = 0; i < AXIS_MAX; i++)
	{
		_IniHandle->setArrayIndex(i);
		devspeedSet->axisid_mapup[i] = _IniHandle->value(MAP_AXIDUP).toInt();
	}

	for (int i = 0; i < AXIS_MAX; i++)
	{
		_IniHandle->setArrayIndex(i);
		devspeedSet->axisid_mapdown[i] = _IniHandle->value(MAP_AXIDDown).toInt();
	}
	_IniHandle->endArray();


}

\


/*
[Database-Config]
Redis_server="172.16.100.101"
db-save=false
dbindex=2
devtype=0
[App-Config]
DeviceName="ADA721-M2"
AppVer="ADA-M System Ver1.0.1"


[Dev-config]
xy_speed=800
xy_ghome_speed=100
xynormal_accspeed=3000
xynormal_daccspeed=5000
xy_unit=2000
z_unit=1600
z_speed=10
z_gohome_speed=10
znormal_accspeed=3000
znormal_daccspeed=5000
Isnew_Light=true
Dev_quadrant=2

[Axid_MAP]
1\axid_plaptup=0
2\axid_plaptup=1
3\axid_plaptup=0
4\axid_plaptup=0
5\axid_plaptup=0
6\axid_plaptup=0
7\axid_plaptup=1
8\axid_plaptup=0
9\axid_plaptup=0
10\axid_plaptup=0
11\axid_plaptup=0
12\axid_plaptup=0
1\axid_plaptdown=0
2\axid_plaptdown=0
3\axid_plaptdown=0
4\axid_plaptdown=0
5\axid_plaptdown=0
6\axid_plaptdown=0
7\axid_plaptdown=0
8\axid_plaptdown=0
9\axid_plaptdown=0
10\axid_plaptdown=0
11\axid_plaptdown=0
12\axid_plaptdown=0
size=12


*/