/******************************************************************************
* FH130头文件定义                                                             *
* 版本                                                                        *
* 说明                                                                        *
******************************************************************************/

#ifndef __FH_130_API_H__
#define __FH_130_API_H__

/*类型定义*/
typedef short                                    FCSHORT;
typedef int                                      FCINT;
typedef unsigned char                            FCUCHAR;
typedef unsigned short                           FCUSHORT;
typedef unsigned int                             FCUINT;
typedef unsigned long long                       FCUINT64;
typedef int                                     *FCHANDLE;

/*ASM接收回调定义*/
typedef FCUINT (* FC_ASM_RECVMSG_FUNCPTR)(FCHANDLE hDev, FCUINT msgID);

/*中断回调定义*/
typedef FCUINT (* FC_INT_FUNCPTR)(FCHANDLE hDev, FCUINT intCode, FCUINT param0);
typedef void (* FC_MEMCPY_FUNCPTR)(void *dest, void *src, unsigned int size);


/*自检返回值*/
#define BIT_SUCCESS                              0
#define BIT_FAILURE                              1


#define NC_OFF_NET                               0
#define NC_ON_NET                                1

#define NT_OFF_NET                               0
#define NT_ON_NET                                1

#define NT_OFF_LINE                              0
#define NT_ON_LINE                               1


#define CONFIG_MODE_PROJECT                      0
#define CONFIG_MODE_FLASH                        1

/*最大蓝图个数 */
#define FC_MAJOR_SCHEME_MAX                      128
/*每个蓝图的配置块个数 */
#define FC_MINOR_SCHEME_MAX                      4

/*角色*/
#define ROLE_NC                                  1
#define ROLE_BNC                                 2 
#define ROLE_NRT                                 3

/*网络时钟服务器，模块时钟客户端*/
#define CLK_SYNC_ROLE_SERVER_MASTER              1
/*网络时钟客户端*/
#define CLK_SYNC_ROLE_CLIENT                     2

/* RTC同步角色定义*/
/*1 服务器- 发送广播消息*/
#define SYNC_MODE_SERVER                         1
/*2 客户端- 接收广播消息*/
#define SYNC_MODE_CLIENT                         2

/*WDT周期禁止*/
#define WDT_LOADER_PERIOD_DISABLE                0
/*WDT周期使能*/
#define WDT_LOADER_PERIOD_ENAB                   1
/*没有收到ELS帧*/
#define RECV_ELS_INIT                            0
/*已经收到ELS帧*/
#define RECV_ELS_COMPLETE                        1

/* 网络角色定义 */
#define FC_NET_ROLE_NC                           1 /*网络控制器*/
#define FC_NET_ROLE_BNC                          2 /*备份网络控制器*/
#define FC_NET_ROLE_NRT                          3 /*网络远程终端*/

#define FC_NET_CLK_SYNC_ROLE_SERVER_MASTER       1 /*网络时钟服务器，模块时钟客户端*/
#define FC_NET_CLK_SYNC_ROLE_CLIENT              2 /*网络时钟客户端*/

#define FC_SYNC_MODE_SERVER                      1 /*发送RTC时钟*/
#define FC_SYNC_MODE_CLIENT                      2 /*接收RTC时钟*/

#define FC_WDT_LOADER_PERIOD_DISABLE             0 /*WDT加载周期禁止*/
#define FC_WDT_LOADER_PERIOD_ENAB                1 /*WDT加载周期使能*/

#define FC_WDT_LOCAL_MODE                        1 /*本地模式*/
#define FC_WDT_NET_MODE                          2 /*网络模式*/

#define FC_NODE_STATE_OFF_LINE                   0 /*节点不在线*/
#define FC_NODE_STATE_ON_LINE                    1 /*节点在线*/

#define FC_PORT_STATUS_LINK_DOWN                 0 /* 端口链路DOWN */
#define FC_PORT_STATUS_LINK_UP                   1 /* 端口链路UP */

#define FC_CHANNEL_NUM_MAX                       256 /*发送和接收通道的个数，最大256*/

#define FC_SW_NUM_MAX                            2   /*交换机的数目*/
#define FC_SW_PORT_NUM_MAX                       36  /*交换机的端口数目*/

#define FC_CONFIG_MODE_PROJECT                   0   /*工程模式*/
#define FC_CONFIG_MODE_FLASH                     1   /*FLASH模式*/

