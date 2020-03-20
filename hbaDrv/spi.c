/* spi.c - CPM SPI initialization */
#include <vxworks.h>
#include "spi.h"



#define MAX_SPI_DEV_NUM        4            /* 最大的SPI flash 设备数 */

#define MAX_BYTES_PER_WRITE    256            /* 每次写入byte数 */

#define SECTOR_SIZE         0x10000        /* 扇区大小定义 */

#define SUB_SECTOR_SIZE     0x1000        /* 子扇区大小定义 */


typedef struct tagSPI_DEV
{
    int status;
    UINT32 * pCfgAddr;
}SPI_DEV;

SPI_DEV spiDev[MAX_SPI_DEV_NUM];
BOOL spiDrvInited = FALSE;

int spiDebugEnable=0;

/*延时ns 纳秒，需要调整系数*/
void spi_Delay(int ns)
{
    int i = 0,j = 0;
    
    for(i = 0; i< ns; i++)
    {
         j=j+1;
    }
}



void spiFlashDrvInit(void)
{
    int i;
    memset(spiDev, 0, sizeof(spiDev));
    for (i=0; i<MAX_SPI_DEV_NUM; i++)
    {
        spiDev[i].status = 0;
    }
}




/*spi flash片选有效*/
void spi_ce_low(int spiDevId)
{
    hwSysPciOutLong((ULONG)spiDev[spiDevId].pCfgAddr, 0x0);
}

/*spi flash片选取消*/
void spi_ce_high(int spiDevId)
{
    hwSysPciOutLong((ULONG)spiDev[spiDevId].pCfgAddr, 0x08000000);
}

/*spi flash时钟低电平*/
void spi_clk_low(int spiDevId)
{
    UINT32 regValue = 0;

    regValue = hwSysPciInLong((ULONG)spiDev[spiDevId].pCfgAddr);

    if(spiDebugEnable)
  {
        printf("clk low IN %p=0x%08x!\n", spiDev[spiDevId].pCfgAddr, (int)regValue);
  }
    regValue &= ~0x20;
    hwSysPciOutLong((ULONG)spiDev[spiDevId].pCfgAddr, regValue);

    if(spiDebugEnable)
    {
        printf("clk low Out %p=0x%08x!\n\n", spiDev[spiDevId].pCfgAddr, (int)regValue);
  }
}
/*spi flash片时钟高电平*/
void spi_clk_high(int spiDevId)
{
    UINT32 regValue = 0;

    regValue = hwSysPciInLong((ULONG)spiDev[spiDevId].pCfgAddr);

    if(spiDebugEnable)
    {
        printf("clk high IN %p=0x%08x!\n", spiDev[spiDevId].pCfgAddr, (int)regValue);
    }
    regValue |= 0x20;
    hwSysPciOutLong((ULONG)spiDev[spiDevId].pCfgAddr, regValue);

    if(spiDebugEnable)
    {
        printf("clk high Out %p=0x%08x!\n\n", spiDev[spiDevId].pCfgAddr, (int)regValue);
    }
}
/*设置spi mosi的值*/
void Spi_Mosi_Set(int spiDevId, unsigned char value)
{
    UINT32 regValue = 0;

    regValue = hwSysPciInLong((ULONG)spiDev[spiDevId].pCfgAddr);

    if(spiDebugEnable)
    {
        printf("mosi IN %p=0x%08x!\n", spiDev[spiDevId].pCfgAddr, (int)regValue);
    }
    if (value == 1)
    {
        regValue |= 0x1;
    }
    else
    {
        regValue &= ~0x1;
    }
    hwSysPciOutLong((ULONG)spiDev[spiDevId].pCfgAddr, regValue);

    if(spiDebugEnable)
    {
        printf("mosi Out %p=0x%08x!\n\n", spiDev[spiDevId].pCfgAddr, (int)regValue);
    }
}

/*获取spi miso的值*/
UINT8 Spi_Miso_Get(int spiDevId)
{
    UINT32 regValue = 0;

    regValue = hwSysPciInLong((ULONG)spiDev[spiDevId].pCfgAddr);

    if(spiDebugEnable)
    {
        printf("miso In %p=0x%08x, %d!\n\n", spiDev[spiDevId].pCfgAddr, (int)regValue, ((regValue >> 1) & 0x00000001));
    }
    regValue = (regValue >> 9) & 0x00000001;/*取最低位*/    
    return (regValue);

}


