#pragma once
#include <stdbool.h>  //支持C99布尔类型 bool, true(!0=1), false(0) 
#include <stdio.h>  //sprintf
#include <memory.h>



#include "yx00_macro.h"
typedef unsigned char			byte;
typedef unsigned char			BYTE;
typedef unsigned short			WORD;
typedef unsigned short			USHORT;
typedef float					FLOAT; 
typedef unsigned int			UINT;
typedef unsigned long			DWORD;
typedef void* LPVOID;
#ifndef _MSC_VER
#ifndef JNI
#define JNI
typedef long long 				jlong;			//linux:printf("%llu\n",a); lld     windows:%l64u  l64d   
#endif
typedef unsigned long long		ujlong;			//
#else
typedef _int64					jlong;			//
typedef unsigned __int64		ujlong;			//
#endif

#ifndef _MSC_VER
typedef pthread_t				HANDLE_THREAD;	//未来用统一线程
typedef int						SOCKET;
#else
typedef void* HANDLE_THREAD;
#endif

typedef unsigned char* COLPTR;

#define TYPE_BYTE				10
#define TYPE_CHAR				11
#define TYPE_BOOL				12			//重大改动 支持C99布尔类型,只能是0,或者1   
//#define TYPE_BOOL_BYTE			12			// 重大改动 支持C99布尔类型,只能是0,或者1   

#define TYPE_YEAR				15			//MYSQL year data type		//不提倡使用
#define TYPE_SHORT				20
#define TYPE_INT16				20
#define TYPE_INT				40
#define TYPE_INT32				40
#define TYPE_LONG				40
#define TYPE_FLOAT				41	

#define TYPE_BOOL_INT			42			// 整型的BOOL  


#define TYPE_DATE				43			//MYSQL year data type 日期类型，后来加的 MYSQL 3 Byte 1000-01-01          ~ 9999-12-31			
#define TYPE_TIME				44			//MYSQL year data type 时间类型，后来加的 3B  '-838:59:59'/'838:59:59' HH:MM:SS 时间值或持续时间

#define TYPE_TIMESTAMP			46			//timestamp      4 bytes   YYYY-MM-DD HH:MM:SS   1970-01-01 00:00:01 ~ 2038
#define TYPE_REFCODE			49			//ref to yx_code	//720


#define TYPE_LLONG				80
#define TYPE_JLONG				80
#define TYPE_INT64				80
#define TYPE_DOUBLE				81
#define TYPE_DATETIME			86			//MySql 日期时间类型，后来加的   MySQL datetime       8 bytes   YYYY-MM-DD HH:MM:SS   1000-01-01 00:00:00 ~ 9999-12-31 23:59:59
#define TYPE_REFTBL				89			//ref to other tables,such as stu:stuid->stuname	//710

#define TYPE_STRING_ID			510			// 重大新增  需要指定长度的，间隔符号,
#define TYPE_BLOB_ID			520			// 重大新增  需要指定长度的，间隔符号,
#define TYPE_STRING_NAME		550			// 重大新增  

#define TYPE_STRING				610			// 
#define TYPE_BINARY				620			// 长度有限，在256字节内	
#define TYPE_CLOB				630			// 
#define TYPE_BLOB				640			// 

typedef void(*FUN_CHN_PROPROC)(const char* rcvbuf, int& rcvbuflen, char* sndbuf, int& sndbuflen, void* obj);//通道协议处理函数

typedef struct _ITEMLOB {				//
	int			devno;					//部署三级参数，devno 01-99
	int			modno;					//分片编号，如控制器00-09；驱动器20-39
	int			partno;					//尽量不使用，到具体参数定. 00,01-99
//	int			keyno;					//
	char		keyname[LEN_ITEM];		//KEY
	int			datatype;				//
	int			datalen;				//数值字节长度
	char* value;					//数值指针
}ITEMLOB;

typedef struct _ITEM {					//管理表格，目前用于初始化
	char		mkey[LEN_ITEM];
	char		pkey[LEN_ITEM];
	//	jlong		id;						//内部标识号，长整型
	int			devno;					//部署三级参数，devno00,01-99
	int			modno;					//分片编号，如控制器00-09；驱动器20-39
	int			partno;					//尽量不使用，到具体参数定. 00,01-99
//	int			keyno;					//
	char		key[LEN_ITEM];		//KEY
	bool		ifvar;					// 
	int			datatype;				//1:1bit; 10:单字节; 20 short; 40 int;41 float;46 datatime; 80 jlong; 81 double; 610字符串\0结束 32位以内
	int			datalen;				//数值字节长度
	char		value[LEN_ITEM];		//VALUE
	char		valdef[LEN_ITEM];		//VALUE缺省值 如果因为没有设置、或者采集到，则填写为缺省值
	char		valall[LEN_ITEM];		//分割符号
	char		style[LEN_ITEM];		//text,radio,range,select
}ITEM;

