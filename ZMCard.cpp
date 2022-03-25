#include <windows.h>
#include "ZMCard.h"

//#include "dll/EFileIOHelper.h"
#include "EFileIOHelper.h"
#include "dll/zauxdll2.h"
//#include <libloaderapi.h>
//#include <iostream>
#include <assert.h> 


#define IpAddr  (char*)"192.168.0.11"

#define UAxisUnit 10000

int mAxisZ1, mAxisZ2 = 0;

std::string GetExePath(void)
{
	char szFilePath[261] = { 0 };
	GetModuleFileNameA(NULL, szFilePath, MAX_PATH);
	(strrchr(szFilePath, '\\'))[0] = 0; // 删除文件名，只获得路径字串  
	std::string path = szFilePath;
	return path;
}


ZMC_HANDLE ZMCard::zHandle = nullptr;

ZMCard::ZMCard(int nNum) :nMaxAxis(nNum), openStatus(-1)
{
	openStatus = ZAux_OpenEth(IpAddr, &ZMCard::zHandle);
	////download businit below 
	std::string strPath = GetExePath() + "\\ZmotionInit\\bus_inits.bas";
	auto resF = ::isFileExis(strPath);
	int Err = ZAux_BasDown(zHandle, strPath.data(), 1);
	uint16 BusFlag = 0;
	////float BusFlag = 0;
	DWORD dStart = GetTickCount();
	m_axis_cunit = UAxisUnit;
#ifdef _DEBUGA
	while (BusFlag == 0)
	{
		Sleep(20);
		Err = ZAux_Modbus_Get4x(zHandle, 0, 1, &BusFlag);
		//Err = ZAux_Direct_GetVariablef(zHandle, "Bus_InitStatus", &BusFlag);
		if (GetTickCount() - dStart > 5000)
			break;
	}
#endif
	//std::cout << BusFlag;
}


void ZMCard::setDEVSpeedSet(DEVSpeedSet* speedPack)
{
	//assert(speedPack != nullptr); //qglobal.h 
	m_axis_xynormal_Speed = speedPack->xynormal_speed;
	m_axis_xyhome_Speed = speedPack->xyhome_speed;
	//

	m_axis_xynormal_accspeed = speedPack->xynormal_accspeed;
	m_axis_xynormal_daccspeed = speedPack->xynormal_daccspeed;

	m_axis_znormal_Speed = speedPack->znormal_speed;
	m_axis_zhome_Speed = speedPack->zhome_speed;
	m_axis_znormal_accspeed = speedPack->znormal_accspeed;
	m_axis_znormal_daccspeed = speedPack->znormal_daccspeed;
	m_axis_xyunit = speedPack->xy_unitc;
	m_axis_zunit = speedPack->z_unitc;

}

void ZMCard::moveto_point(int axid1, int axid2, float x, float y, bool isAbs)
{
	ZAux_Direct_SetAccel(zHandle, axid1, m_axis_xynormal_accspeed);
	ZAux_Direct_SetDecel(zHandle, axid1, m_axis_xynormal_daccspeed);
	ZAux_Direct_SetSpeed(zHandle, axid1, m_axis_xynormal_Speed);

	ZAux_Direct_SetAccel(zHandle, axid2, m_axis_xynormal_accspeed);
	ZAux_Direct_SetDecel(zHandle, axid2, m_axis_xynormal_daccspeed);

	ZAux_Direct_SetSpeed(zHandle, axid2, m_axis_xynormal_Speed);

	ZAux_Direct_SetForceSpeed(zHandle, axid1, (float)m_axis_xynormal_Speed);
	ZAux_Direct_SetForceSpeed(zHandle, axid2, (float)m_axis_xynormal_Speed);

	int axidlist[2] = { axid1,axid2 };
	float postList[2] = { x,y };
	if (isAbs)
		ZAux_Direct_MoveAbs(zHandle, 2, axidlist, postList);
	else
		ZAux_Direct_Move(zHandle, 2, axidlist, postList);

	waitMoveingStop(axid1);
	waitMoveingStop(axid2);
}


