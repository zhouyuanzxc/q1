#include "yx_groupflow.h"
#include <iostream>
#include <flatbuffers/util.h>
#include <flatbuffers/flatbuffers.h>
#include "groupflow_generated.h"
#include <minwindef.h>
#include <libloaderapi.h>
#include <sstream>
#include <atlstr.h>
#include <WebsockSvrExport.h>
#include <jsoncpp/json/value.h>

using namespace std;
#define  ACTION   "action"
#define  ORDER     "order"
#define  DEVN    "devicename"
#define  FLOW    "flowConfig"
//
// subdefine
#define  IKEY  "key"
#define  IOrder  "ordindex"
#define  IAXIS   "axistype"
#define  ISHAPE  "shape"
#define  IPX_S   "ptx_start"
#define  IPY_S   "pty_start"
#define  IPX_E   "ptx_end"
#define  IPY_E   "pty_end"
//
#define  IPZP    "ptz_pos"
#define  ILen     "length"
#define  IWD      "width"
#define  IRS      "radius"
#define  ANGLE    "angle"
#define  STS      "status"




//#include <CSUtility.h>
std::string FlowGroupPack::getCurrentFilePath()
{
	if (strCurrPath.length() < 1)
	{
		TCHAR szBuffer[MAX_PATH];
		GetModuleFileName(NULL, szBuffer, MAX_PATH);
		CString strPath = szBuffer;
		int i = strPath.ReverseFind('\\');
		strPath = strPath.Left(i + 1) + "Gfiles\\";
		strCurrPath = CT2A(strPath);
		//strCurrPath = std::string((LPCTSTR)strPath) + "Gfiles\\";;
	}
	return strCurrPath;
}
std::string FlowGroupPack::getFlowProcesResultJson(SFlowItem& sitem)
{

	//std::string jsonStr;
	Json::Value root, fileList, qx, qy;
	Json::Value devinfovalue;
	Json::Value minmaxValue;
	Json::StreamWriterBuilder writeBuilder;
	std::unique_ptr<Json::StreamWriter> jsonWriter(writeBuilder.newStreamWriter());
	//数组方式输出，
	root[DEVN] = this->devName;	//
	root["tasknumber"] = mSflowItemList.size();
	root["currentnode"] = sitem.ordeindex;
	root["status"] = sitem.status;
	//-----------
	std::ostringstream oss;
	jsonWriter->write(root, &oss);
	std::string strjson = oss.str();
	std::cout << strjson;
	return strjson;	//broadcastString(webserver, jsonStr);
}


bool FlowGroupPack::getFlowProcesResultJson(std::string& strjson)
{
	if (mSflowItemList.size() < 1 || currentnode >= mSflowItemList.size())
	{
		throw invalid_argument("no flow could be proces");
		return false;
	}
	//std::string jsonStr;
	Json::Value root, fileList, qx, qy;
	Json::Value devinfovalue;
	Json::Value minmaxValue;
	Json::StreamWriterBuilder writeBuilder;
	std::unique_ptr<Json::StreamWriter> jsonWriter(writeBuilder.newStreamWriter());
	//数组方式输出，
	root[DEVN] = this->devName;	//
	root["tasknumber"] = mSflowItemList.size();
	root["currentnode"] = currentnode;
	root["status"] = mSflowItemList[currentnode].status;
	//-----------
	std::ostringstream oss;
	jsonWriter->write(root, &oss);
	strjson = oss.str();
	std::cout << strjson;
	return true;	//broadcastString(webserver, jsonStr);
}




bool FlowGroupPack::getDeviceinfoJson(std::string& strjson)
{

	//std::string jsonStr;
	Json::Value root, fileList, qx, qy;
	Json::Value devinfovalue;
	Json::Value minmaxValue;
	Json::StreamWriterBuilder writeBuilder;
	std::unique_ptr<Json::StreamWriter> jsonWriter(writeBuilder.newStreamWriter());
	//数组方式输出，
	root[DEVN] = this->devName;

	//
	int axis = 0;
	//x axis 最小值，最大值
	devinfovalue["axisx_minmax"][0] = axisMinmax[axis][0];
	devinfovalue["axisx_minmax"][1] = axisMinmax[axis++][1];
	//y axis
	devinfovalue["axisy_minmax"][0] = axisMinmax[axis][0];
	devinfovalue["axisy_minmax"][1] = axisMinmax[axis++][1];
	//z axis
	//z1 axis
	devinfovalue["axisz_minmax"][0] = axisMinmax[axis][0];
	devinfovalue["axisz_minmax"][1] = axisMinmax[axis++][1];
	//z2 axis
	devinfovalue["axisz2_minmax"][0] = axisMinmax[axis][0];

	devinfovalue["axisz2_minmax"][1] = axisMinmax[axis++][1];

	//U
	devinfovalue["axisu_minmax"][0] = axisMinmax[axis][0];
	devinfovalue["axisu_minmax"][1] = axisMinmax[axis++][1];
	//R
	devinfovalue["axisr_minmax"][0] = axisMinmax[axis][0];
	devinfovalue["axisr_minmax"][1] = axisMinmax[axis++][1];
	//
	devinfovalue["axisnumber"] = axisnumber;
	root["deviceinfo"] = devinfovalue;
	std::ostringstream oss;
	jsonWriter->write(root, &oss);
	strjson = oss.str();
	std::cout << strjson;
	return true;	//broadcastString(webserver, jsonStr);

}


