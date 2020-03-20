/*++
文件名
    hw.c

描述
    
--*/
/* 接口函数 */
#include <vxworks.h>
#include "hw.h"
#include "fc_asm.h"

UINT32 g_hwDebugFlag = 0;

#define HW_DBG_CONFIG  0x00000001
#define HW_DBG_SEND    0x00000100
#define HW_DBG_RECV    0x00000200



extern void sysPciOutLong(ULONG address, ULONG data); 
extern ULONG sysPciInLong(ULONG address);  

void hw_delay(FCUINT mCycleTime)
{
    FCUINT i = 0;
    for(i = 0; i < mCycleTime; i++ )
    {
        ;
    }
}


/* 创建通道 */
int hwCreateChannel(REG_HW *reg_hw, int direct, int mode, unsigned int index, int priority, int asmid, int fcid, int msg_recover)
{
    int ret, sid, did;
    FC_ASM fc_asm;
    INDIRECT_CONTROL i_control;
    ULONG value;

    if (g_hwDebugFlag & HW_DBG_CONFIG)
    {
        /*printf("[hwCreateChannel]enter\n");*/
    }
    
    ret = 0;
    if (direct == HOST_READ)
    {
        /* RX */
        sid = fcid;
        did = hwGetPortFcid(reg_hw);
    }
    else
    {
        /* TX */
        sid = hwGetPortFcid(reg_hw);
        did = fcid;
    }
    InitFcAsmHeader(&fc_asm, asmid, sid, did);
    
    /* config tx/rx register */
    if (direct == HOST_READ)
    {
        /* RX */
        /*printf("[hwCreateChannel]mode=%d priority=%d\n", mode, priority);*/
        if (mode == ASM_MODE) 
        { /* block */
            /* set hash */
            ret = SetHashValue(reg_hw, asmid, sid, index);
            if (ret) { /* hash conflict */
                return ret;
            }
            SetChannelPriority(reg_hw, index, priority);
        }
        else
        {
            SetRawPriority(reg_hw, priority);
        }
        hwSetChannelActiveMode(reg_hw, mode, index, RX_ACTIVE);
    }
    else
    { /* TX */
        if (mode == ASM_MODE)
        {
            /* common of control register */
            i_control.value = 0;
            i_control.u.direct = IDC_DIRECT_TX;
            /* FA_IDX_RSV0 */
            i_control.u.address = ((index << 4) | FA_IDX_RSV0);
            value = 0;
            WriteIndirectRegisterUlong(reg_hw, i_control.value, value);

            if (g_hwDebugFlag & HW_DBG_CONFIG)
            {
                printf("FA_IDX_RSV0=0x%08x\n", (int)value);
            }
            /* FA_IDX_RSV1 */
            i_control.u.address = ((index << 4) | FA_IDX_RSV1);
            value = 0;
            WriteIndirectRegisterUlong(reg_hw, i_control.value, value);
            if (g_hwDebugFlag & HW_DBG_CONFIG) 
            {
                printf("FA_IDX_RSV1=0x%08x\n", (int)value);
            }
            /* FA_IDX_DID */
            i_control.u.address = ((index << 4) | FA_IDX_DID);
            value = fc_asm.fc_header.DID_R_CTL.value;
            WriteIndirectRegisterUlong(reg_hw, i_control.value, value);
            if (g_hwDebugFlag & HW_DBG_CONFIG) 
            {
                printf("FA_IDX_DID=0x%08x\n", (int)value);
            }
            /* FA_IDX_SID */
            i_control.u.address = ((index << 4) | FA_IDX_SID);
            fc_asm.fc_header.SID_CS_CTL_Priority.u.cs_ctl_priority = priority;
            value = fc_asm.fc_header.SID_CS_CTL_Priority.value;
            WriteIndirectRegisterUlong(reg_hw, i_control.value, value);
            if (g_hwDebugFlag & HW_DBG_CONFIG) 
            {
                printf("FA_IDX_SID=0x%08x\n", (int)value);
            }
            /* FA_IDX_FCTL */
            i_control.u.address = ((index << 4) | FA_IDX_FCTL);
            value = fc_asm.fc_header.F_CTL_TYPE.value;
            WriteIndirectRegisterUlong(reg_hw, i_control.value, value);
            if (g_hwDebugFlag & HW_DBG_CONFIG) 
            {
                printf("FA_IDX_FCTL=0x%08x\n", (int)value);
            }
            /* FA_IDX_SEQ_ID_SEQ_CNT */
            i_control.u.address = ((index << 4) | FA_IDX_SEQ_ID_SEQ_CNT);
            value = fc_asm.fc_header.SEQ_CNT_DF_CTL_SEQ_ID.value;
            WriteIndirectRegisterUlong(reg_hw, i_control.value, value);
            if (g_hwDebugFlag & HW_DBG_CONFIG) 
            {
                printf("FA_IDX_SEQ_ID_SEQ_CNT=0x%08x\n", (int)value);
            }
            /* FA_IDX_OXID_RXID */
            i_control.u.address = ((index << 4) | FA_IDX_OXID_RXID);
            value = fc_asm.fc_header.RX_ID_OX_ID.value;
            WriteIndirectRegisterUlong(reg_hw, i_control.value, value);
            if (g_hwDebugFlag & HW_DBG_CONFIG) 
            {
                printf("FA_IDX_OXID_RXID=0x%08x\n", (int)value);
            }
            /* FA_IDX_PARAMETER */
            i_control.u.address = ((index << 4) | FA_IDX_PARAMETER);
            value = 0;
            WriteIndirectRegisterUlong(reg_hw, i_control.value, value);
            if (g_hwDebugFlag & HW_DBG_CONFIG) 
            {
                printf("FA_IDX_PARAMETER=0x%08x\n", (int)value);
            }
            /* FA_IDX_MESSAGEID */
            i_control.u.address = ((index << 4) | FA_IDX_MESSAGEID);
            value = fc_asm.asm_header.MESSAGE_ID;
            WriteIndirectRegisterUlong(reg_hw, i_control.value, value);
            if (g_hwDebugFlag & HW_DBG_CONFIG) 
            {
                printf("FA_IDX_MESSAGEID=0x%08x\n", (int)value);
            }
            /* FA_IDX_SECURITY */
            i_control.u.address = ((index << 4) | FA_IDX_SECURITY);
            value = 0x00008000;        /* liuxiuqing */
            WriteIndirectRegisterUlong(reg_hw, i_control.value, value);
            if (g_hwDebugFlag & HW_DBG_CONFIG) 
            {
                printf("FA_IDX_SECURITY=0x%08x\n", (int)value);
            }
            /* FA_IDX_RSV2 */
            i_control.u.address = ((index << 4) | FA_IDX_RSV2);
            value = 0;
            WriteIndirectRegisterUlong(reg_hw, i_control.value, value);
            if (g_hwDebugFlag & HW_DBG_CONFIG) 
            {
                printf("FA_IDX_RSV2=0x%08x\n", (int)value);
            }
        }
    }
    if (g_hwDebugFlag & HW_DBG_CONFIG)
    {
        printf("[hwCreateChannel]leave\n");
    }
    
    return ret;
}