#define FC_MAJOR_SCHEME_MAX                      128 /*最大蓝图个数 */
#define FC_MINOR_SCHEME_MAX                      4   /*每个蓝图的配置块个数*/

#define FC_ASM_RUN_DISABLE                       0   /*禁止ASM发送接收*/
#define FC_ASM_RUN_ENAB                          1   /*允许ASM发送接收*/

#define FC_NC_BNC_MULTICAST_ADDR                 0x00FFFBFE  /*保留组播号，用于向NC和BNC节点发送组播消息*/

/* 发送/接收消息类型 */
#define MSG_TYPE_URGENCY_MSG				1
#define MSG_TYPE_EVENT_MSG					2
#define MSG_TYPE_ELS_MSG					3	/* 保留，不要使用 */
#define MSG_TYPE_STREAM_MSG					4


/* 发送优先级 */
#define MAX_PRIORITY_LEVEL_NUM              4
#define PRIORITY_LEVEL_0 	                0 /* LOW , for ELS*/
#define PRIORITY_LEVEL_1  	                1	
#define PRIORITY_LEVEL_2 	                2
#define PRIORITY_LEVEL_3 	                3 /* HIGH*/

/* 消息覆盖标记 */
#define MSG_NO_RECOVER		0	/* 当接收消息超过最大缓存数时，丢弃新来的消息 */
#define MSG_RECOVER			1	/* 当接收消息超过最大缓存数时，覆盖最老的一条消息，保留新来的消息 */


/******************************************************************************
* 中断子码定义                                                                *
******************************************************************************/

#define IC_VOLTAGE_SUCCESS                       0x100      /*电压从错误值变为正常值*/
#define IC_VOLTAGE_FAILED                        0x101      /*电压错误*/
#define IC_TEMP_SUCCESS                          0x102      /*温度从错误值变为正常值*/
#define IC_TEMP_FAILED                           0x103      /*温度错误*/
#define IC_LINK_STATUS_SUCCESS                   0x104      /*link状态从错误值变为正常值*/
#define IC_LINK_STATUS_FAILED                    0x105      /*link状态错误*/
#define IC_IO_BUF_WRITE_FAILED                   0x106      /*收发缓冲区写错误*/
#define IC_IO_BUF_READ_FAILED                    0x107      /*收发缓冲区读错误*/
#define IC_DISCARD_MSG           		         0x108      /*消息丢弃*/
#define IC_COVER_MSG             		         0x109      /*消息覆盖*/
#define IC_IU_TIMEOUT             		         0x10A      /*IU超时*/
#define IC_IU_SEQ_ERR             		         0x10B      /*IU超时*/
#define IC_IU_LENGTH_INVALID         	         0x10C      /*IU长度无效*/
#define IC_ELS_RECV_RECONSTRUCT                  0x200      /*重构*/
#define IC_ELS_RECV_NC_ON_NET                    0x201      /*NC在网*/
#define IC_ELS_RECV_NC_TIMEOUT                   0x202      /*WDT超时*/
#define IC_ELS_RECV_RECONSTRUCT_SUCCESS          0x203      /*重构完成*/
#define IC_ELS_RECV_RECONSTRUCT_FAIL             0x204      /*重构失败*/
#define IC_NC_CONFLICT                           0x208      /*NC冲突*/
#define IC_NC_CHANGED                            0x209      /*NC切换*/

/******************************************************************************
* 错误码
******************************************************************************/

/* 通用错误码 */
#define FC_SUCCESS                               0          /* 成功 */
#define FC_FAILURE                               0xE000FFFF /* 失败 */

#define FC_INVALID_HANDLE						 0xE0000001 /* 无效句柄 */
#define FC_PARAMS_INVALID   			         0xE0000002 /* 无效的参数  */
#define FC_INVALID_PORT_NUMBER					 0xE0000003 /* 无效的端口号*/	

/* 配置管理错误码 */
#define FC_DEVICE_ID_INVALID                     0xE1000001 /* 无效的设备ID */
#define FC_DEVICE_STATE_INVALID                  0xE1000002 /* 无效的设备状态 */
#define FC_DEVICE_NOT_FOUNT                      0xE1000003 /* 设备没有找到 */

