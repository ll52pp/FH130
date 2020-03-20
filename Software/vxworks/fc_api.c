#include <vxworks.h>
#include <taskLib.h>
#include "hba.h"
#include "fc_utility.h"
#include "fc_api.h"

/*-------------------- 设备管理接口 --------------------*/
/* 打开FC节点卡,分配资源 */
FCUINT FC_DevOpen(FCHANDLE *hDev, FCUINT DevId)
{
    HBA_DEV_CB *pHbaDevCB;
    
    if (hDev == NULL)
    {
        return FC_PARAMS_INVALID;
    }
    if (DevId >= MAX_DEVICE_NUM)
    {
        return FC_PARAMS_INVALID;
    }
    
    pHbaDevCB = hbaDevCreate(DevId);
    if (pHbaDevCB == NULL)
    {
        return FC_FAILURE;
    }
    
    /* 把取得的设备句柄返回给应用层 */
    *hDev = (FCHANDLE)pHbaDevCB;
    return FC_SUCCESS;
}

/* 关闭FC节点卡，释放资源 */
FCUINT FC_DevClose(FCHANDLE hDev)
{
    INT32 ret;
    HBA_DEV_CB *pHbaDevCB;
    
    if (hDev == NULL)
    {
        return FC_PARAMS_INVALID;
    }
    
    pHbaDevCB = (HBA_DEV_CB *)hDev;
    ret = hbaDevDestroy(pHbaDevCB);
    if (ret != DEV_SUCCESS)
    {
        return FC_FAILURE;
    }
    return FC_SUCCESS;
}


FCUINT FC_DevReset(FCHANDLE hDev)
{
    INT32 ret;
    HBA_DEV_CB *pHbaDevCB;
    
    if (hDev == NULL)
    {
        return FC_PARAMS_INVALID;
    }
    
    pHbaDevCB = (HBA_DEV_CB *)hDev;
    ret = hbaDevReset(pHbaDevCB);
    if (ret != DEV_SUCCESS)
    {
        return FC_FAILURE;
    }
    return FC_SUCCESS;
}

/* 获取FC节点机的N端口状态 */
FCUINT FC_DevGetState(FCHANDLE hDev, FCUINT *state)
{
    INT32 ret;
    FCUINT portStatus[2];
    HBA_DEV_CB *pHbaDevCB;
    
    if (hDev == NULL)
    {
        return FC_FAILURE;
    }
    if (state == NULL)
    {
        return FC_FAILURE;
    }
    
    pHbaDevCB = (HBA_DEV_CB *)hDev;
    ret = hbaDevGetPortState(pHbaDevCB, portStatus, 2);
    if (ret != DEV_SUCCESS)
    {
        return FC_FAILURE;
    }
    if (portStatus[0] == PORT_LINK_UP || portStatus[1] == PORT_LINK_UP)
    {
        *state = PORT_LINK_UP;
    }
    else
    {
        *state = PORT_LINK_DOWN;
    }
    
    return FC_SUCCESS;
}

/* 获取FC节点机的N端口版本号 */
FCUINT FC_DevGetVersion(FCHANDLE hDev, FCUINT *version)
{
    INT32 ret;
    HBA_DEV_CB *pHbaDevCB;
    
    if (hDev == NULL)
    {
        return FC_FAILURE;
    }
    if (version == NULL)
    {
        return FC_FAILURE;
    }
    
    pHbaDevCB = (HBA_DEV_CB *)hDev;
    ret = hbaDevGetVersion(pHbaDevCB, version);
    if (ret != DEV_SUCCESS)
    {
        return FC_FAILURE;
    }
    
    return FC_SUCCESS;
}

/* 配置FC节点卡 */
FCUINT FC_DevConfig(FCHANDLE hDev, PDEV_CONFIG dev_config)
{
    INT32 ret;
    HBA_DEV_CB *pHbaDevCB;

    if (hDev == NULL)
    {
        return FC_FAILURE;
    }
    if (dev_config == NULL)
    {
        return FC_FAILURE;
    }
    /* 信用 1-16 */
    if (!(dev_config->credit_num > 0 && dev_config->credit_num <= 16))
    {
        return FC_FAILURE;
    }
    /* 速率 0 自适应 1-1Gbps 2-2Gbps */
    if (!(dev_config->speed == 1 || dev_config->speed == 2))
    {
        return FC_FAILURE;
    }
    /* 接收方向DID过滤使能 */
    if (!(dev_config->did_filter_enab == 0 || dev_config->did_filter_enab == 1))
    {
        return FC_FAILURE;
    }
    /* e_d_tov时间，单位是毫秒 */
    if (!(dev_config->e_d_tov > 0 && dev_config->e_d_tov < 3600))
    {
        return FC_FAILURE;
    }
    /* 冗余使能 0-禁止 1-使能 */
    if (!(dev_config->redundant_enab == 0 || dev_config->redundant_enab == 1))
    {
        return FC_FAILURE;
    }
    /* 超时覆盖的时间，单位是毫秒 */
#if 0
    if (!(dev_config->time_out > 0 && dev_config->time_out < 3600))
    {
        return FC_FAILURE;
    }
#endif

    if (!(dev_config->qdrBufUnitSize >= QDR_BUF_UNIT_SIZE_MIN && dev_config->qdrBufUnitSize <= QDR_BUF_UNIT_SIZE_MAX))
    {
        return FC_FAILURE;
    }	
	
    /* 配置端口 */
    pHbaDevCB = (HBA_DEV_CB *)hDev;
    ret = hbaDevConfig(pHbaDevCB, dev_config);
    if (ret != DEV_SUCCESS)
    {
        return FC_FAILURE;
    }
    /* 初始化设备 */
    ret = hbaDevInitialize(pHbaDevCB);
    if (ret != DEV_SUCCESS) 
    {
            return FC_INITIALISE_FAIL;
    }
    /* 使设备可以接收数据 */
    hbaDevRun(pHbaDevCB);
    
    return FC_SUCCESS;
}

