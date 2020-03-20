/*++
文件名
    hw.c

描述
    
--*/
/* 接口函数 */
#include <vxworks.h>
#include "hw.h"

/* 取得端口的状态 */
int hwGetPortStatus(PREG_HW reg_hw, int *portStatus, int portCount)
{
    PORT_STATUS status;

    status.value = ReadRegisterUlong(&reg_hw->PORT_STATUS);
    portStatus[0] = status.u.p0_status;
    portStatus[1] = status.u.p1_status;

    return OK;
}

/* 取得QDR缓冲区的状态 */
int hwGetQdrBufferEmpty(PREG_HW reg_hw)
{
    PORT_STATUS status;

    status.value = ReadRegisterUlong(&reg_hw->PORT_STATUS);
    return status.u.qdr_buf_empty;
}

/* 取得reset的结果 */
int hwGetSoftResetDone(PREG_HW reg_hw)
{
    PORT_STATUS status;

    status.value = ReadRegisterUlong(&reg_hw->PORT_STATUS);
    return status.u.reset_done;
}

/* 设置cpu soft reset */
void hwSetSoftReset(PREG_HW reg_hw)
{
    PORT_RX_ENAB p;

    p.value = ReadRegisterUlong(&reg_hw->PORT_CONFIG);
    p.u.reset = 1;
    WriteRegisterUlong(&reg_hw->PORT_CONFIG, p.value);
}


void hwResetFpga(
    PREG_HW reg_hw,
    int forceOffLine
)
{
    PORT_RX_ENAB enab;
	PORT_STATUS status;
	
    enab.value = ReadRegisterUlong(&reg_hw->PORT_RX_ENAB);
	enab.u.reset = 1;
	enab.u.p0_mac_switch = forceOffLine;
	WriteRegisterUlong(&reg_hw->PORT_RX_ENAB, enab.value);

	/* wait until reset is completed */
	while(1)
	{
		status.value = ReadRegisterUlong(&reg_hw->PORT_STATUS);
		if (status.u.reset_done == 1)
		{
			break;
		}
	}

	if (forceOffLine == 1)
	{
	    /* mac on*/
        enab.value = ReadRegisterUlong(&reg_hw->PORT_RX_ENAB);		
    	enab.u.p0_mac_switch = 0;
	    WriteRegisterUlong(&reg_hw->PORT_RX_ENAB, enab.value);	
	}
}


/* 获取FPGA版本信息 */
int hwGetFpgaVersion(PREG_HW reg_hw)
{
    FPGA_VER version;

    version.value = ReadRegisterUlong(&reg_hw->FPGA_VER);
    version.value &= 0xFF; /* only 8bit */
    return version.value;
}

/* 端口FCID */
void hwSetPortFcid(PREG_HW reg_hw, int fcid)
{
    PORT_CONFIG p;

    p.value = ReadRegisterUlong(&reg_hw->PORT_CONFIG);
    p.u.sid = fcid;
    WriteRegisterUlong(&reg_hw->PORT_CONFIG, p.value);
}

int hwGetPortFcid(PREG_HW reg_hw)
{
    PORT_CONFIG p;

    p.value = ReadRegisterUlong(&reg_hw->PORT_CONFIG);
    return p.u.sid;
}

/* 信用 */
void hwSetPortCreditNum(PREG_HW reg_hw, int credit)
{
    PORT_CONFIG p;

    p.value = ReadRegisterUlong(&reg_hw->PORT_CONFIG);
    p.u.credit = credit - 1; /* 0 - base */
    WriteRegisterUlong(&reg_hw->PORT_CONFIG, p.value);
}

int hwGetPortCreditNum(PREG_HW reg_hw)
{
    PORT_CONFIG p;

    p.value = ReadRegisterUlong(&reg_hw->PORT_CONFIG);
    return p.u.credit + 1; /* 0 - base */
}

