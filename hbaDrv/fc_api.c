#include <vxworks.h>
#include <taskLib.h>
#include "hba.h"
#include "hba_time.h"
#include "fc_api.h"



#define FC_ELS_LOAD_SWDATA_TIME_OUT     (sysClkRateGet())                    /* 加载交换机配置超时时间 */
#define FC_ELS_SYNC_IO_TIME_OUT         (sysClkRateGet()*200/1000)            /* 同步发送ELS帧以后等待接收的超时值*/
#define FC_ELS_SYNC_IO_DELAY_STEP        ((sysClkRateGet()*10 + 999)/1000)   /* 周期等待ELS返回帧的步长值*/

/* 打开FC节点机的N端口,为FC设备分配资源 */
FCUINT FC_NP_Open(FCHANDLE *hDev, FCUINT DevId)
{
    FCUINT ret;
    HBA_DEV_CB *dc;

    if (hDev == NULL)
    {
        return FC_PARAMS_INVALID;
    }
    
    ret = hbaDevCreate(&dc, DevId);
    if (ret == FC_SUCCESS)
    {
        *hDev = (FCHANDLE)dc;
    }
    
    return ret;
}

/* 关闭FC节点机的N端口 */
FCUINT FC_NP_Close(FCHANDLE hDev)
{
    HBA_DEV_CB *dc;
    
    dc = (HBA_DEV_CB *)hDev;
        
    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    
    if (hbaDevDestroy(dc) == DEV_SUCCESS) 
    {
        return FC_SUCCESS;
    }
    
    return FC_FAILURE;
}

/* 获取FC节点机的N端口状态 */
FCUINT FC_NP_GetState(FCHANDLE hDev, FCUINT *fcState)
{
    FCUINT ps[FC_PORT_NUM_MAX];
    HBA_DEV_CB *dc;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }

    if (fcState == NULL)
    {
        return FC_PARAMS_INVALID;
    }

    dc = (HBA_DEV_CB *)hDev;

    memset(ps, 0, sizeof(ps));
    
    if (hbaDevGetDevState(dc, ps, FC_PORT_NUM_MAX) != DEV_SUCCESS)
    {
        return FC_FAILURE;
    }

    /*作为冗余端口，只要有一个端口是linkup，就向应用返回linkup*/
    if (ps[FC_PORT_0] == FC_PORT_STATUS_LINK_UP || ps[FC_PORT_1] == FC_PORT_STATUS_LINK_UP)
    {
        *fcState = FC_PORT_STATUS_LINK_UP;
    }
    else
    {
        *fcState = FC_PORT_STATUS_LINK_DOWN;
    }
    
    return FC_SUCCESS;
}

/* 获取FC节点机的N端口版本号 */
FCUINT FC_NP_GetVersion(FCHANDLE hDev, FCUINT *version)
{
    HBA_DEV_CB *dc;
        
    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (version == NULL)
    {
        return FC_PARAMS_INVALID;
    }
    
    dc = (HBA_DEV_CB *)hDev;
    if (hbaDevGetVersion(dc, version) != DEV_SUCCESS) 
    {
        return FC_FAILURE;
    }
    
    return FC_SUCCESS;
}

/* 软复位FC节点机的N端口 */
FCUINT FC_NP_SoftReset(FCHANDLE hDev)
{
    HBA_DEV_CB *dc;
        
    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    
    dc = (HBA_DEV_CB *)hDev;
    if (hbaDevReset(dc, TRUE) != DEV_SUCCESS) 
    {
        return FC_FAILURE;
    }
    
    return FC_SUCCESS;
}

/* 启动FC节点机的N端口BIT操作 */
FCUINT FC_NP_IBit(FCHANDLE hDev, FC_BIT_RESULT_MANUAL *bitResult)
{
    HBA_DEV_CB *dc;
    FC_BIT_RESULT *result;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (bitResult == NULL)
    {
        return FC_PARAMS_INVALID;
    }

    dc = (HBA_DEV_CB *)hDev;
    
    /* 自检 */
    hbaDevManualSelfCheck(dc);
    result = &dc->bitResult;    
    bitResult->flash = result->flash;
    bitResult->temperature = result->temperature;
    bitResult->voltage = result->voltage;

    return FC_SUCCESS;
}

/*取得 上电自检结果*/
FCUINT FC_NP_GetPuBitResult(FCHANDLE hDev, FC_BIT_RESULT_POWER *bitResult)
{
    HBA_DEV_CB *dc;
    FC_BIT_RESULT *result;

    if (hDev == NULL)
       {
        return FC_INVALID_HANDLE;
       }
    if (bitResult == NULL)
    {
        return FC_PARAMS_INVALID;
    }

    dc = (HBA_DEV_CB *)hDev;
    result = &dc->bitResult;
    bitResult->memory = result->memory;
    bitResult->reg = result->reg;
    bitResult->temperature= result->temperature;
    bitResult->voltage = result->voltage;
    bitResult->flash = result->flash;

    return FC_SUCCESS;
}

/* 注册网络管理事件处理函数 */
FCUINT FC_NP_RegEvtHandler(FCHANDLE hDev, FC_INT_FUNCPTR func)
{
    HBA_DEV_CB *dc;
    
    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (func == NULL)
    {
        return FC_PARAMS_INVALID;
    }
    
    
    dc = (HBA_DEV_CB *)hDev;
    if (dc->status == HBA_DEV_STATUS_NONE)
    {
        return FC_DEVICE_STATE_INVALID;
    }
    
    dc->pIntCallbackFunc = func;

    return FC_SUCCESS;
}

/* 注销网络管理事件处理函数 */
FCUINT FC_NP_UnRegEvtHandler(FCHANDLE hDev)
{
    HBA_DEV_CB *dc;
    
    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }

    dc = (HBA_DEV_CB *)hDev;
    if (dc->status == HBA_DEV_STATUS_NONE)
    {
        return FC_DEVICE_STATE_INVALID;
    }
    
    dc->pIntCallbackFunc = NULL;

    return FC_SUCCESS;     
}

/* 通信管理接口 */
/* 配置FC节点机的ASM通信模式 */
/* 必须在FC_NP_LoadConfig之前调用才会有效，否则取缺省值 */
FCUINT FC_NP_ConfigMode(FCHANDLE hDev, FCUINT configMode)
{
    HBA_DEV_CB *dc;
        
    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    
    if (configMode != FC_CONFIG_MODE_PROJECT && configMode != FC_CONFIG_MODE_FLASH)
    {
        return FC_PARAMS_INVALID;
    }

    dc = (HBA_DEV_CB *)hDev;
    if (dc->status != HBA_DEV_STATUS_CREATED)
    {
        return FC_DEVICE_STATE_INVALID;
    }

    dc->configMode = configMode;
    
    return FC_SUCCESS;
}