bool FlowGroupPack::toflowgroupjson(std::string& strdst)
{

	//std::string jsonStr;
	Json::Value root, fileList, qx, qy;
	Json::StreamWriterBuilder writeBuilder;
	std::unique_ptr<Json::StreamWriter> jsonWriter(writeBuilder.newStreamWriter());
	//数组方式输出，
	root[DEVN] = this->devName;
	root[ACTION] = this->actionid;
	root[ORDER] = this->orderid;
	//
	int ls = mSflowItemList.size();
	for (int j = 0; j < ls; j++)
	{
		fileList[j][IKEY] = mSflowItemList.at(j).Flowkey;
		fileList[j][IOrder] = mSflowItemList.at(j).ordeindex;
		fileList[j][IAXIS] = mSflowItemList.at(j).axistype;
		fileList[j][ISHAPE] = mSflowItemList.at(j).shape;
		//
		fileList[j][IPX_S] = mSflowItemList.at(j).ptx_start;
		fileList[j][IPY_S] = mSflowItemList.at(j).pty_start;
		fileList[j][IPX_E] = mSflowItemList.at(j).ptx_end;
		fileList[j][IPY_E] = mSflowItemList.at(j).pty_end;
		fileList[j][IPZP] = mSflowItemList.at(j).ptz_pos;
		//
		fileList[j][ILen] = mSflowItemList.at(j).sqlength;
		fileList[j][IWD] = mSflowItemList.at(j).sqwidth;
		fileList[j][IRS] = mSflowItemList.at(j).radius;
		fileList[j][ANGLE] = mSflowItemList.at(j).angle;
		fileList[j][STS] = mSflowItemList.at(j).status;
	}

	root[FLOW] = fileList;
	//jsonWriter->write(root, os2);
	std::ostringstream oss;
	jsonWriter->write(root, &oss);
	strdst = oss.str();
	std::cout << strdst;
	return true;	//broadcastString(webserver, jsonStr);
}
bool FlowGroupPack::parseflowgroup_fromjson(std::string strjson)
{
	mSflowItemList.clear();
	Json::CharReaderBuilder builder;
	Json::Value root;
	JSONCPP_STRING errs;
	Json::CharReader* reader = builder.newCharReader();
	if (!reader->parse(strjson.data(), strjson.c_str() + strjson.length(), &root, &errs)) //json read	
	{
		throw invalid_argument("Json file is not valid!");
		return false;
	}
	this->actionid = root[ACTION].asCString();
	this->orderid = root[ORDER].asInt();
	this->devName = root[DEVN].asCString();
	Json::Value flowConfigs = root[FLOW];
	int sz = flowConfigs.size();
	for (int i = 0; i < sz; i++)
	{
		SFlowItem mitem;
		mitem.Flowkey = flowConfigs[i][IKEY].asInt();
		mitem.ordeindex = flowConfigs[i][IOrder].asInt();
		mitem.axistype = flowConfigs[i][IAXIS].asInt();
		mitem.shape = flowConfigs[i][ISHAPE].asInt();
		mitem.ptx_start = flowConfigs[i][IPX_S].asFloat();
		mitem.pty_start = flowConfigs[i][IPY_S].asFloat();
		mitem.ptx_end = flowConfigs[i][IPX_E].asFloat();
		mitem.pty_end = flowConfigs[i][IPY_E].asFloat();
		mitem.ptz_pos = flowConfigs[i][IPZP].asFloat();
		mitem.sqlength = flowConfigs[i][ILen].asFloat();
		mitem.sqwidth = flowConfigs[i][IWD].asFloat();
		mitem.radius = flowConfigs[i][IRS].asFloat();
		mitem.angle = flowConfigs[i][ANGLE].asFloat();
		mitem.status = flowConfigs[i][STS].asInt();
		mSflowItemList.push_back(mitem);
	}
	return true;

}

