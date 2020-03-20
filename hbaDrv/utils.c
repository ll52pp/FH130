/*++
�ļ���
utils.c

����
ͨ��
--*/
#include "endian.h"
#include "hw.h"
#include "utils.h"

/*ת��16λ�ֽ��� FCЭ��Ҫ�����ֽ���*/
unsigned short HbaUShortByteSwap(unsigned short v)
{
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
    return v;
#else
    return HBA_BYTE_ORDER_CONVERT_16(v);
#endif
}

/*ת��32λ�ֽ��� FCЭ��Ҫ�����ֽ���*/
unsigned int HbaUlongByteSwap(unsigned int v)
{
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
    return v;
#else
    return HBA_BYTE_ORDER_CONVERT_32(v);
#endif
}

/*ת��64λ�ֽ��� FCЭ��Ҫ�����ֽ���*/
unsigned long long HbaUlonglongByteSwap(unsigned long long v)
{
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
    return v;
#else
    UINT32 lo, hi;

    /*ȡ��32λ*/
    lo = (UINT32)v;
    /*ȡ��32λ*/
    hi = (UINT32)(v >> 32);

    lo = HBA_BYTE_ORDER_CONVERT_32((UINT32)lo);
    hi = HBA_BYTE_ORDER_CONVERT_32((UINT32)hi);
    /*ע��64λƴ�Ӹߵ�32λҪ����λ�� 0x1122334455667788 => 0x8877665544332211*/
    return (unsigned long long)lo << 32 | hi;
#endif
}

/*�ж�֪ͨ*/
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

/*����ת��Ϊtick�� ���ת��ֵΪ0������1tick*/
unsigned int HbaDrvMilliSecond2Tick(unsigned int milliSecond)
{
    unsigned int tick;

    /*�������С��1000����������0������ת��Ϊ���͵����*/
    tick = (milliSecond * HbaDrvClkRateGet()) / 1000;
    if (tick == 0)
    {
        /*��Сֵ��1tick*/
        tick = 1;
    }

    return tick;
}

/*��ȡϵͳÿ��tick��*/
UINT32 HbaDrvClkRateGet()
{
#if 1
    return sysClkRateGet();
#else
    return 1000; /* for ����2 */
#endif

}