/* 加载FC节点机的ASM配置 */
FCUINT FC_NP_LoadConfig(FCHANDLE hDev, FCUINT majorScheme, FCUINT minorScheme)
{
    STATUS st;
    INT32 ret;
    HBA_DEV_CB *dc;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }

    if (majorScheme >= FC_MAJOR_SCHEME_MAX)
    {
        return FC_INVALID_MAJOR_SCHEME;
    }

    if (minorScheme >= FC_MINOR_SCHEME_MAX)
    {
        return FC_INVALID_MINOR_SCHEME;
    }

    dc = (HBA_DEV_CB *)hDev;
    if (dc->status != HBA_DEV_STATUS_CREATED)
    {
        return FC_DEVICE_STATE_INVALID;
    }
    
    dc->majorScheme = majorScheme;
    dc->minorScheme = minorScheme;
    if (hbaDevLoadConfig(dc) != DEV_SUCCESS) 
    {
        return FC_DEV_GET_CONFIG_FAILED;
    }

    ret = hbaDevCheckConfig(dc);
    if (ret != FC_SUCCESS)
    {
        return ret;
    }

    if (hbaDevInitialize(dc) != DEV_SUCCESS) 
    {
        return FC_DEV_CB_INIT_FAILED;
    }

    /* 接收消息丢弃使能 */
    hbaDevSetDiscardEnab(dc, MSG_DISCARD_ENABLE);

    /*上电自检*/
    st = hbaDevPuSelfCheck(dc);
    if (st != OK)
    {
        return FC_SELF_CHECK_FAIL;
    }
    
    ret = hbaDevRun(dc);
    if (ret != DEV_SUCCESS)
    {
        return FC_DEV_START_FAILED;
    }

    return FC_SUCCESS;
}

/* 卸载FC节点机的ASM配置 */
FCUINT FC_NP_UnLoadConfig(FCHANDLE hDev)
{
    HBA_DEV_CB *dc;
        
    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    
    dc = (HBA_DEV_CB *)hDev;

    if (hbaDevReset(dc, FALSE) != DEV_SUCCESS) 
    {
        return FC_FAILURE;
    }

    return FC_SUCCESS;
}

/* 对flash进行配置 */
FCUINT FC_NP_FlashConfig(FCHANDLE hDev)
{
    HBA_DEV_CB *dc = (HBA_DEV_CB *)hDev;
    /*int i;*/
        
    if (dc == NULL)
    {
        return FC_INVALID_HANDLE;
    }

    if (hbaDevFlashConfig(dc, &(dc->configBlock), dc->majorScheme, dc->minorScheme) != DEV_SUCCESS) 
    {
        return FC_FAILURE;
    }    
        
    
    return FC_SUCCESS;
}

/* 发送指定的ASM消息 */
FCUINT FC_NP_SendMsg(FCHANDLE hDev, FCUINT msgID, FCUCHAR *pMsg, FCUINT nLen)
{ 
    FCUINT ret;
    HBA_DEV_CB *dc;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (pMsg == NULL)
    {
        return FC_SEND_INVALID_BUFFER;
    }
    if (nLen == 0 ||nLen > FC_ASM_IU_LENGTH_MAX)
    {
        return FC_SEND_INVALID_LENGTH;
    }
    

    dc = (HBA_DEV_CB *)hDev;
    ret = HbaDevIoState(dc, IO_STATE_MODE_ASM);
    if (ret != FC_SUCCESS)
    {
        return ret;
    }

#if 0
    ret = hbaDevIsOnNet(dc);
    if (ret != DEV_SUCCESS)
    {
        return FC_NOT_ON_NET;
    }
#endif

    ret = hbaDevSendAsmMsg(dc, msgID, pMsg, nLen, WAIT_FOREVER);
        
    return ret;
}

/* 接收指定的ASM消息 */
FCUINT FC_NP_RecvMsg(FCHANDLE hDev, FCUINT msgID, FCUCHAR *pMsg, FCUINT *nLen)
{
    FCINT ret;
    HBA_DEV_CB *dc;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }

    if (pMsg == NULL)
    {
        return FC_RECV_INVALID_BUFFER;
    }

    if (nLen == NULL)
    {
        return FC_PARAMS_INVALID;
    }

    if (*nLen == 0)
    {
        return FC_RECV_LENGTH_IS_ZERO;
    }

    dc = (HBA_DEV_CB *)hDev;
    if (dc->status != HBA_DEV_STATUS_STARTED)
    {
        return FC_DEVICE_STATE_INVALID;
    }

#if 0    
    ret = hbaDevIsOnNet(dc);
    if (ret != DEV_SUCCESS)
    {
        return FC_NOT_ON_NET;
    }
#endif    
    ret = hbaDevRecvAsmMsg(dc, msgID, pMsg, nLen, NO_WAIT);
        
    return ret;
}

/* 注册ASM消息处理函数 */
FCUINT FC_NP_RegMsgHandler(FCHANDLE hDev, FC_ASM_RECVMSG_FUNCPTR func)
{
    HBA_DEV_CB *dc;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (func == NULL)
    {
        return FC_PARAMS_INVALID;
    }
    

    dc = (HBA_DEV_CB *)hDev;
    if (dc->status == HBA_DEV_STATUS_NONE)
    {
        return FC_DEVICE_STATE_INVALID;
    }
    
    if (hbaDevRegMsgHandler(dc, func) != DEV_SUCCESS) 
    {
        return FC_FAILURE;
    }
    
    return FC_SUCCESS;
}

/* 注销ASM消息处理函数 */
FCUINT FC_NP_UnRegMsgHandler(FCHANDLE hDev)
{
    HBA_DEV_CB *dc;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }

    dc = (HBA_DEV_CB *)hDev;
    if (dc->status == HBA_DEV_STATUS_NONE)
    {
        return FC_DEVICE_STATE_INVALID;
    }
    
    if (hbaDevUnRegMsgHandler(dc) != DEV_SUCCESS) 
    {
        return FC_FAILURE;
    }
    
    return FC_SUCCESS;
}



FCUINT FC_NP_GetPortLinkStatus(FCHANDLE hDev, FCUINT port, FCUINT *status)
{
    HBA_DEV_CB *dc;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (port != 0 && port != 1)
    {
        return FC_INVALID_PORT_NUMBER;
    }
    if (status == NULL)
    {
        return FC_PARAMS_INVALID;
    }

    dc = (HBA_DEV_CB *)hDev;
    *status = hbaDevGetPortLinkStatus(dc, port);
    
    return FC_SUCCESS;

}

FCUINT FC_NP_GetTemp(FCHANDLE hDev, FCINT *temperature)
{
    HBA_DEV_CB *dc;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (temperature == NULL)
    {
        return FC_PARAMS_INVALID;
    }

    dc = (HBA_DEV_CB *)hDev;
    *temperature = hbaDevGetTemp(dc); 
    
    return FC_SUCCESS;
}

FCUINT FC_NP_GetWorkStatus(FCHANDLE hDev, FCUINT *status)
{
    HBA_DEV_CB *dc;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (status == NULL)
    {
        return FC_PARAMS_INVALID;
    }

    dc = (HBA_DEV_CB *)hDev;
    *status = hbaDevGetWorkStatus(dc);
    
    return FC_SUCCESS;
}    

/*控制ASM发送和接收
control 0-禁止ASM发送和接收            FC_ASM_RUN_DISABLE
        1-允许ASM发送和接收            FC_ASM_RUN_ENAB
*/
FCUINT FC_NP_AsmRunControl(FCHANDLE hDev, FCUINT control)
{
    HBA_DEV_CB *dc;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (control != FC_ASM_RUN_DISABLE && control != FC_ASM_RUN_ENAB)
    {
        return FC_INVALID_RUN_CONTROL;
    }

    dc = (HBA_DEV_CB *)hDev;
    if (dc->status != HBA_DEV_STATUS_STARTED)
    {
        return FC_DEVICE_STATE_INVALID;
    }
    dc->asmRunControl = control;
    
    return FC_SUCCESS;
}