FlowGroupPack::FlowGroupPack()
{
	evnPath = getCurrentFilePath();
	//auto strPP = std::string((LPCTSTR)strP) + strName + ".G";
}
uint8_t* FlowGroupPack::getFlowbufferPack(int& buffersize)
{
	flatbuffers::FlatBufferBuilder builder_data;
	auto tdevname = builder_data.CreateString(devName.data());
	int sz = mSflowItemList.size();
	std::vector<flatbuffers::Offset<GroupLayer::FlowItem_Fb>> vitemlist;

	//auto pointsList = builder_data.CreateVector(devPoints);//数组转换成
	for (int i = 0; i < sz; i++)
	{
		auto flowitem = GroupLayer::CreateFlowItem_Fb(
			builder_data, mSflowItemList[i].Flowkey,
			mSflowItemList[i].ordeindex, mSflowItemList[i].axistype, mSflowItemList[i].shape,
			mSflowItemList[i].ptx_start, mSflowItemList[i].pty_start,
			mSflowItemList[i].ptx_end, mSflowItemList[i].pty_end,
			mSflowItemList[i].radius,
			mSflowItemList[i].sqlength, mSflowItemList[i].sqwidth,
			mSflowItemList[i].angle);
		vitemlist.push_back(flowitem);
	}
	auto fitemlist = builder_data.CreateVector(vitemlist);
	auto rootlyaer = GroupLayer::CreateGroupLayer_Fb(builder_data, tdevname, fitemlist);
	builder_data.Finish(rootlyaer);
	//std::cout << builder_data.GetSize() << std::endl;

	buffersize = builder_data.GetSize();
	uint8_t* tempt;
	tempt = new uint8_t[buffersize];
	memset(tempt, 0, sizeof(uint8_t) * buffersize);
	memcpy(tempt, builder_data.GetBufferPointer(), buffersize);
	return tempt;
}

bool FlowGroupPack::load_flowgroup_frombuffer(uint8_t* gbuffer, const int bsize)
{

	bool needBinary = true;
	std::string binaryfile;
	flatbuffers::FlatBufferBuilder builder_out;
	builder_out.PushBytes(gbuffer, bsize);
	std::cout << "descrixe size :" << builder_out.GetSize() << std::endl;
	//builder_out.Finished();
	flatbuffers::Verifier tex_verify(builder_out.GetCurrentBufferPointer(), builder_out.GetSize());
	bool verify_flag = GroupLayer::VerifyGroupLayer_FbBuffer(tex_verify);
	if (!verify_flag)
	{
		return false;
	}
	auto layer_fb = GroupLayer::GetGroupLayer_Fb(builder_out.GetCurrentBufferPointer());
	mSflowItemList.clear();
	devName = layer_fb->devname()->str();
	int sizeLen = layer_fb->flowitemlist()->size();
	for (int i = 0; i < sizeLen; i++)
	{
		SFlowItem mitem;
		mitem.Flowkey = layer_fb->flowitemlist()->Get(i)->key();
		mitem.ordeindex = layer_fb->flowitemlist()->Get(i)->ordindex();
		mitem.axistype = layer_fb->flowitemlist()->Get(i)->axistype();
		//
		mitem.shape = layer_fb->flowitemlist()->Get(i)->shape();
		mitem.ptx_start = layer_fb->flowitemlist()->Get(i)->ptx_start();
		mitem.pty_start = layer_fb->flowitemlist()->Get(i)->pty_start();
		//
		mitem.ptx_end = layer_fb->flowitemlist()->Get(i)->ptx_end();
		mitem.pty_end = layer_fb->flowitemlist()->Get(i)->pty_end();
		//
		mitem.radius = layer_fb->flowitemlist()->Get(i)->radius();
		mitem.sqlength = layer_fb->flowitemlist()->Get(i)->length();
		mitem.sqwidth = layer_fb->flowitemlist()->Get(i)->width();
		mitem.angle = layer_fb->flowitemlist()->Get(i)->angle();
		mSflowItemList.push_back(mitem);
		//		
	}
	return true;

}


