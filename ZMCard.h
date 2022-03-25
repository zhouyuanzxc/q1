#pragma once
#include "dll/zauxdll2.h"
#include "dll/zmotion.h"
//#include <zmotion/zauxdll2.h>
//#include <zmotion/zmotion.h>
#include <iostream>
using namespace std;
#define MAX_AXIS 12




struct DEVSpeedSet
{
	//all the speed is the Unite speed
	int xynormal_speed;
	int xyhome_speed;
	int znormal_speed;
	int zhome_speed;
	//
	int xynormal_accspeed;
	int xynormal_daccspeed;
	//
	int xy_unitc;
	int z_unitc;
	int znormal_accspeed;
	int znormal_daccspeed;
	int axisid_mapup[MAX_AXIS] = { 0 };
	int dev_quadrant = 2;
	int dbindex = 0;
	string deviceName;
	string appName;
	string redisSerAddr;
	int devtype = 0;//0: ada ,1:agv,2:...
	int redisPort = 6379;
	int axisNumber = 3;
	bool dbWriter = true;
	//QString connectURL()
	//{
	//	return QString("tcp://%1:%2/db%3").arg(redisSerAddr).arg(redisPort).arg(dbindex);
	//	//return QString::asprintf("tcp:://%s:%d", redisSerAddr, redisPort);
	//}

	//上平台数据：
	//   x,y,z1,z2,u,
	//   r,light1,light2,light3,light4,
	//   camera1,camera2

	//每一个平台  有两个预留
	int axisid_mapdown[MAX_AXIS] = { 0 };//下平台数据
	bool islightNew;
	//
	//light1-4  u6


	DEVSpeedSet() :xyhome_speed(100), xynormal_speed(800), znormal_speed(10), zhome_speed(10)
		, xynormal_accspeed(3000), xynormal_daccspeed(5000),
		znormal_accspeed(3000), znormal_daccspeed(5000), xy_unitc(2000), z_unitc(1600), islightNew(false)
	{
		memset(axisid_mapup, 0, MAX_AXIS * sizeof(int));
		memset(axisid_mapdown, 0, MAX_AXIS * sizeof(int));
	}
};
class ZMCard
{
private:
	int nMaxAxis;
	int m_axis_xynormal_Speed;
	int m_axis_xyhome_Speed;
	int m_axis_znormal_Speed;
	int m_axis_zhome_Speed;
	//
	int m_axis_xynormal_accspeed;
	int m_axis_xynormal_daccspeed;
	int m_axis_znormal_accspeed;
	int m_axis_znormal_daccspeed;
	int m_axis_zunit;
	int m_axis_xyunit;
	int m_axis_cunit;

public:
	int openStatus;
	ZMCard(int nNum);
	ZMCard() = delete;
	~ZMCard() = default;
	void setAxisUnit(const int axisID);
	void setDEVSpeedSet(DEVSpeedSet* speedPack);
	bool isZCardConnected();
	void moveAxis(const int axisID, double distance);
	void moveAxisAbs(const int axisID, double distance);
	void moveZAxis(const int axisID, double distance);
	void moveZAxisAbs(const int axisID, double distance);
	void moveUAxis(const int axisID, double distance);
	void moveUAxisAbs(const int axisID, double distance);
	//
	void setXYDatumnIN(const int nAxis, const int datumn);
	bool goHomeXY(int nAxis, int direct, const int fwinvert, const int fminusinvert);
	bool goHomeZ(const int nAxis, const int direct = 1, int invert = 193);
	bool _goHomez(int nAxis, int direct = 1, int invert = 193);
	bool goHomeU();
	bool getAxisPos(const int axisID, float& npos);
	float getAxisDPos(const int axisID);
	int getUDegree(const int axisID);
	//-----
	void stopAxis(const int nAxis);
	void stopAllAxis();
	bool clearAlarm(const int nAxis);
	int clearSoftLimit(const int nAxis);
	bool SetAxisServoOn(int nAxis, int newStatus = 1);//newStatus:1 on,0:off

	bool isAxisMoving(int nAxisNum);
	bool isAxisMoving();
	bool waitMoveingStop(int nAxisNum);
	bool waitMoveingStop();
	//---init and config axis
	bool initAxis(const int nAxis);
	void SetAxismapZero(const int nAxis, const int ioAddress, const int nFlag);
	void SetAxismapZZero(const int nAxis, const int ioAddress, const int nFlag);
	//
	int SdoUpload(int slaveId, int index, int subindex, int& sdoBuffSize, int& nReadValue);
	int SdoDownload(int slaveId, int index, int subindex, int sdoDataSize, int nWriteValue);
	void lightPower(int flagstatus, int slavID = 3, bool isnewBoard = true);
	void setAxisUnitZ(const int axisID);
	//U Axis
	void setAxisUnitU(const int axisID, int nunit);
	void gohomeU(const int axisID);
	void rotateU(const int axisID, int degree, bool isAbs = false);
	void setAxisUEnable(const int axisID);
	void setUGrap(const int axisID, bool status);
	void stopAxisU(const int axisID);

	void moveto_point3(int axid1, int axid2, int axid3, float x, float y, float z1, bool isAbs = true);


	void moveto_point4(int axid1, int axid2, int axid3, int axid4, float x, float y,
		float z1, float z2, bool isAbs);

	void moveline4(int axid1, int axid2, float x1, float y1, float x2, float y2, bool isAbs);
	void movequare4(int axid1, int axid2, float x1, float y1, float x2, float y2,
		float x3, float y3, float x4, float y4, bool isAbs);

	void doxyzMove(int axid1, int axid2, int zxid1, int zxid2, float x1, float y1, float z1, float z2, bool isAbs = true);

	void moveto_point(int axid1, int axid2, float x, float y, bool isAbs = true);
	void moveline(int axid1, int axid2, float x1, float y1, float x2, float y2, bool isAbs);
	void movequare(int axid1, int axid2, float x1, float y1, float x2, float y2,
		float x3, float y3, float x4, float y4, bool isAbs);
	void movecircle();



public:
	static ZMC_HANDLE zHandle;

	enum class signType
	{
		u8 = 5,
		u16 = 6,
		u32 = 7,
		s32 = 4,
		s16 = 3,
		s8 = 2,
	};

};

/*

//#include "LCommon.h"


#include <string>

//#include <qdebug.h>



*/