/* 设置通道激活/非激活 */
void hwSetChannelActiveMode(REG_HW *reg_hw, ULONG mode, ULONG index, ULONG active)
{
    UINT quotient, remainder;
    ULONG value, original_value;
    INDIRECT_CONTROL i_control;

    i_control.value = 0;
    i_control.u.direct = IDC_DIRECT_RX;;
       if (mode == RAW_MODE)
    {
        /*printf("mode=RAW_MODE active=%d\n", active);*/
        /* set active bit */
        /* 2014-5-26 Modified by Huilin for RAW channel Priority change */
        i_control.u.address = IDA_RX_RAW_ACTIVE_BASE;
        value = ReadIndirectRegisterUlong(reg_hw, i_control.value);
        
        value &= ~0x1;                /* Clear bit0 */
        value |= (active & 0x1);    /* set bit0 */
        
        WriteIndirectRegisterUlong(reg_hw, i_control.value, value);
        /*printf("active bit=%d\n", ReadIndirectRegisterUlong(reg_hw, i_control.value));*/
    } 
    else
    { /* block mode */
        quotient = index / 16;
        remainder = (index % 16);
        i_control.u.address = IDA_RX_ACTIVE_BASE + quotient;
        original_value = ReadIndirectRegisterUlong(reg_hw, i_control.value);
        /* clear 2bit for channel */
        original_value &= (~(3 << (remainder << 1)));
        /* set active bit default no active */
        value = active;
        /* set mode bit */
        value |= (1 << 1);
        value = original_value | (value << (remainder << 1));
        WriteIndirectRegisterUlong(reg_hw, i_control.value, value);
    }
}

/* 清除所有接收通道的配置 */
void hwClearAllChannel(REG_HW *reg_hw)
{
    FCINT index;
    
    if (g_hwDebugFlag & HW_DBG_CONFIG)
    {
        printf("[hwClearAllChannel]enter\n");
    }
    
    /* 清除hash */
    EmptyHashTable(reg_hw);
    
    for (index = 0; index < 256; ++index)
    {
        hwSetChannelActiveMode(reg_hw, ASM_MODE, index, RX_INACTIVE);
    }
    hwSetChannelActiveMode(reg_hw, RAW_MODE, (unsigned long)-1, RX_INACTIVE);
    
    if (g_hwDebugFlag & HW_DBG_CONFIG)
    {
        printf("[hwClearAllChannel]leave\n");
    }
}

/* 设置端口的FCID */
void hwSetPortFcid(REG_HW *reg_hw, int fcid)
{
    PORT_INFO pi;

    pi.value = ReadRegisterUlong(&reg_hw->PORT_CONFIG);
    pi.u.sid = fcid;
    WriteRegisterUlong(&reg_hw->PORT_CONFIG, pi.value);
    hwSetPortDidFilterEnab(reg_hw, 1);
}

/* 获取端口的FCID */
int hwGetPortFcid(REG_HW *reg_hw)
{
    PORT_INFO pi;

    pi.value = ReadRegisterUlong(&reg_hw->PORT_CONFIG);
    return pi.u.sid;
}

/* 设置端口的速率 */
void hwSetPortSpeed(REG_HW *reg_hw, int speed)
{
    PORT_INFO pi;

    pi.value = ReadRegisterUlong(&reg_hw->PORT_CONFIG);
    pi.u.speed = speed;
    WriteRegisterUlong(&reg_hw->PORT_CONFIG, pi.value);
}

/* 获取端口的速率 */
int hwGetPortSpeed(REG_HW *reg_hw)
{
    PORT_INFO pi;

    pi.value = ReadRegisterUlong(&reg_hw->PORT_CONFIG);
    return pi.u.speed;
}

/* 设置端口的信用 */
void hwSetPortCredit(REG_HW *reg_hw, int credit)
{
    PORT_INFO pi;
    
    if (credit == 0)
    {
        credit = 8;
    }
    pi.value = ReadRegisterUlong(&reg_hw->PORT_CONFIG);
    pi.u.credit = (credit - 1);        /* 0 - base */
    WriteRegisterUlong(&reg_hw->PORT_CONFIG, pi.value);
}

/* 获取端口的信用 */
int hwGetPortCredit(REG_HW *reg_hw)
{
    PORT_INFO pi;
    pi.value = ReadRegisterUlong(&reg_hw->PORT_CONFIG);
    return (pi.u.credit + 1);        /* 0 - base */
}

/* 设置端口的回环 */
void hwSetPortGtxLoopBack(REG_HW *reg_hw, int gtx_loopback)
{
    PORT_INFO pi;

    pi.value = ReadRegisterUlong(&reg_hw->PORT_CONFIG);
    pi.u.gtx_loopback = gtx_loopback;
    WriteRegisterUlong(&reg_hw->PORT_CONFIG, pi.value);
}

/* 获取端口的回环 */
int hwGetPortGtxLoopBack(REG_HW *reg_hw)
{
    PORT_INFO pi;
    pi.value = ReadRegisterUlong(&reg_hw->PORT_CONFIG);
    return pi.u.gtx_loopback;
}

/*设置端口的DID过滤使能*/
void hwSetPortDidFilterEnab(REG_HW *reg_hw, int did_filter_enab)
{
    PORT_INFO pi;
    
    pi.value = ReadRegisterUlong(&reg_hw->PORT_CONFIG);
    pi.u.did_filter_enab = did_filter_enab;
    WriteRegisterUlong(&reg_hw->PORT_CONFIG, pi.value);
}

/*获取端口的DID过滤使能*/
int hwGetPortDidFilterEnab(REG_HW *reg_hw)
{
    PORT_INFO pi;
    pi.value = ReadRegisterUlong(&reg_hw->PORT_CONFIG);
    return pi.u.did_filter_enab;
}

/* 设置端口的接收使能 */
void hwSetPortRxEnab(REG_HW *reg_hw, int enab)
{
    PORT_RX_ENAB port_rx_enab;

    if (g_hwDebugFlag & HW_DBG_CONFIG)
    {
        printf("[hwSetPortRxEnab]enter\n");
    }
    /* set redundancy recv enab */
    port_rx_enab.value = ReadRegisterUlong(&reg_hw->PORT_RX_ENAB);
    
    port_rx_enab.u.reset = 0;
    port_rx_enab.u.p0_mac_switch = enab == 1 ? 0 : 1; /* port0 Mac force off 0-mac on 1-mac off */
    port_rx_enab.u.redundancy_enab = 1;
    port_rx_enab.u.e_d_tov = 10;
    port_rx_enab.u.p0_rx_enab = enab;

    WriteRegisterUlong(&reg_hw->PORT_RX_ENAB, port_rx_enab.value);

    /*端口使能后必须给FPGA一定的时间建立link*/
    taskDelay(50);
}


/* 设置消息丢弃使能 */
void hwSetDiscardEnab(REG_HW *reg_hw, int enab)
{
    PORT_RX_ENAB port_rx_enab;

    port_rx_enab.value = ReadRegisterUlong(&reg_hw->PORT_RX_ENAB);
    port_rx_enab.u.discard_enab = enab;
    WriteRegisterUlong(&reg_hw->PORT_RX_ENAB, port_rx_enab.value);
}

/* 获取消息丢弃使能 */
int hwGetDiscardEnab(REG_HW *reg_hw)
{
    PORT_RX_ENAB port_rx_enab;

    port_rx_enab.value = ReadRegisterUlong(&reg_hw->PORT_RX_ENAB);
    return port_rx_enab.u.discard_enab;
}


