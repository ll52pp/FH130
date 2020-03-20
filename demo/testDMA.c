#include "fc_api.h"
BLUE_PRINT gBluePrint;
extern int abc;
void test(int v)
{
   abc = v;
   printf("abc=%d\n", abc);
   printf("gBluePrint=%p\n", gBluePrint);
}

#if 0

#include <vxworks.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <tickLib.h>
#include <sysLib.h>
#include <semLib.h>

/* whether to use DMA interrupt*/
#define USE_DMA_INTERRUPT

#define DMA0_INT_VERTOR_BASE 16

/*
#define DMA1_INT_VERTOR        17
#define DMA2_INT_VERTOR     18
#define DMA3_INT_VERTOR        19
*/

#define CCSR_MR             0x00
#define CCSR_SR              0x04
#define CCSR_BCR            0x20
#define CCSR_DATR          0x18
#define CCSR_DAR            0x1C
#define CCSR_SATR          0x10
#define CCSR_SAR            0x14

#define MR_SWR              (1<<10)
#define MR_EOSIE            (1<<9)
#define MR_CDSM             (1<<4)
#define MR_CTM               (1<<2)
#define MR_CS                  (1<<1)


#define SR_CB                   (1<<2)
#define SR_EOSI                (1<<1)

#define SATR_SREADTTYPE_READ_SNOOP           (5<<16)
#define DATR_SWRITETTYPE_READ_SNOOP         (5<<16)

#define DMA_REG_READ(addr)                    (*(UINT *)(addr))
#define DMA_REG_WRITE(addr, value)        (*(UINT *)(addr) = (value))


#define MAX_DMA_CHANNEL_NUM            4


typedef struct
{
    int bUsed;
    int channelIndex;
    UINT baseRegDMA;
    SEM_ID semLock;
    SEM_ID semCompleted;
    int vector;
}DMA_CHANNEL;

DMA_CHANNEL DmaChannel[MAX_DMA_CHANNEL_NUM];

int bMyDmaInited = 0;
int bPrintDmaInfo = 0;

UINT iDmaIntCounter = 0;

void myDmaIntHandler(DMA_CHANNEL * pDMAChannel)
{
    if (bPrintDmaInfo)
    {
        logMsg("%s: enter, channel %d, CCSR_SR = 0x%x \n", (int)__FUNCTION__, pDMAChannel->channelIndex, DMA_REG_READ(pDMAChannel->baseRegDMA + CCSR_SR), 4,5,6);
    }

    iDmaIntCounter ++;

    DMA_REG_WRITE(pDMAChannel->baseRegDMA + CCSR_SR, SR_EOSI);

    /* 唤醒处理任务 */
    semGive(pDMAChannel->semCompleted);

    if (bPrintDmaInfo)
    {
        logMsg("%s: enter, channel %d \n", (int)__FUNCTION__, pDMAChannel->channelIndex, 3,4,5,6);
    }

}


int myDmaInit()
{
    int i;
    int ret;

    for (i=0; i<MAX_DMA_CHANNEL_NUM; i++)
    {
        /* Base Address of Memory Mapped Registers */
        /* #define CCSBAR  0xE0000000 */
        
        if (i==0)
        {
            DmaChannel[i].baseRegDMA = 0xE0021100;
        }
        else if (i==1)
        {
            DmaChannel[i].baseRegDMA = 0xE0021180;
        }
        else if (i==2)
        {
            DmaChannel[i].baseRegDMA = 0xE0021200;
        }
        else /* (i==3) */
        {
            DmaChannel[i].baseRegDMA = 0xE0021280;
        }

        DmaChannel[i].channelIndex = i;
        DmaChannel[i].vector = DMA0_INT_VERTOR_BASE + i;

#ifdef USE_DMA_INTERRUPT
        DMA_REG_WRITE((DmaChannel[i].baseRegDMA + CCSR_MR), (MR_SWR | MR_CDSM | MR_CTM | MR_EOSIE));
#else
        DMA_REG_WRITE((DmaChannel[i].baseRegDMA + CCSR_MR), (MR_SWR | MR_CDSM | MR_CTM ));
#endif
        DMA_REG_WRITE((DmaChannel[i].baseRegDMA + CCSR_SR), 0xFFFFFFFF);
        DMA_REG_WRITE((DmaChannel[i].baseRegDMA + CCSR_DATR), DATR_SWRITETTYPE_READ_SNOOP);
        DMA_REG_WRITE((DmaChannel[i].baseRegDMA + CCSR_SATR), SATR_SREADTTYPE_READ_SNOOP);


        DmaChannel[i].semLock         = semBCreate(SEM_Q_FIFO, SEM_FULL);
        DmaChannel[i].semCompleted     = semBCreate(SEM_Q_FIFO, SEM_EMPTY);

#ifdef USE_DMA_INTERRUPT
        ret = ret = intConnect ( (VOIDFUNCPTR *)DmaChannel[i].vector, (VOIDFUNCPTR)myDmaIntHandler, (int) &DmaChannel[i]);
        if (ret != OK)
        {
            printf("intConnect() Fail, irq=%d\n", DmaChannel[i].vector);    
        }
        ret = intEnable (DmaChannel[i].vector);
        if (ret != OK)
        {
            printf("intEnable() Fail, irq=%d\n", DmaChannel[i].vector);    
        }
#endif        

    }
}


