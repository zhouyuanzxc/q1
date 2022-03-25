#pragma once
#define ERROR_IDX					-1			//
#define ERROR_COMMON				-1			//
#define LEN_APP_NAME				64			//应用名
#define MAX_APP_NUM					1 

#define LEN_FILE_NAMES				256			//附件,可能包含多个								//LEN_FILES
#define LEN_FILE_PATH				256			//路径名										//LEN_PATH
#define LEN_FILE_NAME				64			//文件名  都可能超长,容易引起系统堆栈错误		//LEN_FILENAME
#define LEN_FILE_PATHFILE			256			//路径名加文件名								//LEN_PATHFILE
#define LEN_FILE_LINE				256			//												//LEN_LINE

#define MAX_DB_NUM					3			// 
#define DB_DIC_IN					0			//字典所在的数据库

#define TYPE_DB_MYSQL				100			//DB_MYSQL	
#define TYPE_DB_SQLSERVER			200			//DB_SQLSERVER
#define TYPE_DB_ORACLE				300			//DB_ORACLE	

#define LEN_DB_INIARG				256			//yxdbsrv.cpp loadCfg()
#define LEN_DB_HOST					32			//name or ip Address
#define LEN_DB_PORT					32			//port
#define LEN_DB_USR					32			//name or ip Address
#define LEN_DB_PWD					32			//name or ip Address
#define LEN_DB_NAME					32			//name or ip Address
#define LEN_DB_DESC					1024		//数据库整体描述
#define LEN_DB_SQL					10240		//max sql statement length
#define LEN_DB_WHERES				1024		

#define LEN_LOGUSR_IP				32			
#define LEN_LOGUSR_TBL				32			
#define LEN_LOGUSR_ACT				32				
#define LEN_LOGUSR_MSG				256
#define LEN_CHNTASK_TITLE           1024

//zhou2018
#define MAX_TABLE_NUM				250			//最多多少张表，要和tbl定义一致
#define MAX_COL_NUM					100			//最多多少列
#define LEN_COL_NAME				32			//列名长度
//#define LEN_COL_MAXTEXT			8192		//设定每列最多8K数据
#define LEN_COL_STRING				8192		//设定每列最多8K数据

#define MAX_ROW_TBL_NUM				10000		//MAX_ROW_TBL_NUM	每个表最多的纪录数   随着系统的增加，将更新该数据   !!!!!!!!!!!!!!!!!!!!!!!
#define MAX_ROW_PAGE_NUM			300			//每页最多多少行数据
#define MAX_PAGE_ROW				1000		//目前没有超出1000条记录的常驻表 


//#define MAX_DB_TABLE				250			//MAX_TABLE_NUM		最多250张表  //要和tbl定义一致
//#define MAX_DB_ROW_TBL			10000		//MAX_ROW_TBL_NUM	每个表最多的纪录数   随着系统的增加，将更新该数据   !!!!!!!!!!!!!!!!!!!!!!!
//#define MAX_DB_ROW_PAGE			300			//MAX_ROW_PAGE_NUM	每页最多100行数据
//#define MAX_DB_PAGE				1000		//MAX_PAGE_ROW		目前没有超出1000条记录的常驻表  

#define LEN_TABLE_NAME				32			
#define LEN_TABLE_TITLE				32
#define LEN_TABLE_FUNS				1024		//表格函数长度
#define LEN_TABLE_ORDERBY			256			//2013
#define LEN_TABLE_REMARK			256			//2013

#define LEN_COL						32

#define LEN_DIC_TBL					32			//
#define LEN_DIC_COL					32			//
#define LEN_DIC_TITLE				32			//
#define LEN_DIC_REFIID				32			//
#define LEN_DIC_REFNAME				32			//
#define LEN_DIC_REFTABLE			32			//
#define LEN_DIC_ARGS				256			//
#define LEN_DIC_REMARK				32			//