/* 设置端口的EDTOV */
void hwSetPortEDTOV(REG_HW *reg_hw, int edtov)
{
    PORT_RX_ENAB port_rx_enab;

    port_rx_enab.value = ReadRegisterUlong(&reg_hw->PORT_RX_ENAB);
    port_rx_enab.u.e_d_tov = edtov;    
    WriteRegisterUlong(&reg_hw->PORT_RX_ENAB, port_rx_enab.value);
}

/* 获取端口的接收使能 */
int hwGetPortRxEnab(REG_HW *reg_hw)
{
    PORT_RX_ENAB port_rx_enab;
    if (g_hwDebugFlag & HW_DBG_CONFIG)
    {
        printf("[hwGetPortRxEnab]enter\n");
    }
    port_rx_enab.value = ReadRegisterUlong(&reg_hw->PORT_RX_ENAB);
    if (g_hwDebugFlag & HW_DBG_CONFIG)
    {
        printf("[hwGetPortRxEnab]leave\n");
    }
    return port_rx_enab.u.p0_rx_enab;
}


/* 获取FPGA的版本 */
int hwGetFpgaVersion(REG_HW *reg_hw)
{
    FPGA_VER ver;

    ver.value = ReadRegisterUlong(&reg_hw->FPGA_VER);
    if (g_hwDebugFlag & HW_DBG_CONFIG)
    {
        printf("[hwGetFpgaVersion]leave ver=%d\n", ver.value);
    }
    return ver.value; /* ver.u.version; */
}

/* 获取端口的状态 */
int hwGetPortStatus(REG_HW *reg_hw, int *portStatus, int portCount)
{
    /* 该函数会在中断处理函数中被调用，因此不能调用printf */
    PORT_STATUS status;

    status.value = ReadRegisterUlong(&reg_hw->PORT_STATUS);
    portStatus[0] = status.u.p0_status;
    portStatus[1] = status.u.p1_status;

    return OK;
}

/* 读取电压 */
int hwGetVoltage(REG_HW *reg_hw)
{
    int voltage = 0;
    PORT_STATUS status;

    status.value = ReadRegisterUlong(&reg_hw->PORT_STATUS);
    voltage = ((status.u.voltage) * 3000) / 4096;

    return voltage;    
}

/* 读取温度  */
int hwGetTemperature(REG_HW *reg_hw)
{
    PORT_STATUS status;
    int temperature;
    status.value = ReadRegisterUlong(&reg_hw->PORT_STATUS);

    temperature = (((status.u.temperature) * 503975)/4096) - 273150; /* X1000 */
    return (int)temperature;
}

/* 关闭/打开接收中断 */
int hwSetIntrptEnable(REG_HW *reg_hw, int bEnable)
{
    INTERRUPT  intrp;

    if (bEnable)
    {
        intrp.value = 0;
        intrp.u.intr_enable_global = 1;
        intrp.u.intr_enable_Rx_IU  = 1;
        intrp.u.intr_enable_link_change = 1;

        /* clear all pending interrupt*/
        intrp.u.pending_link_change    = 1;
        intrp.u.pending_send_bd_empty = 1; 
        intrp.u.pending_Tx_IU = 1; 
        intrp.u.pending_Rx_credit_out = 1;
        intrp.u.pending_Rx_IU = 1;
    }
    else
    {
        intrp.value = 0;
        intrp.u.intr_enable_global = 0;
        intrp.u.intr_enable_Rx_IU  = 0;

        /* clear all pending interrupt*/
        intrp.u.pending_link_change    = 1;
        intrp.u.pending_send_bd_empty = 1; 
        intrp.u.pending_Tx_IU = 1; 
        intrp.u.pending_Rx_credit_out = 1;
        intrp.u.pending_Rx_IU = 1;
    }
    WriteRegisterUlong(&reg_hw->INTERRUPT_CTRL, intrp.value);
    
    return OK;
}

/* 获取链路变化中断位 */
int hwGetLinkChangePending(REG_HW *reg_hw)
{
    INTERRUPT  intrp;
    
    intrp.value = ReadRegisterUlong(&reg_hw->INTERRUPT_CTRL);
    return (int)(intrp.u.intr_enable_link_change);
}

/* 复位FPGA */
void hwResetFpga(REG_HW *reg_hw, int forceOffLine)
{
    INT32 count;
    PORT_RX_ENAB enab;
    PORT_STATUS status;
    
    enab.value = ReadRegisterUlong(&reg_hw->PORT_RX_ENAB);
    enab.u.reset = 1;
    WriteRegisterUlong(&reg_hw->PORT_RX_ENAB, enab.value);

    /*等待复位完成(resetCpl=1)*/
    count = 0;
    do
    {
        taskDelay(10);
        status.value = ReadRegisterUlong(&reg_hw->PORT_STATUS);
        if (status.u.resetCplt == 1) break;
    } while (++count < 10);
    if (count >= 10)
    {
        printf("wait fpga reset timeout\n");
    }
}

/* 注册Tx的缓冲区 */
int hwRegisterTxDmaBuf(REG_HW *reg_hw, int index, int value)
{
    int ret;
    INDIRECT_CONTROL i_control;
    
    ret = 0;
    if (g_hwDebugFlag & HW_DBG_CONFIG) 
    {
        printf("[hwRegisterTxDmaBuf] enter, index=%d, value=%d\n", index, value);
    }
    i_control.value = 0;
    i_control.u.direct = IDC_DIRECT_TX;
    i_control.u.address = IDA_TX_LOGIC_BUF_BASE + index;
    WriteIndirectRegisterUlong(reg_hw, i_control.value, value);
    return ret;
}

/* 注册Rx的缓冲区 */
int hwRegisterRxDmaBuf(REG_HW *reg_hw, int priority, int index, int value)
{
    int ret;
    INDIRECT_CONTROL i_control;
    
    ret = 0;
    if (g_hwDebugFlag & HW_DBG_CONFIG)
    {
        printf("[hwRegisterRxDmaBuf] enter, priority=%d, index=%d, value=%d\n", priority, index, value);
    }
    i_control.value = 0;
    i_control.u.direct = IDC_DIRECT_RX;
    i_control.u.address = IDA_RX_LOGIC_BUF_BASE + (priority * 0x400) + index;
    WriteIndirectRegisterUlong(reg_hw, i_control.value, value);

    return ret;
}

/*注册Rx的缓冲区*/
void hwRegisterRxDmaBufSize(REG_HW *reg_hw, int priority, int buf_size)
{
    int value, byte_4k;
    INDIRECT_CONTROL i_control;
    
    byte_4k = 4096;
    value = buf_size / byte_4k;
    
    /* 注册RX接收缓冲区的大小 以8K为单位 */
    i_control.value = 0;
    i_control.u.direct = IDC_DIRECT_RX;
    i_control.u.address = IDA_RX_LOGIC_BUF_SIZE_BASE + priority;
    WriteIndirectRegisterUlong(reg_hw, i_control.value, value);
}

/*设置节点的同步角色*/
void hwSetSyncMode(REG_HW *reg_hw, FCUINT enab)
{
    RTC_CONTROL rtc_control;
    
    rtc_control.value = ReadRegisterUlong(&reg_hw->RTC_CONTROL);
    rtc_control.u.global_sync_enab = enab;
    WriteRegisterUlong(&reg_hw->RTC_CONTROL, rtc_control.value);
}