/* 注册中断接收回调函数 */
FCUINT FC_DevRegMsgHandler(FCHANDLE hDev, FC_NP_RECV_FUNCPTR func)
{
    INT32 ret;
    HBA_DEV_CB *pHbaDevCB;

    if (hDev == NULL)
    {
        return FC_FAILURE;
    }
    if (func == NULL)
    {
        return FC_FAILURE;
    }
    pHbaDevCB = (HBA_DEV_CB *)hDev;
    ret = hbaDevRegMsgHandler(pHbaDevCB, func);
    if (ret == DEV_SUCCESS)
    {
        return FC_SUCCESS;
    }
    return FC_FAILURE;
}

/* 注销中断接收回调函数 */
FCUINT FC_DevUnRegMsgHandler(FCHANDLE hDev)
{
    INT32 ret;
    HBA_DEV_CB *pHbaDevCB;

    if (hDev == NULL)
    {
        return FC_FAILURE;
    }
    pHbaDevCB = (HBA_DEV_CB *)hDev;
    ret = hbaDevUnRegMsgHandler(pHbaDevCB);
    if (ret == DEV_SUCCESS)
    {
        return FC_SUCCESS;
    }
    return FC_FAILURE;
}

/*-------------------- 通信管理接口 --------------------*/
/* 请求有数据的缓冲区 */
FCUINT FC_RecvData(FCHANDLE hDev, void **ppBuffer, FCUINT *nLen)
{
    INT32 ret;
    HBA_DEV_CB *pHbaDevCB;
    
    if (hDev == NULL)
    {
        return FC_FAILURE;
    }
    if (ppBuffer == NULL)
    {
        return FC_FAILURE;
    }
    if (nLen == NULL)
    {
        return FC_FAILURE;
    }
    
    pHbaDevCB = (HBA_DEV_CB *)hDev;
    ret = hbaDevRecvData(pHbaDevCB, ppBuffer, nLen);
    if (ret == DEV_SUCCESS)
    {
        return FC_SUCCESS;
    }
    if (ret == ASM_RECV_NO_DATA)
    {
        return FC_RECV_NO_DATA;
    }
    return FC_FAILURE;
}

/* 释放接收缓冲区 */
FCUINT FC_ReleaseBuf(FCHANDLE hDev, void * pBuffer)
{
    INT32 ret;
    HBA_DEV_CB *pHbaDevCB;
    
    if (hDev == NULL)
    {
        return FC_FAILURE;
    }
    if (pBuffer == NULL)
    {
        return FC_FAILURE;
    }
    
    pHbaDevCB = (HBA_DEV_CB *)hDev;
    ret = hbaDevReleaseBuf(pHbaDevCB, pBuffer);
    if (ret != DEV_SUCCESS)
    {
        return FC_FAILURE;
    }
    return FC_SUCCESS;
}

/* --------------------时统管理接口 --------------------*/

/* 获取FC节点机的时间 */
FCUINT FC_TM_GetRtc(FCHANDLE hDev, FCTime *time)
{
    HBA_DEV_CB *pHbaDevCB;
    
    if (hDev == NULL)
    {
        return FC_FAILURE;
    }
    if (time == NULL)
    {
        return FC_FAILURE;
    }

    pHbaDevCB = (HBA_DEV_CB *)hDev;
    hbaDevGetRtc(pHbaDevCB, time);
    
    return FC_SUCCESS;
}

/* 设置FC节点机的时间 */
FCUINT FC_TM_SetRtc(FCHANDLE hDev, FCTime *time)
{
    HBA_DEV_CB *pHbaDevCB;

    if (hDev == NULL || time == NULL)
    {
        return FC_FAILURE;
    }

    pHbaDevCB = (HBA_DEV_CB *)hDev;
    hbaDevSetRtc(pHbaDevCB, time);
    return FC_SUCCESS;
}

/*开始监控*/
FCUINT FC_DevStartMonitor(FCHANDLE hDev)
{
    HBA_DEV_CB *pHbaDevCB;

    if (hDev == NULL)
    {
        return FC_FAILURE;
    }
    
    pHbaDevCB = (HBA_DEV_CB *)hDev;
    hbaDevStartMonitor(pHbaDevCB);
    
    return FC_SUCCESS;

}

/*停止监控*/
FCUINT FC_DevStopMonitor(FCHANDLE hDev)
{
    HBA_DEV_CB *pHbaDevCB;

    if (hDev == NULL)
    {
        return FC_FAILURE;
    }
    
    pHbaDevCB = (HBA_DEV_CB *)hDev;
    hbaDevStopMonitor(pHbaDevCB);
    
    return FC_SUCCESS;

}