/* 时统管理接口 */
/* 获取FC节点机的时间 */
FCUINT FC_TM_GetRtc(FCHANDLE hDev, FCTime *time)
{
    HBA_DEV_CB *dc;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (time == NULL)
    {
        return FC_PARAMS_INVALID;
    }

    dc = (HBA_DEV_CB *)hDev;
    hbaDevGetRtc(dc, time);

    return FC_SUCCESS;
}

/* 设置FC节点机的时间 */
FCUINT FC_TM_SetRtc(FCHANDLE hDev, FCTime *time)
{
    HBA_DEV_CB *dc;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (time == NULL)
    {
        return FC_PARAMS_INVALID;
    }
    if (time->hour >= HOUR_MAX)
    {
        return FC_TM_INVALID_HOUR_VALUE;
    }

    if (time->minute >= MINUTE_MAX)
    {
        return FC_TM_INVALID_MINUTE_VALUE;
    }
    if (time->second >= SECOND_MAX)
    {
        return FC_TM_INVALID_SECOND_VALUE;
    }
    

    dc = (HBA_DEV_CB *)hDev;
    if (hbaDevSetRtc(dc, time) == ERROR)
    {
        return FC_TM_SET_RTC_FAIL;
    }

    return FC_SUCCESS;
}

FCUINT FC_TM_SetCarrierRTCSyn(FCHANDLE hDev, FCUINT carrier_rtc_enb, FCUINT mode, FCUINT pluse_duty)
{
    HBA_DEV_CB *dc;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (carrier_rtc_enb != 0  && carrier_rtc_enb != 1)
    {
        return FC_PARAMS_INVALID;
    }
    if (mode != 0 && mode != 1)
    {
        return FC_TM_INVALID_CARRIER_RTC_SYN_MODE;
    }
    if (pluse_duty <= 0)
    {
        return FC_TM_INVALID_PLUSE_DUTY;
    }

    dc = (HBA_DEV_CB *)hDev;
    hbaSetCarrierRTCSyn(dc, carrier_rtc_enb, mode, pluse_duty);
    
    return FC_SUCCESS;
}
/* 获取FC节点机的日期 */
FCUINT FC_TM_GetDateTime(FCHANDLE hDev, FCDate *date, FCTime *time)
{
    HBA_DEV_CB *dc;
    
    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (date == NULL)
    {
        return FC_PARAMS_INVALID;
    }

    if (time == NULL)
    {
        return FC_PARAMS_INVALID;
    }

    dc = (HBA_DEV_CB *)hDev;
    hbaDevGetDateTime(dc, date, time);
    
    return FC_SUCCESS;
}

/* 设置FC节点机的日期 */
FCUINT FC_TM_SetDate(FCHANDLE hDev, FCDate *date)
{
    FCUINT ret, sid, clk_sync_role;
    UINT32 value, index;
    HBA_DEV_CB *dc;
    FC_ELS_CONFIG ecSend;


    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (date == NULL)
    {
        return FC_PARAMS_INVALID;
    }

    if ( date->year < _BASE_YEAR)
    {
        return FC_TM_INVALID_YEAR_VALUE;
    }

    if ( (date->month < MONTH_MIN) || (date->month > MONTH_MAX))
    {
        return FC_TM_INVALID_MONTH_VALUE;
    }

    if ( (date->day < DAY_MIN) || (date->day > DAY_MAX))
    {
        return FC_TM_INVALID_DAY_VALUE;
    }

    
    dc = (HBA_DEV_CB *)hDev;

    /* 只有在这两种状态下才能访问配置数据 */
    if (dc->status != HBA_DEV_STATUS_STARTED && dc->status != HBA_DEV_STATUS_INITED)
    {
        return FC_DEVICE_STATE_INVALID;
    }
    
    clk_sync_role = dc->configBlock.port_config.clk_sync_role;
    if (clk_sync_role != FC_NET_CLK_SYNC_ROLE_SERVER_MASTER)
    {
        return FC_TM_ROLE_ILLE_OPERATION;
    }

    if (hbaDevSetDate(dc, date) != OK)
    {
        return FC_TM_SET_DATE_FAIL;
    }

#if 0    /* 2018-4-4: deleted by Huilin, NC有些情况下也是不能发WDT帧的，比如刚起来的观望期。因此WDT应该在定时处理的地方统一控制 */
    /* 发送WDT帧，通知其他节点时间有变化 */
    if (dc->configBlock.port_config.role == FC_NET_ROLE_NC)
    {       
        sid = dc->configBlock.port_config.port_id;
        value = dc->configBlock.port_config.wdt_loader_period;
        index = (unsigned char)sid;
        if (index >= FC_SW_PORT_NUM_MAX)
        {
            return FC_NET_TBL_INDEX_INVALID;
        }
        dc->onNetTbl.Status[index] = FC_NODE_STATE_ON_LINE;
        hbaConstructE1_0203(&ecSend, sid, value, dc->onNetTbl.Status, date);
        ecSend.port0 = 1;
        ecSend.port1 = 1;
        
        /* 发送ELS帧 */
        ret = hbaElsSend(dc, &ecSend);
        if (ret)
        {
            /* 失败*/
            /*printf("dbg send els failed ret=%d\n", ret);*/
        }
    }
#endif

    return FC_SUCCESS;
}

/*设置节点的同步角色*/
FCUINT FC_TM_SyncModeSet(FCHANDLE hDev, FCUINT mode)
{
    HBA_DEV_CB *dc;

    if (hDev == NULL)
    {
           return FC_INVALID_HANDLE;
    }

    if (mode != FC_SYNC_MODE_SERVER && mode != FC_SYNC_MODE_CLIENT)
       {
        return FC_PARAMS_INVALID;
    }

    dc = (HBA_DEV_CB *)hDev;

    /* 只有在这两种状态下才能访问配置数据 */
    if (dc->status != HBA_DEV_STATUS_STARTED && dc->status != HBA_DEV_STATUS_INITED)
    {
        return FC_DEVICE_STATE_INVALID;
    }
    
    dc->configBlock.port_config.clk_sync_role = mode;
    hbaDevSetRTCRxTx(dc, 0,0);
    
    return FC_SUCCESS;
}

/*使能同步接收*/
FCUINT FC_TM_SyncEnable(FCHANDLE hDev)
{
    HBA_DEV_CB *dc;
    
    if (hDev == NULL)
    {
           return FC_INVALID_HANDLE;
    }
    dc = (HBA_DEV_CB *)hDev;

    /* 只有在这两种状态下才能访问配置数据 */
    if (dc->status != HBA_DEV_STATUS_STARTED && dc->status != HBA_DEV_STATUS_INITED)
    {
        return FC_DEVICE_STATE_INVALID;
    }
    
    if(dc->configBlock.port_config.clk_sync_role == FC_NET_CLK_SYNC_ROLE_SERVER_MASTER)
    {
        hbaDevSetRTCRxTx(dc, 0, 1);    
    }
    else
    {
        hbaDevSetRTCRxTx(dc, 1, 0);    
    }

    return FC_SUCCESS;
}