//--------------------------------------------------------
bool FlowGroupPack::load_flowgroup_fromfile(std::string strName)
{

	auto strPP = evnPath + strName + ".G";
	bool needBinary = false;
	std::string binaryfile;
	bool ok = flatbuffers::LoadFile(strPP.data(), needBinary, &binaryfile);
	if (!ok)
	{
		return false;
	}
	flatbuffers::FlatBufferBuilder builder_out;
	builder_out.PushBytes(reinterpret_cast<unsigned char*>(const_cast<char*>(binaryfile.data())), binaryfile.size());
	std::cout << "descrixe size :" << builder_out.GetSize() << std::endl;
	//builder_out.Finished();
	flatbuffers::Verifier tex_verify(builder_out.GetCurrentBufferPointer(), builder_out.GetSize());
	bool verify_flag = GroupLayer::VerifyGroupLayer_FbBuffer(tex_verify);
	if (!verify_flag)
	{
		return false;
	}
	auto layer_fb = GroupLayer::GetGroupLayer_Fb(builder_out.GetCurrentBufferPointer());
	resetdata();
	devName = layer_fb->devname()->str();
	int sizeLen = layer_fb->flowitemlist()->size();
	//layer_fb->flowitemlist
	for (int i = 0; i < sizeLen; i++)
	{
		SFlowItem mitem;
		mitem.Flowkey = layer_fb->flowitemlist()->Get(i)->key();
		mitem.ordeindex = layer_fb->flowitemlist()->Get(i)->ordindex();
		mitem.axistype = layer_fb->flowitemlist()->Get(i)->axistype();
		//
		mitem.shape = layer_fb->flowitemlist()->Get(i)->shape();
		mitem.ptx_start = layer_fb->flowitemlist()->Get(i)->ptx_start();
		mitem.pty_start = layer_fb->flowitemlist()->Get(i)->pty_start();
		//
		mitem.ptx_end = layer_fb->flowitemlist()->Get(i)->ptx_end();
		mitem.pty_end = layer_fb->flowitemlist()->Get(i)->pty_end();
		//
		mitem.radius = layer_fb->flowitemlist()->Get(i)->radius();
		mitem.sqlength = layer_fb->flowitemlist()->Get(i)->length();
		mitem.sqwidth = layer_fb->flowitemlist()->Get(i)->width();
		mitem.angle = layer_fb->flowitemlist()->Get(i)->angle();
		mSflowItemList.push_back(mitem);
		//		
	}
	return true;

}
int  FlowGroupPack::getFlowitem(const int index, SFlowItem& fitem)
{
	if (mSflowItemList.size() < 1 || mSflowItemList.size() < index)
	{
		return -1;
	}
	else
	{
		fitem = mSflowItemList[index];
		return 0;
	}

}
//strName: fileName
bool FlowGroupPack::save_flowgroup_tofile(std::string strName)
{
	flatbuffers::FlatBufferBuilder builder_data;
	auto tdevname = builder_data.CreateString(devName.data());
	int sz = mSflowItemList.size();
	std::vector<flatbuffers::Offset<GroupLayer::FlowItem_Fb>> vitemlist;

	//auto pointsList = builder_data.CreateVector(devPoints);//数组转换成
	for (int i = 0; i < sz; i++)
	{
		auto flowitem = GroupLayer::CreateFlowItem_Fb(
			builder_data, mSflowItemList[i].Flowkey,
			mSflowItemList[i].ordeindex, mSflowItemList[i].axistype, mSflowItemList[i].shape,
			mSflowItemList[i].ptx_start, mSflowItemList[i].pty_start,
			mSflowItemList[i].ptx_end, mSflowItemList[i].pty_end,
			mSflowItemList[i].radius,
			mSflowItemList[i].sqlength, mSflowItemList[i].sqwidth,
			mSflowItemList[i].angle);
		vitemlist.push_back(flowitem);
	}
	auto fitemlist = builder_data.CreateVector(vitemlist);
	auto rootlyaer = GroupLayer::CreateGroupLayer_Fb(builder_data, tdevname, fitemlist);
	builder_data.Finish(rootlyaer);
	//std::cout << builder_data.GetSize() << std::endl;
	bool needBinary = true;
	auto strPP = evnPath + strName + ".G";
	flatbuffers::SaveFile(strPP.data(), reinterpret_cast<char*>(builder_data.GetCurrentBufferPointer()),
		builder_data.GetSize(), needBinary);
	return true;

}



void FlowGroupPack::printDevInfo()
{
	//std::cout << "devname is " << devName << "xcore" << xcors << "ycors" << ycors << " zcors" << zcors << " ucors" << ucors << " rcors" << rcors;

}

/*
	SFlowItem(int _key, int _ordindex, int _axistype, int _shape,
		float _pxS, float _pyS, float _pxEnd, float _pyEnd,
		float _radius,float plength,float pwidth,float pangle)
*/
void FlowGroupPack::addFlowitem(int mkey, const int ordindex, const int axistype,
	const int shape, const float pxStart, const float pyStart,
	const float pxEnd, const float pyEnd, const float radius,
	const float plength, const float pwidth, const float pangle, const int mstatus)
{
	SFlowItem item(mkey, ordindex, axistype, shape, pxStart, pyStart, pxEnd, pyEnd, radius, plength, pwidth, pangle, mstatus);
	mSflowItemList.push_back(item);
}


int FlowGroupPack::numpoints()
{
	return mSflowItemList.size();
}
void FlowGroupPack::resetdata()
{
	mSflowItemList.clear();

}


void FlowGroupPack::printUAxis()
{
	//for (int i = 0; i < ucors.size(); i++)
	{
		//qDebug() << "u axis is " <<i <<" "<< ucors[i] ;
	}

}
