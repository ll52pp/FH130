/*++
文件名
utils.h

描述
通用
--*/

#ifndef __UTILS_H__
#define __UTILS_H__

#ifdef __cplusplus
extern "C" {
#endif  /*__cplusplus */

#include "endian.h"

#define FC_FCID_EMPTY                            0x0 /*无效的FCID*/
#define FC_WDT_LOADER_PERIOD_IS_DISABLE          0xE3000007 /*WDT加载周期使能位禁止*/


#define RECV_ELS_INIT                            0          /*没有收到ELS帧*/
#define RECV_ELS_COMPLETE                        1          /*已经收到ELS帧*/


#define ELS_USE_PORT_0                           0x1
#define ELS_USE_PORT_1                           0x2

#define TASK_CYCLE_DELAY                         100        /* 每次等待周期发送ELS帧的延时, 单位ms */
#define TASK_RECV_ELS_DELAY                      50         /* 没有ELS帧要接收时的延时, 单位ms*/
#define ELS_LENGTH_DESC                          8          /* RAW帧前面的长度描述符占8个字节FPGA使用*/
#define FC_FRAME_MAX                             2148       /* FC帧的最大长度*/
#define FC_ELS_SOF_SIZE                          4          /* SOF的长度固定4字节*/
#define FC_ELS_HEADER_SIZE                       sizeof(FC_HEADER)   /*FC头的长度*/
#define FC_ELS_CRC_SIZE                          4          /* CRC的长度固定4字节*/
#define FC_ELS_EOF_SIZE                          4          /* EOF的长度固定4字节*/
#define FC_ELS_PAYLOAD_MAX                       (FC_FRAME_MAX - FC_ELS_SOF_SIZE - FC_ELS_HEADER_SIZE - FC_ELS_CRC_SIZE - FC_ELS_EOF_SIZE)
#define FC_ELS_KEY_SIZE                          16         /* 业务key的长度固定16字节*/

#define SOFi3                                    0xBCB55656 /* 0xBCB55656 */
#define EOFt_n                                   0xBCB57575 /* 0xBCB57575 */
#define FC_FRAME_R_CTRL_REQ                      0x22
#define FC_FRAME_R_CTRL_RESP                     0x23




/*转换16位字节序 FC协议要求大端字节序*/
unsigned short HbaUShortByteSwap(unsigned short v);

/*转换32位字节序 FC协议要求大端字节序*/
unsigned int HbaUlongByteSwap(unsigned int v);

/*转换64位字节序 FC协议要求大端字节序*/
unsigned long long HbaUlonglongByteSwap(unsigned long long v);

/*中断通知*/
VOID HbaDevEventNotify(HBA_DEV_CB *dc, UINT32 eventCode, UINT32 param);

/*毫秒转换为tick数 如果转换值为0，返回1tick*/
unsigned int HbaDrvMilliSecond2Tick(unsigned int milliSecond);

/*获取系统每tick的毫秒数*/
UINT32 HbaDrvClkRateGet();



#ifdef __cplusplus
}
#endif  /*__cplusplus*/

#endif /*__UTILS_H__*/