/*禁止同步接收*/
FCUINT FC_TM_SyncDisable(FCHANDLE hDev)
{
    HBA_DEV_CB *dc;
    
    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }

    dc = (HBA_DEV_CB *)hDev;
    /* 只有在这两种状态下才能访问配置数据 */
    if (dc->status != HBA_DEV_STATUS_STARTED && dc->status != HBA_DEV_STATUS_INITED)
    {
        return FC_DEVICE_STATE_INVALID;
    }
    
    hbaDevSetRTCRxTx(dc, 0,0);

    return FC_SUCCESS;
}

/******************************************************************************
* 网络管理接口
******************************************************************************/

/*设置端口的网络管理角色。只能NC设置为BNC、或者BNC设置为NC*/
FCUINT FC_NM_RoleSet(FCHANDLE hDev, FCUINT nmRole)
{
    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }

    if (nmRole != FC_NET_ROLE_NC && nmRole != FC_NET_ROLE_BNC)
    {
        return FC_PARAMS_INVALID;
    }

    return hbaElsRoleSet((HBA_DEV_CB *)hDev, nmRole);
}

/*取得端口的网络管理角色*/
FCUINT FC_NM_RoleGet(FCHANDLE hDev,    FCUINT *nmRole)
{
    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (nmRole == NULL)
    {
        return FC_PARAMS_INVALID;
    }
    
    return hbaElsRoleGet((HBA_DEV_CB *)hDev, nmRole);
}

/*取得时钟同步角色*/
FCUINT FC_TM_SyncModeGet(FCHANDLE hDev, FCUINT *mode)
{
    HBA_DEV_CB *dc;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (mode == NULL)
    {
        return FC_PARAMS_INVALID;
    }

    dc = (HBA_DEV_CB *)hDev; 
    /* 只有在这两种状态下才能访问配置数据 */
    if (dc->status != HBA_DEV_STATUS_STARTED && dc->status != HBA_DEV_STATUS_INITED)
    {
        return FC_DEVICE_STATE_INVALID;
    }
    
    *mode = dc->configBlock.port_config.clk_sync_role;
    
    return FC_SUCCESS;    
}

/*取得上网状态表*/
FCUINT FC_NM_GetOnNetTable(FCHANDLE hDev, OnNetTbl *pOnNetTbl)
{
    HBA_DEV_CB *dc;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (pOnNetTbl == NULL)
    {
        return FC_PARAMS_INVALID;
    }
    
    dc = (HBA_DEV_CB *)hDev;     
    if (dc->status != HBA_DEV_STATUS_STARTED)
    {
        return FC_DEVICE_STATE_INVALID;
    }
    
    memcpy(pOnNetTbl, &dc->onNetTbl, FC_SW_PORT_NUM_MAX);
    
    return FC_SUCCESS;    
}

/*取得本地上网状态*/
FCUINT FC_NM_GetOnNetState(FCHANDLE hDev, FCUINT *pState)
{
    FCUINT index;
    HBA_DEV_CB *dc;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (pState == NULL)
    {
        return FC_PARAMS_INVALID;
    }
    dc = (HBA_DEV_CB *)hDev; 
    if (dc->status != HBA_DEV_STATUS_STARTED)
    {
        return FC_DEVICE_STATE_INVALID;
    }
    
    index = (dc->configBlock.port_config.port_id & 0xFF);
    if (index >= FC_SW_PORT_NUM_MAX)
    {
        return FC_FAILURE;
    }
    *pState = dc->onNetTbl.Status[index];
    
    return FC_SUCCESS;    
}

/*取得网络节点统计信息*/
FCUINT FC_NM_GetLocalStatistics(FCHANDLE hDev, NetStatistics *pNetStatistics)
{

    HBA_DEV_CB *dc;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (pNetStatistics == NULL)
    {

        return FC_FAILURE;
    }

    dc = (HBA_DEV_CB *)hDev;
    if (dc->status != HBA_DEV_STATUS_STARTED)
    {
        return FC_DEVICE_STATE_INVALID;
    }
    
    hbaDevGetLocalStatistics(dc, pNetStatistics);

    return FC_SUCCESS;
    
}

/* 加载交换机配置*/
FCUINT FC_NM_NC_LoadSwConfig(FCHANDLE hDev,FCUINT port, SwConfig *pSwConfig)
{
    FCUINT ret, sid, did, delay, role;
    HBA_DEV_CB * dc;
    FC_ELS_CONFIG elsConfig;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (port != FC_PORT_0 && port != FC_PORT_1)
    {
        return FC_INVALID_PORT_NUMBER;
    }
    if (pSwConfig == NULL)
    {
        return FC_PARAMS_INVALID;
    }

    dc = (HBA_DEV_CB *)hDev;
    if (dc->status != HBA_DEV_STATUS_STARTED)
    {
        return FC_DEVICE_STATE_INVALID;
    }

    /* 仅NC可以执行 */
    role = dc->configBlock.port_config.role;
    if (role != FC_NET_ROLE_NC)
    {
        ret = FC_NM_ROLE_ILLE_OPERATION;
        return ret;
    }
    
    dc->elsKeyRecvList[E3_0105] = RECV_ELS_INIT;
    
    sid = dc->configBlock.port_config.port_id;
    did = FCID_SWITCH;
    hbaConstructE1_0105(&elsConfig, sid, did, pSwConfig);
    if (port == FC_PORT_0)
    {
        elsConfig.port0 = 1;
        elsConfig.port1 = 0;
    }
    else if (port == FC_PORT_1)
    {
        elsConfig.port0 = 0;
        elsConfig.port1 = 1;
    }
    else
    {
        return FC_FAILURE;
    }

    /* 发送ELS帧 */
    ret = hbaElsSend(dc, &elsConfig);
    if (ret)
    {
        /* 失败*/
        /*printf("E1_0105 send els failed\n");*/
        return FC_NM_FRAME_SEND_FAILED;
    }

    delay = 0;
    while (delay < FC_ELS_LOAD_SWDATA_TIME_OUT)
    {
        if (dc->elsKeyRecvList[E3_0105] == RECV_ELS_COMPLETE)
        {
            SwConfig * pSwConfigRet;
            FCUINT result;

            dc->elsKeyRecvList[E3_0105] = RECV_ELS_INIT;
        
            pSwConfigRet = (SwConfig *)dc->elsConfig[E3_0105].payload;
            pSwConfigRet->configMode     = HbaUlongByteSwap(pSwConfigRet->configMode);
            pSwConfigRet->configLength     = HbaUlongByteSwap(pSwConfigRet->configLength);
            pSwConfigRet->checksum         = HbaUlongByteSwap(pSwConfigRet->checksum);            
            
            result = *(FCUINT *)(dc->elsConfig[E3_0105].payload + sizeof(SwConfig));
            result =  HbaUlongByteSwap(result);

            if (memcmp(pSwConfigRet, pSwConfig, sizeof(SwConfig)) != 0)
            {
                return FC_FAILURE;
            }

            if ((result & 0xFF) == 0)
            {
                 return FC_SUCCESS;
            }
            else
            {
                 return FC_FAILURE;
            }
        }

        taskDelay(FC_ELS_SYNC_IO_DELAY_STEP);
        delay = delay + FC_ELS_SYNC_IO_DELAY_STEP;
    }
    if (delay >= FC_ELS_LOAD_SWDATA_TIME_OUT)
    {
        /*printf("E1_0105 wait recv els(E3_0105) time out\n");*/
        return FC_NM_SYNC_IO_WAIT_FAILED;
    }
    return FC_SUCCESS;

}



