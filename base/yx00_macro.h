#pragma once
#define ERROR_IDX					-1			//
#define ERROR_COMMON				-1			//
#define LEN_APP_NAME				64			//Ӧ����
#define MAX_APP_NUM					1 

#define LEN_FILE_NAMES				256			//����,���ܰ������								//LEN_FILES
#define LEN_FILE_PATH				256			//·����										//LEN_PATH
#define LEN_FILE_NAME				64			//�ļ���  �����ܳ���,��������ϵͳ��ջ����		//LEN_FILENAME
#define LEN_FILE_PATHFILE			256			//·�������ļ���								//LEN_PATHFILE
#define LEN_FILE_LINE				256			//												//LEN_LINE

#define MAX_DB_NUM					3			// 
#define DB_DIC_IN					0			//�ֵ����ڵ����ݿ�

#define TYPE_DB_MYSQL				100			//DB_MYSQL	
#define TYPE_DB_SQLSERVER			200			//DB_SQLSERVER
#define TYPE_DB_ORACLE				300			//DB_ORACLE	

#define LEN_DB_INIARG				256			//yxdbsrv.cpp loadCfg()
#define LEN_DB_HOST					32			//name or ip Address
#define LEN_DB_PORT					32			//port
#define LEN_DB_USR					32			//name or ip Address
#define LEN_DB_PWD					32			//name or ip Address
#define LEN_DB_NAME					32			//name or ip Address
#define LEN_DB_DESC					1024		//���ݿ���������
#define LEN_DB_SQL					10240		//max sql statement length
#define LEN_DB_WHERES				1024		

#define LEN_LOGUSR_IP				32			
#define LEN_LOGUSR_TBL				32			
#define LEN_LOGUSR_ACT				32				
#define LEN_LOGUSR_MSG				256
#define LEN_CHNTASK_TITLE           1024

//zhou2018
#define MAX_TABLE_NUM				250			//�������ű�Ҫ��tbl����һ��
#define MAX_COL_NUM					100			//��������
#define LEN_COL_NAME				32			//��������
//#define LEN_COL_MAXTEXT			8192		//�趨ÿ�����8K����
#define LEN_COL_STRING				8192		//�趨ÿ�����8K����

#define MAX_ROW_TBL_NUM				10000		//MAX_ROW_TBL_NUM	ÿ�������ļ�¼��   ����ϵͳ�����ӣ������¸�����   !!!!!!!!!!!!!!!!!!!!!!!
#define MAX_ROW_PAGE_NUM			300			//ÿҳ������������
#define MAX_PAGE_ROW				1000		//Ŀǰû�г���1000����¼�ĳ�פ�� 


//#define MAX_DB_TABLE				250			//MAX_TABLE_NUM		���250�ű�  //Ҫ��tbl����һ��
//#define MAX_DB_ROW_TBL			10000		//MAX_ROW_TBL_NUM	ÿ�������ļ�¼��   ����ϵͳ�����ӣ������¸�����   !!!!!!!!!!!!!!!!!!!!!!!
//#define MAX_DB_ROW_PAGE			300			//MAX_ROW_PAGE_NUM	ÿҳ���100������
//#define MAX_DB_PAGE				1000		//MAX_PAGE_ROW		Ŀǰû�г���1000����¼�ĳ�פ��  

#define LEN_TABLE_NAME				32			
#define LEN_TABLE_TITLE				32
#define LEN_TABLE_FUNS				1024		//���������
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

#define MAX_CHN_NUM					10			//����Ŀ��5��
#define TYPE_CHN_TCPSVR				210			//CHN_TCPSVR	 tcp server 
#define TYPE_CHN_TCPCLN				220			//CHN_TCPCLN	 tcp client 
#define TYPE_CHN_UDPSVR				230			//CHN_UDPSVR	 udp server
#define TYPE_CHN_UDPCLN				240			//CHN_UDPCLN	 udp client
#define TYPE_CHN_HTTPSVR			245			//CHN_HTTPSVR	 udp client
#define TYPE_CHN_HTTPCLN			246			//CHN_HTTPCLN	 udp client
#define TYPE_CHN_WSSVR				250			//CHN_WSSVR		 websocket server
#define TYPE_CHN_WSCLN				280			//CHN_WSCLN		 websocket client
#define TYPE_CHN_COM				300			//CHN_COM		 COMM serial port communication 