void ZMCard::moveline(int axid1, int axid2, float x1, float y1, float x2, float y2, bool isAbs)
{
	//ZAux_Direct_MoveAbs
	moveto_point(axid1, axid2, x1, y1, isAbs);
	moveto_point(axid1, axid2, x2, y2, isAbs);
}
void ZMCard::doxyzMove(int axid1, int axid2, int zxid1, int zxid2, float x1, float y1, float z1, float z2, bool isAbs)
{
	if (zxid1 < 1)
	{
		moveto_point(axid1, axid2, x1, y1, isAbs);
	}
	else if (zxid1 > 0 && zxid2 < 1)
	{
		moveto_point3(axid1, axid2, zxid1, x1, y1, z1, isAbs);

	}
	else if (zxid1 > 0 && zxid2 > 0)
	{
		moveto_point4(axid1, axid2, zxid1, zxid2, x1, y1, z1, z2, isAbs);
	}
}


void ZMCard::moveto_point3(int axid1, int axid2, int axid3, float x, float y, float z1, bool isAbs)
{
	ZAux_Direct_SetAccel(zHandle, axid1, m_axis_xynormal_accspeed);
	ZAux_Direct_SetDecel(zHandle, axid1, m_axis_xynormal_daccspeed);
	ZAux_Direct_SetSpeed(zHandle, axid1, m_axis_xynormal_Speed);

	ZAux_Direct_SetAccel(zHandle, axid2, m_axis_xynormal_accspeed);
	ZAux_Direct_SetDecel(zHandle, axid2, m_axis_xynormal_daccspeed);
	ZAux_Direct_SetSpeed(zHandle, axid2, m_axis_xynormal_Speed);
	//x,y
	ZAux_Direct_SetForceSpeed(zHandle, axid1, (float)m_axis_xynormal_Speed);
	ZAux_Direct_SetForceSpeed(zHandle, axid2, (float)m_axis_xynormal_Speed);

	//z...........
	ZAux_Direct_SetAccel(zHandle, axid3, m_axis_znormal_accspeed);
	ZAux_Direct_SetDecel(zHandle, axid3, m_axis_znormal_daccspeed);
	ZAux_Direct_SetSpeed(zHandle, axid3, m_axis_znormal_Speed);
	const int toatl = 3;
	int axidlist[toatl] = { axid1,axid2,axid3 };
	float postList[toatl] = { x,y,z1 };
	if (isAbs)
		ZAux_Direct_MoveAbs(zHandle, toatl, axidlist, postList);
	else
		ZAux_Direct_Move(zHandle, toatl, axidlist, postList);

	waitMoveingStop(axid1);
	waitMoveingStop(axid2);
	waitMoveingStop(axid3);

}
void moveline3(int axid1, int axid2, float x1, float y1, float x2, float y2, bool isAbs)
{


}
void movequare3(int axid1, int axid2, float x1, float y1, float x2, float y2,
	float x3, float y3, float x4, float y4, bool isAbs)
{


}

void ZMCard::moveto_point4(int axid1, int axid2, int axid3, int axid4, float x, float y,
	float z1, float z2, bool isAbs)
{
	ZAux_Direct_SetAccel(zHandle, axid1, m_axis_xynormal_accspeed);
	ZAux_Direct_SetDecel(zHandle, axid1, m_axis_xynormal_daccspeed);
	ZAux_Direct_SetSpeed(zHandle, axid1, m_axis_xynormal_Speed);

	ZAux_Direct_SetAccel(zHandle, axid2, m_axis_xynormal_accspeed);
	ZAux_Direct_SetDecel(zHandle, axid2, m_axis_xynormal_daccspeed);
	ZAux_Direct_SetSpeed(zHandle, axid2, m_axis_xynormal_Speed);
	//----
	ZAux_Direct_SetForceSpeed(zHandle, axid1, (float)m_axis_xynormal_Speed);
	ZAux_Direct_SetForceSpeed(zHandle, axid2, (float)m_axis_xynormal_Speed);
	ZAux_Direct_SetAccel(zHandle, axid3, m_axis_znormal_accspeed);
	ZAux_Direct_SetDecel(zHandle, axid3, m_axis_znormal_daccspeed);
	ZAux_Direct_SetSpeed(zHandle, axid3, m_axis_znormal_Speed);

	ZAux_Direct_SetAccel(zHandle, axid4, m_axis_znormal_accspeed);
	ZAux_Direct_SetDecel(zHandle, axid4, m_axis_znormal_daccspeed);
	ZAux_Direct_SetSpeed(zHandle, axid4, m_axis_znormal_Speed);

	constexpr int total = 4;
	int axidlist[total] = { axid1,axid2,axid3, axid4 };
	float postList[total] = { x,y,z1,z2 };
	if (isAbs)
		ZAux_Direct_MoveAbs(zHandle, total, axidlist, postList);
	else
		ZAux_Direct_Move(zHandle, total, axidlist, postList);
	waitMoveingStop(axid1);
	waitMoveingStop(axid2);
	waitMoveingStop(axid3);
	waitMoveingStop(axid4);

}
void moveline4(int axid1, int axid2, float x1, float y1, float x2, float y2, bool isAbs)
{


}
void movequare4(int axid1, int axid2, float x1, float y1, float x2, float y2,
	float x3, float y3, float x4, float y4, bool isAbs)
{


}