typedef struct _KEYNO {					//
	int			no;						//key no， actual key，将定义为宏
	char		name[LEN_ITEM];			//key title
}KEYNO;									//

typedef enum class _MCAT { UNKNOWN = 0, MCC = 100, LGT = 200, HGT = 200, WGT = 400 } MCAT;
typedef enum class _DCAT { UNKNOWN = 0, JET = 100 } DCAT;

#define BYTES_BYTE			1
#define BYTES_CHAR			1
#define BYTES_BOOL			4			// 重大改动 支持C99布尔类型,只能是0,或者1   
#define BYTES_YEAR			1			// MYSQL year data type	//不提倡使用
#define BYTES_SHORT			2
#define BYTES_INT16			2
#define BYTES_INT			4
#define BYTES_INT32			4
#define BYTES_LONG			4
#define BYTES_FLOAT			4	
#define BYTES_BOOL_INT		4			// 整型的BOOL  
#define BYTES_DATE			4			//MYSQL year data type 日期类型，后来加的 MYSQL 3 Byte 1000-01-01          ~ 9999-12-31			
#define BYTES_TIME			4			//MYSQL year data type 时间类型，后来加的 3B  '-838:59:59'/'838:59:59' HH:MM:SS 时间值或持续时间
#define BYTES_TIMESTAMP		4			//timestamp      4 bytes   YYYY-MM-DD HH:MM:SS   1970-01-01 00:00:01 ~ 2038
#define BYTES_REFCODE		4			//ref to yx_code	//720
#define BYTES_LLONG			8
#define BYTES_JLONG			8
#define BYTES_INT64			8
#define BYTES_DOUBLE		8
#define BYTES_DATETIME		8			//MySql 日期时间类型，后来加的   MySQL datetime       8 bytes   YYYY-MM-DD HH:MM:SS   1000-01-01 00:00:00 ~ 9999-12-31 23:59:59
#define BYTES_REFTBL		8			//ref to other tables,such as stu:stuid->stuname	//710
#define BYTES_STRING_ID		32			// 目前缺省长度支持到32
#define BYTES_BLOB_ID		32			// 
#define BYTES_STRING_NAME	32			// 
#define BYTES_STRING		32			// 目前缺省长度支持到32
#define BYTES_BINARY		32			// 	
#define BYTES_CLOB			32			// 
#define BYTES_BLOB			32			// 

typedef struct _COLDATA {
	int type;								//datatype
	union {
		byte bytev;
		char charv;
		short shortv;
		int datev;
		int timev;
		int intv;
		float floatv;
		int timestampv;
		jlong llongv;
		double doublev;
		jlong datetimev;
		//char strv[LEN_COLDATA_STRV];
		int  refcodev;						//
		jlong  reftblv;  					//long long  
	};
	_COLDATA() { memset((void*)this, 0, sizeof(_COLDATA)); };						//DLLSO TBL::_TBL(){memset((void*)this,0,sizeof(_TBL));}
}COLDATA;

typedef struct _GRIDDATA {
	int type;								//datatype
	union {
		byte bytev;
		char charv;
		short shortv;
		int datev;
		int timev;
		int intv;
		float floatv;
		int timestampv;
		jlong llongv;
		double doublev;
		jlong datetimev;
		char strv[LEN_COL_STRING];			//最大列设定4K数据    
		int  refcodev;						//
		jlong  reftblv;  					//long long  
	};
	_GRIDDATA() { memset((void*)this, 0, sizeof(_GRIDDATA)); };
}GRIDDATA;

typedef struct _COLDSPARG {
	char col[LEN_COL];
	char style[LEN_STYLE];
	char href[LEN_HREF];
	_COLDSPARG() { memset((void*)this, 0, sizeof(_COLDSPARG)); };
	bool newobj(const char* col, const char* colstyles);
}COLDSPARG;


typedef struct _GRIDRECS {   //按页查询到的数据的分行列存放
	GRIDDATA recs[MAX_ROW_PAGE_NUM][MAX_COL_NUM];
	char cols[MAX_COL_NUM][LEN_COL];
	int rownum;  //查询到的实际行数
	int colnum;  //查询到的实际列数
}GRIDRECS;


typedef struct _RESULT {
	bool ret;
	int  iret;
	int count;
	char msg[LEN_BLOCK_MSG];// 10240];
	char jsoncols[LEN_BLOCK_JSONCOLS];// 10240];
	char jsonrow[LEN_BLOCK_JSONROW];// 40240];
	char jsonrows[LEN_BLOCK_JSONROWS];// 280240];
	void tostr(char* str) {
		sprintf(str, "ret=%s@@iret=%d@@count=%d@@msg=%s@@jsocols=%s@@jsonrow=%s@@jsonrows=%s@@", (ret == true) ? "true" : "false", iret, count, msg, jsoncols, jsonrow, jsonrows);
	};
	_RESULT() { memset((void*)this, 0, sizeof(_RESULT));	iret = -1; };
}RESULT;