/* RTC控制 */
void hwRtcControl(REG_HW *reg_hw, int global_sync_enab, int event_period, int sync_enab, int rtc_base)
{
    RTC_CONTROL rtc_control;
    
    rtc_control.value = ReadRegisterUlong(&reg_hw->RTC_CONTROL);
    rtc_control.u.global_sync_enab = global_sync_enab;
    rtc_control.u.event_period = event_period;
    rtc_control.u.p0_sync_enab = sync_enab;
    rtc_control.u.p1_sync_enab = sync_enab;
    rtc_control.u.rtc_base = rtc_base;
    WriteRegisterUlong(&reg_hw->RTC_CONTROL, rtc_control.value);
}

void hwSetRtcControlRxTx(REG_HW *reg_hw, int rx_enab, int tx_enab)
{
    RTC_CONTROL rtc_control;
    
    rtc_control.value = ReadRegisterUlong(&reg_hw->RTC_CONTROL);
    rtc_control.u.global_sync_enab = rx_enab;
    rtc_control.u.p0_sync_enab = tx_enab;
    rtc_control.u.p1_sync_enab = tx_enab;
    WriteRegisterUlong(&reg_hw->RTC_CONTROL, rtc_control.value);
}

/*设置时钟同步周期*/
int hwSetClkSyncPeriod(REG_HW *reg_hw, int clkSyncPeriod)
{
    RTC_CONTROL rtc_control;
    
    rtc_control.value = ReadRegisterUlong(&reg_hw->RTC_CONTROL);
    rtc_control.u.rtc_base = 0;
    rtc_control.u.event_period = clkSyncPeriod;
    WriteRegisterUlong(&reg_hw->RTC_CONTROL, rtc_control.value);
    
    return OK;
}

/* set Snapshot CMD day bit */
void hwReadRtcPrepare(REG_HW *reg_hw)
{
    ULONG value = ((unsigned int)1 << 31);    /* bit31 = 1*/

    WriteRegisterUlong(&reg_hw->RTC_DATE_READ, value);
}

/* clear Snapshot CMD day bit */
void hwReadRtcFinish(REG_HW *reg_hw)
{
    ULONG value = 0;

    WriteRegisterUlong(&reg_hw->RTC_DATE_READ, value);
}

/* 读取RTC */
UINT64 hwGetRtc(REG_HW *reg_hw)
{
    ULONG  high, low;
    UINT64 time;
    
    low = ReadRegisterUlong(&reg_hw->RTC_READ_LOW);
    high = ReadRegisterUlong(&reg_hw->RTC_READ_HIGH);
    time = (((UINT64)high) << 32) | (UINT64)low;
    
    return time;
}

/* 写入RTC */
void hwSetRtc(REG_HW *reg_hw, UINT64 time)
{    
    WriteRegisterUlong(&reg_hw->RTC_WRITE_HIGH, (ULONG)(time >> 32));
    WriteRegisterUlong(&reg_hw->RTC_WRITE_LOW,  (ULONG)(time & 0xFFFFFFFF));
}

/* CARRIER_RTC_CTRL  载板时钟同步配置*/
void hwSetCarrierRTCSyn(REG_HW *reg_hw, int carrier_rtc_enb, int mode, int pluse_duty)
{
    CARRIER_RTC_CTRL p;

    p.value = ReadRegisterUlong(&reg_hw->CARRIER_RTC_CTRL);
    p.u.pluse_duty = pluse_duty;
    p.u.mode = mode;
    p.u.carrier_rtc_enb = carrier_rtc_enb;
    WriteRegisterUlong(&reg_hw->CARRIER_RTC_CTRL, p.value);
}

/* 读取DATE */
UINT32 hwGetDate(REG_HW *reg_hw)
{
    ULONG value = 0;
    
    value = ReadRegisterUlong(&reg_hw->RTC_DATE_READ);
    value &= 0xFFFF; /* bit0 ~ bit15*/

    return (UINT32)value;
}

/* 设置DATE */
void hwSetDate(REG_HW *reg_hw, UINT32 date )
{
    WriteRegisterUlong(&reg_hw->RTC_DATE_WRITE, (ULONG)(date & 0xFFFF));
}

/*读取本地统计寄存器的值*/
void hwGetLocalStatisticsInfo(REG_HW *reg_hw, LocalStatisticsInfo *lsi)
{
    STATISTICS_CONTROL sc;

    sc.value = 0;
    sc.u.start = 1;
    WriteRegisterUlong(&reg_hw->STATISTICS_CONTROL, sc.value);

    sc.value = 0;
    sc.u.type = LSI_RECV_FRAM_NUM;
    WriteRegisterUlong(&reg_hw->STATISTICS_CONTROL, sc.value);
    lsi->recvFrameNum = ReadRegisterUlong(&reg_hw->STATISTICS_DATA);

    sc.value = 0;
    sc.u.type = LSI_RECV_IU_NUM;
    WriteRegisterUlong(&reg_hw->STATISTICS_CONTROL, sc.value);
    lsi->recvIuNum = ReadRegisterUlong(&reg_hw->STATISTICS_DATA);

    sc.value = 0;
    sc.u.type = LSI_RECV_IU_ERR_NUM;
    WriteRegisterUlong(&reg_hw->STATISTICS_CONTROL, sc.value);
    lsi->recvIuErrNum = ReadRegisterUlong(&reg_hw->STATISTICS_DATA);

    sc.value = 0;
    sc.u.type = LSI_RECV_IU_DISCARD_NUM;
    WriteRegisterUlong(&reg_hw->STATISTICS_CONTROL, sc.value);
    lsi->recvIuDiscardNum = ReadRegisterUlong(&reg_hw->STATISTICS_DATA);

    sc.value = 0;
    sc.u.type = LSI_RECV_IU_INVALID_NUM;
    WriteRegisterUlong(&reg_hw->STATISTICS_CONTROL, sc.value);
    lsi->recvIuInvalidNum = ReadRegisterUlong(&reg_hw->STATISTICS_DATA);

    sc.value = 0;
    sc.u.type = LSI_SEND_FRAME_NUM;
    WriteRegisterUlong(&reg_hw->STATISTICS_CONTROL, sc.value);
    lsi->sendFrameNum = ReadRegisterUlong(&reg_hw->STATISTICS_DATA);

    sc.value = 0;
    sc.u.type = LSI_SEND_IU_NUM;
    WriteRegisterUlong(&reg_hw->STATISTICS_CONTROL, sc.value);
    lsi->sendIuNum = ReadRegisterUlong(&reg_hw->STATISTICS_DATA);
}

/* 向FPGA写入BD */
void hwPushBufDesc(REG_HW *reg_hw, int dma_read_num, int buf_num, int channel_num, int priority, int raw_flag)
{
    DMA_READ_BUF_DESC desc;
    
    desc.u.dma_read_num = dma_read_num;
    desc.u.buf_num = buf_num;
    desc.u.channel_num = channel_num;
    desc.u.raw_flag = raw_flag;
    /*printf("desc[dma_read_num=%d buf_num=%d channel_num=%d priority=%d raw_flag=%d]\n",
        desc.u.dma_read_num, desc.u.buf_num, desc.u.channel_num, desc.u.priority, desc.u.raw_flag);*/
    switch (priority)
    {
        case PRIORITY_LEVEL_0:
        {
            WriteRegisterUlong(&reg_hw->DMA_READ_BUF_DESC_0, desc.value);
            break;
        }
        case PRIORITY_LEVEL_1:
        {
            WriteRegisterUlong(&reg_hw->DMA_READ_BUF_DESC_1, desc.value);
            break;
        }
        case PRIORITY_LEVEL_2:
        {
            WriteRegisterUlong(&reg_hw->DMA_READ_BUF_DESC_2, desc.value);
            break;
        }
        case PRIORITY_LEVEL_3:
        {
            WriteRegisterUlong(&reg_hw->DMA_READ_BUF_DESC_3, desc.value);
            break;
        }
        default:
        {
            WriteRegisterUlong(&reg_hw->DMA_READ_BUF_DESC_3, desc.value);
            printf("invalid priorty=%d\n", priority);
            break;
        }
    }
}

