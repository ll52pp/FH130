/******************************************************************************
* FH180/FH101测试用例
* 版本-V1.02
* 说明-适用于嵌入式和仿真平台的节点卡测试，拓扑支持点对点和多点交换式。
* 配置表说明
1 节点0 方案0 作为NCT
2 节点1 方案0 作为BNC
3 节点2 方案0 作为NRT
4 节点3 方案0 测试自环多通道收发字节数的正确性和性能
******************************************************************************/
#include <vxWorks.h>
#include <semLib.h>
#include <time.h>
#include "fc_api.h"
#include "..\hba.h"
#include "..\hw.h"

/*任务的状态*/
typedef enum
{
    HTS_PAUSE, /*暂停*/
    HTS_RUN,   /*运行*/
    HTS_STOP,  /*停止*/
} HBA_TASK_STATE;

/*任务描述*/
typedef int (* HBA_TASK_CALLBACK)(VOID *);

typedef struct
{
    INT32  id;             /*ID*/
    SEM_ID sem;            /*信号量*/
    int    flag;           /*标志信号量是否初始化*/
    char   name[16];       /*名称*/
    INT32  priority;       /*优先级*/
    INT32  stackSize;      /*栈大小*/
    HBA_TASK_STATE state;  /*任务的状态*/
    HBA_TASK_CALLBACK func;/*回调例程*/
} HBA_TASK_DESC;

/*通道描述*/
typedef struct
{
    int count;
    struct
    {
        int msg_id;
        int length;
    } msg_info[FC_CHANNEL_NUM_MAX];
} DEMO_CHANNEL_DESC;

typedef struct
{
    FCHANDLE h_dev;          /*设备句柄*/
    int config_block_no;     /*配置块号*/
    int scheme_no;           /*方案号*/
    int topo;                /*拓扑*/
    int nm_role;             /*网络管理角色*/
    HBA_TASK_DESC send_task; /*发送任务描述*/
    HBA_TASK_DESC recv_task; /*接收任务描述*/
    HBA_TASK_DESC online_task;/*维护网络状态*/
    char *send_buf;          /*发送缓冲区*/
    char *recv_poll_buf;     /*轮询接收缓冲区*/
    char *recv_int_buf;      /*中断接收缓冲区*/

    int send_count;          /*发送次数*/

    int asm_recv_mode;       /*ASM接收方式 0-轮询接收 1-中断接收*/
    DEMO_CHANNEL_DESC send_channels;
    DEMO_CHANNEL_DESC recv_channels;

    FC_ASM_RECVMSG_FUNCPTR asmRecvCallBack;/*ASM接收回调*/
    FC_INT_FUNCPTR eventCallBack;/*事件回调*/

    unsigned long long send_iu_ch[FC_CHANNEL_NUM_MAX];
    unsigned long long send_bytes_ch[FC_CHANNEL_NUM_MAX];
    unsigned long long send_iu_total;
    unsigned long long send_bytes_total;
    unsigned long long recv_iu_ch[FC_CHANNEL_NUM_MAX];
    unsigned long long recv_bytes_ch[FC_CHANNEL_NUM_MAX];
    unsigned long long recv_iu_total;
    unsigned long long recv_bytes_total;
} DEMO_DEV_CONTROL;

/*******************************************************************************
* 全局变量                                                                     *
*******************************************************************************/
#define FC_NT_VER_MAJOR                         1
#define FC_NT_VER_MINOR                         2
#define DEMO_DEV_NUM_MAX                     2
#define FC_ASM_IU_LENGTH_MAX                (16 * 1024 * 1024) /*按照FC协议，IU的最大字节长度16MB*/
#define MB_TOPO_LOOPBACK                      1                  /*自环测试*/
#define MB_TOPO_NET_MANAGER                2                  /*点对点测试*/
#define MB_RECV_MODE_POLL                     0                  /*轮询接收*/
#define MB_RECV_MODE_INT                       1                  /*中断接收*/

#define MB_NODE1_FCID        0x010000
#define MB_NODE2_FCID        0x010001
#define MB_NODE3_FCID        0x010002
#define MB_NODE4_FCID        0x010003

#define HBA_SEM_FLAG_CREATED    0xCEADCEAD
#define HBA_SEM_FLAG_DELETED    0

unsigned int g_dev_count = 0;
DEMO_DEV_CONTROL g_ddc[DEMO_DEV_NUM_MAX] = { 0 };

/*应用定义的蓝图的使用方式：
在配置设备前先调用FC_NP_SetBluePrint设置应用定义的蓝图，
配置设备时不再使用FLASH保存的蓝图
*/
#define DEMO_CONFIG_MODE
#ifdef DEMO_CONFIG_MODE
#include "config.c"
#endif

/******************************************************************************
 函数声明
******************************************************************************/
/******************************************************************************
函数名称：输出命令
******************************************************************************/
void CmdUsage();

/******************************************************************************
函数名称：设备自检
参数说明：
devId      - 设备ID，从0开始
chCount    - 通道个数
msgIdBase  - 消息ID的初始值
msgIdStep  - 消息ID递增的步长
ioByteBase - IO字节数的初始值
ioByteStep - IO字节数递增的步长
ioCount    - 发送消息的次数
******************************************************************************/
FCUINT CmdDevBit(FCUINT devId, FCUINT chCount, FCUINT msgIdBase, FCUINT ioByteBase, FCUINT ioByteStep, FCUINT ioCount);

FCUINT FC_NP_DevBit(FCUINT devId, FCUINT chCount, FCUINT msgIdBase, FCUINT ioByteBase, FCUINT ioByteStep, FCUINT ioCount);
/******************************************************************************
函数名称：自环测试
参数说明：
devId      - 设备ID，从0开始
ioByteBase - IO字节数的初始值
ioByteStep - IO字节数递增的步长
ioCount    - 发送消息的次数
******************************************************************************/
FCUINT CmdSetRing(FCUINT devId, FCUINT ioCount);

/******************************************************************************
函数名称：设置为NCT
参数说明：
devId      - 设备ID，从0开始
ioCount    - 发送消息的次数
******************************************************************************/
FCUINT CmdSetNct(FCUINT devId, FCUINT ioCount);

/******************************************************************************
函数名称：设置为NRT
参数说明：
devId      - 设备ID，从0开始
ioCount    - 发送消息的次数
******************************************************************************/
FCUINT CmdSetNrt(FCUINT devId, FCUINT ioCount);

/******************************************************************************
函数名称：打印统计信息
******************************************************************************/
void CmdPrintStat();

#if 0
/******************************************************************************
函数名称：加载蓝图文件写入FLASH
参数说明：
devId  - 设备ID，从0开始
hostIp - FTP服务器的IP地址
user   - FTP的用户名
pwd    - FTP的密码
******************************************************************************/
FCUINT CmdSaveBluePrintToFlash(FCUINT devId, char *hostIp, char *user, char *pwd);

/******************************************************************************
函数名称：烧录FPGA映像
参数说明：
devId    - 设备ID，从0开始
hostIp   - FTP服务器的IP地址
user     - FTP的用户名
pwd      - FTP的密码
fileName - FPGA映像文件名
******************************************************************************/
FCUINT CmdBurnFpgaImage(FCUINT devId, char *hostIp, char *user, char *pwd, char *fileName);
#endif

/******************************************************************************
函数名称：时间遍历测试
参数说明：
devId    - 设备ID，从0开始
******************************************************************************/
FCUINT CmdTimeEnum(FCUINT devId);

/******************************************************************************
函数名称：日期遍历测试
参数说明：
devId    - 设备ID，从0开始
dayCount - 天数
******************************************************************************/
FCUINT CmdDateEnum(FCUINT devId, FCUINT dayCount);

/******************************************************************************
函数名称：测试时间日期同步
参数说明：
devId    - 设备ID，从0开始
tm_role  - 时钟服务角色 0-时钟服务器 1-时钟客户端
times    - 测试的次数，两次测试之间延迟1000tick
******************************************************************************/
FCUINT CmdSyncDateTime(FCUINT devId, FCUINT tm_role, FCUINT ticks);

/******************************************************************************
* 内部函数
******************************************************************************/
/*开始发送接收*/
FCUINT CmdRun(FCUINT devid, FCUINT sendCount, FCUINT topo, FCUINT nm_role, FCUINT asm_recv_mode);

/*发送任务回调*/
int HbaDemoSendTask(VOID *context);

/*接收任务回调*/
int HbaDemoRecvTask(VOID *context);

/*维护网络状态任务回调*/
int HbaDemoOnLineTask(VOID *context);

/*ASM接收回调*/
FCUINT HbaDemoRecvCallBack(FCHANDLE hDev, FCUINT msgId);

/*事件中断的回调*/
FCUINT HbaDemoEventCallback(FCHANDLE hDev, FCUINT intCode, FCUINT param1);

#if 1/*to be deleted by liujin*/
/*查询设备*/
FCUINT CmdQueryDev(FCUINT topo, FCUINT nm_role);

FCUINT check_env(FCUINT devid);
#endif

/*退出*/
FCUINT CmdExit(FCUINT devid);

/*初始化配置*/
void InitAsmInfo(DEMO_DEV_CONTROL *ddc, int topo, int nm_role);

/*测试代码，获取pbit\cbit\统计信息*/
void GetInfo(FCHANDLE hDev);

/******************************************************************************
 函数定义
******************************************************************************/
/*输出命令*/
void CmdUsage()
{
    printf("\n");
    printf("---------------------------------------------------------------------\n");
    printf("测试版本号%d.%02d\n", FC_NT_VER_MAJOR, FC_NT_VER_MINOR);
    printf("输出命令：\n");
    printf("CmdUsage：\n");
    printf("\n");
    printf("设备自检：\n");
    printf("CmdDevBit  devid, chCount, msgIdBase, ioByteBase, ioByteStep, ioCount\n");
    printf("\n");
    printf("自环测试：\n");
    printf("CmdSetRing devId, ioCount\n");
    printf("\n");
    printf("设置为NCT：\n");
    printf("CmdSetNct  devId, ioCount\n");
    printf("\n");
    printf("设置为NRT：\n");
    printf("CmdSetNrt  devId, ioCount\n");
    printf("\n");
    printf("打印统计信息：\n");
    printf("CmdPrintStat\n");
    printf("\n");
#if 0
    printf("烧录蓝图文件：\n");
    printf("CmdSaveBluePrintToFlash    devId, hostIp, user, pwd\n");
    printf("\n");
    printf("烧录FPGA映像：\n");
    printf("CmdBurnFpgaImage devId, hostIp, user, pwd, fileName\n");
    printf("\n");
#endif    
    printf("测试RTC日期：\n");
    printf("CmdTimeEnum devId\n");
    printf("\n");
    printf("测试RTC时间：\n");
    printf("CmdDateEnum devId, dayCount\n");
    printf("\n");
    printf("测试时间日期同步：\n");
    printf("CmdSyncDateTime\n");
    printf("\n");
    printf("退出：\n");
    printf("CmdExit devid\n");    
}

#if 0/*added by liujin*/
UINT32 gDeviceCount = 0;

extern HBA_DEV_CB gHbaDevCB[];