/* 速率 0 自适应 1-1Gbps 2-2Gbps */
void hwSetPortSpeed(PREG_HW reg_hw, int speed)
{
    PORT_CONFIG p;

    p.value = ReadRegisterUlong(&reg_hw->PORT_CONFIG);
    p.u.speed = speed;
    WriteRegisterUlong(&reg_hw->PORT_CONFIG, p.value);
}

int hwGetPortSpeed(PREG_HW reg_hw)
{
    PORT_CONFIG p;

    p.value = ReadRegisterUlong(&reg_hw->PORT_CONFIG);
    return p.u.speed;
}

/* 接收方向DID过滤使能 */
void hwSetPortDidFilterEnab(PREG_HW reg_hw, int did_filter_enab)
{
    PORT_CONFIG p;

    p.value = ReadRegisterUlong(&reg_hw->PORT_CONFIG);
    p.u.did_filter_enab = did_filter_enab;
    WriteRegisterUlong(&reg_hw->PORT_CONFIG, p.value);    
}

int hwGetPortDidFilterEnab(PREG_HW reg_hw)
{
    PORT_CONFIG p;

    p.value = ReadRegisterUlong(&reg_hw->PORT_CONFIG);
    return p.u.did_filter_enab;
}

/* e_d_tov时间，单位是毫秒 */
void hwSetPortEdtovTime(PREG_HW reg_hw, int e_d_tov)
{
    PORT_RX_ENAB p;

    p.value = ReadRegisterUlong(&reg_hw->PORT_RX_ENAB);
    p.u.e_d_tov = e_d_tov;
    WriteRegisterUlong(&reg_hw->PORT_RX_ENAB, p.value);    
}

int hwGetPortEdtovTime(PREG_HW reg_hw)
{
    PORT_RX_ENAB p;

    p.value = ReadRegisterUlong(&reg_hw->PORT_RX_ENAB);
    return p.u.e_d_tov;
}

/* 冗余使能 0-禁止 1-使能 */
void hwSetPortRedundantEnab(PREG_HW reg_hw, int redundancy_enab)
{
    PORT_RX_ENAB p;

    p.value = ReadRegisterUlong(&reg_hw->PORT_RX_ENAB);
    p.u.redundancy_enab = redundancy_enab;
    WriteRegisterUlong(&reg_hw->PORT_RX_ENAB, p.value);
}

int hwGetPortRedundantEnab(PREG_HW reg_hw)
{
    PORT_RX_ENAB p;

    p.value = ReadRegisterUlong(&reg_hw->PORT_RX_ENAB);
    return p.u.redundancy_enab;
}


/* 使能/禁止端口接收 0-禁止 1-使能 */
void hwSetPortRxEnab(PREG_HW reg_hw, int rx_enab)
{
    PORT_RX_ENAB p;

    p.value = ReadRegisterUlong(&reg_hw->PORT_RX_ENAB);
	p.u.reset = 0;
	p.u.p0_mac_switch = 0;
    p.u.p0_rx_enab = rx_enab;
    WriteRegisterUlong(&reg_hw->PORT_RX_ENAB, p.value);
}

int hwGetPortRxEnab(PREG_HW reg_hw)
{
    PORT_RX_ENAB p;

    p.value = ReadRegisterUlong(&reg_hw->PORT_RX_ENAB);
    return p.u.p0_rx_enab;
}

/* 超时覆盖的时间，单位是毫秒 */
void hwSetPortTimeOut(PREG_HW reg_hw, int time)
{
    TIME_OUT t;

    t.value = 0;
    t.u.time = time;
    WriteRegisterUlong(&reg_hw->TIME_OUT, t.value);
}

int hwGetPortTimeOut(PREG_HW reg_hw)
{
    TIME_OUT t;

    t.value = ReadRegisterUlong(&reg_hw->TIME_OUT);
    return t.u.time;
}