/* 加载交换机配置*/
FCUINT FC_NM_NC_LoadSwConfigData(FCHANDLE hDev,FCUINT port, SwConfigData *pSwConfigData)
{
    FCUINT ret, sid, did, delay, role;
    HBA_DEV_CB *dc;
    FC_ELS_CONFIG elsConfig;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (port != FC_PORT_0 && port != FC_PORT_1)
    {
        return FC_INVALID_PORT_NUMBER;
    }
    if (pSwConfigData == NULL)
    {
        return FC_PARAMS_INVALID;
    }

    dc = (HBA_DEV_CB *)hDev;
    if (dc->status != HBA_DEV_STATUS_STARTED)
    {
        return FC_DEVICE_STATE_INVALID;
    }
    
    role = dc->configBlock.port_config.role;
    if (role != FC_NET_ROLE_NC)
    {
        return FC_NM_ROLE_ILLE_OPERATION;
    }
    
    dc->elsKeyRecvList[E3_0106] = RECV_ELS_INIT;
    
    sid = dc->configBlock.port_config.port_id;
    did = FCID_SWITCH;
    hbaConstructE1_0106(&elsConfig, sid, did, pSwConfigData);
    if (port == FC_PORT_0)
    {
        elsConfig.port0 = 1;
        elsConfig.port1 = 0;
    }
    else if (port == FC_PORT_1)
    {
        elsConfig.port0 = 0;
        elsConfig.port1 = 1;
    }
    else
    {
        return FC_FAILURE;
    }

    /* 发送ELS帧 */
    ret = hbaElsSend(dc, &elsConfig);
    if (ret)
    {
        /* 失败*/
        /*printf("E1_0105 send els failed\n");*/
        return FC_NM_FRAME_SEND_FAILED;
    }

    delay = 0;
    while (delay < FC_ELS_SYNC_IO_TIME_OUT)
    {
        if (dc->elsKeyRecvList[E3_0106] == RECV_ELS_COMPLETE)
        {
            SwConfigData * pSwConfigDataRet;
            FCUINT result;

            dc->elsKeyRecvList[E3_0106] = RECV_ELS_INIT;
            
            pSwConfigDataRet = (SwConfigData *)dc->elsConfig[E3_0106].payload;
            pSwConfigDataRet->endFlag = HbaUlongByteSwap(pSwConfigDataRet->endFlag);
            pSwConfigDataRet->length  = HbaUlongByteSwap(pSwConfigDataRet->length);
            pSwConfigDataRet->order   = HbaUlongByteSwap(pSwConfigDataRet->order);
            
            result = *(FCUINT *)(dc->elsConfig[E3_0106].payload + sizeof(SwConfigData) );
            result =  HbaUlongByteSwap(result);
            
            if (memcmp(pSwConfigDataRet, pSwConfigData, sizeof(SwConfigData)) != 0)
            {
                 return FC_FAILURE;
            }

            if ((result & 0xFF) == 0)
            {
                  return FC_SUCCESS;
            }
            else
            {
                  return FC_FAILURE;
            }

        }
        taskDelay(FC_ELS_SYNC_IO_DELAY_STEP);
        delay =delay + FC_ELS_SYNC_IO_DELAY_STEP;
    }
    if (delay >= FC_ELS_SYNC_IO_TIME_OUT)
    {
        /*printf("E1_0106 wait recv els(E3_0106) time out\n");*/
        return FC_NM_SYNC_IO_WAIT_FAILED;
    }
    return FC_SUCCESS;

}

/*取得交换机link状态*/
FCUINT FC_NM_GetSwLinkStatus(FCHANDLE hDev, SwLinkStatusTbl *pSwLinkStatusTbl)
{
    HBA_DEV_CB *dc;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }

    if (pSwLinkStatusTbl == NULL)
    {
        return FC_PARAMS_INVALID;
    }
    
    dc = (HBA_DEV_CB *)hDev;
    if (dc->status != HBA_DEV_STATUS_STARTED)
    {
        return FC_DEVICE_STATE_INVALID;
    }

    memcpy(pSwLinkStatusTbl, &dc->swLinkStatusTbl, sizeof(SwLinkStatusTbl));
    
    return FC_SUCCESS;
}

/*取得交换机广播的应用软件信息和BSP*/
FCUINT FC_NM_GetSwVersion(FCHANDLE hDev, FCUINT port, SW_IMPSoftWareVersion *pSwAppVersion, SW_IMPSoftWareVersion *pSwBspVersion)
{
    HBA_DEV_CB *dc;
    FCUINT role;
    
    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (port != FC_PORT_0 && port != FC_PORT_1)
    {
        return FC_INVALID_PORT_NUMBER;
    }
    if (pSwAppVersion == NULL || pSwBspVersion == NULL)
    {
        return FC_PARAMS_INVALID;
    }
    
    dc = (HBA_DEV_CB *)hDev; 
    if (dc->status != HBA_DEV_STATUS_STARTED)
    {
        return FC_DEVICE_STATE_INVALID;
    }

    role = dc->configBlock.port_config.role;
    if (role != FC_NET_ROLE_NC)
    {
        return FC_NM_ROLE_ILLE_OPERATION;
    }
    
    /*应用软件信息*/
    memcpy(pSwAppVersion, &dc->swAppVersion[port], sizeof(SW_IMPSoftWareVersion));

    /*BSP*/
    memcpy(pSwBspVersion, &dc->swBspVersion[port], sizeof(SW_IMPSoftWareVersion));

    return FC_SUCCESS;
}

/*取得交换机自检结果*/
FCUINT FC_NM_NC_GetSwBitResult(FCHANDLE hDev, FCINT port, FCUINT64 *pSwBitResult)
{
    FCUINT ret, sid, did, delay, role;
    HBA_DEV_CB *dc;
    FC_ELS_CONFIG elsConfig;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (port != FC_PORT_0 && port != FC_PORT_1)
    {
        return FC_INVALID_PORT_NUMBER;
    }
    if (pSwBitResult == NULL)
    {
        return FC_PARAMS_INVALID;
    }
    

    dc = (HBA_DEV_CB *)hDev;
    if (dc->status != HBA_DEV_STATUS_STARTED)
    {
        return FC_DEVICE_STATE_INVALID;
    }

    role = dc->configBlock.port_config.role;
    if (role != FC_NET_ROLE_NC)
    {
        return FC_NM_ROLE_ILLE_OPERATION;
    }
    
    dc->elsKeyRecvList[E3_0103] = RECV_ELS_INIT;
    
    sid = dc->configBlock.port_config.port_id;
    did = FCID_SWITCH;
    hbaConstructE2_0103(&elsConfig, sid, did);
    if (port == FC_PORT_0)
    {
        elsConfig.port0 = 1;
        elsConfig.port1 = 0;
    }
    else if (port == FC_PORT_1)
    {
        elsConfig.port0 = 0;
        elsConfig.port1 = 1;
    }
    else
    {
        /* cannot come here  */
        return FC_FAILURE;
    }

    /* 发送ELS帧 */
    ret = hbaElsSend(dc, &elsConfig);
    if (ret)
    {
        /* 失败*/
        /*printf("E2_0103 send els failed\n");*/
        return FC_NM_FRAME_SEND_FAILED;
    }

    delay = 0;
    while (delay < FC_ELS_SYNC_IO_TIME_OUT)
    {
        if (dc->elsKeyRecvList[E3_0103] == RECV_ELS_COMPLETE)
        {
            FCUINT64 SwBitResult;
            
            SwBitResult = *(FCUINT64 *)dc->elsConfig[E3_0103].payload;
            *pSwBitResult = HbaUlonglongByteSwap(SwBitResult);
                
            dc->elsKeyRecvList[E3_0103] = RECV_ELS_INIT;
            break;
        }
        taskDelay(FC_ELS_SYNC_IO_DELAY_STEP);
        delay =delay + FC_ELS_SYNC_IO_DELAY_STEP;
    }
    if (delay >= FC_ELS_SYNC_IO_TIME_OUT)
    {
        /*printf("E2_0103 wait recv els(E3_0103) time out\n");*/
        return FC_NM_SYNC_IO_WAIT_FAILED;
    }
    return FC_SUCCESS;
}