void ZMCard::movequare(int axid1, int axid2, float x1, float y1, float x2,
	float y2, float x3, float y3, float x4, float y4, bool isAbs)
{
	moveto_point(axid1, axid2, x1, y1, isAbs);
	moveto_point(axid1, axid2, x2, y2, isAbs);
	moveto_point(axid1, axid2, x3, y3, isAbs);
	moveto_point(axid1, axid2, x4, y4, isAbs);

}
void ZMCard::movecircle()
{



}



bool ZMCard::isZCardConnected()
{
	return (openStatus == 0 && zHandle != nullptr);
}

void ZMCard::moveAxis(const int axisID, double distance)
{

	ZAux_Direct_SetAccel(zHandle, axisID, m_axis_xynormal_accspeed);
	ZAux_Direct_SetDecel(zHandle, axisID, m_axis_xynormal_daccspeed);
	ZAux_Direct_SetSpeed(zHandle, axisID, m_axis_xynormal_Speed);
	ZAux_Direct_Single_Move(zHandle, axisID, distance);
	waitMoveingStop(axisID);
}

void ZMCard::moveAxisAbs(const int axisID, double distance)
{

	ZAux_Direct_SetAccel(zHandle, axisID, m_axis_xynormal_accspeed);
	ZAux_Direct_SetDecel(zHandle, axisID, m_axis_xynormal_daccspeed);
	ZAux_Direct_SetSpeed(zHandle, axisID, m_axis_xynormal_Speed);
	ZAux_Direct_Single_MoveAbs(zHandle, axisID, distance);
	waitMoveingStop(axisID);
}

void ZMCard::moveZAxis(const int axisID, double distance)
{

	ZAux_Direct_SetAccel(zHandle, axisID, m_axis_znormal_accspeed);
	ZAux_Direct_SetDecel(zHandle, axisID, m_axis_znormal_daccspeed);
	ZAux_Direct_SetSpeed(zHandle, axisID, m_axis_znormal_Speed);
	ZAux_Direct_Single_Move(zHandle, axisID, distance);
	waitMoveingStop(axisID);
}

void ZMCard::moveZAxisAbs(const int axisID, double distance)
{

	ZAux_Direct_SetAccel(zHandle, axisID, m_axis_znormal_accspeed);
	ZAux_Direct_SetDecel(zHandle, axisID, m_axis_znormal_daccspeed);
	ZAux_Direct_SetSpeed(zHandle, axisID, m_axis_znormal_Speed);
	ZAux_Direct_Single_MoveAbs(zHandle, axisID, distance);
	waitMoveingStop(axisID);

}



void ZMCard::setAxisUnitZ(const int axisID)
{

	ZAux_Direct_SetUnits(zHandle, axisID, m_axis_zunit);
}

void ZMCard::setAxisUnitU(const int axisID, int nunit)
{
	m_axis_cunit = nunit;
}

void ZMCard::gohomeU(const int axisID)
{
	//SdoDownload Z相回零
	SdoDownload(axisID, 0x2030, 0, 6, 12);//ghome mode
	SdoDownload(axisID, 0x2000, 0, 6, 1);//go home do
}

