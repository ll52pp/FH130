/*++
文件名
endian.h

描述
大小端的定义
--*/

#ifndef __ENDIAN_H__
#define __ENDIAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/*如果定义宏，编译时使用大端字节序，否则编译时使用小端字节序*/
#define _HBA_COMPILE_BIG_ENDIAN

/*****************************************************************************
 寄存器读写操作的控制宏定义，该宏定义是互斥的，只能定义一个有效
 注意CPU的类型，定义错误不能读写寄存器
*****************************************************************************/
#ifdef _HBA_COMPILE_BIG_ENDIAN
    /*按照POWER PC的汇编指令操作寄存器*/
    #define _HBA_IO_REG_MODE_POWER_PC
#else
    /*按照ARM的方式操作寄存器*/
    #define _HBA_IO_REG_MODE_ARM
#endif

/******************************************************************************
 按照位来解析寄存器的值的宏定义，该宏定义是互斥的，只能定义一个有效
 POWER PC 大端
 X86      小端
 ARM      
 注意CPU的位序，如果定义错误对寄存器的值的解析是错误的
******************************************************************************/
#define _HBA_BIG_ENDIAN                  1  /*大端字节序*/
#define _HBA_LITTLE_ENDIAN               2  /*小端字节序*/

#ifdef _HBA_COMPILE_BIG_ENDIAN
    #define _HBA_ENDIAN                      _HBA_BIG_ENDIAN     /*使用大端字节序*/
#else
    #define _HBA_ENDIAN                      _HBA_LITTLE_ENDIAN  /*使用小端字节序*/
#endif

/*16位的值按字节转换大小端*/
#define HBA_BYTE_ORDER_CONVERT_16(_v)    ((((_v) & 0x000000FF) << 8) | (((_v) & 0x0000FF00) >> 8))

/*32位的值按字节转换大小端*/
#define HBA_BYTE_ORDER_CONVERT_32(_v)    ((((_v) & 0x000000FF) << 24) | (((_v) & 0x0000FF00) << 8) | (((_v) & 0x00FF0000) >> 8) | (((_v) & 0xFF000000) >> 24))

#ifdef VXWORKS
#ifndef __INCvxTypesOldh
typedef long long          INT64; /*有符号64bit*/
typedef unsigned long long UINT64;/*无符号64bit*/
typedef signed int         INT32; /*有符号32bit*/
typedef unsigned int       UINT32;/*无符号32bit*/
typedef signed short       INT16; /*有符号16bit*/
typedef unsigned short     UINT16;/*无符号16bit*/
typedef signed char        INT8;  /*有符号8bit*/
typedef unsigned char      UINT8; /*无符号8bit*/
typedef    int                BOOL;  /* BOOL类型 */
typedef void               VOID;  /* VOID类型 */
#endif    /* __INCvxTypesOldh */
#endif    /* VXWORKS */

#ifdef __cplusplus
}
#endif

#endif /*__ENDIAN_H__*/