int DMAErrCount = 0;


STATUS myDmaStartDirect
(
    DMA_CHANNEL * pDMAChannel,
    UINT32 sourceAddress,
    UINT32 destinationAddress,
    UINT32 numberOfBytes
)

{

    int delay = 10;
    SEM_ID * pSem = NULL;

    if (bMyDmaInited == 0)
    {
        myDmaInit();
        bMyDmaInited = 1;
    }

    semTake(pDMAChannel->semLock, WAIT_FOREVER);

    /* Stop DMA channel and set direct mode */
#ifdef USE_DMA_INTERRUPT
    DMA_REG_WRITE((pDMAChannel->baseRegDMA +CCSR_MR), (MR_SWR | MR_CDSM | MR_CTM | MR_EOSIE));    
#else
    DMA_REG_WRITE((pDMAChannel->baseRegDMA +CCSR_MR), (MR_SWR | MR_CDSM | MR_CTM) );    
#endif

    
    if (bPrintDmaInfo) 
    {
        printf("wait for the channel to be free ... ");
    }
    /* waitting for the channelto be free */
    while(DMA_REG_READ(pDMAChannel->baseRegDMA +CCSR_SR) & SR_CB);
    
    if (bPrintDmaInfo) 
    {
        printf("OK\n ");
    }

    /* cleare status register*/
    DMA_REG_WRITE((pDMAChannel->baseRegDMA +CCSR_SR), 0xFFFFFFFF);

    /* Program the number of bytes int the Byte Count Register */
    DMA_REG_WRITE((pDMAChannel->baseRegDMA +CCSR_BCR), numberOfBytes);

    /* Program the Destination Address Register */
    DMA_REG_WRITE((pDMAChannel->baseRegDMA +CCSR_DAR), destinationAddress);

    /* Program the Source Address Register and start DMA */
    DMA_REG_WRITE((pDMAChannel->baseRegDMA +CCSR_SAR), sourceAddress);

#ifdef USE_DMA_INTERRUPT
    semTake(pDMAChannel->semCompleted, 10);
#else
    while(delay --);
#endif


    if (bPrintDmaInfo) 
    {
        printf("waiting for the channel to be free ... ");
    }
    while( DMA_REG_READ(pDMAChannel->baseRegDMA + CCSR_SR) & SR_CB);
    
    if (bPrintDmaInfo) 
    {
        printf("OK\n");
    }

    if ( DMA_REG_READ(pDMAChannel->baseRegDMA + CCSR_SR) == 0)
    {
        semGive(pDMAChannel->semLock);
        
        return OK;
    }

    semGive(pDMAChannel->semLock);

    DMAErrCount ++;
    return ERROR;
    
}


void * myDmaCopy( char * dest, char * src, int size)
{
    if ( size < 256)
    {
        return memcpy(dest, src, size);
    }

    if (myDmaStartDirect(&DmaChannel[0], (UINT32)src, (UINT32)dest, (UINT32) size) == OK)
    {
        return dest;
    }

    return NULL;
}



/* testDmaMemCpySpeed 0, 1000, 0x100000 */
/* testDmaMemCpySpeed 0, 100, 0x1000000 */
void testDmaMemCpySpeed(int channel, UINT count, UINT size)
{
    int i;
    char *pMsg1 = NULL;
    char *pMsg2 = NULL;
    UINT tickFrom, tick;    
    UINT64 bytes = 0;
    UINT64 speed = 0;
    
    pMsg1 = (char *)cacheDmaMalloc(size);
    if (pMsg1 == NULL)
    {
        printf("testMemCpySpeed : malloc return NULL.\n");
        return;
    }

    pMsg2 = (char *)cacheDmaMalloc(size);
    if (pMsg2 == NULL)
    {
        printf("testMemCpySpeed : malloc return NULL.\n");
        free(pMsg1);
        return;
    }

    tickFrom = tickGet();
    for (i=0; i<count; i++)
    {
        myDmaStartDirect(&DmaChannel[0], (UINT32)pMsg1, (UINT32)pMsg2, (UINT32) size);
    }
    tick= tickGet() - tickFrom;
    bytes = ((UINT64)count) * ((UINT64)size);
    if (tick == 0)
    {
        speed = bytes;
    }
    else
    {
        speed = bytes * sysClkRateGet() /tick;
    }
    

    printf("copy %s bytes in %u ticks,", UInt64toStr2(bytes), tick);
    printf("speed %s byte/s\n,", UInt64toStr2(speed));
    
    cacheDmaFree(pMsg1);
    cacheDmaFree(pMsg2);
}

#endif