/*发送地址*/
int testSpiWriteDoneCnt=0;
int testSpiWriteDoneMaxCnt = 0;
void spi_write_byte(int spiDevId, UINT8 value)
{

    UINT32 regValue = 0;

    regValue = 0x80000000 | value;
    hwSysPciOutLong((ULONG)spiDev[spiDevId].pCfgAddr, regValue);

    if(spiDebugEnable)
    {
        printf("write byte Out ,%p=0x%08x!\n\n", spiDev[spiDevId].pCfgAddr, (int)regValue);
    }

    do
    {
        regValue = hwSysPciInLong((ULONG)spiDev[spiDevId].pCfgAddr);

    }while((regValue & 0x40000000)==0);

}


/*发送spi flash操作命令*/
void spi_write_command(int spiDevId, UINT8 command)
{
    spi_write_byte(spiDevId, command);
}

/*发送地址*/
void spi_write_address(int spiDevId, UINT8 address)
{
    spi_write_byte(spiDevId, address);
}

/*发送数据*/
void spi_write_data(int spiDevId, UINT8 data)
{
    spi_write_byte(spiDevId, data);
}


/*读取数据*/
UINT8 spi_read_data(int spiDevId)
{

    UINT32 regValue = 0;
    UINT8 value=0;

    regValue = 0x20000000;
    hwSysPciOutLong((ULONG)spiDev[spiDevId].pCfgAddr, regValue);

    if(spiDebugEnable)
    {
        printf("read byte Out %p=0x%08x!\n\n", spiDev[spiDevId].pCfgAddr, (int)regValue);
    }
    do
    {
        regValue = hwSysPciInLong((ULONG)spiDev[spiDevId].pCfgAddr);

    }while((regValue & 0x10000000) == 0);

    
    value = (UINT8)((regValue>>8)&0xFF);

    if(spiDebugEnable)
    {
        printf("read byte %p=0x%08x, value=0x%08x!\n\n", spiDev[spiDevId].pCfgAddr, (int)regValue, (int)value);
    }
    return value;


}

/************************************************************************/
/* PROCEDURE: sst_WREN                            */
/*                                    */
/* This procedure enables the Write Enable Latch.            */
/*                                    */
/* Input:                                */
/*        None                            */
/*                                    */
/* Returns:                                */
/*        Nothing                            */
/************************************************************************/
void sst_WREN(int spiDevId)
{
    spi_ce_low(spiDevId);            /* enable device */
    spi_write_command(spiDevId, 0x06);        /* send WREN command */
    spi_ce_high(spiDevId);            /* disable device */
}

/************************************************************************/
/* PROCEDURE: sst_WRDI                            */
/*                                    */
/* This procedure disables the Write Enable Latch.            */
/*                                    */
/* Input:                                */
/*        None                            */
/*                                    */
/* Returns:                                */
/*        Nothing                            */
/************************************************************************/
void sst_WRDI(int spiDevId)
{
    spi_ce_low(spiDevId);                    /* enable device */
    spi_write_command(spiDevId, 0x04);        /* send WRDI command */
    spi_ce_high(spiDevId);                    /* disable device */
}

/************************************************************************/
/* PROCEDURE: sst_EWSR                            */
/*                                    */
/* This procedure Enables Write Status Register.              */
/*                                    */
/* Input:                                */
/*        None                            */
/*                                    */
/* Returns:                                */
/*        Nothing                            */
/************************************************************************/
void sst_EWSR(int spiDevId)
{

}