/*设置交换机方案号*/
FCUINT FC_NM_NC_SetMonitorScheme(FCHANDLE hDev, FCINT port, FCINT SchemeNo)
{
    FCUINT ret, sid, did, delay, role;
    HBA_DEV_CB *dc;
    FC_ELS_CONFIG elsConfig;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (port != FC_PORT_0 && port != FC_PORT_1)
    {
        return FC_INVALID_PORT_NUMBER;
    }

    dc = (HBA_DEV_CB *)hDev;
    if (dc->status != HBA_DEV_STATUS_STARTED)
    {
        return FC_DEVICE_STATE_INVALID;
    }

    role = dc->configBlock.port_config.role;
    if (role != FC_NET_ROLE_NC)
    {
        return FC_NM_ROLE_ILLE_OPERATION;
    }
    /* clear response */
    dc->elsKeyRecvList[E3_0104] = RECV_ELS_INIT;

    /* send request */
    sid = dc->configBlock.port_config.port_id;
    did = FCID_SWITCH;
    hbaConstructE1_0104(&elsConfig, sid, did, SchemeNo);    
    if (port == FC_PORT_0)
    {
        elsConfig.port0 = 1;
        elsConfig.port1 = 0;
    }
    else if (port == FC_PORT_1)
    {
        elsConfig.port0 = 0;
        elsConfig.port1 = 1;
    }
    else
    {
        return FC_FAILURE;
    }

    /* 发送ELS帧 */
    ret = hbaElsSend(dc, &elsConfig);
    if (ret)
    {
        /* 失败*/
        /*printf("E1_0104 send els failed\n");*/
        return FC_NM_FRAME_SEND_FAILED;
    }

    delay = 0;
    while (delay < FC_ELS_SYNC_IO_TIME_OUT)
    {
           if (dc->elsKeyRecvList[E3_0104] == RECV_ELS_COMPLETE)
        {
             FCINT schemeNo2; 
            FCUINT result;
             
            dc->elsKeyRecvList[E3_0104] = RECV_ELS_INIT;
             
            schemeNo2 = *(FCINT *)(dc->elsConfig[E3_0104].payload);
            schemeNo2 = HbaUlongByteSwap(schemeNo2);
            
            result = *(FCUINT *)(dc->elsConfig[E3_0104].payload + sizeof(FCINT));
            result =  HbaUlongByteSwap(result);
            
             if (schemeNo2 != SchemeNo)
            {
                return FC_FAILURE;
            }
                          
            if ((result & 0xFF) == 0)
            {
                   return FC_SUCCESS;
            }
            else
            {
                   return FC_FAILURE;
            }
           
            break;
        }
        
        taskDelay(FC_ELS_SYNC_IO_DELAY_STEP);
        delay =delay + FC_ELS_SYNC_IO_DELAY_STEP;
    }
    
    if (delay >= FC_ELS_SYNC_IO_TIME_OUT)
    {
        /*printf("E1_0104 wait recv els(E3_0104) time out\n");*/
        return FC_NM_SYNC_IO_WAIT_FAILED;
    }
    
    return FC_SUCCESS;
    
}

/*授权上网请求*/
FCUINT FC_NM_NC_GrantNrtOnNet(FCHANDLE hDev, FCUINT PortId)
{
    FCUINT ret, sid, did, role;
    FC_ELS_CONFIG ecSend;
    HBA_DEV_CB *dc;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if ((PortId & 0xFF) >= FC_SW_PORT_NUM_MAX)
    {
        return FC_NM_INVALID_PORT_ID;
    }

    dc = (HBA_DEV_CB *)hDev;
    if (dc->status != HBA_DEV_STATUS_STARTED)
    {
        return FC_DEVICE_STATE_INVALID;
    }

    role = dc->configBlock.port_config.role;
    if (role != FC_NET_ROLE_NC)
    {
        return FC_NM_ROLE_ILLE_OPERATION;
    }

    sid = dc->configBlock.port_config.port_id;
    did = PortId;
    dc->onNetTbl.Status[PortId & 0xFF] = 1;
    hbaConstructE1_0202(&ecSend, sid, did, &dc->onNetTbl);
    ecSend.port0 = 1;
    ecSend.port1 = 1;

    /* 发送ELS帧 */
    ret = hbaElsSend(dc, &ecSend);
    if (ret)
    {
        /* 失败*/
        /*printf("E1_0202 send els failed\n");*/
        return FC_NM_FRAME_SEND_FAILED;
    }    
    
    return FC_SUCCESS;    
}

/*授权下网请求*/
FCUINT FC_NM_NC_GrantNrtOffNet(FCHANDLE hDev, FCUINT PortId)
{
    FCUINT ret, sid, did, role;
    FC_ELS_CONFIG ecSend;
    HBA_DEV_CB *dc;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if ((PortId & 0xFF) >= FC_SW_PORT_NUM_MAX)
    {
        return FC_NM_INVALID_PORT_ID;
    }

    dc = (HBA_DEV_CB *)hDev;
    if (dc->status != HBA_DEV_STATUS_STARTED)
    {
        return FC_DEVICE_STATE_INVALID;
    }

    role = dc->configBlock.port_config.role;
    if (role != FC_NET_ROLE_NC)
    {
        return FC_NM_ROLE_ILLE_OPERATION;
    }
    
    sid = dc->configBlock.port_config.port_id;
    did = PortId;
    dc->onNetTbl.Status[PortId & 0xFF] = 0;
    hbaConstructE1_0202(&ecSend, sid, did, &dc->onNetTbl);
    ecSend.port0 = 1;
    ecSend.port1 = 1;

    /* 发送ELS帧 */
    ret = hbaElsSend(dc, &ecSend);
    if (ret)
    {
        /* 失败*/
        /*printf("E1_0202 send els failed\n");*/
        return FC_NM_FRAME_SEND_FAILED;
    }    
    
    return FC_SUCCESS;    

}