/* 配置管理错误码 */
#define FC_GET_CONFIG_FAIL   			         0xE2000001 /* 获取配置数据失败 */
#define FC_INITIALISE_FAIL   			         0xE2000002 /* 初始化失败 */  
#define FC_SELF_CHECK_FAIL   			         0xE2000003 /* 自检失败 */
#define FC_HASH_CONFLICT                         0xE2000004 /* 哈希冲突 */
#define FC_DEV_GET_CONFIG_FAILED                 0xE2000005 /* 设备获取配置失败 */
#define FC_DEV_CB_INIT_FAILED                    0xE2000006 /* 设备上下文初始化失败 */
#define FC_DEV_START_FAILED                      0xE2000007 /* 设备启动失败 */
#define FC_INVALID_MAJOR_SCHEME					 0xE2000008 /* 无效的大版本号 */
#define FC_INVALID_MINOR_SCHEME					 0xE2000009 /* 无效的小版本号 */

#define FC_INVALID_FCID					 		 0xE2000011 /* FCID无效 */
#define FC_INVALID_NM_ROLE					 	 0xE2000012 /* 网络管理角色无效 */
#define FC_INVALID_TM_ROLE					 	 0xE2000013 /* 时钟同步角色无效 */
#define FC_INVALID_WDT_PERIOD				     0xE2000014 /* WDT定时器无效 */
#define FC_INVALID_CLK_SYNC_PERIOD				 0xE2000015 /* 时钟同步周期无效 */
#define FC_SEND_CHANNEL_BEYOND					 0xE2000016 /* 发送通道数超出范围 */	
#define FC_RECV_CHANNEL_BEYOND					 0xE2000017 /* 接收通道数超出范围 */
#define FC_TX_MSG_MAX_LEN_BEYOND				 0xE2000021 /* 无效的发送消息最大长度 */
#define FC_INVALID_TX_MSG_SRC_ID				 0xE2000022 /* 无效的发送消息源ID */
#define FC_INVALID_TX_MSG_DST_ID				 0xE2000023 /* 无效的发送消息目的ID */
#define FC_INVALID_TX_MSG_TYPE					 0xE2000024 /* 无效的发送消息类型 */
#define FC_INVALID_TX_MSG_PRIORITY               0xEC000025 /*无效的发送消息优先级*/
#define FC_RX_MSG_MAX_LEN_BEYOND				 0xE2000031 /* 无效的接收消息最大长度 */
#define FC_INVALID_RX_MSG_TYPE					 0xE2000032 /* 无效的接收消息类型 */
#define FC_INVALID_RX_MSG_SRC_ID				 0xE2000033 /* 无效的接收消息源ID */
#define FC_INVALID_RX_MSG_RECOVER				 0xE2000034 /* 无效的接收消息覆盖标记 */

/* 数据通讯错误原因值 */
#define FC_MSG_ID_INVALID   			         0xE3000001 /* 无效的msgID  */
#define FC_ASM_RUN_INVALID                       0xE3000002 /* ASM运行控制是禁止 */
#define FC_DEV_CLOSED 					         0xE3000003 /* 设备已经关闭 */
#define FC_INVALID_RUN_CONTROL					 0xE3000004 /* 无效的运行控制值 */
#define FC_PORT_LINK_DOWN                        0xE3000005 /* 端口linkdown */

#define FC_SEND_INVALID_LENGTH                   0xE3000011 /* 无效的发送长度 */
#define FC_SEND_INVALID_BUFFER                   0xE3000012 /* 无效的发送缓存 */
#define FC_SEND_MSG_BUFFER_EMPTY 		         0xE3000013 /* 发送缓存用完 */

#define FC_RECV_INVALID_BUFFER                   0xE3000021 /* 无效的发送缓存 */
#define FC_RECV_LENGTH_IS_ZERO                   0xE3000022 /* 接收字节长度是零 */
#define FC_RECV_LENGTH_TOO_BIG                   0xE3000023 /* 接收字节长度超过ASM IU的最大字节长度 */
#define FC_RECV_LENGTH_TOO_SMALL                 0xE3000024 /* 接收字节长度超过ASM IU的最大字节长度 */
#define FC_RECV_NO_DATA             	         0xE3000025 /* 没有收到数据 */
#define FC_RECV_ASM_TIMEOUT						 0xE3000026 /* 接收超时 */