void ZMCard::rotateU(const int axisID, int degree, bool isAbs)
{
	//set the target pos for u axis
	int mpos = degree * m_axis_cunit / 360;

	SdoDownload(axisID, 0x2042, 0, 4, mpos);
	//rotate now
	int res;
	int bufszie = 2;
	SdoDownload(axisID, 0x2000, 0, bufszie, 3);//clear the erro
	SdoDownload(axisID, 0x2000, 0, bufszie, (isAbs ? 9 : 10));//执行旋转动作
	do
	{
		int rest = SdoUpload(axisID, 0x2001, 0, bufszie, res);
		std::cout << "query ratote u res  " << rest << res;
	} while (res != 3);

}
//int ZMCard::SdoDownload(int slaveId, int index, int subindex, int sdoDataSize, int nWriteValue)
void ZMCard::setAxisUEnable(const int axisID)
{
	//SdoDownload(axisID,0x2010,0,6,2);
	SdoDownload(axisID, 0x2010, 0, 6, 3);
}

//status=7  ,U配合气缸夹取
//status=8,U 松开夹头


void ZMCard::setUGrap(const int axisID, bool status)
{
	SdoDownload(axisID, 0x2000, 0, 6, (status ? 7 : 8));
}
void ZMCard::stopAxisU(const int axisID)
{
	SdoDownload(axisID, 0x2000, 0, 6, 2);
}

//脉冲当量
void ZMCard::setAxisUnit(const int axisID)
{

	ZAux_Direct_SetUnits(zHandle, axisID, m_axis_xyunit);
}



void ZMCard::moveUAxis(const int axisID, double distance)
{

}


void ZMCard::moveUAxisAbs(const int axisID, double distance)
{
}
void ZMCard::setXYDatumnIN(const int nAxis, const int datumn)
{
	int32 Err = ZAux_Direct_SetDatumIn(zHandle, nAxis, datumn);
}
void ZMCard::SetAxismapZero(const int nAxis, const int ioAddress, const int nFlag)
{
	int32 Err = 0;
	int mvalue = 0;
	if (nFlag == 1)
	{
		Err = ZAux_Direct_SetFwdIn(zHandle, nAxis, ioAddress);

	}
	else
	{
		Err = ZAux_Direct_SetRevIn(zHandle, nAxis, ioAddress);
		//Err = ZAux_Direct_SetInvertIn(ghandle, ioAddress, 1);
	}


}
void ZMCard::SetAxismapZZero(const int nAxis, const int ioAddress, const int nFlag)
{
	int32 Err = 0;
	int mvalue = 0;
	if (nFlag == 1)
	{
		Err = ZAux_Direct_SetFwdIn(zHandle, nAxis, ioAddress);
		ZAux_Direct_SetDatumIn(zHandle, nAxis, ioAddress);
		mvalue = 13;
	}
	else
	{
		Err = ZAux_Direct_SetRevIn(zHandle, nAxis, ioAddress);
		mvalue = 14;
	}
	//Err = ZAux_Direct_SetDatumIn(zHandle, nAxis, ioAddress);
	//Err = ZAux_Direct_SetInvertIn(ghandle, ioAddress, 1);
	//Err = ZAux_Direct_Single_Datum(ghandle, nAxis, mvalue);//正向限位回零，正方向运动

}
void ZMCard::stopAllAxis()
{
	for (int i = 0; i < nMaxAxis; i++)
	{
		stopAxis(i);
	}
}
int ZMCard::SdoUpload(int slaveId, int index, int subindex, int& sdoBuffSize, int& nReadValue)
{
	int32 Err = 0;
	switch (sdoBuffSize)
	{
	case 2:
		Err = ZAux_BusCmd_SDORead(zHandle, 0, slaveId, index, subindex, (uint32)signType::s16, &nReadValue);
		break;
	case 4:
		Err = ZAux_BusCmd_SDORead(zHandle, 0, slaveId, index, subindex, (uint32)signType::s32, &nReadValue);
		break;
	default:
		return 0;
		break;
	}

	if (Err != 0)
	{
		return Err;
	}

	return 0;
}

bool ZMCard::SetAxisServoOn(int nAxis, int newStatus)
{
	if (!isZCardConnected())
		return false;
	int32 Err = 0;
	Err = ZAux_Direct_SetAxisEnable(zHandle, nAxis, newStatus);
	if (Err != 0)
	{
		return 1;
	}
	return 0;
}

bool ZMCard::isAxisMoving(int nAxisNum)
{
	if (!isZCardConnected())
		return false;
	int32 Err = 1;
	int AxiIdle = -1;
	float AxisSpeed = 0;
	Err = ZAux_Direct_GetIfIdle(zHandle, nAxisNum, &AxiIdle);
	if (Err != 0)
		return false;
	if (AxiIdle == -1) //axis is stopped
	{
		//Err = ZAux_Direct_SetMerge(zHandle, nAxisNum, 0);
		return false;
	}
	else return true;

}

