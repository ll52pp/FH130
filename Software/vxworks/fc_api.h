#ifndef __FC_API_H__
#define __FC_API_H__

#include <vxworks.h>

/*------------------------------设备管理接口------------------------------*/
/* 打开FC节点卡,分配资源 */
FCUINT FC_DevOpen(FCHANDLE *hDev, FCUINT DevId);
/* 关闭FC节点卡，释放资源 */
FCUINT FC_DevClose(FCHANDLE hDev);

/*软复位FC节点卡*/
FCUINT FC_DevReset(FCHANDLE hDev);

/* 获取FC节点机的N端口状态 */
FCUINT FC_DevGetState(FCHANDLE hDev, FCUINT *state);
/* 获取FC节点机的N端口版本号 */
FCUINT FC_DevGetVersion(FCHANDLE hDev, FCUINT *version);
/* 配置FC节点卡 */
FCUINT FC_DevConfig(FCHANDLE hDev, PDEV_CONFIG dev_config);
/* 注册中断接收回调函数 */
FCUINT FC_DevRegMsgHandler(FCHANDLE hDev, FC_NP_RECV_FUNCPTR func);
/* 注销中断接收回调函数 */
FCUINT FC_DevUnRegMsgHandler(FCHANDLE hDev);
/*------------------------------通信管理接口------------------------------*/
/* 请求有数据的缓冲区 */
FCUINT FC_RecvData(FCHANDLE hDev, void **ppBuffer, FCUINT *nLen);
/* 释放接收缓冲区 */
FCUINT FC_ReleaseBuf(FCHANDLE hDev, void *pBuffer);
/*------------------------------时统管理接口------------------------------*/
/* 获取FC节点机的时间 */
FCUINT FC_TM_GetRtc(FCHANDLE hDev, FCTime *time);
/* 设置FC节点机的时间 */
FCUINT FC_TM_SetRtc(FCHANDLE hDev, FCTime *time);

/*开始监控*/
FCUINT FC_DevStartMonitor(FCHANDLE hDev);

/*停止监控*/
FCUINT FC_DevStopMonitor(FCHANDLE hDev);



#endif /* __FC_API_H__ */