/* 时钟管理错误原因值 */
#define FC_TM_INVALID_YEAR_VALUE				 0xE4000001 /* 无效的年份值 */
#define FC_TM_INVALID_MONTH_VALUE				 0xE4000002 /* 无效的月份值 */
#define FC_TM_INVALID_DAY_VALUE					 0xE4000003 /* 无效的日期值 */
#define FC_TM_INVALID_HOUR_VALUE				 0xE4000004 /* 无效的时钟值 */
#define FC_TM_INVALID_MINUTE_VALUE				 0xE4000005 /* 无效的分钟值 */
#define FC_TM_INVALID_SECOND_VALUE				 0xE4000006 /* 无效的秒钟值 */
#define FC_TM_SET_DATE_FAIL					 	 0xE4000007 /* 设置日期错误 */
#define FC_TM_SET_RTC_FAIL					 	 0xE4000008 /* 设置RTC时间错误 */
#define FC_TM_ROLE_ILLE_OPERATION                0xE4000009 /* 时钟角色的非法操作 */
#define FC_TM_INVALID_CARRIER_RTC_SYN_MODE		 0xE400000A /* 无效的载板RTC同步模式 */	
#define FC_TM_INVALID_PLUSE_DUTY		 		 0xE400000B /* 无效的载板RTC同步PLUSE_DUTY */	

/* 网络管理错误原因值 */
#define FC_NM_ROLE_SAMED                         0xE5000001 /* 设置了相同的网络管理角色 */
#define FC_NM_ROLE_ILLE_OPERATION                0xE5000002 /* 网络管理角色的非法操作 */
#define FC_NM_NC_IS_OFF_LINE                     0xE5000003 /* NC节点没有在线 */
#define FC_NM_SYNC_IO_WAIT_FAILED                0xE5000004	/* 发送ELS帧以后等待接收ELS帧超时 */
#define FC_NM_FRAME_SEND_FAILED                  0xE5000005 /* 发送网络管理帧失败 */
#define FC_NM_INVALID_PORT_ID		 			 0xE5000006 /* 无效的port ID */
#define FC_NM_INVALID_PORT_COUNT				 0xE5000007 /* 无效的端口数目 */	
#define FC_NM_INVALID_NET_TBL_INDEX				 0xE5000008 /*无效的网表索引位*/


/*手动自检结果*/
typedef struct
{
	FCUINT flash;        /*flash读写*/
	FCUINT temperature;  /*温度*/
	FCUINT voltage;      /*电压*/	
} FC_BIT_RESULT_MANUAL;

/*上电自检结果*/
typedef struct
{
	FCUINT memory;       /*内存测试*/
	FCUINT reg;          /*寄存器读写*/
	FCUINT temperature;  /*温度*/
	FCUINT voltage;      /*电压*/
	FCUINT flash;        /*flash读写*/
} FC_BIT_RESULT_POWER;

/*自检结果*/
typedef struct
{
	FCUINT memory;       /*内存测试*/
	FCUINT reg;          /*寄存器读写*/
	FCUINT temperature;  /*温度*/
	FCUINT voltage;      /*电压*/
	FCUINT flash;        /*flash读写*/
} FC_BIT_RESULT;

/*时间结构体*/
typedef struct
{
	FCUINT hour;         /*时*/
	FCUINT minute;       /*分*/
	FCUINT second;       /*秒*/
	FCUINT millisecond;  /*毫秒*/
	FCUINT microsecond;  /*微秒*/
	FCUINT nanosecond;   /*纳秒*/
} FCTime;

/*FTP参数*/
typedef struct
{
	FCUCHAR hostIp[16]; /*主机的IP地址，最大15个字符以\0结尾*/
	FCUCHAR user[16];   /*用户名，最大15个字符以\0结尾*/
	FCUCHAR pwd[16];    /*密码，最大15个字符以\0结尾*/
} FC_FTP_PARAM;

/*日期结构体*/
typedef struct
{
	FCUINT year;         /*年*/
	FCUINT month;        /*月*/
	FCUINT day;          /*日*/
} FCDate;

/*上网状态表*/
typedef struct
{
	FCUCHAR Status[FC_SW_PORT_NUM_MAX]; /*0: off net, 1: on net*/
} OnNetTbl;