#define LEN_CHN_NAME				32			// ͨ�ſ���
#define LEN_CHN_ADDR				512			// such as 192.168.30.249  ws://192.168.8.31:33333/ws/connect
#define LEN_CHN_URL					512			// url such as ws://192.168.8.31:33333/ws/connect,Ŀǰ��addr ����
//#define LEN_CHN_BUF				802400		// ÿ��ͨ����ౣ��200K�ֽڵĻ�����

#define LAN_WEBSVR_PORT				4567		// ��̬�ģ���ȷ����
#define LEN_LASCELL_NAME			16			
#define LEN_LASCELL_TRAYNO			16			
#define LEN_LASCELL_PARTDESC		64			//��λ--��������


#define MAX_TASKMES_NUM				30			//���300MES����������̣�
#define MAX_TASKWMS_NUM				250			//����׼WMS����
#define MAX_TASKWCS_NUM				300			//����׼WCS����	
#define MAX_CELL_NUM				2227		//��λ��

#define LEN_TASKWMS_NAME			32			//
#define LEN_TASKWCS_NAME			32			//

#define LEN_TASKMES_NAME			32			//
#define LEN_TASKMES_TASKID			48
#define LEN_TASKMES_TASKARG			2048
#define LEN_TASKMES_TASKITEM		2048
//#define LEN_LASTASK_ECPTEXT  256
#define TYPE_CHNTASK_AT				100			//��Ҫ����������Ϣ
#define TYPE_CHNTASK_TIMER			200			//��ʱ������Ϣ



//��������ҪôΪ�գ�ҪôΪ�ȴ����ͣ�ҪôΪִ���С�һ����һ������ִ����������breakѭ��
#define STATUS_CHNTASK_IDLE			0			//�ȴ����ȣ����еȴ���
#define STATUS_CHNTASK_SEND			100			//������
#define STATUS_CHNTASK_RECV			200			//������
#define STATUS_CHNTASK_DATAPROC		300			//������
//#define STATUS_COMTASK_FAIL		400			//ʧ�ܣ�ͨ�Źرգ���ͨ�ų�ʱ
#define STATUS_COMTASK_FINISHED		500			//ʧ�ܣ�ͨ�Źرգ���ͨ�ų�ʱ

#define MAX_CHNTASK_NUM				150			//���䵽��ͨ��

#define LEN_CHNTASK_NAME			48			
#define LEN_CHNTASK_CHN				48			
#define LEN_CHNTASK_SENDBUF			256			
#define LEN_CHNTASK_RECVBUF			2048		
#define LEN_CHNTASK_ECPTTEXT		256			
//#define MAX_CHNTASK_HOR_NUM		2
#define LEN_CHNTASK_SENDBUF_BLOCK	10240000			
#define LEN_CHNTASK_RECVBUF_BLOCK	10240000	
#define LEN_CHNTASK_ECPTTEXT		256					

#define LEN_BLOCK_MSG				10240		//������Ϣ
#define LEN_BLOCK_JSONCOLS			10240		//���ݱ���
#define LEN_BLOCK_JSONROW			40240		//���ݱ���
#define LEN_BLOCK_JSONROWS			280240		//���ݶ���
#define LEN_BLOCK_CHNTASK_BUF		280240		//ͨ�Ŵ���ϴ����� ����28K

#define LEN_WEB_ARG					256		// Ӧ�ø��� //��Դ�����ҵ�wheres=cats like '%���ƾ���Ѷ��%'   @@   orderby=id desc @@



#define ERROR_COMMON				-1			//һ����󣬲���Ҫ����

//�ļ������
#define ERROR_FILE_NOTEXIST			-10010001	//�ļ�������
#define ERROR_FILE_SEEK				-10010010	//�ļ���λ����

//���ݿ������
#define ERRNO_DB_INIT  				-20010001	//���ݿ��ʼ������		
#define ERRNO_DB_DB_NULL			-20010010	//���ݿ����ָ���		
#define ERRNO_DB_REC_NULL			-20010030	//���ݼ�¼Ϊ��			
#define ERRNO_DB_REC_EXISTED		-20010031	//���ݼ�¼�Ѿ�����		

#define ERRLINE_DB_INIT				"���ݿ��ʼ������"		
#define ERRLINE_DBPRNULL			"���ݷ���ָ���"		

#define ERRLINE_INTERNAL_ARG		"�ڲ���������"			
#define ERRLINE_REPEAT_DO			"�ظ�ִ�еĴ���"		
#define ERRLINE_DB_REC_NULL			"���ݼ�¼Ϊ��"			
#define ERRLINE_DB_REC_EXIST		"���ݼ�¼�Ѿ�����"			
#define ERRLINE_IPV4_NULL			"�����IP��ַ�գ��޷��ַ�ҵ��"      

#define MAX_LASCELL_NUM				2227
#define MAX_LASINF_NUM				202
#define MAX_LASDEV_NUM				18			//���������豸����




#define LEN_STYLE					256		//��ʾ��ʽ
#define LEN_HREF					256		//���ӵĳ�����
#define LEN_COL_DSPARG				256		//����ʾ����
#define LEN_WEB_ARG					256		// Ӧ�ø��� //��Դ�����ҵ�wheres=cats like '%���ƾ���Ѷ��%'   @@   orderby=id desc @@

#define LEN_ITEM					48				//���32λ��Ϊ��������48λ
#define LEN_ITEM_NAME				LEN_ITEM		//���32λ��Ϊ��������48λ
#define LEN_ITEM_VALUE				LEN_ITEM		//���32λ��Ϊ��������48λ

#define MAX_ITEMPAR_NUM				2000			//Ŀǰ�豸֧��2000������
#define MAX_ITEMVAR_NUM				2000			//Ŀǰ�豸֧��2000������

#define LOGCONST         __FILE__,__LINE__,TYPECTRL|DESTFILE|DISPALL
#define CPPFILE          __FILE__,__LINE__,TYPECTRL|DESTFILE|DISPALL

#define MAX_MOD_NUM					20				//Ŀǰ�豸֧��20��ģ��

//���Կ���constexpr ��������ķ�ʽ�������
#define MODMCC			10 //������
#define MODMCCSVO		11 //��Ӯ������
#define MODMCCZMN		12 //���˶������� ZMOTION
#define MODMCCGTS		15 //�̸߿�����
#define MODMCCLS		16 //����������  LeadShine 
#define MODIO			20 //IO
#define MODTRK			23 //���
#define MODAX			24 //��
#define MODAXX			25 //��X
#define MODAXY			26 //��Y
#define MODAXZ			27 //��Z
#define MODAXU			28 //��U
#define MODWGT			30 //����
#define MODHGT			32 //���
#define MODTMP			34 //����
#define MODLGT			40 //��Դ
#define MODCAM			44 //���
#define MODCAMHK		45 //�������
#define MODCAMDH		46 //������
#define MODSVN			50 //�Ӿ�
#define MODSVNHLC		52 //�Ӿ�halcon
#define MODSVNOCV		54 //�Ӿ�Opencv
#define MODSVNCK		56 //�Ӿ�����
#define MODG			60	//G�ļ�ģ��
#define MODMRK			62	//�궨����

#define MODCHN			70	//�궨����


#define NEXT_TO_BADREQUEST  100		//���������   
#define NEXT_TO_ROOT		200		//���ʸ�Ŀ¼   
#define NEXT_TO_FILE		300		//��ת��һҳ   
#define NEXT_TO_AJAX		400		//����ajax   
