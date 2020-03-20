#include <vxworks.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fc_api.h"

FCUINT FC_NP_Open(FCHANDLE *hDev, FCUINT devId);
FCUINT FC_NP_Close(FCHANDLE hDev);
FCUINT FC_NP_SoftReset(FCHANDLE hDev);
FCUINT FC_NP_SendMsg(FCHANDLE hDev, FCUINT msgID, FCUCHAR *pMsg, FCUINT nLen);
FCUINT FC_NP_RecvMsg(FCHANDLE hDev, FCUINT msgID, FCUCHAR *pMsg, FCUINT *nLen);




int openDev()
{

}

int closeDev()
{

}

int msgSend()
{

}

int msgRecv()
{

}

int resetDev()
{


}