/*节点统计信息*/
typedef struct
{
    FCUINT RxMinFrameErrCnt[2]; /*Indicates the number of frames received that did not meet the minimum frame length requirement since this register was last read*/
    FCUINT RxMaxFrameErrCnt[2]; /*Indicates the number of frames received that exceeded the maximum frame length requirement since this register was last read*/
    FCUINT RxFrameCnt[2];       /*Indicates the number of frames received since this register was last read*/
    FCUINT RxWordCnt[2];        /*number of 32-bit data words received within FC frame(s) since this register was last read*/
    FCUINT RxPSMErrCnt[2];      /*Indicates the number of illegal PSM transactions that occurred since this register was last read*/
    FCUINT RxRRDYCnt[2];        /*Indicates the number of R_RDYs received since this register was last read*/
    FCUINT TxFrameCnt[2];       /*Indicates the number of frames transmitted since this register was last read*/
    FCUINT TxWordCnt[2];        /*Indicates the number of 32-bit data words transmitted within FC frame(s) since this register was last read*/
    FCUINT TxKErrCnt[2];        /*Indicates the number of 32-bit data words transmitted with an invalid K character since this register was last read*/
    FCUINT TxRRDYCnt[2];        /*Indicates the number of R_RDYs transmitted since this register was last read*/
} NetStatistics;

/*交换机link状态表*/
typedef struct
{
	FCUCHAR Status[FC_SW_NUM_MAX][FC_SW_PORT_NUM_MAX]; /*0: off line, 1: on line*/
} SwLinkStatusTbl;

/*交换机版本号*/
/*应用传下来的内存是按照1字节对齐的，适配其对齐方式，
否则会导致用sizeof取结构大小取大了,memcpy的时候会踩内存!!!*/
typedef struct 
{
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
	
	/*软件版本号*/
	FCUSHORT VersionA   : 4;  /*A(0~9)(LSB=1)*/
	FCUSHORT VersionB   : 7;  /*B(00~99)(LSB=1)*/
	FCUSHORT VersionC   : 5;  /*C(00~25)软件技术状态标识(A~Z)*/

	/*软件版本生成日期*/
	FCUINT BuildYear    : 12; /*年(LSB=1)*/
	FCUINT BuildMonth   : 4;  /*月(LSB=1)*/
	FCUINT BuildDay     : 5;  /*日(LSB=1)*/
    FCUINT              : 2;  /**/
	FCUINT SoftwareCode : 9;  /*软件编码*/
	/*软件版本生成时间*/
	FCUINT BuildHour    : 5;  /*时(LSB=1)*/
	FCUINT BuildMinute  : 6;  /*分(LSB=1)*/
	FCUINT BuildSecond  : 6;  /*秒(LSB=1)*/
    FCUINT              : 15; /**/
    
#else
    
	/*软件版本号*/
	FCUSHORT VersionC   : 5;  /*C(00~25)软件技术状态标识(A~Z)*/
	FCUSHORT VersionB   : 7;  /*B(00~99)(LSB=1)*/
	FCUSHORT VersionA   : 4;  /*A(0~9)(LSB=1)*/

	/*软件版本生成日期*/
	FCUINT SoftwareCode : 9;  /*软件编码*/
	FCUINT              : 2;  /**/
	FCUINT BuildDay     : 5;  /*日(LSB=1)*/
	FCUINT BuildMonth   : 4;  /*月(LSB=1)*/
	FCUINT BuildYear    : 12; /*年(LSB=1)*/
	
	/*软件版本生成时间*/
	FCUINT              : 15; /**/
	FCUINT BuildSecond  : 6;  /*秒(LSB=1)*/
	FCUINT BuildMinute  : 6;  /*分(LSB=1)*/
	FCUINT BuildHour    : 5;  /*时(LSB=1)*/
	
#endif
}__attribute__((packed,aligned(1))) SW_IMPSoftWareVersion;

/*软件版本号*/
typedef struct 
{
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
	
	/*软件版本号*/
	FCUSHORT VersionA   : 4;  /*A(0~9)(LSB=1)*/
	FCUSHORT VersionB   : 7;  /*B(00~99)(LSB=1)*/
	FCUSHORT VersionC   : 5;  /*C(00~25)软件技术状态标识(A~Z)*/

	/*软件版本生成日期*/
	FCUINT BuildYear    : 12; /*年(LSB=1)*/
	FCUINT BuildMonth   : 4;  /*月(LSB=1)*/
	FCUINT BuildDay     : 5;  /*日(LSB=1)*/
    FCUINT              : 11;  /**/

	/*软件版本生成时间*/
	FCUINT BuildHour    : 5;  /*时(LSB=1)*/
	FCUINT BuildMinute  : 6;  /*分(LSB=1)*/
	FCUINT BuildSecond  : 6;  /*秒(LSB=1)*/
	FCUINT              : 15; /**/
	
#else
	
	/*软件版本号*/
	FCUSHORT VersionC   : 5;  /*C(00~25)软件技术状态标识(A~Z)*/
	FCUSHORT VersionB   : 7;  /*B(00~99)(LSB=1)*/
	FCUSHORT VersionA   : 4;  /*A(0~9)(LSB=1)*/

	/*软件版本生成日期*/
    FCUINT              : 11;  /**/
    FCUINT BuildDay     : 5;  /*日(LSB=1)*/
   	FCUINT BuildMonth   : 4;  /*月(LSB=1)*/
	FCUINT BuildYear    : 12; /*年(LSB=1)*/

	/*软件版本生成时间*/
	FCUINT              : 15; /**/
	FCUINT BuildSecond  : 6;  /*秒(LSB=1)*/
	FCUINT BuildMinute  : 6;  /*分(LSB=1)*/
	FCUINT BuildHour    : 5;  /*时(LSB=1)*/
	
#endif	
} FC_SoftwareVersion;