/*设备关闭时的回调例程*/
VOID HbaDevShutDown()
{
    INT32 i;

    for (i = 0; i < MAX_DEVICE_NUM; ++i)
    {
        if (gHbaDevCB[i].status != HBA_DEV_STATUS_NONE)
        {
            hwSetPortRxEnab(gHbaDevCB[i].reg, 0);
        }
    }
}
/*查询设备*/
VOID HbaDevQuery(UINT32 *count)
{
    INT32 ret, i, busNo, deviceNo, funcNo;
    UINT32 membaseCsr;
    UINT8 irq;
    HBA_DEV_CB *dc;

    ASSERT(count != NULL);

    /*初始化设备上下文*/
    dc = gHbaDevCB;

    if (gDeviceCount == 0)
    {
        /*第1次查询设备，先初始化设备管理的全局数组*/
        for (i = 0; i < MAX_DEVICE_NUM; ++i)
        {
            ASSERT(dc->status == HBA_DEV_STATUS_NONE);
            memset(&dc[i], 0, sizeof(HBA_DEV_CB));
            dc[i].busNo = -1;    /*bus number*/
            dc[i].deviceNo = -1; /*device number*/
            dc[i].funcNo = -1;   /*function number*/
            dc[i].reg = NULL;
            dc[i].irq = 0xFF;
            dc[i].devId = -1;
            dc[i].status = HBA_DEV_STATUS_NONE;
            dc[i].configMode = 0;
            dc[i].configBlockIndex = 0xFFFFFFFF;
            dc[i].schemeIndex = 0xFFFFFFFF;
            dc[i].loadFlag = 0;
        }
    }
    
#ifdef ACORES653    
    /* rebootHookAdd((FUNCPTR)HbaDevShutDown); */
#else
    rebootHookAdd((FUNCPTR)HbaDevShutDown);
#endif

    for (i = 0; i < DEV_NUM_MAX; ++i)
    {
#ifdef ACORES653
        ret = pcieFindDevice(PCIE_IFNUM, HBA_VENDOR_ID, HBA_DEVICE_ID, i, &busNo, &deviceNo, &funcNo);
#else
        ret = pciFindDevice(HBA_VENDOR_ID, HBA_DEVICE_ID, i, &busNo, &deviceNo, &funcNo);
#endif

        if (ret == OK)
        {
#ifdef ACORES653
            pcieConfigInLong(PCIE_IFNUM, busNo, deviceNo, funcNo, PCI_CFG_BASE_ADDRESS_0, &membaseCsr);
            pcieConfigInByte(PCIE_IFNUM, busNo, deviceNo, funcNo, PCI_CFG_DEV_INT_LINE, &irq);
#else
            pciConfigInLong(busNo, deviceNo, funcNo, PCI_CFG_BASE_ADDRESS_0, &membaseCsr);
            pciConfigInByte(busNo, deviceNo, funcNo, PCI_CFG_DEV_INT_LINE, &irq);
#endif
            if (HbaDevFindDevCB(busNo, deviceNo, funcNo, membaseCsr) == FALSE)
            {
                /*新的设备没有记录过*/
                dc = &gHbaDevCB[gDeviceCount];
                dc->busNo = busNo;
                dc->deviceNo = deviceNo;
                dc->funcNo = funcNo;
                dc->reg = (REG_HW *)membaseCsr;
                dc->irq = irq;
                dc->useInt = bUseInterrupt;
                dc->devId = gDeviceCount;
                dc->status = HBA_DEV_STATUS_INITED;

                gDeviceCount++;
            }
        }
    }
    *count = gDeviceCount;
}

/******************************************************************************/
/*查询设备*/
FCUINT FC_NP_DevQuery(FCUINT *count)
{
    if (count == NULL)
    {
        return FC_PARAMS_INVALID;
    }
    HbaDevQuery(count);
    return FC_SUCCESS;
}
#endif
/******************************************************************************
函数名称：设备自检
参数说明：
devId      - 设备ID，从0开始
chCount    - 通道个数
msgIdBase  - 消息ID的初始值
msgIdStep  - 消息ID递增的步长
ioByteBase - IO字节数的初始值
ioByteStep - IO字节数递增的步长
ioCount    - 发送消息的次数
******************************************************************************/
#if 1
FCUINT CmdDevBit(FCUINT devId, FCUINT chCount, FCUINT msgIdBase, FCUINT ioByteBase, FCUINT ioByteStep, FCUINT ioCount)
{
    FCUINT ret;

    ret = FC_NP_DevBit(devId, chCount, msgIdBase, ioByteBase, ioByteStep, ioCount);
    if (ret)
    {
        printf("FC_NP_DevBit failed ret=0x%08x\n", ret);
    }
    else
    {
        printf("FC_NP_DevBit success\n");
    }

    return ret;
}
#endif

/*自环测试*/
FCUINT CmdSetRing(FCUINT devId, FCUINT ioCount)
{
    FCUINT ret, sendCount;

    if (devId >= DEMO_DEV_NUM_MAX)
    {
        printf("invalid devId=%d DEMO_DEV_NUM_MAX=%d\n", devId, DEMO_DEV_NUM_MAX);
        return FC_PARAMS_INVALID;
    }

    if (ioCount == 0)
    {
        printf("invalid ioCount=%d\n", ioCount);
        return FC_PARAMS_INVALID;
    }

    sendCount = ioCount;
    ret = CmdRun(devId, sendCount, MB_TOPO_LOOPBACK, FC_NET_ROLE_NC, MB_RECV_MODE_INT);
    if (ret)
    {
        printf("CmdRun failed ret=0x%08x\n", ret);
    }
    else
    {
        printf("CmdRun success\n");
    }

    return ret;
}

/*设置为NC*/
FCUINT CmdSetNct(FCUINT devId, FCUINT ioCount)
{
    FCUINT ret, sendCount;

    if (devId >= DEMO_DEV_NUM_MAX)
    {
        printf("invalid devId=%d DEMO_DEV_NUM_MAX=%d\n", devId, DEMO_DEV_NUM_MAX);
        return FC_PARAMS_INVALID;
    }

    if (ioCount == 0)
    {
        printf("invalid ioCount=%d\n", ioCount);
        return FC_PARAMS_INVALID;
    }

    sendCount = ioCount;
    ret = CmdRun(devId, sendCount, MB_TOPO_NET_MANAGER, FC_NET_ROLE_NC, MB_RECV_MODE_INT);/*MB_RECV_MODE_INT*/
    if (ret)
    {
        printf("CmdRun failed ret=0x%08x\n", ret);
    }
    else
    {
        printf("CmdRun success\n");
    }

    return ret;
}

/*设置为NRT*/
FCUINT CmdSetNrt(FCUINT devId, FCUINT ioCount)
{
    FCUINT ret, sendCount;

    if (devId >= DEMO_DEV_NUM_MAX)
    {
        printf("invalid devId=%d DEMO_DEV_NUM_MAX=%d\n", devId, DEMO_DEV_NUM_MAX);
        return FC_PARAMS_INVALID;
    }

    if (ioCount == 0)
    {
        printf("invalid ioCount=%d\n", ioCount);
        return FC_PARAMS_INVALID;
    }

    sendCount = ioCount;
    ret = CmdRun(devId, sendCount, MB_TOPO_NET_MANAGER, FC_NET_ROLE_NRT, MB_RECV_MODE_INT);/*MB_RECV_MODE_INT*/
    if (ret)
    {
        printf("CmdRun failed ret=0x%08x\n", ret);
    }
    else
    {
        printf("CmdRun success\n");
    }

    return ret;
}

/*打印统计信息*/
void CmdPrintStat()
{
    int k, i;
    DEMO_DEV_CONTROL *ddc;

    /*打印软件的统计信息*/
    for (k = 0; k < g_dev_count; ++k)
    {
        ddc = &g_ddc[k];
        if (ddc->h_dev == 0) 
        {    
            continue;
        }

        printf("devid=%d\n", k);
        for (i = 0; i < ddc->send_channels.count; ++i)
        {
            if (ddc->send_iu_ch[i] == 0 && ddc->send_bytes_ch[i] == 0) 
            {
                continue;
            }
            printf("  [send][msgId=%08x]iu=%lld bytes=%lld\n", ddc->send_channels.msg_info[i].msg_id, ddc->send_iu_ch[i], ddc->send_bytes_ch[i]);
        }
        printf("  [send sum]iu=%lld bytes=%lld\n", ddc->send_iu_total, ddc->send_bytes_total);
        for (i = 0; i < ddc->recv_channels.count; ++i)
        {
            if (ddc->recv_iu_ch[i] == 0 && ddc->recv_bytes_ch[i] == 0) 
            {
                continue;
            }
            printf("  [recv][msgId=%08x]iu=%lld bytes=%lld\n", ddc->recv_channels.msg_info[i].msg_id, ddc->recv_iu_ch[i], ddc->recv_bytes_ch[i]);
        }
        printf("  [recv sum]iu=%lld bytes=%lld\n", ddc->recv_iu_total, ddc->recv_bytes_total);
    }
}

#if 0
/*加载蓝图文件文件写入FLASH*/
FCUINT CmdSaveBluePrintToFlash(FCUINT devId, char *hostIp, char *user, char *pwd)
{
    FCUINT ret, count;
    FC_FTP_PARAM ftpParam;
    FCHANDLE hDev;

    if (hostIp == NULL)
    {
        printf("invalid hostIp=%p\n", hostIp);
        return FC_PARAMS_INVALID;
    }
    if (user == NULL)
    {
        printf("invalid user=%p\n", user);
        return FC_PARAMS_INVALID;
    }
    if (pwd == NULL)
    {
        printf("invalid pwd=%p\n", pwd);
        return FC_PARAMS_INVALID;
    }

#if 0
    /*查询设备*/
    ret = FC_NP_DevQuery(&count);
    if (ret)
    {
        printf("FC_NP_DevQuery failed ret=0x%08x\n", ret);
        return ret;
    }
    printf("FC_NP_DevQuery success dev count=%d\n", count);

    if (count == 0)
    {
        printf("device not found\n");
        return FC_NOT_FOUND_DEVICE;
    }

    if (devId >= count)
    {
        printf("invalid devId=%d dev count=%d\n", devId, count);
        return FC_PARAMS_INVALID;
    }
#endif

    /*打开设备*/
    ret = FC_NP_Open(&hDev, devId);
    if (ret)
    {
        printf("[devid=%d]FC_NP_Open failed ret=0x%08x\n", devId, ret);
        return ret;
    }
    printf("[devid=%d]FC_NP_Open success h_dev=%p\n", devId, hDev);
    
#if 0
    /*保存蓝图到FLASH*/
    memset(&ftpParam, 0, sizeof(FC_FTP_PARAM));
    memcpy(ftpParam.hostIp, hostIp, strlen(hostIp));
    memcpy(ftpParam.user, user, strlen(user));
    memcpy(ftpParam.pwd, pwd, strlen(pwd));
    printf("[devid=%d tick=%d]burn blue print...\n", devId, tickGet());
    ret = FC_NP_SaveBluePrint(hDev, &ftpParam);
    if (ret)
    {
        printf("[devid=%d]FC_NP_SaveBluePrint failed ret=0x%08x\n", devId, ret);
        return ret;
    }
    printf("[devid=%d tick=%d]FC_NP_SaveBluePrint success\n", devId, tickGet());
#endif

    /*关闭设备*/
    ret = FC_NP_Close(hDev);
    if (ret)
    {
        printf("[devid=%d]FC_NP_Close failed ret=0x%08x\n", devId, ret);
        return ret;
    }
    printf("[devid=%d]FC_NP_Close success\n", devId);

    return ret;
}

