#ifndef __SPI_H__
#define __SPI_H__

#include <vxworks.h>
#include <semLib.h>

#if 0
typedef unsigned int UINT32;
typedef unsigned short UINT16;
typedef unsigned char UINT8;
typedef unsigned char UCHAR;

typedef int INT32;
typedef short INT16;
typedef char INT8;
#endif

typedef volatile UCHAR VCHAR;   /* shorthand for volatile UCHAR */
typedef volatile INT32 VINT32; /* volatile unsigned word */
typedef volatile INT16 VINT16; /* volatile unsigned halfword */
typedef volatile INT8 VINT8;   /* volatile unsigned byte */
typedef volatile UINT32 VUINT32; /* volatile unsigned word */
typedef volatile UINT16 VUINT16; /* volatile unsigned halfword */
typedef volatile UINT8 VUINT8;   /* volatile unsigned byte */




#define INVALID_SPI_FLASH_DEV_ID    (-1)    /* 无效的SPI Flash 设备标识 */



void spiFlashDrvInit(void);
int spiFlashOpen(UINT32 * pCfgAddr);
void spiFlashClose(int spiDevId);
UINT spiFlashRead(int spiDevId, UINT32 Dst, UINT8 * pBuffer, UINT len);
int spiFlashSectorErase(int spiDevId, UINT32 Dst, UINT len);
int spiFlashWrite(int spiDevId, UINT32 Dst, UINT8 * pData, UINT len);
int spiFlashTest(int spiDevId, UINT32 Dst, UINT len);

#endif /* #define __SPI_H__ */

