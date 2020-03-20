#include <vxworks.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <taskLib.h>
#include <tickLib.h>
#include <logLib.h>
#include "hba.h"
#include "hba_els.h"
#include "hw.h"
#include "utils.h"
#include "d_list.h"



FCUINT gElsKeyList[FC_ELS_KEY_COUNT][FC_ELS_KEY_SIZE] =
{

};


int hbaElsKeyToIndex(UINT32 * pElsKey)
{

}

VOID hbaElsRecvHandler(HBA_DEV_CB *dc, UINT32 index, FC_ELS_CONFIG *ecRecv);

/******************************************************************************
* 时统管理接口
******************************************************************************/

/*设置节点的同步角色*/
void hbaDevSyncModeSet(HBA_DEV_CB *dc, FCUINT enab)
{

}


/*设置不同时钟角色 收发*/
void hbaDevSetRTCRxTx(HBA_DEV_CB *dc, FCUINT rx_enab, FCUINT tx_enab)
{

}


/* ELS定时器处理 */
INT32 hbaElsCycleCheck(HBA_DEV_CB *dc)
{

}

INT32 hbaElsCycleCheckTask(HBA_DEV_CB *dc)
{
    dc->hbaElsCycleCheckTaskId = ERROR;    
}



/* 网络管理器的WDT定时检查周期，这个只是针对BNC和RT才有 */
FCUINT hbaDevWdtCheckPeriodHandler(HBA_DEV_CB *dc)
{

}

/* WDT加载周期, 仅NC */
FCUINT hbaDevNcWdtLoaderPeriodHandler(HBA_DEV_CB *dc)
{

}

/* ELS接收回调 */
INT32 hbaElsRecvTask(HBA_DEV_CB *dc)
{

}

/*处理接收到的ELS帧*/
VOID hbaElsRecvHandler(HBA_DEV_CB *dc, UINT32 index, FC_ELS_CONFIG *ecRecv)
{
    dc->hbaElsRecvTaskId = ERROR;
}

/*检查接收帧的有效性*/
UINT32 HbaDevElsCheckNmFrame(HBA_DEV_CB *dc, FC_ELS_CONFIG *r_frame)
{

}


/* ELS接收 */
INT32 hbaElsRecv(HBA_DEV_CB *dc, FC_ELS_CONFIG *elsConfig)
{

}


/* ELS接收 */
INT32 hbaElsRecv2(HBA_DEV_CB *dc, FC_ELS_CONFIG *elsConfig)
{

}


/* 解析ELS帧为ELS_CONFIG结构 */
void hbaParseElsFrame(FC_ELS_CONFIG *elsConfig, UINT8 *frame, UINT length, UINT port)
{

}

/* ELS发送 */
UINT32 hbaElsSend(struct tagHBA_DEV_CB *dc, FC_ELS_CONFIG *elsConfig)
{

}


FCUINT hbaElsRoleSet(struct tagHBA_DEV_CB *dc, FCUINT nmRole)
{

}

/*取得端口的网络管理角色*/
FCUINT hbaElsRoleGet(struct tagHBA_DEV_CB *dc, FCUINT *nmRole)
{

}

/* 构造ELS帧 */
void hbaConstructElsFrame(FC_ELS_CONFIG *elsConfig, UINT8 * frame, UINT *length)
{

}

void hbaConstructE1_0102(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did, UINT32 config)
{

}

void hbaConstructE1_0202(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did, OnNetTbl *onNetTbl)
{

}

void hbaConstructE2_0103(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did)
{

}

void hbaConstructE1_0105(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did, SwConfig *pSwConfig)
{

}

void hbaConstructE1_0106(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did, SwConfigData *pSwConfigData)
{

}

void hbaConstructE1_0104(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did, FCINT SchemeNo)
{

}

void hbaConstructE4_0203(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did, UINT32 status)
{

}

void hbaConstructE1_0203(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 value, FCUCHAR *onNetTblStatus, FCDate * pFCDate)
{

}

void hbaConstructE1_0204(FC_ELS_CONFIG *elsConfig, UINT32 sid, FCDate *fcDate)
{

}

void hbaConstructE1_0205(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did, UINT32 config)
{

}

void hbaConstructE2_0202(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did)
{

}

void hbaConstructE2_0201(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did)
{

}

void hbaConstructE3_0201(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did, UINT32 value)
{

}

void hbaConstructE3_0202(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did,  NetStatistics *pStatInfo)
{

}