/*烧录FPGA映像*/
FCUINT CmdBurnFpgaImage(FCUINT devId, char *hostIp, char *user, char *pwd, char *fileName)
{
    FCUINT ret, count;
    FC_FTP_PARAM ftpParam;
    FCHANDLE hDev;

    if (hostIp == NULL)
    {
        printf("invalid hostIp=%p\n", hostIp);
        return;
    }
    if (user == NULL)
    {
        printf("invalid user=%p\n", user);
        return;
    }
    if (pwd == NULL)
    {
        printf("invalid pwd=%p\n", pwd);
        return;
    }
    if (fileName == NULL)
    {
        printf("invalid fileName=%p\n", fileName);
        return;
    }

    /*查询设备*/
    ret = FC_NP_DevQuery(&count);
    if (ret)
    {
        printf("FC_NP_DevQuery failed ret=0x%08x\n", ret);
        return ret;
    }
    printf("FC_NP_DevQuery success dev count=%d\n", count);

    if (count == 0)
    {
        printf("device not found\n");
        return FC_NOT_FOUND_DEVICE;
    }

    if (devId >= count)
    {
        printf("invalid devId=%d dev count=%d\n", devId, count);
        return FC_PARAMS_INVALID;
    }

    /*打开设备*/
    ret = FC_NP_DevOpen(&hDev, devId);
    if (ret)
    {
        printf("[devid=%d]FC_NP_DevOpen failed ret=0x%08x\n", devId, ret);
        return ret;
    }
    printf("[devid=%d]FC_NP_DevOpen success h_dev=%p\n", devId, hDev);

    /*写FPGA映像文件*/
    printf("[devid=%d tick=%d]burn fpga image...\n", devId, tickGet());

    memset(&ftpParam, 0, sizeof(FC_FTP_PARAM));
    memcpy(ftpParam.hostIp, hostIp, strlen(hostIp));
    memcpy(ftpParam.user, user, strlen(user));
    memcpy(ftpParam.pwd, pwd, strlen(pwd));

    ret = FC_NP_BurnFpgaImage(hDev, &ftpParam, fileName);
    if (ret)
    {
        printf("[devid=%d]FC_NP_BurnFpgaImage failed ret=0x%08x\n", devId, ret);
        return ret;
    }
    printf("[devid=%d tick=%d]FC_NP_BurnFpgaImage success\n", devId, tickGet());

    /*关闭设备*/
    ret = FC_NP_DevClose(hDev);
    if (ret)
    {
        printf("[devid=%d]FC_NP_DevClose failed ret=0x%08x\n", devId, ret);
        return ret;
    }
    printf("[devid=%d]FC_NP_DevClose success\n", devId);

    return ret;
}
#endif

/*时间遍历测试*/
FCUINT CmdTimeEnum(FCUINT devId)
{
    FCUINT ret, dev_open_flag, count, i, flag, k;
    FCUCHAR str[12];
    FCHANDLE hDev;
    FCDate get_date;
    FCTime set_time, get_time;
    time_t s;
    struct tm *t;

    dev_open_flag = 0;
    hDev = NULL;

    do
    {
#if 0
        /*查询设备*/
        ret = FC_NP_DevQuery(&count);
        if (ret)
        {
            break;
        }
        if (count == 0)
        {
            break;
        }
        if (devId >= count)
        {
            break;
        }
#endif

        /*打开设备*/
        ret = FC_NP_Open(&hDev, devId);
        if (ret)
        {
            break;
        }
        dev_open_flag = 1;

        s = time(NULL);
        ret = FC_SUCCESS;
        count = 24 * 3600;
        for (i = 0; i < count; ++i)
        {
            t = localtime(&s);
            s++;

            memset(&set_time, 0, sizeof(FCTime));

            /*设置时间*/
            set_time.hour = t->tm_hour;
            set_time.minute = t->tm_min;
            set_time.second = t->tm_sec;
            set_time.millisecond = 1;
            set_time.microsecond = 1;
            set_time.nanosecond = 1;

            ret = FC_TM_SetRtc(hDev, &set_time);
            if (ret)
            {
                printf("FC_TM_SetTime failed ret=0x%08x\n", ret);
                break;
            }

            /*获取RTC*/
            memset(&get_date, 0, sizeof(FCDate));
            memset(&get_time, 0, sizeof(FCTime));
            ret = FC_TM_GetDateTime(hDev, &get_date, &get_time);
            if (ret)
            {
                printf("FC_TM_GetRtc failed ret=0x%08x\n", ret);
                break;
            }

            /*判断*/
            memset(str, '_', sizeof(str));
            flag = 0;
            if (set_time.hour != get_time.hour
                || set_time.minute != get_time.minute
                || set_time.second != get_time.second
                /*
                || set_time.millisecond != get_time.millisecond
                || set_time.microsecond != get_time.microsecond
                || set_time.nanosecond != get_time.nanosecond*/)
            {
                flag = 1;
                if (set_time.hour != get_time.hour) { str[0] = str[1] = 'H'; }
                if (set_time.minute != get_time.minute) { str[2] = str[3] = 'M'; }
                if (set_time.second != get_time.second) { str[4] = str[5] = 'S'; }
                if (set_time.millisecond != get_time.millisecond) { str[6] = 'M'; str[7] = 'S'; }
                if (set_time.microsecond != get_time.microsecond) { str[8] = 'M'; str[9] = 'I'; }
                if (set_time.nanosecond != get_time.nanosecond) { str[10] = 'N'; str[11] = 'A'; }
            }

            if (flag == 1)
            {
                for (k = 0; k < sizeof(str); ++k) printf("%c", str[k]);
                printf(" set time[%02d:%02d:%02d %03d:%03d:%03d] get time[%02d:%02d:%02d %03d:%03d:%03d]\n",
                    set_time.hour, set_time.minute, set_time.second, set_time.millisecond, set_time.microsecond, set_time.nanosecond,
                    get_time.hour, get_time.minute, get_time.second, get_time.millisecond, get_time.microsecond, get_time.nanosecond);
                ret = FC_FAILURE;
                break;
            }
        }
        
        if (ret)
        {
            printf("time enum error\n");
            break;
        }
        printf("time enum success\n");
    } while (FALSE);

    if (dev_open_flag)
    {
        FCUINT t;
        t = FC_NP_Close(hDev);
        if (t)
        {
            printf("FC_NP_Close failed ret=0x%08x\n", ret);
        }
    }

    return ret;
}

/*日期遍历测试*/
FCUINT CmdDateEnum(FCUINT devId, FCUINT dayCount)
{
    FCUINT ret, dev_open_flag, count;
    FCUCHAR str[12];
    FCHANDLE hDev;
    FCDate set_date, get_date;
    FCTime get_time;
    time_t s;
    struct tm *t;
    HBA_DEV_CB *dc;

    dev_open_flag = 0;
    hDev = NULL;

    do
    {
#if 0
        /*查询设备*/
        ret = FC_NP_DevQuery(&count);
        if (ret)
        {
            break;
        }
        if (count == 0)
        {
            break;
        }
        if (devId >= count)
        {
            break;
        }
#endif

        /*打开设备*/
        ret = FC_NP_Open(&hDev, devId);
        if (ret)
        {
            break;
        }
        dev_open_flag = 1;
 #if 1/*temp by liujin FH130的FC_TM_SetDate要求设备状态为HBA_DEV_STATUS_INITED或HBA_DEV_STATUS_STARTED*/    
        dc = (HBA_DEV_CB *)hDev;
        dc->status = HBA_DEV_STATUS_INITED;
 #endif
        s = time(NULL);
        while (dayCount-- > 0)
        {
            t = localtime(&s);

            /*设置日期*/
            set_date.year = t->tm_year + 1900;/*从1900年开始的年数*/
            set_date.month = t->tm_mon + 1; /*[0:11]*/
            set_date.day = t->tm_mday;

            ret = FC_TM_SetDate(hDev, &set_date);
            if (ret)
            {
                printf("FC_TM_SetDate failed ret=0x%08x\n", ret);
                break;
            }

            memset(&get_date, 0, sizeof(FCDate));
            ret = FC_TM_GetDateTime(hDev, &get_date, &get_time);
            if (ret)
            {
                printf("FC_TM_GetRtc failed ret=0x%08x\n", ret);
                break;
            }

            /*比较日期*/
            if (set_date.year != get_date.year || set_date.month != get_date.month || set_date.day != get_date.day)
            {
                printf("set date[%04d-%02d-%02d] get date[%04d-%02d-%02d]\n", set_date.year, set_date.month, set_date.day, get_date.year, get_date.month, get_date.day);
                ret = FC_FAILURE;
                break;
            }
            s += 24 * 3600;
        }
        
        if (ret)
        {
            printf("date enum error\n");
            break;
        }
        printf("date enum success\n");
    } while (FALSE);

    if (dev_open_flag)
    {
        FCUINT t;
        t = FC_NP_Close(hDev);
        if (t)
        {
            printf("FC_NP_Close failed ret=0x%08x\n", ret);
        }
    }

    return ret;
}