/************************************************************************/
/* PROCEDURE: sst_WRSR                            */
/*                                    */
/* This procedure writes a byte to the Status Register.            */
/*                                    */
/* Input:                                */
/*        byte                            */
/*                                    */
/* Returns:                                */
/*        Nothing                            */
/************************************************************************/
void sst_WRSR(int spiDevId, UINT8 byte)
{
    spi_ce_low(spiDevId);                    /* enable device */
    spi_write_command(spiDevId, 0x01);        /* select write to status register */
    spi_write_data(spiDevId, byte);            /* data that will change the status of BPx 
                                                or BPL (only bits 2,3,7 can be written) */
    spi_ce_high(spiDevId);                    /* disable the device */
}
/************************************************************************/
/* PROCEDURE: sst_read_status_register                    */
/*                                    */
/* This procedure read the status register and returns the byte.    */
/*                                    */
/* Input:                                */
/*        None                            */
/*                                    */
/* Returns:                                */
/*        byte                            */
/************************************************************************/
UINT8 sst_read_status_register(int spiDevId)
{
    UINT8 byte = 0;
    spi_ce_low(spiDevId);                    /* enable device */
    spi_write_command(spiDevId, 0x05);        /* send RDSR command */
    byte = spi_read_data(spiDevId);            /* receive byte */
    spi_ce_high(spiDevId);                    /* disable device */
    return byte;
}

/************************************************************************/
/* PROCEDURE: sst_wait_busy                            */
/*                                    */
/* This procedure waits until device is no longer busy (can be used by    */
/* Byte-Program, Sector-Erase, Block-Erase, Chip-Erase).        */
/*                                    */
/* Input:                                */
/*        None                            */
/*                                    */
/* Returns:                                */
/*        Nothing                            */
/************************************************************************/
void sst_wait_busy(int spiDevId)
{
    while (sst_read_status_register(spiDevId) == 0x03)    /* waste time until not busy */
    {
        sst_read_status_register(spiDevId);
    }
}

/*********************************************************************************************************
** Function name: sst_get_id
** Descriptions: 读取spi flash ID (ID Read1)
** Input: 无
** Output: 返回值即时读出的3字节ID信号 (先读出的数据放在最高字节处)
** Created by: 
** Created Date:2008-03-13 
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified Date: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/


UINT32 sst_get_id(int spiDevId)
{
    UINT32    id = 0;
    
    /*发送命令和地址*/
    spi_ce_low(spiDevId);           /*片选有效*/
    
    spi_write_command(spiDevId, 0x9f);       /*发送读ID命令*/

    
    taskDelay(1);
    
    /*读取ID信息*/
    id |= spi_read_data(spiDevId); /*manufacture ID*/
    
    id <<= 8;
    id |= spi_read_data(spiDevId); /*device code 1*/
    id <<= 8;
    id |= spi_read_data(spiDevId); /*device code 2*/

    id <<= 8;
    id |= spi_read_data(spiDevId); /*Unique ID Length*/

    taskDelay(1);

    spi_ce_high(spiDevId); /*片选取消*/

    /*printf("spi get id=%x!\n", id);*/
    
    return id;
}



/************************************************************************/
/* PROCEDURE: sst_sector_erase                        */
/*                                    */
/* This procedure Sector Erases the Chip.                */
/*                                    */
/* Input:                                */
/*        Dst:        Destination Address 000000H - 07FFFFH    */
/*                                    */
/* Returns:                                */
/*        Nothing                            */
/************************************************************************/
void sst_sector_erase(int spiDevId, UINT32 Dst)
{
    sst_WREN(spiDevId);
    spi_ce_low(spiDevId);                /* enable device */
    spi_write_command(spiDevId, 0xD8);            /* send Sector Erase command */
    spi_write_address(spiDevId, (UINT8)((Dst & 0xFFFFFF) >> 16));     /* send 3 address bytes */
    spi_write_address(spiDevId, (UINT8)((Dst & 0xFFFF) >> 8));
    spi_write_address(spiDevId, (UINT8)(Dst & 0xFF));
    spi_ce_high(spiDevId);                /* disable device */
    sst_WRDI(spiDevId);

}

/************************************************************************/
/* PROCEDURE: sst_subsector_erase                        */
/*                                    */
/* This procedure Sector Erases the Chip.                */
/*                                    */
/* Input:                                */
/*        Dst:        Destination Address 000000H - 07FFFFH    */
/*                                    */
/* Returns:                                */
/*        Nothing                            */
/************************************************************************/
void sst_subsector_erase(int spiDevId, UINT32 Dst)
{
    sst_WREN(spiDevId);
    spi_ce_low(spiDevId);                /* enable device */
    spi_write_command(spiDevId, 0x20);            /* send Sector Erase command */
    spi_write_address(spiDevId, (UINT8)((Dst & 0xFFFFFF) >> 16));     /* send 3 address bytes */
    spi_write_address(spiDevId, (UINT8)((Dst & 0xFFFF) >> 8));
    spi_write_address(spiDevId, (UINT8)(Dst & 0xFF));
    spi_ce_high(spiDevId);                /* disable device */
    sst_WRDI(spiDevId);

}