/*网络重构请求*/
FCUINT FC_NM_NC_NetRestruct(FCHANDLE hDev, FCUINT configNum)
{
    FCUINT ret, sid, did, role;
    HBA_DEV_CB *dc;
    FC_ELS_CONFIG ecSend;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    
    dc = (HBA_DEV_CB *)hDev;
    if (dc->status != HBA_DEV_STATUS_STARTED)
    {
        return FC_DEVICE_STATE_INVALID;
    }

    role = dc->configBlock.port_config.role;
    if (role != FC_NET_ROLE_NC)
    {
        return FC_NM_ROLE_ILLE_OPERATION;
    }

    /* clear response */
    dc->elsKeyRecvList[E3_0102] = RECV_ELS_INIT;

    /* send request */
    sid = dc->configBlock.port_config.port_id;
    did = FCID_SWITCH;

    hbaConstructE1_0102(&ecSend, sid, did, configNum);
    ecSend.port0 = 1;
    ecSend.port1 = 1;
    
    /* 发送ELS帧 */
    ret = hbaElsSend(dc, &ecSend);
    if (ret)
    {
        /* 失败*/
        /*printf("E1_0102 send els failed did=0x%08x\n", did);*/
        return FC_NM_FRAME_SEND_FAILED;
    }    

    return FC_SUCCESS;
}

/*取得网络节点自检结果*/
FCUINT FC_NM_NC_GetNrtBitResult(FCHANDLE hDev, FCUINT PortId, FCUINT *pNrtBitResult)
{
    FCUINT ret, sid, did, delay, role;
    HBA_DEV_CB *dc;
    FC_ELS_CONFIG elsConfig;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    
    if ((PortId & 0xFF) >= FC_SW_PORT_NUM_MAX)
    {
        return FC_NM_INVALID_PORT_ID;
    }
    
    if (pNrtBitResult == NULL)
    {
        return FC_PARAMS_INVALID;
    }
    
    dc = (HBA_DEV_CB *)hDev;
    if (dc->status != HBA_DEV_STATUS_STARTED)
    {
        return FC_DEVICE_STATE_INVALID;
    }

    role = dc->configBlock.port_config.role;
    if (role != FC_NET_ROLE_NC)
    {
        return FC_NM_ROLE_ILLE_OPERATION;
    }    
    
    /* clear response */
    dc->elsKeyRecvList[E3_0201] = RECV_ELS_INIT;

    /* send request */
    sid = dc->configBlock.port_config.port_id;
    did = PortId;
    hbaConstructE2_0201(&elsConfig, sid, did);
    elsConfig.port0 = 1;
    elsConfig.port1 = 1;

    /* 发送ELS帧 */
    ret = hbaElsSend(dc, &elsConfig);
    if (ret)
    {
        /* 失败*/
        /*printf("E2_0201 send els failed\n");*/
        return FC_NM_FRAME_SEND_FAILED;
    }

    /* wait and recv response */
    delay = 0;
    while (delay < FC_ELS_SYNC_IO_TIME_OUT)
    {
        if (dc->elsKeyRecvList[E3_0201] == RECV_ELS_COMPLETE)
        {
            FCUINT nrtBitResult;
            
            nrtBitResult = *(FCUINT *)dc->elsConfig[E3_0201].payload;            
            *pNrtBitResult = HbaUlongByteSwap(nrtBitResult);
            
            dc->elsKeyRecvList[E3_0201] = RECV_ELS_INIT;
            break;
        }
        taskDelay(FC_ELS_SYNC_IO_DELAY_STEP);
        delay =delay + FC_ELS_SYNC_IO_DELAY_STEP;
    }
    if (delay >= FC_ELS_SYNC_IO_TIME_OUT)
    {
        /*printf("E2_0201 wait recv els(E3_0201) time out\n");*/
        return FC_NM_SYNC_IO_WAIT_FAILED;
    }
    
    return FC_SUCCESS;
}

/*取得网络节点统计信息*/
FCUINT FC_NM_NC_GetNetStatistics(FCHANDLE hDev, FCUINT portId, NetStatistics *pNetStatistics)
{
    FCUINT ret, sid, did, delay, nmRole;
    HBA_DEV_CB *dc;
    FC_ELS_CONFIG elsConfig;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    
    if ((portId & 0xFF) >= FC_SW_PORT_NUM_MAX)
    {
        return FC_NM_INVALID_PORT_ID;
    }
    
    if (pNetStatistics == NULL)
    {
        return FC_PARAMS_INVALID;
    }
    
    dc = (HBA_DEV_CB *)hDev;
    if (dc->status != HBA_DEV_STATUS_STARTED)
    {
        return FC_DEVICE_STATE_INVALID;
    }

    nmRole = dc->configBlock.port_config.role;
    if (nmRole != FC_NET_ROLE_NC)
    {
        return FC_NM_ROLE_ILLE_OPERATION;
    }    
    
    dc->elsKeyRecvList[E3_0202] = RECV_ELS_INIT;
    
    sid = dc->configBlock.port_config.port_id;
    did = portId;
    hbaConstructE2_0202(&elsConfig, sid, did);
    elsConfig.port0 = 1;
    elsConfig.port1 = 1;

    /* 发送ELS帧 */
    ret = hbaElsSend(dc, &elsConfig);
    if (ret)
    {
        /* 失败*/
        /*printf("E2_0202 send els failed\n");*/
        return FC_NM_FRAME_SEND_FAILED;
    }
    
    delay = 0;
    while (delay < FC_ELS_SYNC_IO_TIME_OUT)
    {
        if (dc->elsKeyRecvList[E3_0202] == RECV_ELS_COMPLETE)
        {
            memcpy(pNetStatistics, dc->elsConfig[E3_0202].payload, dc->elsConfig[E3_0202].length);
            hbaDevConvertStatistics(pNetStatistics);  /* 2018-3-14: 网络序到主机序的转换 */
            
            dc->elsKeyRecvList[E3_0202] = RECV_ELS_INIT;
            break;
        }
        taskDelay(FC_ELS_SYNC_IO_DELAY_STEP);
        delay =delay + FC_ELS_SYNC_IO_DELAY_STEP;
    }
    if (delay >= FC_ELS_SYNC_IO_TIME_OUT)
    {
        /*printf("E2_0202 wait recv els(E3_0202) time out\n");*/
        return FC_NM_SYNC_IO_WAIT_FAILED;
    }
    
    return FC_SUCCESS;
}

/*判断网络节点是否在网*/
FCUINT FC_NM_NRT_NcIsOnNet(FCHANDLE hDev, FCUINT *pNcIsOnNet)
{
    HBA_DEV_CB *dc;
    FCUINT nmRole;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (pNcIsOnNet == NULL)
    {
        return FC_PARAMS_INVALID;
    }

    dc = (HBA_DEV_CB *)hDev;
    if (dc->status != HBA_DEV_STATUS_STARTED)
    {
        return FC_DEVICE_STATE_INVALID;
    }

    nmRole = dc->configBlock.port_config.role;
    if (nmRole == FC_NET_ROLE_NC)
    {
        *pNcIsOnNet = 1;
    }
    else
    {
        if (dc->ncFcid == FC_FCID_EMPTY)
        {
            *pNcIsOnNet = 0;
        }
        else
        {
            *pNcIsOnNet = 1;
        }
    }

    return FC_SUCCESS;
}