/* 向FPGA写入CREDIT */
void hwPushCredit(REG_HW *reg_hw, int priority, int buf_num_of_1st, int buf_num_of_2nd, int buf_num_of_3rd, int valid_buf_num)
{
    CREDIT credit;
    
    credit.u.buf_num_of_1st = buf_num_of_1st;
    credit.u.buf_num_of_2nd = buf_num_of_2nd;
    credit.u.buf_num_of_3rd = buf_num_of_3rd;
    credit.u.valid_buf_num = valid_buf_num;
    switch (priority)
    {
        case PRIORITY_LEVEL_0 :
        {
            WriteRegisterUlong(&reg_hw->P0_CREDIT, credit.value);
            break;
        }
        case PRIORITY_LEVEL_1 :
        {
            WriteRegisterUlong(&reg_hw->P1_CREDIT, credit.value);
            break;
        }
        case PRIORITY_LEVEL_2 :
        {
            WriteRegisterUlong(&reg_hw->P2_CREDIT, credit.value);
            break;
        }
        case PRIORITY_LEVEL_3 :
        {
            WriteRegisterUlong(&reg_hw->P3_CREDIT, credit.value);
            break;
        }
        default:
        {
            printf("invalid priorty=%d\n", priority);
            break;
        }
    } 
}

/* 初始化OX_ID */
void hwInitOxid(REG_HW *reg_hw)
{
    int index;
    ULONG value;
    INDIRECT_CONTROL i_control;
    
    i_control.value = 0;
    i_control.u.direct = IDC_DIRECT_RX;
    value = 0;
    for (index = 0; index < 256; ++index)
    {
        i_control.u.address = IDA_OX_ID_INIT_BASE + index;
        WriteIndirectRegisterUlong(reg_hw, i_control.value, value);
    }
}

/* 初始化ELS通道 */
void hwInitElsChannel(REG_HW *reg_hw)
{
    int index;
    ULONG value;    
    INDIRECT_CONTROL i_control;

    i_control.value = 0;
    i_control.u.direct = IDC_DIRECT_RX;
    value = 1;
    for (index = 0; index < 32; ++index)
    {
        i_control.u.address = IDA_ELS_CHANNEL_BASE + index;
        WriteIndirectRegisterUlong(reg_hw, i_control.value, value);
    }
    i_control.u.address = IDA_SWITCH_ELS_CHANNEL_BASE;
    WriteIndirectRegisterUlong(reg_hw, i_control.value, value);
}

/* 初始化switch_id */
void hwInitSwitchId(REG_HW *reg_hw, ULONG switch_sid)
{
    WriteRegisterUlong(&reg_hw->SWITCH_SID, switch_sid);
}

/* 设置通道的优先级 */
void SetChannelPriority(REG_HW *reg_hw, int index, int priority)
{
    ULONG value;
    INDIRECT_CONTROL i_control;
    
    /*printf("[SetChannelPriority] enter\n");*/

    /* set priority */
    i_control.value = 0;
    i_control.u.direct = IDC_DIRECT_RX;
    i_control.u.address = IDA_RX_PRIORITY_BASE + index;
    /* set priority bit */
    value = priority;
    /*printf("[SetChannelPriority] i_control[direct=%d address=0x%08x] value=%d\n",
        i_control.u.direct, i_control.u.address, value);*/
    WriteIndirectRegisterUlong(reg_hw, i_control.value, value);    
    /*printf("[SetChannelPriority] leave\n");*/
}

/* 设置通道的优先级 */
void SetRawPriority(REG_HW *reg_hw, int priority)
{
    ULONG value;
    INDIRECT_CONTROL i_control;
    
    /*printf("[SetRawPriority] enter\n");*/

    /* set priority */
    i_control.value = 0;
    i_control.u.direct = IDC_DIRECT_RX;
    i_control.u.address = IDA_RX_RAW_ACTIVE_BASE;

    /* set priority bit1~bit2 */
    value = ReadIndirectRegisterUlong(reg_hw, i_control.value);
    
    value &= ~( 0x3 << 1 );                /*Clear bit1 ~ bit2*/
    value |=  ((priority & 0x3) << 1);    /*set bit1 ~ bit2*/

    /*printf("[SetChannelPriority] i_control[direct=%d address=0x%08x] value=%d\n",
        i_control.u.direct, i_control.u.address); */
    WriteIndirectRegisterUlong(reg_hw, i_control.value, value);    
    /*printf("[SetRawPriority] leave\n");*/
}

/*设置hash值*/
UINT32 SetHashValue(REG_HW *reg_hw, ULONG asmid, ULONG fcid, ULONG index)
{
    int idx;
    ULONG value;
    UCHAR hash_value;
    INDIRECT_CONTROL i_control;

    /*在NC BNC切换方案中，计算HASH值时忽略FCID*/
    fcid = 0;

    i_control.value = 0;
    i_control.u.direct = IDC_DIRECT_RX;

    /* set hash */
    hash_value = Hash(asmid, fcid);
    /*printf("[SetHashValue] asmid=0x%08x,fcid=0x%08x,hash_value=0x%08x,index=%d\n", asmid, fcid, hash_value, index);*/
    for (idx = 0; idx < 4; ++idx)
    {
        i_control.u.address = IDA_RX_HASH_TAB_BASE + (idx*256) + (hash_value*2);
        value = ReadIndirectRegisterUlong(reg_hw, i_control.value);
        /*printf("[SetHashValue] idx=%d,value=0x%08x\n", idx, value);*/
        if (value == HASH_BIT_FREE)
        {
            /* hash bit is free */
            /*printf("[SetHashValue]prepare write asmid i_control.value=0x%08x\n", i_control.value);*/
            WriteIndirectRegisterUlong(reg_hw, i_control.value, asmid);
            i_control.u.address++;
            /*printf("[SetHashValue] prepare write fcid i_control.value=0x%08x\n", i_control.value);*/
            WriteIndirectRegisterUlong(reg_hw, i_control.value, fcid);
            
            /* set index of channel to channel map table */
            i_control.u.address = IDA_RX_CHANNEL_MAP_TABLE_BASE + (idx*128) + hash_value;
            /*printf("[SetHashValue] prepare write index i_control.value=0x%08x\n", i_control.value);*/

            WriteIndirectRegisterUlong(reg_hw, i_control.value, index);
            /*dbgCheckHashCode(reg_hw, hash_value, asmid, fcid, index);*/
            break;
        }
    }
    if (idx >= 4)
    {
           /*printf("[SetHashValue] hash conflict. asmid=0x%08x,fcid=0x%08x,index=0x%08x,hash value=0x%08x\n", asmid, fcid, index, hash_value);*/
        return FC_HASH_CONFLICT;
    }
    
    return FC_SUCCESS;
}