/************************************************************************/
/* PROCEDURE: sst_Chip_Erase                        */
/*                                    */
/* This procedure erases the entire Chip.                */
/*                                    */
/* Input:                                */
/*        None                            */
/*                                    */
/* Returns:                                */
/*        Nothing                            */
/************************************************************************/
void sst_chip_erase(int spiDevId)
{
    sst_WREN(spiDevId);
    spi_ce_low(spiDevId);                /* enable device */
    spi_write_command(spiDevId, 0xc7);            /* send Chip Erase command */
    spi_ce_high(spiDevId);                /* disable device */
    sst_WRDI(spiDevId);

}

/************************************************************************/
/* PROCEDURE:    sst_page_program                        */
/*                                    */
/* This procedure programs one address of the device.            */
/* Assumption:  Address being programmed is already erased and is NOT    */
/*        block protected.                    */
/*                                    */
/*                                    */
/*                                    */
/* Input:                                */
/*        Dst:        Destination Address 000000H - 07FFFFH    */
/*        byte:        byte to be programmed            */
/*                                      */
/*                                    */
/* Returns:                                */
/*        Nothing                            */
/*                                    */
/************************************************************************/
void sst_page_program(int spiDevId, UINT32 Dst, UINT8 * pData)
{
    int i;
    
    sst_WREN(spiDevId);
    spi_ce_low(spiDevId);                /* enable device */
    spi_write_command(spiDevId, 0x02);             /* send Byte Program command */
    spi_write_address(spiDevId, (UINT8)((Dst & 0xFFFFFF) >> 16));    /* send 3 address bytes */
    spi_write_address(spiDevId, (UINT8)((Dst & 0xFFFF) >> 8));
    spi_write_address(spiDevId, (UINT8)(Dst & 0xFF));
    for (i=0;i<256; i++)
    {
        spi_write_data(spiDevId, pData[i]);            /* send byte to be programmed */
    }
    spi_ce_high(spiDevId);                /* disable device */
    sst_WRDI(spiDevId);

}

/************************************************************************/
/* PROCEDURE:    sst_read_cont                        */
/*                                    */        
/* This procedure reads multiple addresses of the device and stores    */
/* data into 128 byte buffer. Maximum byte that can be read is 128 bytes*/
/*                                    */
/* Input:                                */
/*        Dst:        Destination Address 000000H - 07FFFFH    */
/*          no_bytes    Number of bytes to read    (max = 128)    */
/*                                    */
/* Returns:                                */
/*        Nothing                            */
/*                                    */
/************************************************************************/
void sst_read_cont(int spiDevId, UINT32 Dst, UINT32 no_bytes)
{
    UINT32 i = 0;
    spi_ce_low(spiDevId);                    /* enable device */
    spi_write_command(spiDevId, 0x03);             /* read command */
    spi_write_address(spiDevId, (UINT8)((Dst & 0xFFFFFF) >> 16));     /* send 3 address bytes */
    spi_write_address(spiDevId, (UINT8)((Dst & 0xFFFF) >> 8));
    spi_write_address(spiDevId, (UINT8)(Dst & 0xFF));
    for (i = 0; i < no_bytes; i++)            /* read until no_bytes is reached */
    {
        spi_read_data(spiDevId);            /* receive byte and store at address 80H - FFH */
    }
    spi_ce_high(spiDevId);                    /* disable device */
}
/************************************************************************/
/* PROCEDURE:    sst_byte_read                            */
/*                                    */        
/* This procedure reads one address of the device.  It will return the     */
/* byte read in variable byte.                        */
/*                                    */
/*                                    */
/*                                    */
/* Input:                                */
/*        Dst:    Destination Address 000000H - 07FFFFH        */
/*                                      */
/*                                    */
/* Returns:                                */
/*        byte                            */
/*                                    */
/************************************************************************/
UINT8 sst_byte_read(int spiDevId, UINT32 Dst) 
{
    UINT8 byte = 0;    

    spi_ce_low(spiDevId);            /* enable device */
    spi_write_command(spiDevId, 0x03);         /* read command */
    spi_write_address(spiDevId, (UINT8)((Dst & 0xFFFFFF) >> 16));    /* send 3 address bytes */
    spi_write_address(spiDevId, (UINT8)((Dst & 0xFFFF) >> 8));
    spi_write_address(spiDevId, (UINT8)(Dst & 0xFF));
    byte = spi_read_data(spiDevId);
    spi_ce_high(spiDevId);            /* disable device */
    return byte;                    /* return one byte read */
}



