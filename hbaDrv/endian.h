/*++
�ļ���
endian.h

����
��С�˵Ķ���
--*/

#ifndef __ENDIAN_H__
#define __ENDIAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/*�������꣬����ʱʹ�ô���ֽ��򣬷������ʱʹ��С���ֽ���*/
#define _HBA_COMPILE_BIG_ENDIAN

/*****************************************************************************
 �Ĵ�����д�����Ŀ��ƺ궨�壬�ú궨���ǻ���ģ�ֻ�ܶ���һ����Ч
 ע��CPU�����ͣ���������ܶ�д�Ĵ���
*****************************************************************************/
#ifdef _HBA_COMPILE_BIG_ENDIAN
    /*����POWER PC�Ļ��ָ������Ĵ���*/
    #define _HBA_IO_REG_MODE_POWER_PC
#else
    /*����ARM�ķ�ʽ�����Ĵ���*/
    #define _HBA_IO_REG_MODE_ARM
#endif

/******************************************************************************
 ����λ�������Ĵ�����ֵ�ĺ궨�壬�ú궨���ǻ���ģ�ֻ�ܶ���һ����Ч
 POWER PC ���
 X86      С��
 ARM      
 ע��CPU��λ������������ԼĴ�����ֵ�Ľ����Ǵ����
******************************************************************************/
#define _HBA_BIG_ENDIAN                  1  /*����ֽ���*/
#define _HBA_LITTLE_ENDIAN               2  /*С���ֽ���*/

#ifdef _HBA_COMPILE_BIG_ENDIAN
    #define _HBA_ENDIAN                      _HBA_BIG_ENDIAN     /*ʹ�ô���ֽ���*/
#else
    #define _HBA_ENDIAN                      _HBA_LITTLE_ENDIAN  /*ʹ��С���ֽ���*/
#endif

/*16λ��ֵ���ֽ�ת����С��*/
#define HBA_BYTE_ORDER_CONVERT_16(_v)    ((((_v) & 0x000000FF) << 8) | (((_v) & 0x0000FF00) >> 8))

/*32λ��ֵ���ֽ�ת����С��*/
#define HBA_BYTE_ORDER_CONVERT_32(_v)    ((((_v) & 0x000000FF) << 24) | (((_v) & 0x0000FF00) << 8) | (((_v) & 0x00FF0000) >> 8) | (((_v) & 0xFF000000) >> 24))

#ifdef VXWORKS
#ifndef __INCvxTypesOldh
typedef long long          INT64; /*�з���64bit*/
typedef unsigned long long UINT64;/*�޷���64bit*/
typedef signed int         INT32; /*�з���32bit*/
typedef unsigned int       UINT32;/*�޷���32bit*/
typedef signed short       INT16; /*�з���16bit*/
typedef unsigned short     UINT16;/*�޷���16bit*/
typedef signed char        INT8;  /*�з���8bit*/
typedef unsigned char      UINT8; /*�޷���8bit*/
typedef    int                BOOL;  /* BOOL���� */
typedef void               VOID;  /* VOID���� */
#endif    /* __INCvxTypesOldh */
#endif    /* VXWORKS */

#ifdef __cplusplus
}
#endif

#endif /*__ENDIAN_H__*/