/* 计算hash值 */
UCHAR Hash(ULONG low, ULONG high)
{
    UCHAR ret;
    HASH_VALUE v, c;
    HASH_64_BIT d;
    
    /*printf("[Hash]enter\n");*/
    v.value = 0;
    c.value = (UCHAR)HASH_SEED;
    d.value = 0;
    d.part.high = high;
    d.part.low = low;
    v.u.b0 = (UCHAR)(d.u.b61 ^ d.u.b60 ^ d.u.b56 ^ d.u.b54 ^ d.u.b53 ^ d.u.b52 ^ d.u.b51 ^ d.u.b49 ^ d.u.b48 ^ d.u.b47 ^ d.u.b44 ^ d.u.b40 ^ d.u.b35 ^ d.u.b34 ^ d.u.b32 ^ d.u.b30 ^ d.u.b29 ^ d.u.b27 ^ d.u.b23 ^ d.u.b22 ^ d.u.b21 ^ d.u.b20 ^ d.u.b14 ^ d.u.b11 ^ d.u.b10 ^ d.u.b8 ^ d.u.b7 ^ d.u.b2 ^ d.u.b0 ^ c.u.b3 ^ c.u.b4);
    v.u.b1 = (UCHAR)(d.u.b62 ^ d.u.b60 ^ d.u.b57 ^ d.u.b56 ^ d.u.b55 ^ d.u.b51 ^ d.u.b50 ^ d.u.b47 ^ d.u.b45 ^ d.u.b44 ^ d.u.b41 ^ d.u.b40 ^ d.u.b36 ^ d.u.b34 ^ d.u.b33 ^ d.u.b32 ^ d.u.b31 ^ d.u.b29 ^ d.u.b28 ^ d.u.b27 ^ d.u.b24 ^ d.u.b20 ^ d.u.b15 ^ d.u.b14 ^ d.u.b12 ^ d.u.b10 ^ d.u.b9 ^ d.u.b7 ^ d.u.b3 ^ d.u.b2 ^ d.u.b1 ^ d.u.b0 ^ c.u.b0 ^ c.u.b3 ^ c.u.b5);
    v.u.b2 = (UCHAR)(d.u.b63 ^ d.u.b61 ^ d.u.b58 ^ d.u.b57 ^ d.u.b56 ^ d.u.b52 ^ d.u.b51 ^ d.u.b48 ^ d.u.b46 ^ d.u.b45 ^ d.u.b42 ^ d.u.b41 ^ d.u.b37 ^ d.u.b35 ^ d.u.b34 ^ d.u.b33 ^ d.u.b32 ^ d.u.b30 ^ d.u.b29 ^ d.u.b28 ^ d.u.b25 ^ d.u.b21 ^ d.u.b16 ^ d.u.b15 ^ d.u.b13 ^ d.u.b11 ^ d.u.b10 ^ d.u.b8 ^ d.u.b4 ^ d.u.b3 ^ d.u.b2 ^ d.u.b1 ^ c.u.b0 ^ c.u.b1 ^ c.u.b4 ^ c.u.b6);
    v.u.b3 = (UCHAR)(d.u.b62 ^ d.u.b61 ^ d.u.b60 ^ d.u.b59 ^ d.u.b58 ^ d.u.b57 ^ d.u.b56 ^ d.u.b54 ^ d.u.b51 ^ d.u.b48 ^ d.u.b46 ^ d.u.b44 ^ d.u.b43 ^ d.u.b42 ^ d.u.b40 ^ d.u.b38 ^ d.u.b36 ^ d.u.b33 ^ d.u.b32 ^ d.u.b31 ^ d.u.b27 ^ d.u.b26 ^ d.u.b23 ^ d.u.b21 ^ d.u.b20 ^ d.u.b17 ^ d.u.b16 ^ d.u.b12 ^ d.u.b10 ^ d.u.b9 ^ d.u.b8 ^ d.u.b7 ^ d.u.b5 ^ d.u.b4 ^ d.u.b3 ^ d.u.b0 ^ c.u.b0 ^ c.u.b1 ^ c.u.b2 ^ c.u.b3 ^ c.u.b4 ^ c.u.b5);
    v.u.b4 = (UCHAR)(d.u.b63 ^ d.u.b62 ^ d.u.b61 ^ d.u.b60 ^ d.u.b59 ^ d.u.b58 ^ d.u.b57 ^ d.u.b55 ^ d.u.b52 ^ d.u.b49 ^ d.u.b47 ^ d.u.b45 ^ d.u.b44 ^ d.u.b43 ^ d.u.b41 ^ d.u.b39 ^ d.u.b37 ^ d.u.b34 ^ d.u.b33 ^ d.u.b32 ^ d.u.b28 ^ d.u.b27 ^ d.u.b24 ^ d.u.b22 ^ d.u.b21 ^ d.u.b18 ^ d.u.b17 ^ d.u.b13 ^ d.u.b11 ^ d.u.b10 ^ d.u.b9 ^ d.u.b8 ^ d.u.b6 ^ d.u.b5 ^ d.u.b4 ^ d.u.b1 ^ c.u.b0 ^ c.u.b1 ^ c.u.b2 ^ c.u.b3 ^ c.u.b4 ^ c.u.b5 ^ c.u.b6);
    v.u.b5 = (UCHAR)(d.u.b63 ^ d.u.b62 ^ d.u.b59 ^ d.u.b58 ^ d.u.b54 ^ d.u.b52 ^ d.u.b51 ^ d.u.b50 ^ d.u.b49 ^ d.u.b47 ^ d.u.b46 ^ d.u.b45 ^ d.u.b42 ^ d.u.b38 ^ d.u.b33 ^ d.u.b32 ^ d.u.b30 ^ d.u.b28 ^ d.u.b27 ^ d.u.b25 ^ d.u.b21 ^ d.u.b20 ^ d.u.b19 ^ d.u.b18 ^ d.u.b12 ^ d.u.b9 ^ d.u.b8 ^ d.u.b6 ^ d.u.b5 ^ d.u.b0 ^ c.u.b1 ^ c.u.b2 ^ c.u.b5 ^ c.u.b6);
    v.u.b6 = (UCHAR)(d.u.b63 ^ d.u.b60 ^ d.u.b59 ^ d.u.b55 ^ d.u.b53 ^ d.u.b52 ^ d.u.b51 ^ d.u.b50 ^ d.u.b48 ^ d.u.b47 ^ d.u.b46 ^ d.u.b43 ^ d.u.b39 ^ d.u.b34 ^ d.u.b33 ^ d.u.b31 ^ d.u.b29 ^ d.u.b28 ^ d.u.b26 ^ d.u.b22 ^ d.u.b21 ^ d.u.b20 ^ d.u.b19 ^ d.u.b13 ^ d.u.b10 ^ d.u.b9 ^ d.u.b7 ^ d.u.b6 ^ d.u.b1 ^ c.u.b2 ^ c.u.b3 ^ c.u.b6);
    ret = v.value;
    
    /*
    printf("[Hash]low=%d high=%d hash value=%d\n", low, high, v.value);
    printf("[Hash]leave\n");
    */
    return ret;
}