/*交换机加载配置*/
typedef struct
{
	FCUINT configMode;
	FCUINT configLength;
	FCUINT checksum;
} SwConfig;

/*交换机加载配置数据*/
typedef struct
{
	FCUINT endFlag;
	FCUINT length;
	FCUINT order;
	FCUCHAR configData[0];
} SwConfigData;

/*端口信息*/
typedef struct
{
	FCUCHAR port_name[16];      /*本地端口的名称*/
    FCUINT  port_id;            /*本地port_id*/
    FCUINT  port_type;          /*端口类型 1-ASM*/
    FCUINT  credit_num;         /*信用*/
    FCUINT  role;               /*端口的网络管理角色 1-网络管理器 2-备份网络管理器 3-网络终端*/
	FCUINT  clk_sync_role;      /*时钟同步角色 1-网络时钟服务器，模块时钟客户端 2-网络时钟客户端*/
    FCUINT  nc_wdt_period;      /*网络管理器的WDT定时周期*/
	FCUINT  wdt_loader_period;  /*WDT加载周期send els frame, 这个值必须比nc_wdt_period小 */
    FCUINT  clk_sync_period;    /*时钟同步周期 set to fpga*/
    FCUINT  nonblock_txmsg_num; /*非数据块发送消息的总数*/
    FCUINT  nonblock_rxmsg_num; /*非数据块接收消息的总数*/
    FCUINT  block_txmsg_num;    /*数据块发送消息的总数*/
    FCUINT  block_rxmsg_num;    /*数据块接收消息的总数*/
} FC_PORT_CONFIG;

/*发送通道*/
typedef struct 
{
	FCUCHAR msg_name[16];/*消息的名称*/
	FCUINT  msg_id;      /*发送消息ID*/
	FCUINT  msg_type;    /*消息类型 1-紧急 2-事件 3-保留(不要使用) 4-长消息*/
	FCUINT  msg_priority;/*消息优先级 0-3，0的优先级最低，3的优先级最高 */
	FCUINT  msg_src_id;  /*消息的源ASM端口port_id*/
	FCUINT  msg_dst_id;  /*消息的目的ASM端口port_id*/
} FC_MSG_SEND_ITEM;

/*接收通道*/
typedef struct
{
	FCUCHAR msg_name[16];/*消息的名称*/
	FCUINT  msg_id;      /*接收消息ID*/
	FCUINT  msg_max_len; /*最大消息长度*/
	FCUINT  msg_type;    /*消息类型 1-紧急 2-事件 3-保留(不要使用) 4-长消息*/
	FCUINT  msg_src_id;  /*消息的源ASM端口port_id*/
	FCUINT  msg_recover; /*消息覆盖控制标志0-不覆盖1-覆盖*/
} FC_MSG_RECV_ITEM;

/*配置块*/
typedef struct
{
    FC_PORT_CONFIG port_config;
	FC_MSG_SEND_ITEM send_item[FC_CHANNEL_NUM_MAX];
	FC_MSG_RECV_ITEM recv_item[FC_CHANNEL_NUM_MAX];
} CONFIG_BLOCK;

/*蓝图*/
typedef struct
{
    CONFIG_BLOCK config_block[FC_MINOR_SCHEME_MAX];
} BLUE_PRINT;

/******************************************************************************
* 设备管理接口                                                                *
******************************************************************************/

/*打开FC节点机的N端口,为FC设备分配资源*/
FCUINT FC_NP_Open(FCHANDLE *hDev, FCUINT devId);

