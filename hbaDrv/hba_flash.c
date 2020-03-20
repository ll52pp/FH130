#include <vxworks.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <taskLib.h>
#include <tickLib.h>
#include <logLib.h>
#include <ctype.h>
#include "hba.h"
#include "spi.h"
#include "endian.h"

#define FLASH_CFG_ADDR_OFFSET    0x48

int hbaDevFlashWrite(HBA_DEV_CB *dc, UINT32 Dst, UINT8 * pData, UINT len)
{
    UINT32 * pFlashCfgAddr = 0;
    int spiDevId = INVALID_SPI_FLASH_DEV_ID;
    int ret = OK;
    
    if (dc->status == HBA_DEV_STATUS_NONE)
    {
        return ERROR;
    }
    
    pFlashCfgAddr = (UINT32 *)(dc->pMembaseCsr + FLASH_CFG_ADDR_OFFSET);
    
    
    spiDevId = spiFlashOpen(pFlashCfgAddr);
    if (spiDevId == INVALID_SPI_FLASH_DEV_ID)
    {
        return ERROR;
    }
    if (spiFlashWrite(spiDevId, Dst, pData, len) == OK)
    {
        ret = 0;
    }
    else
    {
        ret = OK;
    }
        
    spiFlashClose(spiDevId);

    return ret;
}


int hbaDevFlashRead(HBA_DEV_CB *dc, UINT32 Dst, UINT8 * pBuffer, UINT len)
{
    UINT32 * pFlashCfgAddr = 0;
    int spiDevId = INVALID_SPI_FLASH_DEV_ID;
    int ret = OK;
    
    if (dc->status == HBA_DEV_STATUS_NONE)
    {
        return ERROR;
    }
    

    pFlashCfgAddr = (UINT32 *)(dc->pMembaseCsr + FLASH_CFG_ADDR_OFFSET);


    spiDevId = spiFlashOpen(pFlashCfgAddr);
    if (spiDevId == INVALID_SPI_FLASH_DEV_ID)
        {
            return ERROR;
        }
    ret = spiFlashRead(spiDevId, Dst, pBuffer, len);
    if(ret != len)
    {
        ret = ERROR;
    }
    else
    {
        ret = OK;
    }

    spiFlashClose(spiDevId);

    return ret;
}


void hbaDrvShowFlash
(
    HBA_DEV_CB *dc,
    void *adrs,    /* address to display (if 0, display next block */
    int nunits,        /* number of units to print (if 0, use default) */
    unsigned int width         /* width of displaying unit (1, 2, 4, 8) */
)
{
    #define MAX_BYTES_PER_LINE       16
    
    static int dNitems = 0x80;    /* default number of item to display */
    static int dWidth  = 2;    /* default width */
    static void *last_adrs = 0;    /* last location displayed */
    static HBA_DEV_CB *pHbaDevCBLast = NULL;
    
    FAST int item;        /* item counter displayed per line */
    char ascii [MAX_BYTES_PER_LINE + 1]; /* ascii buffer for displaying */
    int ix;            /* temporary count */
    UINT8 *pByte;        /* byte pointer for filling ascii buffer */
    UINT8 *tmpByte;        /* temporary byte pointer */
    USHORT *tmpShort;        /* temporary short word pointer */
    ULONG *tmpLong;        /* temporary long word pointer */
    int len;
    UINT8 * pData;
    UINT8 * pDataLast;

    /* 如果输入了新的设备CB，则使用新的, 否则用上次指定的 */
    if (dc != NULL)
    {
        pHbaDevCBLast = dc;
    }
    else
    {
        dc = pHbaDevCBLast;
    }
    
    if (dc == NULL)
    {
        return;
    }
    ascii [MAX_BYTES_PER_LINE] = EOS;    /* put an EOS on the string */

    if (nunits == 0)
        {
            nunits = dNitems;    /* no count specified: use default count */
        }
    else
        {
            dNitems = nunits;    /* change default count */
        }

    if (width == 0)
        {
            width = dWidth;
        }
    else
    {    /* check for valid width */
        if ((width != 1) && (width != 2) && (width != 4) && (width != 8))
            {
                width = 1;
            }
        dWidth = width;
    }

#if 0
    if (adrs == 0)         /* no address specified: use last address */
            adrs = last_adrs;
    else
#endif        
        last_adrs = adrs;

    /* round address down to appropriate boundary */
    
    last_adrs = (void *)(((int) last_adrs) & (~(width - 1)));

    /* get the flash data */
    len = dWidth * nunits;

    if ((UINT32)((char *)adrs + len) > 0x1000000)        /* 16M */
        {
            return;
        }


    /*pData = pDataLast = (UINT8 *)malloc(len + 32);*/
    pData = (UINT8 *)malloc(len + 32);
  pDataLast = pData;
    
    if (pData == NULL)
    {
        /*printf("No full memory\n");*/
        return;
    }
    
    hbaDevFlashRead(pHbaDevCBLast, (UINT32)adrs, pData, len);
    
    /* print leading spaces on first line */

    bfill (ascii, 16, '.');

    printf ("%08x:  ", (int) last_adrs & (~0xf));

    for (item = 0; item < ((int) last_adrs & 0xf) / width; item++)
    {
        printf ("%*s ", 2*width, " ");
        bfill (&ascii[item * width], 2*width, ' ');
    }

    /* print out all the words */

    while (nunits > 0)
    {
        nunits--;
        if (item == (MAX_BYTES_PER_LINE/width))
        {
            /* end of line:
              *   print out ascii format values and address of next line */

            printf ("  *%16s*\n%08x:  ", ascii, (int) last_adrs);
            bfill (ascii, MAX_BYTES_PER_LINE, '.'); /* clear out ascii buffer */
            item = 0;                /* reset word count */
        }

        switch (width)            /* display in appropriate format */
        {
            case 1:
                /*tmpByte = (UINT8 *)pDataLast;*/
                tmpByte = pDataLast;
                printf ("%02x", *tmpByte);
                break;
            case 2:
                tmpShort = (USHORT *)pDataLast;
                printf ("%04x", *tmpShort);
                break;
            case 4:
                tmpLong = (ULONG *)pDataLast;
                printf ("%08lx", *tmpLong);
                break;
        case 8:
                tmpLong = (ULONG *)pDataLast;
#if _HBA_ENDIAN == _HBA_LITTLE_ENDIAN
                printf ("%08lx%08lx", *(tmpLong+1), *tmpLong);
#endif
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
                printf ("%08lx%08lx", *tmpLong, *(tmpLong+1));
#endif
                break;
        default:
                /*tmpByte = (UINT8 *)pDataLast;*/
                tmpByte = pDataLast;
                printf ("%02x", *tmpByte);
                break;
        }

        printf (" ");    /* space between words */

        /* set ascii buffer */

        pByte = pDataLast;
        for (ix = 0; ix < width; ix ++)
        {
            if (((char)*pByte == ' ') || ((isascii (*pByte)) && (isprint (*pByte))))
            {
                ascii[((item*width) + ix)] =(char)*pByte;
            }
            pByte ++;
        }

        pDataLast = (void *)((int)pDataLast + width);
        last_adrs = (void *)((int)last_adrs + width);
        item++;
    }

    /* print remainder of last line */

    for (; item < (MAX_BYTES_PER_LINE/width); item++)
    {
        printf ("%*s ", 2*width, " ");
    }

    printf ("  *%16s*\n", ascii);    /* print out ascii format values */

    free(pData);
}