int hwRtcControl(
    PREG_HW reg_hw,
	int global_sync_enab,
	int event_period,
	int sync_enab,
	int rtc_base
)
{
    RTC_CONTROL rtc_control;
	
	rtc_control.value = ReadRegisterUlong(&reg_hw->RTC_CONTROL);
	rtc_control.u.global_sync_enab = global_sync_enab;
	rtc_control.u.event_period = event_period;
    rtc_control.u.p0_sync_enab = sync_enab;
    rtc_control.u.p1_sync_enab = sync_enab;
	rtc_control.u.rtc_base = rtc_base;
	rtc_control.u.reserve |= 1;
    WriteRegisterUlong(&reg_hw->RTC_CONTROL, rtc_control.value);
    
    return OK;
}



/* 设置快照命令位 */
void hwReadRtcPrepare(PREG_HW reg_hw)
{
    RTC_DATE_READ r;
    
    r.value = 0;
    r.u.snap_shot_cmd = 1;
    WriteRegisterUlong(&reg_hw->RTC_DATE_READ, r.value);
}

/* 清除快照命令位 */
void hwReadRtcFinish(PREG_HW reg_hw)
{
    RTC_DATE_READ r;
    
    r.value = 0;
    r.u.snap_shot_cmd = 0;
    WriteRegisterUlong(&reg_hw->RTC_DATE_READ, r.value);
}

/* 读取RTC */
UINT64 hwGetRtc(PREG_HW reg_hw)
{
    ULONG  high, low;
    UINT64 time;
    
    low = ReadRegisterUlong(&reg_hw->RTC_READ_LOW);
    high = ReadRegisterUlong(&reg_hw->RTC_READ_HIGH);
    time = (((UINT64)high) << 32) | (UINT64)low;
    
    return time;
}

/*写入RTC */
void hwSetRtc(PREG_HW reg_hw, UINT32 high, UINT32 low)
{
    WriteRegisterUlong(&reg_hw->RTC_WRITE_HIGH, high);
    WriteRegisterUlong(&reg_hw->RTC_WRITE_LOW,  low);
}

/* 读取日期 */
UINT32 hwGetDate(PREG_HW reg_hw)
{
    RTC_DATE_READ r;
    
    r.value = ReadRegisterUlong(&reg_hw->RTC_DATE_READ);
    return (UINT32)r.u.real_time_day;
}

/* 写入日期 */
void hwSetDate(PREG_HW reg_hw, UINT32 date )
{
    RTC_DATE_WRITE w;

    w.value = date;
    WriteRegisterUlong(&reg_hw->RTC_DATE_WRITE, w.value);
}

/* 使能/禁止接收中断 */
void hwSetIntrptEnable(PREG_HW reg_hw, int enab)
{
	INTERRUPT  intrp;

	intrp.value = 0;
	if (enab)
	{
		intrp.u.intr_enable_global = 1;
		intrp.u.intr_enable_Rx_IU = 1;
	}
	else
	{
		intrp.u.intr_enable_global = 0;
		intrp.u.intr_enable_Rx_IU  = 0;
	}
	intrp.u.intr_enable_link_change = 1;
	/* clear all pending interrupt*/
	intrp.u.pending_link_change = 1;
	intrp.u.pending_send_bd_empty = 1;
	intrp.u.pending_Tx_IU = 1;
	intrp.u.pending_Rx_credit_out = 1;
	intrp.u.pending_Rx_IU = 1;

	WriteRegisterUlong(&reg_hw->INTERRUPT_CTRL, intrp.value);
}

/* 读取电压 */
int hwGetVoltage(PREG_HW reg_hw)
{
    int result;
    PORT_STATUS status;

    status.value = ReadRegisterUlong(&reg_hw->PORT_STATUS);
    result = status.u.voltage * 3000 / 4096;
    return result;    
}

/* 读取温度 */
int hwGetTemperature(PREG_HW reg_hw)
{
    int result;    
    PORT_STATUS status;

    status.value = ReadRegisterUlong(&reg_hw->PORT_STATUS);
    result = status.u.temperature * 503975 / 4096 - 273150; /* X1000 */
    return result;
}