int spiFlashOpen(UINT32 * pCfgAddr)
{

    int i;

    /*if (spiDrvInited == FALSE)*/
    if (spiDrvInited == 0)
    {
        spiFlashDrvInit();
        spiDrvInited = TRUE;
    }
    
    for (i=0; i<MAX_SPI_DEV_NUM; i++)
    {
        if (spiDev[i].status ==0)
        {
            spiDev[i].pCfgAddr = pCfgAddr;
            spiDev[i].status = 1;
            return i;
        }
    }

    return INVALID_SPI_FLASH_DEV_ID;    
}


void spiFlashClose(int spiDevId)
{
    if ((spiDevId < 0) || (spiDevId >= MAX_SPI_DEV_NUM ))
        {
            return;
        }

    spiDev[spiDevId].status = 0;
}



UINT spiFlashRead(int spiDevId, UINT32 Dst, UINT8 * pBuffer, UINT len) 
{
    UINT i;    
#if 0
    if (Dst + len > 0x80000)
        return 0;
#endif

    spi_ce_low(spiDevId);            /* enable device */
    spi_write_command(spiDevId, 0x03);         /* read command */
    spi_write_address(spiDevId, (UINT8)((Dst & 0xFFFFFF) >> 16));    /* send 3 address bytes */
    spi_write_address(spiDevId, (UINT8)((Dst & 0xFFFF) >> 8));
    spi_write_address(spiDevId, (UINT8)(Dst & 0xFF));
    for (i=0;i<len; i++)
    {
        pBuffer[i] = spi_read_data(spiDevId);        
    }
    spi_ce_high(spiDevId);            /* disable device */
    
    return len;                        /* return one byte read */
}





int spiFlashSectorErase(int spiDevId, UINT32 Dst, UINT len)
{
    UINT32 SectorAddr;

    sst_wait_busy(spiDevId);
    SectorAddr = (Dst & (~(SECTOR_SIZE - 1)));
    while(SectorAddr < (Dst + len))
    {
        /* printf("erase sector 0x%08x ... ", SectorAddr); */
        sst_sector_erase(spiDevId, SectorAddr);
        sst_wait_busy(spiDevId);
        /* printf("OK\n", SectorAddr); */
        SectorAddr =SectorAddr + SECTOR_SIZE;
    }

    return OK;
}





int spiFlashSubSectorErase(int spiDevId, UINT32 Dst, UINT len)
{
    UINT32 SectorAddr;

    sst_wait_busy(spiDevId);
    SectorAddr = (Dst & (~(SUB_SECTOR_SIZE - 1)));
    while(SectorAddr < (Dst + len))
    {

        /* printf("erase sector 0x%08x ... ", SectorAddr); */
        sst_subsector_erase(spiDevId, SectorAddr);
        sst_wait_busy(spiDevId);
        /* printf("OK\n", SectorAddr); */
        SectorAddr = SectorAddr + SUB_SECTOR_SIZE;
    }
    return OK;
}



int spiFlashWrite(int spiDevId, UINT32 Dst, UINT8 * pData, UINT len)
{
    int i;
    
    if ((len & 0xFF)!= 0)
    {
        /*printf("len must be multiple of 256.\n");*/
        return ERROR;
    }

    spiFlashSubSectorErase(spiDevId, Dst, len);

    sst_wait_busy(spiDevId);
    
    for (i = 0; i<(len/MAX_BYTES_PER_WRITE); i++) /* 每次只写256 byte */
    {
        sst_page_program(spiDevId, (Dst+(MAX_BYTES_PER_WRITE*i)), (pData+(MAX_BYTES_PER_WRITE*i)));
        sst_wait_busy(spiDevId);
    }    

    return OK;
}