/* 清空hash表 */
void EmptyHashTable(REG_HW *reg_hw)
{
    int idx, offset;
    INDIRECT_CONTROL i_control;
    
    if (g_hwDebugFlag & HW_DBG_CONFIG)  
    {
        printf("[EmptyHashTable]enter\n");
    }
    /* debug
    {
        ULONG tmp;
        INDIRECT_CONTROL ic;
        
        ic.value = 0;
        ic.u.address = 0x1000;
        ic.u.direct = IDC_DIRECT_RX;
        WriteIndirectRegisterUlong(reg_hw, ic.value, HASH_BIT_FREE);
        
        ic.value = 0;
        ic.u.address = 0x1001;
        ic.u.direct = IDC_DIRECT_RX;
        WriteIndirectRegisterUlong(reg_hw, ic.value, HASH_BIT_FREE);
        
        ic.value = 0;
        ic.u.address = 0x1000;
        ic.u.direct = IDC_DIRECT_RX;
        tmp = ReadIndirectRegisterUlong(reg_hw, ic.value);
        printf("0x1000 tmp=0x%08x\n", tmp);
        
        ic.value = 0;
        ic.u.address = 0x1001;
        ic.u.direct = IDC_DIRECT_RX;
        tmp = ReadIndirectRegisterUlong(reg_hw, ic.value);
        printf("0x1001 tmp=0x%08x\n", tmp);
        
        ic.value = 0;
        ic.u.address = 0;
        ic.u.direct = IDC_DIRECT_TX;
        WriteIndirectRegisterUlong(reg_hw, ic.value, 0xDEADBEEF);
        
        ic.value = 0;
        ic.u.address = 0;
        ic.u.direct = IDC_DIRECT_TX;
        tmp = ReadIndirectRegisterUlong(reg_hw, ic.value);
        printf("0x0 tmp=0x%08x\n", tmp);
    }*/
    
    i_control.value = 0;
    i_control.u.direct = IDC_DIRECT_RX;
    for (idx = 0; idx < 4; ++idx)
    {
        for (offset = 0; offset < 128; ++offset)
        {
            i_control.u.address = IDA_RX_HASH_TAB_BASE + (idx * 256) + (offset * 2);
            WriteIndirectRegisterUlong(reg_hw, i_control.value, HASH_BIT_FREE);
            i_control.u.address = IDA_RX_HASH_TAB_BASE + (idx * 256) + (offset * 2) + 1;
            WriteIndirectRegisterUlong(reg_hw, i_control.value, HASH_BIT_FREE);
        }
    }

       /* clear channel map table */
    i_control.value = 0;
    i_control.u.direct = IDC_DIRECT_RX;
    for (idx = 0; idx < 16; ++idx)
    {
           i_control.u.address = IDA_RX_CHANNEL_MAP_TABLE_BASE + idx;
           WriteIndirectRegisterUlong(reg_hw, i_control.value, 0);
    }
}

/* 初始化FC ASM的头 */
void InitFcAsmHeader(PFC_ASM fc_asm, int asmid, int sid, int did)
{
    /* 清零 */
    memset((char *)fc_asm, 0, sizeof(FC_ASM));
    
    /* sid & did */
    fc_asm->fc_header.DID_R_CTL.u.r_ctl = 0x04;
    fc_asm->fc_header.SID_CS_CTL_Priority.u.sid = sid;
    fc_asm->fc_header.DID_R_CTL.u.did = did;
    /* fctl */
    fc_asm->fc_header.F_CTL_TYPE.u.type = 0x49;
    fc_asm->fc_header.F_CTL_TYPE.u.f_ctl = (0x002A0000 >> 2); /* 0x2A00 */
    fc_asm->fc_header.F_CTL_TYPE.u.fill_byte = 0;
    /* seq_id_seq_cnt */
    /* oxid_rxid */
    fc_asm->fc_header.RX_ID_OX_ID.u.rx_id = 0xffff;
    fc_asm->fc_header.RX_ID_OX_ID.u.ox_id = 0;
    /* parameter */
    /* message id */
    fc_asm->asm_header.MESSAGE_ID = asmid;
    fc_asm->asm_header.RESERVE0 = 0;
    fc_asm->asm_header.RESERVE_SECURITY = 0;
}

#ifndef AE653_BUILD
/******************************************************************************
*  Write a long word (32 bits) to a memory location after the value
*  has been byte swapped (big to little endian or vice versa)      
******************************************************************************/
void hwSysPciOutLong(
    ULONG address, /* I/O address to write to */
    ULONG data     /* data to write */
)
{
/*大端处理*/
#ifdef _HBA_IO_REG_MODE_POWER_PC

       /*EIEIO;*/
    WRS_ASM ("eieio");
    
    *(ULONG *)address = LONGSWAP(data); 
#endif

/*小端处理*/
#ifdef _HBA_IO_REG_MODE_ARM

    *(ULONG *)address = data; 

#endif

#if 0
    #if (defined(_WRS_VXWORKS_MAJOR) && (_WRS_VXWORKS_MAJOR >= 6))    
        _WRS_ASM ("eieio");
    #else    
        __asm__ /* __volatile__ */  ("eieio");
    #endif
#endif
}

/*******************************************************************
 *  Read a long word (32 bits) from a memory location, and byte 
 *  swap the value before returning to the caller.     
 */

ULONG hwSysPciInLong(
    ULONG address /* I/O address to read from */
)
{
   ULONG retVal;

/*大端处理*/
#ifdef _HBA_IO_REG_MODE_POWER_PC
   /*EIEIO;*/
   _WRS_ASM ("eieio");
   
   retVal = LONGSWAP(*(ULONG *)address);
#endif

/*小端处理*/
#ifdef _HBA_IO_REG_MODE_ARM

   retVal = *(ULONG *)address;

#endif

   return (retVal);
}

#else

void hwSysPciOutLong
(
    ULONG address, /* I/O address to write to */
    ULONG data     /* data to write */
)
{
       sysPciOutLong(address, data);
}                                                

/*******************************************************************
 *  Read a long word (32 bits) from a memory location, and byte 
 *  swap the value before returning to the caller.     
 *******************************************************************/
ULONG hwSysPciInLong
(
    ULONG address /* I/O address to read from */
)
{
   return sysPciInLong(address);
}

#endif

/* 读寄存器 */
ULONG ReadRegisterUlong(ULONG * reg)
{
    ULONG value;

    value = hwSysPciInLong((ULONG)reg);
    return value;
}

/* 读间址寄存器 */
ULONG ReadIndirectRegisterUlong(REG_HW *reg_hw, ULONG ic_value)
{
    ULONG value;
    INDIRECT_CONTROL ic;
    
    ic.value = ic_value;
    ic.u.action = IDC_ACTION_READ;
    WriteRegisterUlong(&reg_hw->INDIRECT_CONTROL, ic.value);
    hw_delay(200);
    value = ReadRegisterUlong(&reg_hw->INDIRECT_DATA);
    return value;
}

/* 写寄存器 */
void WriteRegisterUlong(ULONG *reg, ULONG value)
{
    hwSysPciOutLong((ULONG)reg,value);
}

/* 写间址寄存器 */
void WriteIndirectRegisterUlong(REG_HW *reg_hw, ULONG ic_value, ULONG id_value)
{
    INDIRECT_CONTROL ic;
    INDIRECT_DATA id;
    
    ic.value = ic_value;
    id.value = id_value;
    ic.u.action = IDC_ACTION_WRITE;
    WriteRegisterUlong(&reg_hw->INDIRECT_DATA, id.value);
    hw_delay(200);
    WriteRegisterUlong(&reg_hw->INDIRECT_CONTROL, ic.value);
}