/*发起上网请求*/
FCUINT FC_NM_NRT_OnNetReq(FCHANDLE hDev)
{
    FCUINT ret, sid, did, nmRole;
    HBA_DEV_CB *dc;
    FC_ELS_CONFIG ecSend;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    
    dc = (HBA_DEV_CB *)hDev;
    if (dc->status != HBA_DEV_STATUS_STARTED)
    {
        return FC_DEVICE_STATE_INVALID;
    }

    nmRole = dc->configBlock.port_config.role;

    /*只有BNC和NRT节点可以发起上网请求*/
    if (nmRole == FC_NET_ROLE_NC)
    {
        return FC_NM_ROLE_ILLE_OPERATION;
    }

    /*如果没有收到NC的心跳帧，不能发起上网请求*/
    if (dc->ncFcid == FC_FCID_EMPTY)
    {
        return FC_NM_NC_IS_OFF_LINE;
    }

    sid = dc->configBlock.port_config.port_id;
    did = dc->ncFcid;
    hbaConstructE4_0203(&ecSend, sid, did, 1);
    ecSend.port0 = 1;
    ecSend.port1 = 1;
    
    ret = hbaElsSend(dc, &ecSend);
    if (ret)
    {
        return FC_NM_FRAME_SEND_FAILED;
    }

    /*发送成功后，返回。应用通过周期检查网表获取上网请求的回复*/

    return FC_SUCCESS;
}

/*发起下网请求*/
FCUINT FC_NM_NRT_OffNetReq(FCHANDLE hDev)
{
    FCUINT ret, sid, did, nmRole;
    HBA_DEV_CB *dc;
    FC_ELS_CONFIG ecSend;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }

    dc = (HBA_DEV_CB *)hDev; 
    if (dc->status != HBA_DEV_STATUS_STARTED)
    {
        return FC_DEVICE_STATE_INVALID;
    }

    nmRole = dc->configBlock.port_config.role;

    /*只有BNC和NRT节点可以发起上网请求*/
    if (nmRole == FC_NET_ROLE_NC)
    {
        return FC_NM_ROLE_ILLE_OPERATION;
    }

    /*如果没有收到NC的心跳帧，不能发起上网请求*/
    if (dc->ncFcid == FC_FCID_EMPTY)
    {
        return FC_NM_NC_IS_OFF_LINE;
    }
    
    sid = dc->configBlock.port_config.port_id;
    did = dc->ncFcid;
    hbaConstructE4_0203(&ecSend, sid, did, 0);
    ecSend.port0 = 1;
    ecSend.port1 = 1;
    
    if (ret)
    {
        return FC_NM_FRAME_SEND_FAILED;
    }

    /*发送成功后，返回。应用通过周期检查网表获取上网请求的回复*/

    return FC_SUCCESS;
}

/*使能WDT*/
FCUINT FC_NM_WDTEnable(FCHANDLE hDev, FCUINT mode)
{
    HBA_DEV_CB *dc;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }

    if (mode != FC_WDT_LOCAL_MODE && mode != FC_WDT_NET_MODE)
    {
        return FC_PARAMS_INVALID;
    }

    dc = (HBA_DEV_CB *)hDev; 
    if (dc->status != HBA_DEV_STATUS_STARTED)
    {
        return FC_DEVICE_STATE_INVALID;
    }
    /*只有NC节点才能打开或关闭WDT使能，非NC节点的WDT使能永远是禁止的*/
    if (dc->configBlock.port_config.role != FC_NET_ROLE_NC)
    {
        return FC_NM_ROLE_ILLE_OPERATION;
    }

    if (mode == FC_WDT_LOCAL_MODE)
    {
        dc->wdtLoaderPeriodEnab = FC_WDT_LOADER_PERIOD_DISABLE;
    }
    else
    {
        dc->wdtLoaderPeriodEnab = FC_WDT_LOADER_PERIOD_ENAB;
    }

    return FC_SUCCESS;
}

/*禁止WDT*/
FCUINT FC_NM_WDTDisable(FCHANDLE hDev, FCUINT mode)
{
    HBA_DEV_CB *dc;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }

    if (mode != FC_WDT_LOCAL_MODE && mode != FC_WDT_NET_MODE)
    {
        return FC_PARAMS_INVALID;
    }
    
    dc = (HBA_DEV_CB *)hDev; 
    if (dc->status != HBA_DEV_STATUS_STARTED)
    {
        return FC_DEVICE_STATE_INVALID;
    }

    /*只有NC节点才能打开或关闭WDT使能，非NC节点的WDT使能永远是禁止的*/
    if (dc->configBlock.port_config.role != FC_NET_ROLE_NC)
    {
        return FC_NM_ROLE_ILLE_OPERATION;
    }

    if (mode == FC_WDT_LOCAL_MODE)
    {
        /*控制本地timer禁止*/
    }
    else
    {
        dc->wdtLoaderPeriodEnab = FC_WDT_LOADER_PERIOD_DISABLE;
    }

    return FC_SUCCESS;
}

/*取得WDT信息*/
FCUINT FC_NM_GetWDTValue(FCHANDLE hDev, FCUINT *pWdt, FCUINT *pWdtLoader)
{
    HBA_DEV_CB *dc;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (pWdt == NULL)
    {
        return FC_PARAMS_INVALID;
    }
    if (pWdtLoader == NULL)
    {
        return FC_PARAMS_INVALID;
    }
    
    dc = (HBA_DEV_CB *)hDev; 
    if (dc->status != HBA_DEV_STATUS_STARTED)
    {
        return FC_DEVICE_STATE_INVALID;
    }
    *pWdt = dc->configBlock.port_config.nc_wdt_period;
    *pWdtLoader = dc->configBlock.port_config.wdt_loader_period;
    
    return FC_SUCCESS;
}

/*上报FC软件版本*/
FCUINT FC_NM_GetFcSoftwareVersion(FC_SoftwareVersion *pFcSoftwareVersion)
{
    if (pFcSoftwareVersion == NULL)
    {
        return FC_PARAMS_INVALID;
    }
    
    pFcSoftwareVersion->VersionA = 2;
    pFcSoftwareVersion->VersionB = 1;
    pFcSoftwareVersion->VersionC = 0;

    pFcSoftwareVersion->BuildYear = 2017;
    pFcSoftwareVersion->BuildMonth = 11;
    pFcSoftwareVersion->BuildDay = 23;

    pFcSoftwareVersion->BuildHour = 15;
    pFcSoftwareVersion->BuildMinute = 0;
    pFcSoftwareVersion->BuildSecond = 0;

    return FC_SUCCESS;
}

/*615调试函数 获取2个FC端口的link状态*/
FCUINT FC_DBG_GetAllPortStatus(FCHANDLE hDev, FCUINT *ports, FCUINT count)
{
    FCUINT ret;
    HBA_DEV_CB *dc;

    if (hDev == NULL)
    {
        return FC_INVALID_HANDLE;
    }
    if (ports == NULL)
    {
        return FC_PARAMS_INVALID;
    }
    if (count != FC_PORT_NUM_MAX)
    {
         return FC_NM_INVALID_PORT_COUNT;
    }

    dc = (HBA_DEV_CB *)hDev;

    if (dc->status != HBA_DEV_STATUS_STARTED)
    {
        return FC_DEVICE_STATE_INVALID;
    }

    ret = hbaDevGetDevState(dc, ports, count);
    if (ret != DEV_SUCCESS)
    {
        return FC_FAILURE;
    }
        
    return FC_SUCCESS;
}


/*注册内存拷贝函数，用于替换驱动缺省使用的memcpy函数*/
FCUINT FC_NP_RegMemCopyHandler(FC_MEMCPY_FUNCPTR func)
{
    if (func == NULL)
    {
        return FC_PARAMS_INVALID;
    }

    if (hbaDrvRegMemCopyFunc(func) != OK) 
    {
        return FC_FAILURE;
    }
    
    return FC_SUCCESS;
}

