/*++
文件名
utils.c

描述
通用
--*/
#include "endian.h"
#include "hw.h"
#include "utils.h"

/*转换16位字节序 FC协议要求大端字节序*/
unsigned short HbaUShortByteSwap(unsigned short v)
{
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
    return v;
#else
    return HBA_BYTE_ORDER_CONVERT_16(v);
#endif
}

/*转换32位字节序 FC协议要求大端字节序*/
unsigned int HbaUlongByteSwap(unsigned int v)
{
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
    return v;
#else
    return HBA_BYTE_ORDER_CONVERT_32(v);
#endif
}

/*转换64位字节序 FC协议要求大端字节序*/
unsigned long long HbaUlonglongByteSwap(unsigned long long v)
{
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
    return v;
#else
    UINT32 lo, hi;

    /*取低32位*/
    lo = (UINT32)v;
    /*取高32位*/
    hi = (UINT32)(v >> 32);

    lo = HBA_BYTE_ORDER_CONVERT_32((UINT32)lo);
    hi = HBA_BYTE_ORDER_CONVERT_32((UINT32)hi);
    /*注意64位拼接高低32位要倒换位置 0x1122334455667788 => 0x8877665544332211*/
    return (unsigned long long)lo << 32 | hi;
#endif
}

/*中断通知*/
VOID HbaDevEventNotify(HBA_DEV_CB *dc, UINT32 eventCode, UINT32 param)
{
    FCHANDLE h;
    FC_INT_FUNCPTR func;

    func = dc->pIntCallbackFunc;
    if (func == NULL)
    {
        return ;
    }
    h = (FCHANDLE)dc;

    (*func)(h, eventCode, param);
}

/*毫秒转换为tick数 如果转换值为0，返回1tick*/
unsigned int HbaDrvMilliSecond2Tick(unsigned int milliSecond)
{
    unsigned int tick;

    /*如果分子小于1000，结果会等于0，浮点转换为整型的误差*/
    tick = (milliSecond * HbaDrvClkRateGet()) / 1000;
    if (tick == 0)
    {
        /*最小值是1tick*/
        tick = 1;
    }

    return tick;
}

/*获取系统每秒tick数*/
UINT32 HbaDrvClkRateGet()
{
#if 1
    return sysClkRateGet();
#else
    return 1000; /* for 天脉2 */
#endif

}