/* 注册Rx的缓冲区 */
void hwRegisterRxDmaBuf(PREG_HW reg_hw, int index, int value)
{
    INDIRECT_CONTROL i_control;
    
    i_control.value = 0;
    i_control.u.direct = IDC_DIRECT_RX;
    i_control.u.address = IDA_RX_LOGIC_BUF_BASE + index;
    WriteIndirectRegisterUlong(reg_hw, i_control.value, value);
}

/* 配置Qdr buffer size */
void  hwQdrConfigBufferSize(PREG_HW reg_hw, int size)
{
    DIV_QDR_BUF_SIZE div_qdr_buf_size;

    div_qdr_buf_size.value = size;
    WriteRegisterUlong(&reg_hw->DIV_QDR_BUF_SIZE, div_qdr_buf_size.value);
}
 
/* 配置每个Qdr buffer的开始地址  */
void hwQdrConfigBufferStartAddress(PREG_HW reg_hw, int start_address)
{
    DIV_QDR_BUF_START_ADDR div_qdr_buf_start_addr;

    div_qdr_buf_start_addr.value = start_address;
    WriteRegisterUlong(&reg_hw->DIV_QDR_BUF_START_ADDR, div_qdr_buf_start_addr.value);
}

/* 向FPGA写入多个CREDIT */
void hwPushCreditsToFpga(PREG_HW reg_hw, INT32 *credits, INT32 valid_buf_num)
{
    CREDIT credit;
    
    credit.u.buf_num_of_1st = credits[0];
    credit.u.buf_num_of_2nd = credits[1];
    credit.u.buf_num_of_3rd = credits[2];
    credit.u.valid_buf_num = valid_buf_num;
    WriteRegisterUlong(&reg_hw->CREDIT, credit.value);
}

/* 获取链路变化中断位 */
int hwGetLinkChangePending(PREG_HW reg_hw)
{
	INTERRUPT  intrp;

	intrp.value = ReadRegisterUlong(&reg_hw->INTERRUPT_CTRL);
	return (int)(intrp.u.pending_link_change);
}

/* 读寄存器 */
ULONG ReadRegisterUlong(ULONG* reg)
{
    ULONG value;
#if 0	
    value = hwSysPciInLong((ULONG)reg);
#else
	value = sysPciInLong((ULONG)reg);
#endif
    return value;
}

/* 写寄存器 */
void WriteRegisterUlong(ULONG* reg, ULONG value)
{
#if 0
    hwSysPciOutLong((ULONG)reg, value);
#else
    sysPciOutLong((ULONG)reg, value);
#endif	
}

/* 读间址寄存器 */
ULONG ReadIndirectRegisterUlong(PREG_HW reg_hw, ULONG ic_value)
{
    ULONG value;
    INDIRECT_CONTROL ic;
    
    ic.value = ic_value;
    ic.u.action = IDC_ACTION_READ;
    WriteRegisterUlong(&reg_hw->INDIRECT_CONTROL, ic.value);
    value = ReadRegisterUlong(&reg_hw->INDIRECT_DATA);
    return value;
}

/* 写间址寄存器 */
void WriteIndirectRegisterUlong(PREG_HW reg_hw, ULONG ic_value, ULONG id_value)
{
    INDIRECT_CONTROL ic;
    INDIRECT_DATA id;
    
    ic.value = ic_value;
    id.value = id_value;
    ic.u.action = IDC_ACTION_WRITE;
    WriteRegisterUlong(&reg_hw->INDIRECT_DATA, id.value);
    WriteRegisterUlong(&reg_hw->INDIRECT_CONTROL, ic.value);
}

ULONG dbgReadIndirectRegisterUlong(PREG_HW reg_hw, ULONG direct, ULONG address)
{
	ULONG value;
	INDIRECT_CONTROL i_control;
	
	i_control.value = 0;
	i_control.u.direct = direct;
	i_control.u.address = address;
	value = ReadIndirectRegisterUlong(reg_hw, i_control.value);
	return value;
}