/*** debug ***/
/* 测试函数 检查hash值设置的是否正确 */
void dbgCheckHashCode(REG_HW *reg_hw, UCHAR hash_value, ULONG asmid, ULONG fcid, ULONG index)
{
    ULONG t_asmid, t_fcid, t_index;
    INDIRECT_CONTROL i_control;
    
    i_control.value = 0;
    i_control.u.direct = IDC_DIRECT_RX;
    
    i_control.u.address = IDA_RX_HASH_TAB_BASE + (index*256) + (hash_value*2);
    t_asmid = ReadIndirectRegisterUlong(reg_hw, i_control.value);
    
    i_control.u.address++;
    t_fcid = ReadIndirectRegisterUlong(reg_hw, i_control.value);
    
    i_control.u.address = IDA_RX_CHANNEL_MAP_TABLE_BASE + (index*128) + hash_value;
    t_index = ReadIndirectRegisterUlong(reg_hw, i_control.value);
    
    if ((asmid != t_asmid) || (fcid != t_fcid) || (index != t_index)) 
    {
        printf("[dbgCheckHashCode]asmid[0x%08x 0x%08x] fcid[0x%08x 0x%08x] index[0x%08x 0x%08x] hash_value=0x%08x",
                (int)asmid, (int)t_asmid, (int)fcid, (int)t_fcid, (int)index, (int)t_index, hash_value);
    }
}

ULONG dbgReadIndirectRegisterUlong(REG_HW *reg_hw, ULONG direct, ULONG address)
{
    ULONG value;
    INDIRECT_CONTROL i_control;
    
    i_control.value = 0;
    i_control.u.direct = direct;
    i_control.u.address = address;
    value = ReadIndirectRegisterUlong(reg_hw, i_control.value);
    return value;
}

void dbgPrintReg(REG_HW *reg_hw)
{
    printf("FPGA_VER(addr=0x%08x value=0x%08x)\n",         (int)&reg_hw->FPGA_VER, (int)ReadRegisterUlong(&reg_hw->FPGA_VER));
    printf("PORT_CONFIG(addr=0x%08x value=0x%08x)\n",     (int)&reg_hw->PORT_CONFIG, (int)ReadRegisterUlong(&reg_hw->PORT_CONFIG));
    printf("P0_CREDIT(addr=0x%08x value=0x%08x)\n",     (int)&reg_hw->P0_CREDIT, (int)ReadRegisterUlong(&reg_hw->P0_CREDIT));
    printf("PORT_RX_ENAB(addr=0x%08x value=0x%08x)\n",     (int)&reg_hw->PORT_RX_ENAB, (int)ReadRegisterUlong(&reg_hw->PORT_RX_ENAB));
    printf("DMA_READ_BUF_DESC_0(addr=0x%08x value=0x%08x)\n", (int)&reg_hw->DMA_READ_BUF_DESC_0, (int)ReadRegisterUlong(&reg_hw->DMA_READ_BUF_DESC_0));
    printf("RTC_CONTROL(addr=0x%08x value=0x%08x)\n",     (int)&reg_hw->RTC_CONTROL,     (int)ReadRegisterUlong(&reg_hw->RTC_CONTROL));
    printf("PORT_STATUS(addr=0x%08x value=0x%08x)\n",     (int)&reg_hw->PORT_STATUS,     (int)ReadRegisterUlong(&reg_hw->PORT_STATUS));
    printf("INDIRECT_CONTROL(addr=0x%08x value=0x%08x)\n", (int)&reg_hw->INDIRECT_CONTROL, (int)ReadRegisterUlong(&reg_hw->INDIRECT_CONTROL));
    printf("INDIRECT_DATA(addr=0x%08x value=0x%08x)\n", (int)&reg_hw->INDIRECT_DATA, (int)ReadRegisterUlong(&reg_hw->INDIRECT_DATA));
    printf("P1_CREDIT(addr=0x%08x value=0x%08x)\n",     (int)&reg_hw->P1_CREDIT, (int)ReadRegisterUlong(&reg_hw->P1_CREDIT));
    printf("RTC_WRITE_HIGH(addr=0x%08x value=0x%08x)\n", (int)&reg_hw->RTC_WRITE_HIGH, (int)ReadRegisterUlong(&reg_hw->RTC_WRITE_HIGH));
    printf("RTC_WRITE_LOW(addr=0x%08x value=0x%08x)\n", (int)&reg_hw->RTC_WRITE_LOW, (int)ReadRegisterUlong(&reg_hw->RTC_WRITE_LOW));
    printf("RTC_READ_HIGH(addr=0x%08x value=0x%08x)\n", (int)&reg_hw->RTC_READ_HIGH, (int)ReadRegisterUlong(&reg_hw->RTC_READ_HIGH));
    printf("RTC_READ_LOW(addr=0x%08x value=0x%08x)\n",     (int)&reg_hw->RTC_READ_LOW, (int)ReadRegisterUlong(&reg_hw->RTC_READ_LOW));
    printf("DMA_READ_BUF_DESC_1(addr=0x%08x value=0x%08x)\n", (int)&reg_hw->DMA_READ_BUF_DESC_1, (int)ReadRegisterUlong(&reg_hw->DMA_READ_BUF_DESC_1));
    printf("DMA_READ_BUF_DESC_2(addr=0x%08x value=0x%08x)\n", (int)&reg_hw->DMA_READ_BUF_DESC_2, (int)ReadRegisterUlong(&reg_hw->DMA_READ_BUF_DESC_2));
    printf("DMA_READ_BUF_DESC_3(addr=0x%08x value=0x%08x)\n", (int)&reg_hw->DMA_READ_BUF_DESC_3, (int)ReadRegisterUlong(&reg_hw->DMA_READ_BUF_DESC_3));
    printf("STATISTICS_CONTROL(addr=0x%08x value=0x%08x)\n", (int)&reg_hw->STATISTICS_CONTROL, (int)ReadRegisterUlong(&reg_hw->STATISTICS_CONTROL));
    printf("STATISTICS_DATA(addr=0x%08x value=0x%08x)\n", (int)&reg_hw->STATISTICS_DATA, (int)ReadRegisterUlong(&reg_hw->STATISTICS_DATA));
    printf("P2_CREDIT(addr=0x%08x value=0x%08x)\n",     (int)&reg_hw->P2_CREDIT, (int)ReadRegisterUlong(&reg_hw->P2_CREDIT));
    printf("P3_CREDIT(addr=0x%08x value=0x%08x)\n",     (int)&reg_hw->P3_CREDIT, (int)ReadRegisterUlong(&reg_hw->P3_CREDIT));
    printf("FLASH_ADDR_CONTROL(addr=0x%08x value=0x%08x)\n", (int)&reg_hw->FLASH_ADDR_CONTROL, (int)ReadRegisterUlong(&reg_hw->FLASH_ADDR_CONTROL));
    printf("FLASH_DATA(addr=0x%08x value=0x%08x)\n",     (int)&reg_hw->INTERRUPT_CTRL, (int)ReadRegisterUlong(&reg_hw->INTERRUPT_CTRL));
    printf("SWITCH_SID(addr=0x%08x value=0x%08x)\n",     (int)&reg_hw->SWITCH_SID, (int)ReadRegisterUlong(&reg_hw->SWITCH_SID));
}