/*关闭FC节点机的N端口*/
FCUINT FC_NP_Close(FCHANDLE hDev);

/*获取FC节点机的N端口状态*/
FCUINT FC_NP_GetState(FCHANDLE hDev, FCUINT* fcState);

/*获取FC节点机的N端口版本号*/
FCUINT FC_NP_GetVersion(FCHANDLE hDev, FCUINT* version);

/*软复位FC节点机的N端口*/
FCUINT FC_NP_SoftReset(FCHANDLE hDev);

/*启动FC节点机的N端口BIT操作*/
FCUINT FC_NP_IBit(FCHANDLE hDev, FC_BIT_RESULT_MANUAL *bitResult);

/*取得自检结果*/
FCUINT FC_NP_GetPuBitResult(FCHANDLE hDev, FC_BIT_RESULT_POWER *bitResult);

/*注册网络管理事件处理函数*/
FCUINT FC_NP_RegEvtHandler(FCHANDLE hDev, FC_INT_FUNCPTR func);

/*注销网络管理事件处理函数*/
FCUINT FC_NP_UnRegEvtHandler(FCHANDLE hDev);

/******************************************************************************
* 通信管理接口                                                                *
******************************************************************************/

/*配置FC节点机的ASM通信模式*/
FCUINT FC_NP_ConfigMode(FCHANDLE hDev, FCUINT configMode);

/*加载FC节点机的ASM配置*/
FCUINT FC_NP_LoadConfig(FCHANDLE hDev, FCUINT majorScheme, FCUINT minorScheme);

/*卸载FC节点机的ASM配置*/
FCUINT FC_NP_UnLoadConfig(FCHANDLE hDev);
    
/*对flash进行配置*/
FCUINT FC_NP_FlashConfig(FCHANDLE hDev);

/*发送指定的ASM消息*/
FCUINT FC_NP_SendMsg(FCHANDLE hDev, FCUINT msgID, FCUCHAR *pMsg, FCUINT nLen);

/*接收指定的ASM消息*/
FCUINT FC_NP_RecvMsg(FCHANDLE hDev, FCUINT msgID, FCUCHAR *pMsg, FCUINT *nLen);

/*注册ASM消息处理函数*/
FCUINT FC_NP_RegMsgHandler(FCHANDLE hDev, FC_ASM_RECVMSG_FUNCPTR func);

/*注销ASM消息处理函数*/
FCUINT FC_NP_UnRegMsgHandler(FCHANDLE hDev);

/*获取驱动工作状态是否正常*/
FCUINT FC_NP_GetWorkStatus(FCHANDLE hDev, FCUINT *status);

/*获取温度*/
FCUINT FC_NP_GetTemp(FCHANDLE hDev, FCINT *temperature);

/*获取端口的link状态*/
FCUINT FC_NP_GetPortLinkStatus(FCHANDLE hDev, FCUINT port, FCUINT *status);

/*控制ASM发送和接收
control 0-禁止ASM发送和接收
        1-允许ASM发送和接收
*/
FCUINT FC_NP_AsmRunControl(FCHANDLE hDev, FCUINT control);

/******************************************************************************
* 时统管理接口                                                                *
******************************************************************************/
/*获取FC节点机的时间*/
FCUINT FC_TM_GetRtc(FCHANDLE hDev, FCTime * pFCTime);

/*设置FC节点机的时间*/
FCUINT FC_TM_SetRtc(FCHANDLE hDev, FCTime * pFCTime);

/******************************************************************************
载板时钟同步配置
参数说明：
  hDev : 设备句柄
  carrier_rtc_enb : 0 禁止 1 - 允许
  mode : 0 - 客户端 1 - 服务器
  pluse_duty :
*******************************************************************************/
FCUINT FC_TM_SetCarrierRTCSyn(FCHANDLE hDev, FCUINT carrier_rtc_enb, FCUINT mode, FCUINT pluse_duty);

/*获取FC节点机的日期*/
FCUINT FC_TM_GetDateTime(FCHANDLE hDev, FCDate *pFCDate, FCTime *pFCTime);

/*设置FC节点机的日期*/
FCUINT FC_TM_SetDate(FCHANDLE hDev, FCDate * pFCDate);

/*设置节点的同步角色*/
FCUINT FC_TM_SyncModeSet(FCHANDLE hDev, FCUINT mode);

/*取得节点的同步角色*/
FCUINT FC_TM_SyncModeGet(FCHANDLE hDev, FCUINT *mode);