/*时间日期同步测试*/
FCUINT CmdSyncDateTime(FCUINT devId, FCUINT tm_role, FCUINT count)
{
    FCUINT ret, dev_open_flag, dev_count, i;
    FCUCHAR str[12];
    FCHANDLE hDev;
    FCDate set_date, get_date;
    FCTime set_time, get_time;
    time_t s;
    struct tm *t;

    dev_open_flag = 0;
    hDev = NULL;

    if (tm_role != FC_NET_CLK_SYNC_ROLE_SERVER_MASTER && tm_role != FC_NET_CLK_SYNC_ROLE_CLIENT)
    {
        return FC_PARAMS_INVALID;
    }
    if (count >= 100)
    {
        return FC_PARAMS_INVALID;
    }

    if (count == 0) count = 10;
    do
    {
#if 0
        /*查询设备*/
        ret = FC_NP_DevQuery(&dev_count);
        if (ret)
        {
            break;
        }
        if (dev_count == 0)
        {
            break;
        }
        if (devId >= dev_count)
        {
            break;
        }
#endif
        /*打开设备*/
        ret = FC_NP_Open(&hDev, devId);
        if (ret)
        {
            break;
        }
        dev_open_flag = 1;

#if 0
        /*调试模式：直接使用应用定义的蓝图，不使用FLASH保存的配置块*/
        ret = FC_NP_SetBluePrint(hDev, &gBluePrint);
        if (ret)
        {
            printf("[devid=%d]FC_NP_SetBluePrint failed ret=0x%08x\n", devId, ret);
            return;
        }
        printf("[devid=%d]FC_NP_SetBluePrint success\n", devId);
#endif

        if (tm_role == FC_NET_CLK_SYNC_ROLE_SERVER_MASTER)
        {
            /*配置设备*/
            ret = FC_NP_LoadConfig(hDev, 0, 0);
            if (ret)
            {
                printf("[devid=%d]FC_NP_LoadConfig failed ret=0x%08x\n", devId, ret);
                return;
            }
            printf("[devid=%d]FC_NP_LoadConfig success\n", devId);
        }
        else
        {
            /*配置设备*/
            ret = FC_NP_LoadConfig(hDev, 0, 2);
            if (ret)
            {
                printf("[devid=%d]FC_NP_LoadConfig failed ret=0x%08x\n", devId, ret);
                return;
            }
            printf("[devid=%d]FC_NP_LoadConfig success\n", devId);
        }

        /*设置时钟同步使能*/
        ret = FC_TM_SyncEnable(hDev);
        if (ret)
        {
            printf("FC_TM_SetSyncEnab failed ret=0x%08x\n", ret);
            break;
        }
        printf("FC_TM_SetSyncEnab success\n");

        /*设置WDT定时器使能或禁止*/
        if (tm_role == FC_NET_CLK_SYNC_ROLE_SERVER_MASTER)
        {
            /*MCT需要使能WDT周期发送心跳*/
            ret = FC_NM_WDTEnable(hDev, FC_WDT_NET_MODE);
            if (ret)
            {
                printf("FC_NM_SetWdtPeriodEnab failed ret=0x%08x\n", ret);
                return;
            }
            printf("FC_NM_SetWdtPeriodEnab success wdt period is enab\n");
        }

        s = time(NULL);
        for (i = 0; i < count; ++i)
        {
            if (tm_role == FC_NET_CLK_SYNC_ROLE_SERVER_MASTER)
            {
                t = localtime(&s);
                memset(&set_date, 0, sizeof(FCDate));
                /*设置日期*/
                set_date.year = t->tm_year + 1900;/*从1900年开始的年数*/
                set_date.month = t->tm_mon + 1; /*[0:11]*/
                set_date.day = t->tm_mday;
                ret = FC_TM_SetDate(hDev, &set_date);
                if (ret)
                {
                    printf("FC_TM_SetDate failed ret=0x%08x\n", ret);
                    break;
                }

                /*设置时间*/
                memset(&set_time, 0, sizeof(FCTime));

                /*设置时间*/
                set_time.hour = t->tm_hour;
                set_time.minute = t->tm_min;
                set_time.second = t->tm_sec;
                set_time.millisecond = 1;
                set_time.microsecond = 1;
                set_time.nanosecond = 1;
                printf("[tick=%02d]date[%04d-%02d-%02d] time[%02d:%02d:%02d %03d:%03d:%03d] nm_role=FC_NET_CLK_SYNC_ROLE_SERVER_MASTER\n",
                    i, set_date.year, set_date.month, set_date.day,
                    set_time.hour, set_time.minute, set_time.second, set_time.millisecond, set_time.microsecond, set_time.nanosecond);
                ret = FC_TM_SetRtc(hDev, &set_time);
                if (ret)
                {
                    printf("FC_TM_SetRtc failed ret=0x%08x\n", ret);
                    break;
                }

                s += 24 * 3600 + 25;
            }
            else
            {
                /*memset(&get_date, 0, sizeof(FC_DATE));*/
                memset(&get_time, 0, sizeof(FCTime));
                ret = FC_TM_GetRtc(hDev, &get_time);
                if (ret)
                {
                    printf("FC_TM_GetRtc failed ret=0x%08x\n", ret);
                    break;
                }
                printf("[tick=%02d]date[%04d-%02d-%02d] time[%02d:%02d:%02d %03d:%03d:%03d] nm_role=FC_NET_CLK_SYNC_ROLE_CLIENT\n",
                    i, get_date.year, get_date.month, get_date.day,
                    get_time.hour, get_time.minute, get_time.second, get_time.millisecond, get_time.microsecond, get_time.nanosecond);
            }

            taskDelay(200);
        }
        printf("sync date & time success\n");
    } while (FALSE);

    if (dev_open_flag)
    {
        FCUINT t;
        t = FC_NP_Close(hDev);
        if (t)
        {
            printf("FC_NP_Close failed ret=0x%08x\n", ret);
        }
    }

    return ret;
}