bool ZMCard::isAxisMoving()
{
	if (!isZCardConnected())
		return false;
	return (isAxisMoving(0) || isAxisMoving(1));
}



int ZMCard::clearSoftLimit(const int nAxis)
{
	int vals = (2 ^ 30);
	int Err = -1;
	Err = ZAux_Direct_SetFsLimit(zHandle, nAxis, vals);
	Err = ZAux_Direct_SetRsLimit(zHandle, nAxis, -vals);
	return Err;
}

bool ZMCard::initAxis(const int nAxis)
{
	if (!isZCardConnected())
		return false;
	int error = clearAlarm(nAxis);
	error = SetAxisServoOn(nAxis);
	//error = clearSoftLimit(nAxis);
	return (error == 0);
}

bool ZMCard::waitMoveingStop()
{
	while (true)
	{
		if (!isAxisMoving())
		{
			break;
		}
	}
	return true;

}
bool ZMCard::waitMoveingStop(int nAxisNum)
{
	while (true)
	{
		if (!isAxisMoving(nAxisNum))
		{
			break;
		}
	}
	return true;

}

bool ZMCard::goHomeXY(int nAxis, int direct, const int fwinvert, const int fminusinvert)
{
	//SetGoHomeConfig(nAxis);
	if (!isZCardConnected())
		return false;
	int modeType = 1;

	ZAux_Direct_SetSpeed(zHandle, nAxis, m_axis_xyhome_Speed);
	int32 Err = 0;
	int AxisFwdIn = -1;
	int AxisRevIn = -1;
	int imode = 0;
	if (direct == 1)//x轴 正方向运动
	{
		switch (modeType)
		{
		case 0: //原点回零 
			Err = ZAux_Direct_Single_Datum(zHandle, nAxis, 3);//正向原点开关回零，正方向运动
			break;
		case 1: //限位回零 	     
			Err = ZAux_Direct_SetInvertIn(zHandle, fwinvert, 1);
			Err = ZAux_Direct_SetInvertIn(zHandle, fminusinvert, 1);
			Err = ZAux_Direct_Single_Datum(zHandle, nAxis, 13);//正向限位回零，正方向运动
			break;
		case 2: //z相回零 
			Err = ZAux_Direct_Single_Datum(zHandle, nAxis, 11);//正向限位回零
			break;
		default: //限位回零
			Err = ZAux_Direct_GetFwdIn(zHandle, nAxis, &AxisFwdIn);
			Err = ZAux_Direct_SetDatumIn(zHandle, nAxis, AxisFwdIn);
			Err = ZAux_Direct_Single_Datum(zHandle, nAxis, 13);//正向限位回零
		}
		//Err = ZAux_Direct_Single_Move(ghandle, nAxis, -10);
	}
	else if (direct == 0) //负回零
	{
		switch (modeType)
		{
		case 0:
			Err = ZAux_Direct_Single_Datum(zHandle, nAxis, 4);//正向原点开关回零，负方向运动
			break;
		case 1:
			Err = ZAux_Direct_SetInvertIn(zHandle, fwinvert, 1);
			Err = ZAux_Direct_SetInvertIn(zHandle, fminusinvert, 1);
			Err = ZAux_Direct_Single_Datum(zHandle, nAxis, 14);//正向限位回零，正方向运动
			break;
		case 2:
			Err = ZAux_Direct_Single_Datum(zHandle, nAxis, 11);//正向限位回零
			break;
		default:
			Err = ZAux_Direct_GetRevIn(zHandle, nAxis, &AxisRevIn);
			Err = ZAux_Direct_SetDatumIn(zHandle, nAxis, AxisRevIn);
			Err = ZAux_Direct_Single_Datum(zHandle, nAxis, 14);//正向限位回零
		}
		//Err = ZAux_Direct_Single_Move(ghandle, nAxis, 5);
	}
	if (Err != 0)
	{
		return 1;
	}
	waitMoveingStop(nAxis);
	return 0;
}

