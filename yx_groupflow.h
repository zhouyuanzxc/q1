#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <sstream>
#include <iostream>
#include <json/json.h>
//#include "FlatBufferJsonHelper.h"


struct SFlowItem
{
	//SFlowItem() = delete;
	SFlowItem() {};
	SFlowItem(int _key, int _ordindex, int _axistype, int _shape,
		float _pxS, float _pyS, float _pxEnd, float _pyEnd,
		float _radius, float plength, float pwidth, float pangle, int _status)
		:Flowkey(_key), ordeindex(_ordindex), axistype(_axistype), shape(_shape),
		ptx_start(_pxS), pty_start(_pyS), ptx_end(_pxEnd), pty_end(_pyEnd),
		radius(_radius), sqlength(plength), sqwidth(pwidth), angle(pangle), status(_status)
	{

	}
	SFlowItem& operator=(const SFlowItem& c)
	{
		if (this == &c)
		{
			return *this;
		}
		this->Flowkey = c.Flowkey;
		this->ordeindex = c.ordeindex;
		this->axistype = c.axistype;
		this->shape = c.shape;
		this->ptx_start = c.ptx_start;
		this->pty_start = c.pty_start;
		//-----
		this->ptx_end = c.ptx_end;
		this->pty_end = c.pty_end;
		this->radius = c.radius;
		this->sqlength = c.sqlength;
		this->sqwidth = c.sqwidth;
		this->angle = c.angle;
		this->status = c.status;
		return *this;

	}


	void printData()
	{
		std::ostringstream ouptstr;
		ouptstr << "key" << Flowkey << " ordindex " << ordeindex
			<< "  axistype " << axistype << " shape " << shape << " ptx_start" << ptx_start << " pty_start " << pty_start
			<< "ptx_end " << ptx_end << " pyy_end " << pty_end << " radius " << radius;
		std::cout << ouptstr.str().data();
	}
	int Flowkey;
	int ordeindex;
	int axistype;
	int shape; //0 为点，1：线段，2：矩形，3：圆，
	float ptx_start;
	float pty_start;
	//
	float ptz_pos;
	//
	float ptx_end;
	float pty_end;
	float sqlength; //square length
	float sqwidth;//square width
	float radius;
	float angle;
	int status;//执行状态，0，没有执行过，1 流程开始执行或正在执行，2：当前节点流程已执行完成，3：流程执行出现异常

	//自正方形的边长宽计算出其余3个点坐标
	float** caculate_squarepoints(int _qudrant = 2)
	{
		int row = 4;
		int col = 2;
		float** ptsarry = new float* [row];
		for (int i = 0; i < row; i++)
		{
			ptsarry[i] = new float[col];
		}
		if (_qudrant == 2)
		{
			ptsarry[0][0] = ptx_start;//左上角坐标
			ptsarry[0][1] = pty_start;

			ptsarry[1][0] = ptx_start + sqwidth;
			ptsarry[1][1] = pty_start;
			//----
			ptsarry[2][0] = ptsarry[1][0];
			ptsarry[2][1] = pty_start - sqlength;
			ptsarry[3][0] = ptx_start;
			ptsarry[3][1] = pty_start - sqlength;

		}
		return ptsarry;
	}




};

//actionID:"normalFlow","flowCommand


class FlowGroupPack
{

public:
	FlowGroupPack();
public:
	//QString GFilePath;	
private:
	int quadrant = 2;//象限
	std::string evnPath;


public:
	int currentnode = 0;
	float axisMinmax[10][2];//x,y,z,u,r
	int axisnumber = 3;
	//	
	bool getFlowProcesResultJson(std::string& strjson);
	std::string getFlowProcesResultJson(SFlowItem& sitem);

	bool getDeviceinfoJson(std::string& strjson);
	bool toflowgroupjson(std::string& strdst);
	bool parseflowgroup_fromjson(std::string strjson);
	std::string strCurrPath;
	std::vector<SFlowItem> mSflowItemList;
	std::string devName;
	int orderid;//0: flowgroup,1:emgstop 2:reset device to home
	std::string actionid;//0:flowgroup,1:flow command
	void addFlowitem(int mkey, const int ordindex, const int axistype,
		const int shape, const float pxStart, const float pyStart,
		const float pxEnd = 0, const float pyEnd = 0, const float radius = 0,
		const float plength = 0, const float pwidth = 0, const float pangle = 0, const int mstatus = 0);
	int numpoints();
	void resetdata();
	bool load_flowgroup_fromfile(std::string strName);
	bool load_flowgroup_frombuffer(uint8_t* gbuffer, const int bsize);
	uint8_t* getFlowbufferPack(int& buffersize);
	//---------------------------
	bool save_flowgroup_tofile(std::string strName);
	int getFlowitem(const int index, SFlowItem& fitem);
	//char* qstrtochar(std::string qstr);	
	void printUAxis();
	void printDevInfo();
	std::string getCurrentFilePath();
};


