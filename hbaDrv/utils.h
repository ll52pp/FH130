/*++
�ļ���
utils.h

����
ͨ��
--*/

#ifndef __UTILS_H__
#define __UTILS_H__

#ifdef __cplusplus
extern "C" {
#endif  /*__cplusplus */

#include "endian.h"

#define FC_FCID_EMPTY                            0x0 /*��Ч��FCID*/
#define FC_WDT_LOADER_PERIOD_IS_DISABLE          0xE3000007 /*WDT��������ʹ��λ��ֹ*/


#define RECV_ELS_INIT                            0          /*û���յ�ELS֡*/
#define RECV_ELS_COMPLETE                        1          /*�Ѿ��յ�ELS֡*/


#define ELS_USE_PORT_0                           0x1
#define ELS_USE_PORT_1                           0x2

#define TASK_CYCLE_DELAY                         100        /* ÿ�εȴ����ڷ���ELS֡����ʱ, ��λms */
#define TASK_RECV_ELS_DELAY                      50         /* û��ELS֡Ҫ����ʱ����ʱ, ��λms*/
#define ELS_LENGTH_DESC                          8          /* RAW֡ǰ��ĳ���������ռ8���ֽ�FPGAʹ��*/
#define FC_FRAME_MAX                             2148       /* FC֡����󳤶�*/
#define FC_ELS_SOF_SIZE                          4          /* SOF�ĳ��ȹ̶�4�ֽ�*/
#define FC_ELS_HEADER_SIZE                       sizeof(FC_HEADER)   /*FCͷ�ĳ���*/
#define FC_ELS_CRC_SIZE                          4          /* CRC�ĳ��ȹ̶�4�ֽ�*/
#define FC_ELS_EOF_SIZE                          4          /* EOF�ĳ��ȹ̶�4�ֽ�*/
#define FC_ELS_PAYLOAD_MAX                       (FC_FRAME_MAX - FC_ELS_SOF_SIZE - FC_ELS_HEADER_SIZE - FC_ELS_CRC_SIZE - FC_ELS_EOF_SIZE)
#define FC_ELS_KEY_SIZE                          16         /* ҵ��key�ĳ��ȹ̶�16�ֽ�*/

#define SOFi3                                    0xBCB55656 /* 0xBCB55656 */
#define EOFt_n                                   0xBCB57575 /* 0xBCB57575 */
#define FC_FRAME_R_CTRL_REQ                      0x22
#define FC_FRAME_R_CTRL_RESP                     0x23




/*ת��16λ�ֽ��� FCЭ��Ҫ�����ֽ���*/
unsigned short HbaUShortByteSwap(unsigned short v);

/*ת��32λ�ֽ��� FCЭ��Ҫ�����ֽ���*/
unsigned int HbaUlongByteSwap(unsigned int v);

/*ת��64λ�ֽ��� FCЭ��Ҫ�����ֽ���*/
unsigned long long HbaUlonglongByteSwap(unsigned long long v);

/*�ж�֪ͨ*/
VOID HbaDevEventNotify(HBA_DEV_CB *dc, UINT32 eventCode, UINT32 param);

/*����ת��Ϊtick�� ���ת��ֵΪ0������1tick*/
unsigned int HbaDrvMilliSecond2Tick(unsigned int milliSecond);

/*��ȡϵͳÿtick�ĺ�����*/
UINT32 HbaDrvClkRateGet();



#ifdef __cplusplus
}
#endif  /*__cplusplus*/

#endif /*__UTILS_H__*/