bool ZMCard::_goHomez(int nAxis, int direct, int invert)
{
	//SetGoHomeConfig(nAxis);
	if (!isZCardConnected())
		return false;
	int modeType = 1;
	ZAux_Direct_SetSpeed(zHandle, nAxis, m_axis_zhome_Speed);
	int32 Err = 0;
	int AxisFwdIn = -1;
	int AxisRevIn = -1;
	int imode = 0;
	if (direct == 1)//x轴 正方向运动
	{
		switch (modeType)
		{
		case 0: //原点回零 
			Err = ZAux_Direct_Single_Datum(zHandle, nAxis, 3);//正向原点开关回零，正方向运动
			break;
		case 1: //限位回零 	     
			Err = ZAux_Direct_SetInvertIn(zHandle, invert, 1);
			//	Err = ZAux_Direct_SetInvertIn(zHandle, 129, 1);
			Err = ZAux_Direct_Single_Datum(zHandle, nAxis, 13);//正向限位回零，正方向运动
			break;
		case 2: //z相回零 
			Err = ZAux_Direct_Single_Datum(zHandle, nAxis, 11);//正向限位回零
			break;
		default: //限位回零
			Err = ZAux_Direct_GetFwdIn(zHandle, nAxis, &AxisFwdIn);
			Err = ZAux_Direct_SetDatumIn(zHandle, nAxis, AxisFwdIn);
			Err = ZAux_Direct_Single_Datum(zHandle, nAxis, 13);//正向限位回零
		}
		//Err = ZAux_Direct_Single_Move(ghandle, nAxis, -10);
	}
	else if (direct == 0 && nAxis == 1) //负回零
	{
		switch (modeType)
		{
		case 0:
			Err = ZAux_Direct_Single_Datum(zHandle, nAxis, 4);//正向原点开关回零，负方向运动
			break;
		case 1:
			Err = ZAux_Direct_SetInvertIn(zHandle, 161, 1);
			Err = ZAux_Direct_SetInvertIn(zHandle, 160, 1);
			Err = ZAux_Direct_Single_Datum(zHandle, nAxis, 14);//正向限位回零，正方向运动
			break;
		case 2:
			Err = ZAux_Direct_Single_Datum(zHandle, nAxis, 11);//正向限位回零
			break;
		default:
			Err = ZAux_Direct_GetRevIn(zHandle, nAxis, &AxisRevIn);
			Err = ZAux_Direct_SetDatumIn(zHandle, nAxis, AxisRevIn);
			Err = ZAux_Direct_Single_Datum(zHandle, nAxis, 14);//正向限位回零
		}
		//Err = ZAux_Direct_Single_Move(ghandle, nAxis, 5);
	}
	if (Err != 0)
	{
		return 1;
	}
	waitMoveingStop(nAxis);
	return 0;
}

bool ZMCard::goHomeZ(const int nAxis, const int direct, int invert)
{
	//SetGoHomeConfig(nAxis);
	if (!isZCardConnected())
		return false;
	int modeType = 1;

	int32 Err = 0;
	int AxisFwdIn = -1;
	int AxisRevIn = -1;
	int imode = 0;
	ZAux_Direct_SetSpeed(zHandle, nAxis, m_axis_zhome_Speed);

	if (direct == 1)//x轴 正方向运动
	{
		switch (modeType)
		{

		case 0: //原点回零 
			Err = ZAux_Direct_Single_Datum(zHandle, nAxis, 3);//正向原点开关回零，正方向运动
			break;
		case 1: //限位回零 	     
			Err = ZAux_Direct_SetInvertIn(zHandle, 192, 1);
			//Err = ZAux_Direct_SetInvertIn(zHandle, 193, 1);
			Err = ZAux_Direct_Single_Datum(zHandle, nAxis, 13);//正向限位回零，正方向运动
			break;
		case 2: //z相回零 
			Err = ZAux_Direct_Single_Datum(zHandle, nAxis, 11);//正向限位回零
			break;
		default: //限位回零
			Err = ZAux_Direct_GetFwdIn(zHandle, nAxis, &AxisFwdIn);
			Err = ZAux_Direct_SetDatumIn(zHandle, nAxis, AxisFwdIn);
			Err = ZAux_Direct_Single_Datum(zHandle, nAxis, 13);//正向限位回零
		}
		//Err = ZAux_Direct_Single_Move(ghandle, nAxis, -10);
	}
	else  //负回零
	{
		switch (modeType)
		{
		case 0:
			Err = ZAux_Direct_Single_Datum(zHandle, nAxis, 4);//正向原点开关回零，负方向运动
			break;
		case 1:
			Err = ZAux_Direct_SetInvertIn(zHandle, 192, 1);
			Err = ZAux_Direct_SetInvertIn(zHandle, 193, 1);
			Err = ZAux_Direct_Single_Datum(zHandle, nAxis, 14);//正向限位回零，正方向运动
			break;
		case 2:
			Err = ZAux_Direct_Single_Datum(zHandle, nAxis, 11);//正向限位回零
			break;
		default:
			Err = ZAux_Direct_GetRevIn(zHandle, nAxis, &AxisRevIn);
			Err = ZAux_Direct_SetDatumIn(zHandle, nAxis, AxisRevIn);
			Err = ZAux_Direct_Single_Datum(zHandle, nAxis, 14);//正向限位回零
		}
		//Err = ZAux_Direct_Single_Move(ghandle, nAxis, 5);
	}
	if (Err != 0)
	{
		return 1;
	}

	return 0;
}