#define MAX_CHN_NUM					10			//本项目用5个
#define TYPE_CHN_TCPSVR				210			//CHN_TCPSVR	 tcp server 
#define TYPE_CHN_TCPCLN				220			//CHN_TCPCLN	 tcp client 
#define TYPE_CHN_UDPSVR				230			//CHN_UDPSVR	 udp server
#define TYPE_CHN_UDPCLN				240			//CHN_UDPCLN	 udp client
#define TYPE_CHN_HTTPSVR			245			//CHN_HTTPSVR	 udp client
#define TYPE_CHN_HTTPCLN			246			//CHN_HTTPCLN	 udp client
#define TYPE_CHN_WSSVR				250			//CHN_WSSVR		 websocket server
#define TYPE_CHN_WSCLN				280			//CHN_WSCLN		 websocket client
#define TYPE_CHN_COM				300			//CHN_COM		 COMM serial port communication 

#define LEN_CHN_NAME				32			// 通信口名
#define LEN_CHN_ADDR				512			// such as 192.168.30.249  ws://192.168.8.31:33333/ws/connect
#define LEN_CHN_URL					512			// url such as ws://192.168.8.31:33333/ws/connect,目前由addr 兼用
//#define LEN_CHN_BUF				802400		// 每个通道最多保留200K字节的缓冲区

#define LAN_WEBSVR_PORT				4567		// 动态的，不确定。
#define LEN_LASCELL_NAME			16			
#define LEN_LASCELL_TRAYNO			16			
#define LEN_LASCELL_PARTDESC		64			//库位--物料描述


#define MAX_TASKMES_NUM				30			//最多300MES任务（输出大盘）
#define MAX_TASKWMS_NUM				250			//最多标准WMS任务
#define MAX_TASKWCS_NUM				300			//最多标准WCS任务	
#define MAX_CELL_NUM				2227		//库位数

#define LEN_TASKWMS_NAME			32			//
#define LEN_TASKWCS_NAME			32			//

#define LEN_TASKMES_NAME			32			//
#define LEN_TASKMES_TASKID			48
#define LEN_TASKMES_TASKARG			2048
#define LEN_TASKMES_TASKITEM		2048
//#define LEN_LASTASK_ECPTEXT  256
#define TYPE_CHNTASK_AT				100			//需要立即发送信息
#define TYPE_CHNTASK_TIMER			200			//定时发送信息



//所有任务，要么为空，要么为等待发送，要么为执行中。一旦有一个任务执行起来，则break循环
#define STATUS_CHNTASK_IDLE			0			//等待调度，空闲等待中
#define STATUS_CHNTASK_SEND			100			//待发送
#define STATUS_CHNTASK_RECV			200			//待接收
#define STATUS_CHNTASK_DATAPROC		300			//待处理
//#define STATUS_COMTASK_FAIL		400			//失败，通信关闭，或通信超时
#define STATUS_COMTASK_FINISHED		500			//失败，通信关闭，或通信超时

#define MAX_CHNTASK_NUM				150			//分配到各通道

#define LEN_CHNTASK_NAME			48			
#define LEN_CHNTASK_CHN				48			
#define LEN_CHNTASK_SENDBUF			256			
#define LEN_CHNTASK_RECVBUF			2048		
#define LEN_CHNTASK_ECPTTEXT		256			
//#define MAX_CHNTASK_HOR_NUM		2
#define LEN_CHNTASK_SENDBUF_BLOCK	10240000			
#define LEN_CHNTASK_RECVBUF_BLOCK	10240000	
#define LEN_CHNTASK_ECPTTEXT		256					

#define LEN_BLOCK_MSG				10240		//返回消息
#define LEN_BLOCK_JSONCOLS			10240		//数据表列
#define LEN_BLOCK_JSONROW			40240		//数据表行
#define LEN_BLOCK_JSONROWS			280240		//数据多行
#define LEN_BLOCK_CHNTASK_BUF		280240		//通信打包较大数据 限制28K