/******************************************************************************
* 内部函数
******************************************************************************/
/*开始发送接收*/
FCUINT CmdRun(FCUINT devid, FCUINT sendCount, FCUINT topo, FCUINT nm_role, FCUINT asm_recv_mode)
{
    int i, k, err,state,waitID;
    char tt;
    FCUINT ret, count, devID, workState, portStatus, t_nm_role, fcid;
    DEMO_DEV_CONTROL *ddc;
    HBA_TASK_DESC *t;

#if 1/*to be deleted by liujin*/
    /*查询设备*/
    ret = CmdQueryDev(topo, nm_role);
    if (ret)
    {
        return;
    }

    if (check_env(devid))
    {
        return;
    }
#endif
    /*配置节点卡*/
    ddc = &g_ddc[devid];
    ddc->topo = topo;
    ddc->nm_role = nm_role;
    ddc->send_count = sendCount;
    ddc->asm_recv_mode = asm_recv_mode;
    
    /*打开设备*/
    ret = FC_NP_Open(&ddc->h_dev, devid);
    if (ret)
    {
        printf("[devid=%d]FC_NP_Open failed ret=0x%08x\n", devid, ret);
        return;
    }
    printf("[devid=%d]FC_NP_Open success h_dev=%p\n", devid, ddc->h_dev);
    
    /*注册事件回调函数*/
    ret = FC_NP_RegEvtHandler(ddc->h_dev, HbaDemoEventCallback);
    if (ret)
    {
        printf("[devid=%d]FC_NP_RegEvtHandler failed ret=0x%08x\n", devid, ret);
        return;
    }
    printf("[devid=%d]FC_NP_RegEvtHandler success\n", devid);

    ddc->send_buf = (char *)malloc(FC_ASM_IU_LENGTH_MAX);
    if (ddc->send_buf == NULL)
    {
        printf("malloc send buf failed\n");
        return ;
    }

    ddc->recv_poll_buf = (char *)malloc(FC_ASM_IU_LENGTH_MAX);
    if (ddc->recv_poll_buf == NULL)
    {
        printf("malloc recv poll buf failed\n");
        return ;
    }

    ddc->recv_int_buf = (char *)malloc(FC_ASM_IU_LENGTH_MAX);
    if (ddc->recv_int_buf == NULL)
    {
        printf("malloc recv int buf failed\n");
        return ;
    }

    if (ddc->asm_recv_mode == MB_RECV_MODE_INT)
    {
        /*注册中断接收ASM消息的回调函数*/
        ret = FC_NP_RegMsgHandler(ddc->h_dev, HbaDemoRecvCallBack);
        if (ret)
        {
            printf("[devid=%d]FC_NP_RegMsgHandler failed ret=0x%08x\n", ret);
            return;
        }
        printf("[devid=%d]FC_NP_RegMsgHandler success\n", devid);
    }

    /*获取工作状态 0-设备工作正常*/
    ret = FC_NP_GetWorkStatus(ddc->h_dev, &workState);
    if (ret)
    {
        printf("[devid=%d]FC_NP_GetWorkStatus failed ret=0x%08x\n", devid, ret);
        return;
    }
    printf("[devid=%d]FC_NP_GetWorkStatus success\n", devid);
    if (workState != OK)
    {
        printf("[devid=%d]dev work state error\n", devid);
        return;
    }
    printf("[devid=%d]dev work state ok\n", devid);

#if 0
    /*调试模式：直接使用应用定义的蓝图，不使用FLASH保存的配置块*/
    ret = FC_NP_SetBluePrint(ddc->h_dev, &gBluePrint);
    if (ret)
    {
        printf("[devid=%d]FC_NP_SetBluePrint failed ret=0x%08x\n", devid, ret);
        return;
    }
    printf("[devid=%d]FC_NP_SetBluePrint success\n", devid);
#endif    

    /*配置设备*/
    ret = FC_NP_LoadConfig(ddc->h_dev, ddc->config_block_no, ddc->scheme_no);
    if (ret)
    {
        printf("[devid=%d]FC_NP_LoadConfig failed ret=0x%08x\n", devid, ret);
        return;
    }
    printf("[devid=%d]FC_NP_LoadConfig success\n", devid);

    /*获取网络管理角色*/
    ret = FC_NM_RoleGet(ddc->h_dev, &t_nm_role);
    if (ret)
    {
        printf("[devid=%d]FC_NM_RoleGet failed ret=0x%08x\n", devid, ret);
        return;
    }
    printf("[devid=%d]FC_NM_RoleGet success nm_role=%d\n", devid, t_nm_role);
    if (nm_role != t_nm_role)
    {
        printf("[devid=%d]nm_role=%d t_nm_role=%d\n", devid, nm_role, t_nm_role);
        return ;
    }

#if 0
    /*设置时钟同步使能*/
    ret = FC_TM_SetSyncEnab(ddc->h_dev, FC_TM_SYNC_ENAB);
    if (ret)
    {
        printf("FC_TM_SetSyncEnab failed ret=0x%08x\n", ret);
        return;
    }
    printf("[devid=%d]FC_TM_SetSyncEnab success tm sync is enab\n", devid);
#endif

    /*设置WDT定时器使能或禁止*/
    if (nm_role == FC_NET_ROLE_NC)
    {
        /*MCT需要使能WDT周期发送心跳*/
        ret = FC_NM_WDTEnable(ddc->h_dev, FC_WDT_NET_MODE);
        if (ret)
        {
            printf("[devid=%d]FC_NM_WDTEnable failed ret=0x%08x\n", devid, ret);
            return;
        }
        printf("[devid=%d]FC_NM_WDTEnable success wdt period is enab\n", devid);
    }
    printf("[devid=%d]dev is run\n", devid);

    if (ddc->topo == MB_TOPO_NET_MANAGER && ddc->nm_role != FC_NET_ROLE_NC)
    {
        /*启动维护网络状态任务*/
        t = &ddc->online_task;
        t->state = HTS_RUN;
        t->id = taskSpawn(t->name, t->priority, 0, t->stackSize, t->func, (int)ddc, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        if (t->id == ERROR)
        {
            printf("[devid=%d]start online task failed\n", devid);
            return;
        }
        printf("[devid=%d]start online success\n", devid);
    }

    if (ddc->asm_recv_mode == MB_RECV_MODE_POLL)
    {
        /*启动接收*/
        t = &ddc->recv_task;
        printf("[devid=%d]HbaDemoRecvTask=%p t->func=%p\n", devid, HbaDemoRecvTask, t->func);
        t->state = HTS_RUN;
        t->id = taskSpawn(t->name, t->priority, 0, t->stackSize, t->func, (int)ddc, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        if (t->id == ERROR)
        {
            printf("[devid=%d]start recv task failed\n", devid);
            return;
        }
        printf("[devid=%d]start recv success\n", devid);
    }

    taskDelay(10);
    /*启动发送*/
    t = &ddc->send_task;
    printf("[devid=%d]HbaDemoSendTask=%p t->func=%p\n", devid, HbaDemoSendTask, t->func);
    t->state = HTS_RUN;
    t->id = taskSpawn(t->name, t->priority, 0, t->stackSize, t->func, (int)ddc, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if (t->id == ERROR)
    {
        printf("[devid=%d]start send task failed\n", devid);
        return;
    }
    printf("[devid=%d]start send success\n", devid);

    return ret;
}

/*维护网路状态任务*/
int HbaDemoOnlineTask(VOID *context)
{
    FCUINT ret, state;
    DEMO_DEV_CONTROL *ddc;
    HBA_TASK_DESC *task;

    ddc = (DEMO_DEV_CONTROL *)context;

    task = &ddc->online_task;
    while (task->state != HTS_STOP)
    {
        /*任务的状态是暂停*/
        if (task->state == HTS_PAUSE)
        {
            taskDelay(1);
            continue;
        }

        /*semTake(task->sem, WAIT_FOREVER);*/
        taskDelay(10);
        do
        {
            if (task->state != HTS_RUN)
            {
                break;
            }

            /*TODO:查询本地节点是否在线*/
            ret = FC_NM_GetOnNetState(ddc->h_dev, &state);
            if (ret)
            {
                printf("FC_NM_GetOnNetState failed ret=0x%08x\n", ret);
                break;
            }

            if (state == 1)
            {
                /*本地节点在线*/
                break;
            }

            /*查询NCT是否在线*/
            ret = FC_NM_NRT_NcIsOnNet(ddc->h_dev, &state);
            if (ret)
            {
                printf("FC_NM_NRT_NcIsOnNet failed ret=0x%08x\n", ret);
                break;
            }

            if (state == 0)
            {
                /*NCT不在线*/
                break;
            }

            /*发起上网请求*/
            ret = FC_NM_NRT_OnNetReq(ddc->h_dev);
            if (ret)
            {
                printf("FC_NM_NRT_OnNetReq failed ret=0x%08x\n", ret);
                taskDelay(2);
            }
        } while (1);
    }
    printf("[h_dev=%p]online task exit\n", ddc->h_dev);

    task->id = ERROR;

    return 0;
}

/*发送任务*/
int HbaDemoSendTask(VOID *context)
{
    FCINT send_count;
    FCUINT ret, msgId, nLen, ch_idx;
    FCUCHAR *pMsg;
    DEMO_DEV_CONTROL *ddc;
    DEMO_CHANNEL_DESC *cd;
    HBA_TASK_DESC *task;

    ddc = (DEMO_DEV_CONTROL *)context;
    memset(ddc->send_buf, 0, FC_ASM_IU_LENGTH_MAX);
    pMsg = ddc->send_buf;

    task = &ddc->send_task;
    cd = &ddc->send_channels;

    send_count = 0;
    while (task->state != HTS_STOP)
    {
        /*任务的状态是暂停*/
        if (task->state == HTS_PAUSE)
        {
            taskDelay(1);
            continue;
        }
        for (ch_idx = 0; ch_idx < cd->count && task->state != HTS_STOP; ++ch_idx)
        {
            if(cd->msg_info[ch_idx].msg_id == 1) continue;
            while (task->state != HTS_STOP)
            {
                msgId = cd->msg_info[ch_idx].msg_id;
                nLen = cd->msg_info[ch_idx].length;
                ret = FC_NP_SendMsg(ddc->h_dev, msgId, pMsg, nLen);
                if (ret)
                {
                    /*可能因为发送缓冲区已满或对端没有在线*/
                    taskDelay(10);
                    continue;
                }                                
                break;
            }

            /*记录统计数据*/
            ddc->send_iu_ch[ch_idx]++;
            ddc->send_bytes_ch[ch_idx] += nLen;
            ddc->send_iu_total++;
            ddc->send_bytes_total += nLen;
        }
        send_count++;
        if (send_count % 100 == 0)
        {
            printf("[send asm count=%d]msgId=0x%08x nLen=%d\n", send_count, msgId, nLen);
            taskDelay(10);
        }
        if (send_count == ddc->send_count) break;
    }
    printf("[h_dev=%p]send task exit\n", ddc->h_dev);

    task->id = ERROR;

    return 0;
}


/*接收任务*/
int HbaDemoRecvTask(VOID *context)
{
    FCUINT ret, msgId, nLen, ch_idx;
    FCUCHAR *pMsg;
    DEMO_DEV_CONTROL *ddc;
    DEMO_CHANNEL_DESC *cd;
    HBA_TASK_DESC *task;
    UINT recv_count;

    ddc = (DEMO_DEV_CONTROL *)context;
    pMsg = ddc->recv_poll_buf;
    memset(pMsg, 0, FC_ASM_IU_LENGTH_MAX);

    task = &ddc->recv_task;
    cd = &ddc->recv_channels;

    while (task->state != HTS_STOP)
    {
        /*任务的状态是暂停*/
        if (task->state == HTS_PAUSE)
        {
            taskDelay(1);
            continue;
        }
        for (ch_idx = 0; ch_idx < cd->count && task->state != HTS_STOP; ++ch_idx)
        {
            if (cd->msg_info[ch_idx].msg_id == 3) continue;
            msgId = cd->msg_info[ch_idx].msg_id;
            nLen = cd->msg_info[ch_idx].length;
            ret = FC_NP_RecvMsg(ddc->h_dev, msgId, pMsg, &nLen);
            if (ret)
            {
                taskDelay(1);
                break;
            }
            if (nLen == 0)
            {
                taskDelay(1);
                break;
            }

            recv_count++;

            /*记录统计数据*/
            ddc->recv_iu_ch[ch_idx]++;
            ddc->recv_bytes_ch[ch_idx] += nLen;
            ddc->recv_iu_total++;
            ddc->recv_bytes_total += nLen;

            if (recv_count % 1000 == 0)
            {
                printf("[recv count=%d]msgId=%d nLen=%d\n", recv_count, msgId, nLen);
                taskDelay(1);
            }
        }
    }
    printf("[h_dev=%p]recv task exit\n", ddc->h_dev);
    task->id = ERROR;

    return 0;
}

/*ASM接收回调*/
FCUINT HbaDemoRecvCallBack(FCHANDLE hDev, FCUINT msgId)
{
    unsigned int i;
    FCUINT ret;
    DEMO_DEV_CONTROL *ddc;
    FCUINT iuLength = 0;

    iuLength = FC_ASM_IU_LENGTH_MAX;
    
    ddc = NULL;
    for (i = 0; i < g_dev_count; ++i)
    {
        if (g_ddc[i].h_dev == hDev)
        {
            ddc = &g_ddc[i];
            break;
        }
    }

    if (ddc == NULL)
    {
        printf("invalid handle hDev=%p\n", hDev);
        return FC_FAILURE;
    }    

    ret = FC_NP_RecvMsg(hDev, msgId, ddc->recv_int_buf, &iuLength);
    if (ret)
    {
        printf("[devid=%d]FC_NP_RecvMsg failed ret=0x%08x\n", i, ret);
        return ret;
    }
    /*printf("[recv int]msgId=%d iuLength=%d\n", msgId, iuLength);*/

    for (i = 0; i < ddc->recv_channels.count; ++i)
    {
        if (ddc->recv_channels.msg_info[i].msg_id == msgId)
        {
            ddc->recv_iu_ch[i]++;
            ddc->recv_bytes_ch[i] += iuLength;
            break;
        }
    }
    ddc->recv_iu_total++;
    ddc->recv_bytes_total += iuLength;

    return FC_SUCCESS;
}

/*事件中断的回调*/
FCUINT HbaDemoEventCallback(FCHANDLE hDev, FCUINT intCode, FCUINT param1)
{
    switch (intCode)
    {
        case IC_LINK_STATUS_SUCCESS:
        {
            printf("int code=IC_LINK_STATUS_SUCCESS param1=0x%x \n", param1);
            break;
        }
        case IC_LINK_STATUS_FAILED:
        {
            printf("int code=IC_LINK_STATUS_FAILED param1=0x%x \n", param1);
            break;
        }
        case IC_VOLTAGE_SUCCESS:
        {
            printf("int code=IC_VOLTAGE_SUCCESS param1=0x%x \n", param1);
            break;
        }
        case IC_VOLTAGE_FAILED:
        {
            printf("int code=IC_VOLTAGE_FAILED param1=0x%x \n", param1);
            break;
        }
        case IC_TEMP_SUCCESS:
        {
            printf("int code=IC_TEMP_SUCCESS param1=0x%x \n", param1);
            break;
        }
        case IC_TEMP_FAILED:
        {
            printf("int code=IC_TEMP_FAILED param1=0x%x \n", param1);
            break;
        }
        case IC_DISCARD_MSG:
        {
            printf("int code=IC_DISCARD_MSG param1=0x%x \n", param1);
            break;
        }
        case IC_IU_TIMEOUT:
        {
            printf("int code=IC_IU_TIMEOUT param1=0x%x \n", param1);
            break;
        }
        case IC_IU_LENGTH_INVALID:
        {
            printf("int code=IC_IU_LENGTH_INVALID param1=0x%x \n", param1);
            break;
        }
        case IC_ELS_RECV_NC_TIMEOUT:
        {
            printf("int code=IC_ELS_RECV_NC_TIMEOUT param1=0x%x \n", param1);
            break;
        }
        case IC_ELS_RECV_NC_ON_NET:
        {
            FCUINT i;

            for (i = 0; i < DEMO_DEV_NUM_MAX; ++i)
            {
                if (g_ddc[i].h_dev == hDev)
                {
                    if (g_ddc[i].online_task.flag == HBA_SEM_FLAG_CREATED)
                    {
                        semGive(g_ddc[i].online_task.sem);
                    }            
                }
            }
            printf("int code=IC_ELS_RECV_NC_ON_NET param1=0x%x \n", param1);
            break;
        }
        
        case IC_NC_CHANGED:
        {
            printf("int code=IC_NC_CHANGED param1=0x%x \n", param1);
            break;
        }
        
        case IC_NC_CONFLICT:
        {
            printf("int code=IC_NC_CONFLICT param1=0x%x \n", param1);
            break;
        }
        
        default:
        {
            printf("Unknown int code=%d param1=%d \n", intCode, param1);
            break;
        };
    }
    return FC_SUCCESS;
}

#if 1/*to be deleted by liujin*/
/*查询设备*/
FCUINT CmdQueryDev(FCUINT topo, FCUINT nm_role)
{
    int i, k, err;
    FCUINT ret, count;
    err = 0;

    if (topo != MB_TOPO_LOOPBACK && topo != MB_TOPO_NET_MANAGER)
    {
        return FC_PARAMS_INVALID;
    }
    if (nm_role != FC_NET_ROLE_NC && nm_role != FC_NET_ROLE_NRT)
    {
        return FC_PARAMS_INVALID;
    }

    if (g_dev_count == 0)
    {
#if 0
        /*查询设备*/
        ret = FC_NP_DevQuery(&count);
        if (ret)
        {
            printf("FC_NP_DevQuery failed ret=0x%08x\n", ret);
            return ret;
        }
        printf("FC_NP_DevQuery success dev count=%d\n", count);
#endif
        err = 0;
        /*FH130没有FC_NP_DevQuery函数，所以CmdQueryDev放到FC_NP_OPEN之后执行,
        如果能到这一步,就一定有一个设备，这是暂时的替代方案。*/
        count = 1;
        
        for (i = 0; i < count; ++i)
        {
            g_ddc[i].h_dev = 0;
            
            /*发送任务*/
            g_ddc[i].send_task.id = ERROR;
            g_ddc[i].send_task.sem = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
            g_ddc[i].send_task.flag = HBA_SEM_FLAG_CREATED;
            /*
            err = HbaCreateSemB(&g_ddc[i].send_task, 0);
            if (err != OK)
            {
                break;
            }
            */
            memcpy(g_ddc[i].send_task.name, "tDemoSend", 9);
            g_ddc[i].send_task.priority = 100;
            g_ddc[i].send_task.stackSize = 40960;
            g_ddc[i].send_task.state = HTS_STOP;
            g_ddc[i].send_task.func = HbaDemoSendTask;

            /*接收任务*/
            g_ddc[i].recv_task.id = ERROR;
            g_ddc[i].recv_task.sem = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
            g_ddc[i].recv_task.flag = HBA_SEM_FLAG_CREATED;
            /*
            err = HbaCreateSemB(&g_ddc[i].recv_task, 0);
            err = ok;
            if (err != OK)
            {
                break;
            }
            */
            memcpy(g_ddc[i].recv_task.name, "tDemoRecv", 9);
            g_ddc[i].recv_task.priority = 100;
            g_ddc[i].recv_task.stackSize = 40960;
            g_ddc[i].recv_task.state = HTS_STOP;
            g_ddc[i].recv_task.func = HbaDemoRecvTask;

            /*维护网络状态任务*/
            g_ddc[i].online_task.id = ERROR;
            g_ddc[i].online_task.sem = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
            g_ddc[i].online_task.flag = HBA_SEM_FLAG_CREATED;
            /*err = HbaCreateSemB(&g_ddc[i].online_task, 0);
            err = ok;
            if (err != OK)
            {
                break;
            }
            */
            memcpy(g_ddc[i].online_task.name, "tDemoOnline", 11);
            g_ddc[i].online_task.priority = 100;
            g_ddc[i].online_task.stackSize = 40960;
            g_ddc[i].online_task.state = HTS_STOP;
            g_ddc[i].online_task.func = HbaDemoOnlineTask;

            g_ddc[i].send_buf = NULL;
            g_ddc[i].recv_poll_buf = NULL;
            g_ddc[i].recv_int_buf = NULL;

            g_ddc[i].send_count = 0;

            InitAsmInfo(&g_ddc[i], topo, nm_role);

            g_ddc[i].asmRecvCallBack = HbaDemoRecvCallBack;
            g_ddc[i].eventCallBack = HbaDemoEventCallback;
            for (k = 0; k < FC_CHANNEL_NUM_MAX; ++k)
            {
                g_ddc[i].send_iu_ch[k] = g_ddc[i].send_bytes_ch[k] = g_ddc[i].recv_iu_ch[k] = g_ddc[i].recv_bytes_ch[k] = 0;
            }
            g_ddc[i].send_iu_total = 0;
            g_ddc[i].send_bytes_total = 0;
            g_ddc[i].recv_iu_total = 0;
            g_ddc[i].recv_bytes_total = 0;
        }
        if (err)
        {
            for (i = 0; i < count; ++i)
            {
                if (g_ddc[i].send_task.sem) 
                {
                    semDelete(g_ddc[i].send_task.sem); g_ddc[i].send_task.sem = 0; 
                }
                if (g_ddc[i].recv_task.sem) 
                { 
                    semDelete(g_ddc[i].recv_task.sem); g_ddc[i].recv_task.sem = 0; 
                }
            }
        }
        else
        {
            g_dev_count = count;
        }
    }
    return FC_SUCCESS;
}

FCUINT check_env(FCUINT devid)
{
    if (g_dev_count == 0)
    {
        printf("no device\n");
        return 1;
    }
    if (devid < 0 || devid >= g_dev_count)
    {
        printf("invalid devid=%d\n", devid);
        return 2;
    }
    return 0;
}
#endif

/*退出*/
FCUINT CmdExit(FCUINT devid)
{
    FCUINT i, ret, nm_role, state;
    DEMO_DEV_CONTROL *ddc;
    HBA_TASK_DESC *t;

    if (check_env(devid))
    {
        return FC_FAILURE;
    }
    ddc = &g_ddc[devid];
    if (ddc->h_dev == 0)
    {
        printf("invalid hdev=0\n");
        return FC_FAILURE;
    }

    /*停止发送*/
    t = &ddc->send_task;
    if (t->id != ERROR)
    {
        /*停止任务*/
        while (t->id != ERROR)
        {
            t->state = HTS_STOP;
            taskDelay(1);
        }
        printf("[devid=%d]send task is stop\n", devid);
    }

    /*停止接收*/
    t = &ddc->recv_task;
    if (t->id != ERROR)
    {
        /*停止任务*/
        while (t->id != ERROR)
        {
            t->state = HTS_STOP;
            taskDelay(1);
        }
        printf("[devid=%d]recv task is stop\n", devid);
    }

    /*停止维护网络状态任务*/
    t = &ddc->online_task;
    if (t->id != ERROR)
    {
        /*停止任务*/
        while (t->id != ERROR)
        {
            t->state = HTS_STOP;
            if (t->flag == HBA_SEM_FLAG_CREATED)
            {
                semGive(t->sem);
            }    
            taskDelay(1);
        }
        printf("[devid=%d]online task is stop\n", devid);
    }

    ddc->send_count = 0;

    /*关闭WDT定时器*/
    ret = FC_NM_WDTDisable(ddc->h_dev, FC_WDT_NET_MODE);
    if (ret)
    {
        printf("[devid=%d]FC_NM_SetWdtPeriodEnab failed ret=0x%08x\n", devid, ret);
    }
    else
    {
        printf("[devid=%d]FC_NM_SetWdtPeriodEnab success", devid);
    }    

    /*复位设备*/
    ret = FC_NP_SoftReset(ddc->h_dev);
    if (ret)
    {
        printf("[devid=%d]FC_NP_SoftReset failed ret=0x%08x\n", devid, ret);
    }
    else
    {
        printf("[devid=%d]FC_NP_SoftReset success\n", devid);
    }

    /*设置时钟同步使能*/
    ret = FC_TM_SyncDisable(ddc->h_dev);
    if (ret)
    {
        printf("[devid=%d]FC_TM_SyncDisable failed ret=0x%08x\n", devid, ret);
    }
    else
    {
        printf("[devid=%d]FC_TM_SyncDisable success\n", devid);
    }

    /*注销中断接收ASM消息的回调函数*/
    ret = FC_NP_UnRegMsgHandler(ddc->h_dev);
    if (ret)
    {
        printf("[devid=%d]FC_NP_UnRegMsgHandler failed ret=0x%08x\n", devid, ret);
    }
    else
    {
        printf("[devid=%d]FC_NP_UnRegMsgHandler success\n", devid);
    }

    if (ddc->recv_int_buf)
    {
        free(ddc->recv_int_buf);
        ddc->recv_int_buf = NULL;
    }

    if (ddc->recv_poll_buf)
    {
        free(ddc->recv_poll_buf);
        ddc->recv_poll_buf = NULL;
    }
#if 0
    if (ddc->PbitResult)
    {
        free(ddc->PbitResult);
        ddc->PbitResult = NULL;
    }

    if (ddc->CbitResult)
    {
        free(ddc->CbitResult);
        ddc->CbitResult = NULL;
    }

    if (ddc->nsi)
    {
        free(ddc->nsi);
        ddc->nsi = NULL;
    }
#endif
    for (i = 0; i < ddc->send_channels.count; ++i)
    {
        ddc->send_iu_ch[i] = ddc->send_bytes_ch[i] = 0;
    }
    ddc->send_iu_total = ddc->send_bytes_total = 0;
    for (i = 0; i < ddc->recv_channels.count; ++i)
    {
        ddc->recv_iu_ch[i] = ddc->recv_bytes_ch[i] = 0;
    }
    ddc->recv_iu_total = ddc->recv_bytes_total = 0;

    /*注销事件回调函数*/
    ret = FC_NP_UnRegEvtHandler(ddc->h_dev);
    if (ret)
    {
        printf("[devid=%d]FC_NP_UnRegEvtHandler failed ret=0x%08x\n", devid, ret);
    }
    else
    {
        printf("[devid=%d]FC_NP_UnRegEvtHandler success\n", devid);
    }

    /*关闭设备*/
    ret = FC_NP_Close(ddc->h_dev);
    if (ret)
    {
        printf("[devid=%d]FC_NP_Close failed ret=0x%08x\n", devid, ret);
    }
    else
    {
        ddc->h_dev = 0;
        printf("[devid=%d]FC_NP_Close success\n", devid);
    }
    ddc->scheme_no = 0;
    ddc->config_block_no = 0;
    ddc->topo = 0;
    ddc->nm_role = 0;
    if (g_dev_count) 
    {
        g_dev_count--;
    }

    return FC_SUCCESS;
}

#if 1/*jin.liu 20180307*/
#define TEST_MAX_MSG_LENGTH_1    (2097)
#define TEST_MAX_MSG_LENGTH_2    (4*1024*1024)/*(4*1024*1024)*/
#define TEST_MAX_MSG_LENGTH_3    (16*1024*1024)
#define TEST_MAX_MSG_LENGTH  TEST_MAX_MSG_LENGTH_1
#endif

/*初始化配置*/
void InitAsmInfo(DEMO_DEV_CONTROL *ddc, int topo, int nm_role)
{
    /*
    1 节点1 FCID=0x0100000 方案1 作为NCT 发送2个通道(BNC NRT) 接收2个通道(BNC NRT)
    2 节点2 FCID=0x0100002 方案1 作为BNC 发送1个通道(NCT) 接收1个通道(NCT)
    3 节点3 FCID=0x0100001 方案1 作为NRT 发送1个通道(NCT) 接收1个通道(NCT)
    4 节点4 FCID=0x0100003 方案1 用于测试自环多通道收发字节数的正确性和性能，作为NCT 发送2个通道 接收2个通道
    */
    DEMO_CHANNEL_DESC *send, *recv;

    send = &ddc->send_channels;
    recv = &ddc->recv_channels;

    if (topo == MB_TOPO_LOOPBACK)
    {
        /*自环测试*/

        ddc->config_block_no = 0;
        ddc->scheme_no = 3;

        /*发送通道*/
        send->count = 2;

        send->msg_info[0].msg_id = 1;
        send->msg_info[0].length = TEST_MAX_MSG_LENGTH/*512*/;

        send->msg_info[1].msg_id = 2;
        send->msg_info[1].length = TEST_MAX_MSG_LENGTH/*512*/;

        /*接收通道*/
        recv->count = 2;

        recv->msg_info[0].msg_id = 1;
        recv->msg_info[0].length = TEST_MAX_MSG_LENGTH/*512*/;

        recv->msg_info[1].msg_id = 2;
        recv->msg_info[1].length = TEST_MAX_MSG_LENGTH/*512*/;
    }
    else
    {
        /*点对点测试*/
        if (nm_role == FC_NET_ROLE_NC)
        {
            /*NCT*/
            ddc->config_block_no = 0;
            ddc->scheme_no = 0;

            /*发送通道*/
            send->count = 2;

            send->msg_info[0].msg_id = 1;
            send->msg_info[0].length = TEST_MAX_MSG_LENGTH/*512*/; 

            send->msg_info[1].msg_id = 2;
            send->msg_info[1].length = TEST_MAX_MSG_LENGTH/*512*/;
            
            /*接收通道*/
            recv->count = 2;

            recv->msg_info[0].msg_id = 3;
            recv->msg_info[0].length = TEST_MAX_MSG_LENGTH/*512*/;

            recv->msg_info[1].msg_id = 4;
            recv->msg_info[1].length = TEST_MAX_MSG_LENGTH/*512*/;
            
        }
        else if (nm_role == FC_NET_ROLE_BNC)
        {
            /*BNCT*/
            ddc->config_block_no = 0;
            ddc->scheme_no = 1;

            /*发送通道*/
            send->count = 1;

            send->msg_info[0].msg_id = 3;
            send->msg_info[0].length = TEST_MAX_MSG_LENGTH/*512*/;
            
            /*接收通道*/
            recv->count = 1;

            recv->msg_info[0].msg_id = 1;
            recv->msg_info[0].length = TEST_MAX_MSG_LENGTH/*512*/;
        }
        else
        {
            /*NRT*/
            ddc->config_block_no = 0;
            ddc->scheme_no = 2;

            /*发送通道*/
            send->count = 1;

            send->msg_info[0].msg_id = 4;
            send->msg_info[0].length = TEST_MAX_MSG_LENGTH/*512*/;

            /*接收通道*/
            recv->count = 1;

            recv->msg_info[0].msg_id = 2;
            recv->msg_info[0].length = TEST_MAX_MSG_LENGTH/*512*/;
        }
    }
}

void GetInfo(FCHANDLE hDev)
{
    FCUINT i, state, ret;
    OnNetTbl netTable;
    FCUINT nrtBitResult; /*网络节点自检信息*/
    NetStatistics nsi; /*获得指定节点的网络信息*/

    for (i = 0; i < DEMO_DEV_NUM_MAX; ++i)
    {
        printf("hDev=%p\n", hDev);
        printf("h_Dev=%p\n", g_ddc[i].h_dev);
        if (g_ddc[i].h_dev == hDev)
        {
            ret = FC_NM_GetOnNetTable(g_ddc[i].h_dev, &netTable);
           
            if (ret == 0 && netTable.Status[MB_NODE3_FCID & 0xff] == 1 )
            {
                printf("Nrt is online\n");
                /*周期自检*/
                ret = FC_NM_NC_GetNrtBitResult(g_ddc[i].h_dev, MB_NODE3_FCID, &nrtBitResult);
                if (ret == 0)
                {
                    printf("FC_NM_GetCBitResult success\n");
                }
                else
                    printf("CBit ret=%d\n", ret);
                /*统计信息*/
                ret = FC_NM_NC_GetNetStatistics(g_ddc[i].h_dev, MB_NODE3_FCID, &nsi);
                if (ret == 0)
                {
                    printf("FC_NM_GetNetStatisticsInfo success\n");
                }
                else
                    printf("nsi ret=%d", ret);
            }
        }
    }
}


#if 1/*added by liujin*/
/*tick数转换为毫秒数 如果转换值为0，返回1毫秒*/
unsigned int HbaDrvTick2MilliSecond(unsigned int tick)
{
	unsigned int milliSecond;

	/*如果分子大于1000，结果会等于0，浮点转换为整型的误差*/
	milliSecond = (tick * 1000) / sysClkRateGet();
	if (milliSecond == 0)
	{
		/*最小值是1毫秒*/
		milliSecond = 1;
	}

	return milliSecond;
}

FCUINT FC_NM_GetNodeState(FCHANDLE hDev, FCUINT portId, FCUINT *state)
{
    FCUINT ret;
    OnNetTbl netTable;
    
    ret = FC_NM_GetOnNetTable(hDev, &netTable);
    *state = netTable.Status[portId & 0xff] ;
    
    return ret;
}
FCUINT FC_NP_GetVoltage(FCHANDLE hDev, FCINT *voltage)
{
    HBA_DEV_CB *dc;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (voltage == NULL)
    {
        return FC_PARAMS_INVALID;
    }

    dc = (HBA_DEV_CB *)hDev;
    *voltage = hwGetVoltage( (REG_HW *)dc->pMembaseCsr); 
    
    return FC_SUCCESS;    
}
/*测试设备自检*/
FCUINT FC_NP_DevBit(FCUINT devId, FCUINT chCount, FCUINT msgIdBase, FCUINT ioByteBase, FCUINT ioByteStep, FCUINT ioCount)
{
    int i, tick_begin, tick_end, num, dev_open_flag, dev_config_flag;
    FCUINT ret, timeout, port_id, devid, dev_count, status, status0, status1,  voltage, state, enab, role, length, ch_idx, io_count, ch_count, msg_id, msg_max_len, send_len, recv_len, net_node_state;
    FCUINT version;
    FCINT temperature;

    BLUE_PRINT *bp;
    CONFIG_BLOCK *cb;
    FC_PORT_CONFIG *pc;
    FC_MSG_SEND_ITEM *si;
    FC_MSG_RECV_ITEM *ri;
    FCUCHAR *send_msg, *recv_msg;
    NetStatistics psi;

    FCDate t_date;
    FCTime t_time;
/*    NET_DATE d;*/
    time_t raw_time;
    struct tm *ti;

/*    FC_PBIT_RESULT pbit;
    FC_CBIT_RESULT cbit;*/
    NetStatistics nsi;
    OnNetTbl net_node_state_table;
    FCHANDLE hDev;
    HBA_DEV_CB *dc;

    if (devId >= MAX_DEVICE_NUM)
    {
        return FC_PARAMS_INVALID;
    }
    if (chCount == 0 || chCount > FC_CHANNEL_NUM_MAX)
    {
        return FC_PARAMS_INVALID;
    }
    if (msgIdBase == 0)
    {
        return FC_PARAMS_INVALID;
    }
    if (ioByteBase == 0)
    {
        return FC_PARAMS_INVALID;
    }

    dev_open_flag = dev_config_flag = 0;
    port_id = 0x0100000;

    printf("\n");
    num = 1;

    tick_begin = tickGet();
    tick_end = 0;

#if 0
    /*查询设备*/
    dev_count = 0;
    ret = FC_NP_DevQuery(&dev_count);
    if (ret)
    {
        printf("FC_NP_DevQuery failed ret=0x%08x\n", ret);
        return ret;
    }
    printf("%02d FC_NP_DevQuery success dev count=%d\n", num++, dev_count);
    if (dev_count == 0) return;
    printf("   PCIe SUCCESS\n");

    if (devId >= dev_count)
    {
        printf("invalid devid=% dev count=%d\n", devId, dev_count);
        return FC_FAILURE;
    }
#endif

    do
    {
        /*打开设备*/
        ret = FC_NP_Open(&hDev, devId);
        if (ret)
        {
            printf("FC_NP_Open failed ret=0x%08x\n", ret);
            break;
        }
        dev_open_flag = 1;
        printf("%02d FC_NP_Open success dev handle=%p\n", num++, hDev);
        dc = (HBA_DEV_CB *)hDev;

        /*获取温度*/
        ret = FC_NP_GetTemp(hDev, &temperature);
        if (ret)
        {
            printf("FC_NP_GetTemp failed ret=0x%08x\n", ret);
            break;
        }
        printf("%02d FC_NP_GetTemp success temperature=%d\n", num++, temperature);

        /*获取电压*/
        ret = FC_NP_GetVoltage(hDev, &voltage);
        if (ret)
        {
            printf("FC_NP_GetVoltage failed ret=0x%08x\n", ret);
            break;
        }
        printf("%02d FC_NP_GetVoltage success voltage=%d\n", num++, voltage);

        /*获取工作状态*/
        ret = FC_NP_GetWorkStatus(hDev, &state);
        if (ret)
        {
            printf("FC_NP_GetWorkStatus failed ret=0x%08x\n", ret);
            break;
        }
        printf("%02d FC_NP_GetWorkStatus success state=%d\n", num++, state);
        if (state != 0)
        {
            printf("dev work state is errro\n");
            break;
        }

        /*使用临时的内存*/
        bp = &gBluePrint[0];

        /*不依赖外部配置块和FLASH，设置为PROJECT模式*/
        dc->majorScheme = 0;
        dc->minorScheme = 0;
        dc->configMode = FC_CONFIG_MODE_PROJECT;
        cb = &bp->config_block[dc->minorScheme];

        pc = &cb->port_config;

        pc->port_id = port_id;          /*本地port_id*/
        pc->port_type = 1;
        pc->credit_num = 8;
        pc->role = FC_NET_ROLE_NC;  /*网络管理角色*/
        pc->clk_sync_role = FC_NET_CLK_SYNC_ROLE_SERVER_MASTER; /*时钟同步角色*/
        pc->nc_wdt_period = 1000;          /*网络管理器WDT定时周期 单位毫秒*/
        pc->wdt_loader_period = 200;    /*WDT加载周期 单位毫秒*/
        pc->clk_sync_period = 50;       /*时钟同步周期 单位毫秒 一般设置为50ms*/
        
        pc->block_txmsg_num = chCount;  /*数据块发送消息总数   0～256*/
        pc->block_rxmsg_num = chCount;  /*数据块接收消息总数   0～256*/
        pc->nonblock_txmsg_num = 0;       /*流数据块发送消息总数 0～256*/
        pc->nonblock_rxmsg_num = 0;       /*流数据块接收消息总数 0～256*/

        for (ch_idx = 0; ch_idx < chCount; ++ch_idx)
        {
            si = &cb->send_item[ch_idx];
            ri = &cb->recv_item[ch_idx];

            msg_max_len = FC_ASM_IU_LENGTH_MAX;
            msg_id = msgIdBase + ch_idx;
            si->msg_id = msg_id;               /*消息ID*/
            si->msg_src_id = port_id;          /*消息的源FCID*/
            si->msg_dst_id = port_id;          /*消息的目的FCID*/
            si->msg_type = MSG_TYPE_STREAM_MSG; /*消息类型 1-紧急 2-事件 3-长消息*/
             si->msg_priority =PRIORITY_LEVEL_0;

            ri->msg_id = msg_id;                       /*消息ID*/
            ri->msg_max_len = msg_max_len;             /*接收的最大字节数*/
            ri->msg_type = MSG_TYPE_STREAM_MSG;         /*消息类型 1-紧急 2-事件 3-长消息*/
            ri->msg_src_id = port_id;                  /*消息的源FCID*/
            ri->msg_recover = 0;                       /*消息覆盖标志 0-不覆盖 1-覆盖*/
        }

#if 0
        /*填充日期*/
        time(&raw_time);
        ti = localtime(&raw_time);
        d.u.year = ti->tm_year + 1900;/*从1900年开始的年数*/
        d.u.month = ti->tm_mon + 1;/*[0:11]*/
        d.u.day = ti->tm_mday;
#endif
        /*配置设备*/
        ret = FC_NP_LoadConfig(dc, dc->majorScheme, dc->minorScheme);
        /*ret = hbaDevLoadConfig(dc);*/
        if (ret)
        {
            break;
        }

        dev_config_flag = 1;
        printf("%02d dev config success\n", num++);

        /*打印基本信息*/
        printf("   BusNo=%d\n", dc->BusNo);
        printf("   DeviceNo=%d\n", dc->DeviceNo);
        printf("   FuncNo=%d\n", dc->FuncNo);
        printf("   pMembaseCsr=%p\n", dc->pMembaseCsr);

        taskDelay(5);

        /*获取端口的link状态*/
        ret = FC_NP_GetPortLinkStatus(hDev, 0, &status0);
        ret += FC_NP_GetPortLinkStatus(hDev, 1, &status1);
        if (ret)
        {
            printf("FC_NP_GetPortStatus failed ret=0x%08x\n", ret);
            break;
        }
        status = status0 ||status1;
        printf("%02d FC_NP_GetPortStatus success port status=%s\n", num++, status == FC_PORT_STATUS_LINK_UP ? "FC_PORT_STATUS_LINK_UP" : "FC_PORT_STATUS_LINK_DOWN");
        if (status != FC_PORT_STATUS_LINK_UP)
        {
            /*如果端口没有link，使用内部自环*/
            hwSetPortGtxLoopBack((REG_HW *)dc->pMembaseCsr, 1);
            printf("   inside loopback\n");
        }
        else
        {
            printf("   outside loopback\n");
        }

        /*获取版本*/
        ret = FC_NP_GetVersion(hDev, &version);
        if (ret)
        {
            printf("FC_NP_GetVersion failed ret=0x%08x\n", ret);
            break;
        }
        printf("%02d FC_NP_GetVersion success\n", num++);

#if 0
        /*打印版本*/
        printf("   FPGA=");
        for (i = 0; i < 5; ++i)
        {
            unsigned char c = version.fpga[i];
            printf("%c", c);
            if (c == '\0') break;
        }
        printf("\n");
        printf("   API=");
        for (i = 0; i < 5; ++i)
        {
            unsigned char c = version.api[i];
            printf("%c", c);
            if (c == '\0') break;
        }
        printf("\n");
        printf("   BLUE_PRINT_VER=");
        for (i = 0; i < 16; ++i)
        {
            unsigned char c = version.blue_print_ver[i];
            printf("%c", c);
            if (c == '\0') break;
        }
        printf("\n");
        printf("   BLUE_PRINT_DATE=");
        for (i = 0; i < 10; ++i)
        {
            unsigned char c = version.blue_print_date[i];
            printf("%c", c);
            if (c == '\0') break;
        }
        printf("\n");
#endif

        /*设置WDT定时器使能或禁止*/
        ret = FC_NM_WDTEnable(hDev, FC_WDT_NET_MODE);
        if (ret)
        {
            printf("FC_NM_WDTEnable failed ret=0x%08x\n", ret);
            /*break;*/
        }
        printf("%02d FC_NM_WDTEnable success wdt period is enab\n", num++);


        printf("%02d FC_NM_GetNodeState ", num++);
        while (1)
        {
            /*获取指定节点的网络状态*/
            state = 0;
            ret = FC_NM_GetNodeState(hDev, 0, &state);
            if (ret == FC_SUCCESS && state == 1)
            {
                printf("success node online\n");
                break;
            }
            taskDelay(1);
        }

        /******************************************************************************
        * 通信管理接口                                                                 *
        *******************************************************************************/
        ch_count = cb->port_config.block_txmsg_num + cb->port_config.nonblock_txmsg_num;
        
        send_msg = (FCUCHAR *)malloc(FC_ASM_IU_LENGTH_MAX + 1024);
        if(send_msg == NULL)
        {
            printf("malloc sendmsg buf failed!!!\n");
        }
        
        recv_msg = (FCUCHAR *)malloc(FC_ASM_IU_LENGTH_MAX  + 1024);
        if(recv_msg == NULL)
        {
            printf("malloc recv_msg buf failed!!!\n");
        }
        
        io_count = 0;
        while (io_count < ioCount)
        {
            for (ch_idx = 0; ch_idx < ch_count; ++ch_idx)
            {
                si = &cb->send_item[ch_idx];
                ri = &cb->recv_item[ch_idx];

                msg_id = si->msg_id;
                send_len = ioByteBase + io_count * ioByteStep;
                memset(send_msg, (unsigned char)msg_id, send_len);
                printf("%02d IO TEST msg_id=%03d send_msg[0]=0x%02x io_count=%03d send ", num, msg_id, send_msg[0], io_count);
                ret = FC_NP_SendMsg(hDev, msg_id, send_msg, send_len);
                if (ret)
                {
                    printf("NG[0x%08x]\n", ret);
                    break;
                }
                printf("OK recv ");

                timeout = 0;
                do
                {
                    /*接收ASM消息*/
                    msg_id = ri->msg_id;
                    recv_len = send_len;
                    memset(recv_msg, 0, recv_len);
                    ret = FC_NP_RecvMsg(hDev, msg_id, recv_msg, &recv_len);
                    if (ret == FC_SUCCESS && recv_len > 0) break;
                    timeout++;
                    taskDelay(1);
                } while (timeout < 100);
                if (ret || recv_len == 0)
                {
                    printf("time out\n");
                    ret = FC_FAILURE;
                    break;
                }
                printf("OK compare ");
                if (recv_len != send_len || memcmp(send_msg, recv_msg, recv_len) != 0)
                {
                    printf("NG\n");
                    ret = FC_FAILURE;
                    break;
                }
                printf("OK\r");
            }
            if (ret)
            {
                /*IO测试失败*/
                break;
            }
            io_count++;
        }

        free(send_msg);
        free(recv_msg);
        
        if (ret)
        {
            /*IO测试失败*/
            break;
        }

        num++;
        printf("\n");

        /*获取端口统计信息*/
        ret = FC_NM_NC_GetNetStatistics(hDev, cb->port_config.port_id, &psi);
        if (ret)
        {
            printf("FC_NM_NC_GetNetStatistics failed ret=0x%08x\n", ret);
            break;
        }
        printf("%02d FC_NM_NC_GetNetStatistics success\n", num++);



        /******************************************************************************
        * 时统管理接口                                                                 *
        *******************************************************************************/
        time(&raw_time);
        ti = localtime(&raw_time);

        /*设置日期*/
        t_date.year = ti->tm_year + 1900;/*从1900年开始的年数*/
        t_date.month = ti->tm_mon + 1; /*[0:11]*/
        t_date.day = ti->tm_mday;

        ret = FC_TM_SetDate(hDev, &t_date);
        if (ret)
        {
            printf("FC_TM_SetDate failed ret=0x%08x\n", ret);
            break;
        }
        printf("%02d FC_TM_SetDate success date[%04d-%02d-%02d]\n", num++, t_date.year, t_date.month, t_date.day);

        /*设置时间*/
        t_time.hour = 23;
        t_time.minute = 59;
        t_time.second = 59;
        t_time.millisecond = 999;
        t_time.microsecond = 999;
        t_time.nanosecond = 990;
        ret = FC_TM_SetRtc(hDev, &t_time);
        if (ret)
        {
            printf("FC_TM_SetTime failed ret=0x%08x\n", ret);
            break;
        }
        printf("%02d FC_TM_SetTime success time[%02d:%02d:%02d %03d:%03d:%03d]\n", num++,
            t_time.hour, t_time.minute, t_time.second, t_time.millisecond, t_time.microsecond, t_time.nanosecond);

        /*获取RTC*/
        memset(&t_date, 0, sizeof(FCDate));
        memset(&t_time, 0, sizeof(FCTime));
        ret = FC_TM_GetRtc(hDev, &t_time);
        if (ret)
        {
            printf("FC_TM_GetRtc failed ret=0x%08x\n", ret);
            break;
        }
        printf("%02d FC_TM_GetRtc success date[%04d-%02d-%02d] time[%02d:%02d:%02d %03d:%03d:%03d]\n", num++,
            t_date.year, t_date.month, t_date.day, t_time.hour, t_time.minute, t_time.second, t_time.millisecond, t_time.microsecond, t_time.nanosecond);

        /*设置时钟同步使能*/
        ret = FC_TM_SyncEnable(hDev);
        if (ret)
        {
            printf("FC_TM_SyncEnable failed ret=0x%08x\n", ret);
            break;
        }
        printf("%02d FC_TM_SyncEnable success tm sync is enab\n", num++);

        /*设置时钟管理角色*/
       ret = FC_TM_SyncModeSet(hDev, FC_SYNC_MODE_SERVER);
        if (ret)
        {
            printf("FC_TM_SyncModeSet failed ret=0x%08x\n", ret);
            break;
        }
        printf("%02d FC_TM_SyncModeSet success\n", num++);

        /*获取时钟管理角色*/
        ret = FC_TM_SyncModeGet(hDev, &role);
        if (ret)
        {
            printf("FC_TM_SyncModeGet failed ret=0x%08x\n", ret);
            break;
        }
        printf("%02d FC_TM_SyncModeGet success role=", num++);
        if (role == FC_NET_CLK_SYNC_ROLE_SERVER_MASTER) 
        {
            printf("FC_NET_CLK_SYNC_ROLE_SERVER_MASTER\n");
        } 
        else 
        {
            printf("FC_TIME_ROLE_CCT\n");
        }

        /******************************************************************************
        * 网络管理接口                                                                 *
        *******************************************************************************/
        /*获取所有节点的网络状态*/
        ret =  FC_NM_GetOnNetTable(hDev, &net_node_state_table);
        if (ret)
        {
            printf("FC_NM_GetOnNetTable failed ret=0x%08x\n", ret);
            break;
        }
        printf("%02d FC_NM_GetOnNetTable success\n", num++);

        /*获取指定节点的网络状态*/
        ret = FC_NM_GetNodeState(hDev, port_id, &net_node_state);
        if (ret)
        {
            printf("FC_NM_GetNodeState failed ret=0x%08x\n", ret);
            break;
        }
        printf("%02d FC_NM_GetNodeState success netNodeState=%d\n", num++, net_node_state);

#if 0
        /*获取节点上电自检信息*/
        ret = FC_NM_GetPBitResult(hDev, port_id, &pbit);
        if (ret)
        {
            printf("FC_NM_GetPBitResult failed ret=0x%08x\n", ret);
            break;
        }
        printf("%02d FC_NM_GetPBitResult success\n", num++);
        printf("   temperature=%d voltage=%d flash=%d reg=%d els_loopd=%d asm_loop=%d\n",
            pbit.temperature, pbit.voltage, pbit.flash, pbit.reg, pbit.els_loop, pbit.asm_loop);

        /*获取节点周期自检信息*/
        ret = FC_NM_GetCBitResult(hDev, port_id, &cbit);
        if (ret)
        {
            printf("FC_NM_GetCBitResult failed ret=0x%08x\n", ret);
            break;
        }
        printf("%02d FC_NM_GetCBitResult success cycle bit=[temperature=%d voltage=%d]\n", num++, cbit.temperature, cbit.voltage);
#endif

        /*获取指定节点的统计信息*/
        ret = FC_NM_NC_GetNetStatistics(hDev, port_id, &nsi);
        if (ret)
        {
            printf("FC_NM_NC_GetNetStatistics failed ret=0x%08x\n", ret);
            break;
        }
        printf("%02d FC_NM_NC_GetNetStatistics success\n", num++);

#if 0
        /*获取WDT定时器的状态*/
        ret = FC_NM_GetWdtPeriodEnab(hDev, &enab);
        if (ret)
        {
            printf("FC_NM_GetWdtPeriodEnab failed ret=0x%08x\n", ret);
            break;
        }
        printf("%02d FC_NM_GetWdtPeriodEnab success wdt period ", num++);
        if (enab == FC_WDT_PERIOD_ENAB)
        {
            printf("enab\n");

            /*设置WDT定时器使能或禁止*/
            ret = FC_NM_WDTDisable(hDev, FC_WDT_NET_MODE);
            if (ret)
            {
                printf("FC_NM_WDTDisable failed ret=0x%08x\n", ret);
                break;
            }
            printf("%02d FC_NM_WDTDisable success wdt period disable\n", num++);
        }
        else
        {
            printf("diable\n");
        }
#endif

        tick_end = tickGet();
        printf("   +----------------------------------+\n");
        printf("   | DEV(%d) BIT PASS TIMES=%6u(ms) |\n", devid, HbaDrvTick2MilliSecond(tick_end - tick_begin));
        printf("   +----------------------------------+\n");
    } while (FALSE);

    if (dev_config_flag == 1)
    {
        /*复位*/
        ret = FC_NP_SoftReset(hDev);
        if (ret)
        {
            printf("FC_NP_SoftReset failed ret=0x%08x\n", ret);
        }

        else
        {
            printf("%02d FC_NP_SoftReset success\n", num++);
        }
    }
    if (dev_open_flag == 1)
    {
        /*关闭设备*/
        ret = FC_NP_Close(hDev);
        if (ret)
        {
            printf("FC_NP_Close failed ret=0x%08x\n", ret);
        }
        else
        {
            printf("%02d FC_NP_Close success dev handle=%p\n", num++, hDev);
        }
    }
    return ret;
}
#endif