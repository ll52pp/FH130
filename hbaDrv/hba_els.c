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
* ʱͳ����ӿ�
******************************************************************************/

/*���ýڵ��ͬ����ɫ*/
void hbaDevSyncModeSet(HBA_DEV_CB *dc, FCUINT enab)
{

}


/*���ò�ͬʱ�ӽ�ɫ �շ�*/
void hbaDevSetRTCRxTx(HBA_DEV_CB *dc, FCUINT rx_enab, FCUINT tx_enab)
{

}


/* ELS��ʱ������ */
INT32 hbaElsCycleCheck(HBA_DEV_CB *dc)
{

}

INT32 hbaElsCycleCheckTask(HBA_DEV_CB *dc)
{
    dc->hbaElsCycleCheckTaskId = ERROR;    
}



/* �����������WDT��ʱ������ڣ����ֻ�����BNC��RT���� */
FCUINT hbaDevWdtCheckPeriodHandler(HBA_DEV_CB *dc)
{

}

/* WDT��������, ��NC */
FCUINT hbaDevNcWdtLoaderPeriodHandler(HBA_DEV_CB *dc)
{

}

/* ELS���ջص� */
INT32 hbaElsRecvTask(HBA_DEV_CB *dc)
{

}

/*������յ���ELS֡*/
VOID hbaElsRecvHandler(HBA_DEV_CB *dc, UINT32 index, FC_ELS_CONFIG *ecRecv)
{
    dc->hbaElsRecvTaskId = ERROR;
}

/*������֡����Ч��*/
UINT32 HbaDevElsCheckNmFrame(HBA_DEV_CB *dc, FC_ELS_CONFIG *r_frame)
{

}


/* ELS���� */
INT32 hbaElsRecv(HBA_DEV_CB *dc, FC_ELS_CONFIG *elsConfig)
{

}


/* ELS���� */
INT32 hbaElsRecv2(HBA_DEV_CB *dc, FC_ELS_CONFIG *elsConfig)
{

}


/* ����ELS֡ΪELS_CONFIG�ṹ */
void hbaParseElsFrame(FC_ELS_CONFIG *elsConfig, UINT8 *frame, UINT length, UINT port)
{

}

/* ELS���� */
UINT32 hbaElsSend(struct tagHBA_DEV_CB *dc, FC_ELS_CONFIG *elsConfig)
{

}


FCUINT hbaElsRoleSet(struct tagHBA_DEV_CB *dc, FCUINT nmRole)
{

}

/*ȡ�ö˿ڵ���������ɫ*/
FCUINT hbaElsRoleGet(struct tagHBA_DEV_CB *dc, FCUINT *nmRole)
{

}

/* ����ELS֡ */
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