#define LEN_WEB_ARG					256		// 应该更大 //从源串中找到wheres=cats like '%【财经资讯】%'   @@   orderby=id desc @@



#define ERROR_COMMON				-1			//一般错误，不需要命名

//文件类错误
#define ERROR_FILE_NOTEXIST			-10010001	//文件不存在
#define ERROR_FILE_SEEK				-10010010	//文件定位错误

//数据库类错误
#define ERRNO_DB_INIT  				-20010001	//数据库初始化错误		
#define ERRNO_DB_DB_NULL			-20010010	//数据库访问指向空		
#define ERRNO_DB_REC_NULL			-20010030	//数据记录为空			
#define ERRNO_DB_REC_EXISTED		-20010031	//数据记录已经存在		

#define ERRLINE_DB_INIT				"数据库初始化错误"		
#define ERRLINE_DBPRNULL			"数据访问指向空"		

#define ERRLINE_INTERNAL_ARG		"内部参数错误"			
#define ERRLINE_REPEAT_DO			"重复执行的错误"		
#define ERRLINE_DB_REC_NULL			"数据记录为空"			
#define ERRLINE_DB_REC_EXIST		"数据记录已经存在"			
#define ERRLINE_IPV4_NULL			"传入的IP地址空，无法分发业务"      

#define MAX_LASCELL_NUM				2227
#define MAX_LASINF_NUM				202
#define MAX_LASDEV_NUM				18			//智能物流设备数量




#define LEN_STYLE					256		//显示样式
#define LEN_HREF					256		//附加的超链接
#define LEN_COL_DSPARG				256		//列显示参数
#define LEN_WEB_ARG					256		// 应该更大 //从源串中找到wheres=cats like '%【财经资讯】%'   @@   orderby=id desc @@

#define LEN_ITEM					48				//最多32位，为防错，保留48位
#define LEN_ITEM_NAME				LEN_ITEM		//最多32位，为防错，保留48位
#define LEN_ITEM_VALUE				LEN_ITEM		//最多32位，为防错，保留48位

#define MAX_ITEMPAR_NUM				2000			//目前设备支持2000个参量
#define MAX_ITEMVAR_NUM				2000			//目前设备支持2000个变量

#define LOGCONST         __FILE__,__LINE__,TYPECTRL|DESTFILE|DISPALL
#define CPPFILE          __FILE__,__LINE__,TYPECTRL|DESTFILE|DISPALL

#define MAX_MOD_NUM					20				//目前设备支持20个模块

//可以考虑constexpr 定义变量的方式来定义宏
#define MODMCC			10 //控制器
#define MODMCCSVO		11 //软赢控制器
#define MODMCCZMN		12 //正运动控制器 ZMOTION
#define MODMCCGTS		15 //固高控制器
#define MODMCCLS		16 //雷赛控制器  LeadShine 
#define MODIO			20 //IO
#define MODTRK			23 //轨道
#define MODAX			24 //轴
#define MODAXX			25 //轴X
#define MODAXY			26 //轴Y
#define MODAXZ			27 //轴Z
#define MODAXU			28 //轴U
#define MODWGT			30 //称重
#define MODHGT			32 //测高
#define MODTMP			34 //测温
#define MODLGT			40 //光源
#define MODCAM			44 //相机
#define MODCAMHK		45 //海康相机
#define MODCAMDH		46 //大恒相机
#define MODSVN			50 //视觉
#define MODSVNHLC		52 //视觉halcon
#define MODSVNOCV		54 //视觉Opencv
#define MODSVNCK		56 //视觉创科
#define MODG			60	//G文件模块
#define MODMRK			62	//标定参数

#define MODCHN			70	//标定参数


#define NEXT_TO_BADREQUEST  100		//错误的请求   
#define NEXT_TO_ROOT		200		//访问根目录   
#define NEXT_TO_FILE		300		//跳转下一页   
#define NEXT_TO_AJAX		400		//返回ajax   