/*使能同步接收*/
FCUINT FC_TM_SyncEnable(FCHANDLE hDev);

/*禁止同步接收*/
FCUINT FC_TM_SyncDisable(FCHANDLE hDev);

/******************************************************************************
* 网络管理接口                                                                *
******************************************************************************/

/*设置端口的网络管理角色*/
FCUINT FC_NM_RoleSet(FCHANDLE hDev,	FCUINT value);

/*取得端口的网络管理角色*/
FCUINT FC_NM_RoleGet(FCHANDLE hDev,	FCUINT *value);

/*取得上网状态表*/
FCUINT FC_NM_GetOnNetTable(FCHANDLE hDev, OnNetTbl *pOnNetTbl);

/*取得本地上网状态*/
FCUINT FC_NM_GetOnNetState(FCHANDLE hDev, FCUINT *pState);

/*取得本地统计信息*/
FCUINT FC_NM_GetLocalStatistics(FCHANDLE hDev, NetStatistics * pNetStatistics);

/*加载交换机配置*/
FCUINT FC_NM_NC_LoadSwConfig(FCHANDLE hDev, FCUINT portId, SwConfig *pSwConfig);

/*加载交换机配置数据*/
FCUINT FC_NM_NC_LoadSwConfigData(FCHANDLE hDev, FCUINT portId, SwConfigData *pSwConfigData);

/*取得交换机link状态*/
FCUINT FC_NM_GetSwLinkStatus(FCHANDLE hDev, SwLinkStatusTbl *pSwLinkStatusTbl);

/*取得交换机广播的应用软件信息和BSP*/
FCUINT FC_NM_GetSwVersion(FCHANDLE hDev, FCUINT port, SW_IMPSoftWareVersion *pSwAppVersion, SW_IMPSoftWareVersion *pSwBspVersion);

/*上报软件版本*/
FCUINT FC_NM_GetFcSoftwareVersion(FC_SoftwareVersion *pFcSoftwareVersion);

/*取得交换机自检结果*/
FCUINT FC_NM_NC_GetSwBitResult(FCHANDLE hDev, FCINT port, FCUINT64 *pSwBitResult);

/*设置交换机方案号*/
FCUINT FC_NM_NC_SetMonitorScheme(FCHANDLE hDev, FCINT port, FCINT SchemeNo);

/*授权上网请求*/
FCUINT FC_NM_NC_GrantNrtOnNet(FCHANDLE hDev, FCUINT portId);

/*授权下网请求*/
FCUINT FC_NM_NC_GrantNrtOffNet(FCHANDLE hDev, FCUINT portId);

/*网络重构请求*/
FCUINT FC_NM_NC_NetRestruct(FCHANDLE hDev, FCUINT configNum);

/*取得网络节点自检结果*/
FCUINT FC_NM_NC_GetNrtBitResult(FCHANDLE hDev, FCUINT portId, FCUINT *pNrtBitResult);

/*取得网络节点统计信息*/
FCUINT FC_NM_NC_GetNetStatistics(FCHANDLE hDev, FCUINT portId, NetStatistics *pNetStatistics);

/*判断网络节点是否在网*/
FCUINT FC_NM_NRT_NcIsOnNet(FCHANDLE hDev, FCUINT *pNcIsOnNet);

/*发起上网请求*/
FCUINT FC_NM_NRT_OnNetReq(FCHANDLE hDev);

/*发起下网请求*/
FCUINT FC_NM_NRT_OffNetReq(FCHANDLE hDev);

/*使能WDT*/
FCUINT FC_NM_WDTEnable(FCHANDLE hDev, FCUINT mode);

/*禁止WDT*/
FCUINT FC_NM_WDTDisable(FCHANDLE hDev, FCUINT mode);

/*取得WDT信息*/
FCUINT FC_NM_GetWDTValue(FCHANDLE hDev, FCUINT *pWdt, FCUINT *pWdtLoader);

FCUINT FC_TM_BoardSyncRoleSet(FCHANDLE hDev, FCUINT role);

/*615调试函数 获取2个FC端口的link状态*/
FCUINT FC_DBG_GetAllPortStatus(FCHANDLE hDev, FCUINT *ports, FCUINT count);

/*注册内存拷贝函数*/
FCUINT FC_NP_RegMemCopyHandler(FC_MEMCPY_FUNCPTR func);


#endif /*__FH_130_API_H__*/