bool ZMCard::goHomeU()
{
	return true;
}

bool ZMCard::getAxisPos(const int axisID, float& npos)
{
	if (!isZCardConnected())
	{
		return false;
	}
	int32 Err = 0;
	float mpostVal = npos = 0;
	Err = ZAux_Direct_GetDpos(zHandle, axisID, &mpostVal);
	if (Err != 0)
	{
		return false;
	}
	npos = mpostVal;
	return true;
}
//pluse to dgree
int ZMCard::getUDegree(const int axisID)
{
	int dpos = 0;
	int buffsize = 4;
	SdoUpload(axisID, 0x2208, 0, buffsize, dpos);
	dpos = dpos * 360 / 10000;
	return dpos;
}
float ZMCard::getAxisDPos(const int axisID)
{
	float mpostVal = 0;
	int Err = ZAux_Direct_GetDpos(zHandle, axisID, &mpostVal);
	return mpostVal;
}

void ZMCard::stopAxis(const int nAxis)
{
	ZAux_Direct_Single_Cancel(zHandle, nAxis, 2);
}

int ZMCard::SdoDownload(int slaveId, int index, int subindex, int sdoDataSize, int nWriteValue)
{
	if (!isZCardConnected())return -1;
	int32 Err = 0;
	switch (sdoDataSize)
	{
	case 2:
		Err = ZAux_BusCmd_SDOWrite(zHandle, 0, slaveId, index, subindex, (uint32)signType::s16, (int32)nWriteValue);
		break;
	case 4:
		Err = ZAux_BusCmd_SDOWrite(zHandle, 0, slaveId, index, subindex, (uint32)signType::s32, (int32)nWriteValue);
		break;
	case 6:
		Err = ZAux_BusCmd_SDOWrite(zHandle, 0, slaveId, index, subindex, (uint32)signType::u16, (int32)nWriteValue);
		break;
	default:
		return 0;
		break;
	}

	if (Err != 0)
	{
		return 1;
	}

	return 0;
}
//ret = pMain->m_Card0->SdoDownload(slaveId[nTabSel], LIGHTADDRESS, subIndex, LightDataSize, R);
//SdoDownload(slaveId[nCur], LIGHTADDRESS, 7, LightDataSize, nVal);
void ZMCard::lightPower(int flagstatus, int slavID, bool isnewBoard) //flagstatus:1 lighton ,0 :light off
{
	int index, subindex;
	//slaveID = 3;
	index = 0x2000;
	subindex = (isnewBoard ? 7 : 6);
	int svalue = 0;
	if (isnewBoard)
	{
		svalue = (flagstatus == 1 ? 0 : 31);
	}
	else
	{
		svalue = (flagstatus == 1 ? 1 : 0);
	}
	SdoDownload(slavID, 0x2000, subindex, 6, svalue);
}

bool ZMCard::clearAlarm(const int nAxis)
{
	if (!isZCardConnected())return false;
	int32 Err = 0;
	Err = ZAux_BusCmd_DriveClear(zHandle, nAxis, 0);
	Err = ZAux_BusCmd_DriveClear(zHandle, nAxis, 1);
	Err = ZAux_BusCmd_DriveClear(zHandle, nAxis, 2);
	Err = ZAux_Direct_Single_Datum(zHandle, nAxis, 0);
	if (Err != 0)
	{
		return 1;
	}
	return 0;
}

