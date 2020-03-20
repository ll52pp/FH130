/*++
�ļ���
hw.c

����
Ӳ������
--*/

#include "precomp.h"
#include "hw.tmh"

BOOLEAN EvtInterruptIsr(
	IN WDFINTERRUPT Interrupt,
	IN ULONG MessageID
)
/*++
�������жϻص�����
--*/
{
    PFDO_DATA fdoData;
    PREG_HW reg_hw;

	UNREFERENCED_PARAMETER(MessageID);
	fdoData = FdoGetData(WdfInterruptGetDevice(Interrupt));
    reg_hw = fdoData->Reg;
	return FALSE;
}

VOID EvtInterruptDpc(
	IN WDFINTERRUPT WdfInterrupt,
	IN WDFOBJECT WdfDevice
)
/*++
�������жϵ�DPC����
--*/
{
	PFDO_DATA fdoData;

	UNREFERENCED_PARAMETER(WdfInterrupt);
	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_DPC, "%s enter", __FUNCTION__);

	fdoData = FdoGetData(WdfDevice);
	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_DPC, "%s leave", __FUNCTION__);
}

NTSTATUS EvtInterruptEnable(
	IN WDFINTERRUPT Interrupt,
	IN WDFDEVICE AssociatedDevice
)
/*++
�������ж�ʹ��֮ǰ�ص�������
--*/
{
	INTERRUPT_CTRL v;
	PFDO_DATA fdoData;

	UNREFERENCED_PARAMETER(AssociatedDevice);
	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_INTERRUPT, "%s enter", __FUNCTION__);

	fdoData = FdoGetData(WdfInterruptGetDevice(Interrupt));

	// ��ʼ���жϼĴ���
    v.value = ReadRegisterUlong(&fdoData->Reg->INTERRUPT_CTRL);
    v.u.reserved = 0;
    v.u.intr_enable_Rx_IU = 0;
    v.u.intr_enable_Rx_credit_out = 0;
    v.u.intr_enable_Tx_IU = 0;
    v.u.intr_enable_send_bd_empty = 0;
    v.u.intr_enable_link_change = 1;
    v.u.intr_enable_global = 0;
    WriteRegisterUlong(&fdoData->Reg->INTERRUPT_CTRL, v.value);

	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_INTERRUPT, "%s leave", __FUNCTION__);
	return STATUS_SUCCESS;
}

NTSTATUS EvtDeviceD0EntryPostInterruptsEnabled(
	IN WDFDEVICE Device,
	IN WDF_POWER_DEVICE_STATE PreviousState
)
/*++
�������ж�ʹ��֮��ص�������
--*/
{
	PFDO_DATA fdoData;

	PAGED_CODE();
	UNREFERENCED_PARAMETER(PreviousState);
	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "%s entry", __FUNCTION__);
	fdoData = FdoGetData(Device);
	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "%s leave", __FUNCTION__);
    return STATUS_SUCCESS;
}

NTSTATUS EvtDeviceD0ExitPreInterruptsDisabled(
	IN WDFDEVICE Device,
	IN WDF_POWER_DEVICE_STATE TargetState
)
/*++
�����������ж�ǰ�ص�������
--*/
{
	PFDO_DATA fdoData;

	PAGED_CODE();
	UNREFERENCED_PARAMETER(TargetState);
	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "%s entry", __FUNCTION__);
    fdoData = FdoGetData(Device);
	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "%s leave", __FUNCTION__);
    return STATUS_SUCCESS;
}

NTSTATUS EvtInterruptDisable(
	IN WDFINTERRUPT Interrupt,
	IN WDFDEVICE AssociatedDevice
)
/*++
������������豸��Դ״̬��ΪD1 D2 D3ʱ�ص�������
����Ӧ��������ر��ж�
--*/
{
    INTERRUPT_CTRL v;
    PFDO_DATA fdoData;

    UNREFERENCED_PARAMETER(AssociatedDevice);
    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_INTERRUPT, "%s enter", __FUNCTION__);

    fdoData = FdoGetData(WdfInterruptGetDevice(Interrupt));

    // ��ʼ���жϼĴ���
    v.value = ReadRegisterUlong(&fdoData->Reg->INTERRUPT_CTRL);
    v.u.reserved = 0;
    v.u.intr_enable_Rx_IU = 0;
    v.u.intr_enable_Rx_credit_out = 0;
    v.u.intr_enable_Tx_IU = 0;
    v.u.intr_enable_send_bd_empty = 0;
    v.u.intr_enable_link_change = 0;
    v.u.intr_enable_global = 0;
    WriteRegisterUlong(&fdoData->Reg->INTERRUPT_CTRL, v.value);

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_INTERRUPT, "%s leave", __FUNCTION__);
    return STATUS_SUCCESS;
}

NTSTATUS EvtDevicePrepareHardware(
	IN WDFDEVICE Device,
	IN WDFCMRESLIST Resources,
	IN WDFCMRESLIST ResourcesTranslated
)
/*++
�������豸���빤��״̬֮ǰ�ص�������
--*/
{
	NTSTATUS status;
	UINT idx;
	PFDO_DATA fdoData;
	PCM_PARTIAL_RESOURCE_DESCRIPTOR descriptor;

	UNREFERENCED_PARAMETER(Resources);
	PAGED_CODE();
	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "%s enter", __FUNCTION__);
	status = STATUS_SUCCESS;
	fdoData = FdoGetData(Device);
	for (idx = 0; idx < WdfCmResourceListGetCount(ResourcesTranslated); ++idx)
	{
		descriptor = WdfCmResourceListGetDescriptor(ResourcesTranslated, idx);
		if (descriptor == NULL)
		{
			TraceEvents(TRACE_LEVEL_ERROR, DBG_PNP, "WdfCmResourceListGetDescriptor get resource failed");
			break;
		}
		switch (descriptor->Type)
		{
			case CmResourceTypePort:
			{
				TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "ResourcesTranslated[%d] Type=CmResourceTypePort Start.LowPart=0x%08x Length=%d", idx, descriptor->u.Port.Start.LowPart, descriptor->u.Port.Length);
			}
			break;

			case CmResourceTypeMemory:
			{
				fdoData->RegPhyAddr = descriptor->u.Memory.Start;
				fdoData->RegPhyLen = descriptor->u.Memory.Length;
				fdoData->Reg = MmMapIoSpace(descriptor->u.Memory.Start, descriptor->u.Memory.Length, MmNonCached);
				TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "ResourcesTranslated[%d] Type=CmResourceTypeMemory RegPhysAddr=[L:0x%08x H:0x%08x] Reg=0x%08x RegPhyLen=0x%08x",
					idx, fdoData->RegPhyAddr.LowPart, fdoData->RegPhyAddr.HighPart, (ULONG)fdoData->Reg, fdoData->RegPhyLen);
			}
			break;

			case CmResourceTypeInterrupt:
			{
				TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "ResourcesTranslated[%d] Type=CmResourceTypeInterrupt Interrupt[Level:0x%08x Vector:0x%08x Affinity:0x%08x]",
							idx, descriptor->u.Interrupt.Level, descriptor->u.Interrupt.Vector, (INT32)descriptor->u.Interrupt.Affinity);
			}
			break;

			case CmResourceTypeDevicePrivate:
			{
				TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "ResourcesTranslated[%d] Type=CmResourceTypeDevicePrivate Data[0:0x%08x 1:0x%08x 2:0x%08x]",
							idx, descriptor->u.DevicePrivate.Data[0], descriptor->u.DevicePrivate.Data[1], descriptor->u.DevicePrivate.Data[2]);
			}
			break;

			default:
			{
				TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "ResourcesTranslated[%d] Unhandled resource type 0x%08x", idx, descriptor->Type);
			}
			break;
		}
	}

	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "%s leave", __FUNCTION__);
	return status;
}

NTSTATUS EvtDeviceReleaseHardware(
	IN WDFDEVICE Device,
	IN WDFCMRESLIST ResourcesTranslated
)
/*++
�������豸�˳�����״̬֮��ص�������
--*/
{
	NTSTATUS status;
    PFDO_DATA fdoData;

	PAGED_CODE();
	UNREFERENCED_PARAMETER(ResourcesTranslated);
	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "%s enter", __FUNCTION__);
	status = STATUS_SUCCESS;
	fdoData = FdoGetData(Device);

	// �ͷ�ӳ�����Դ
    if (fdoData->Reg)
	{
        MmUnmapIoSpace(fdoData->Reg, fdoData->RegPhyLen);
        fdoData->Reg = NULL;
	}
	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "%s leave", __FUNCTION__);
	return status;
}

/* ȡ�ö˿ڵ�״̬ */
VOID HwGetPortStatus(
    IN PREG_HW reg_hw,
    IN ULONG *portStatus,
    IN INT32 portCount
    )
{
    PORT_STATUS v;

    ASSERT(portCount == 2);
    v.value = ReadRegisterUlong(&reg_hw->PORT_STATUS);
    portStatus[0] = v.u.p0_status;
    portStatus[1] = v.u.p1_status;
}

/* ȡ��QDR��������״̬ */
ULONG HwGetQdrBufState(
    IN PREG_HW reg_hw
    )
{
    PORT_STATUS v;

    v.value = ReadRegisterUlong(&reg_hw->PORT_STATUS);
    return v.u.qdr_buf_empty;
}

/* ��λFPGA */
VOID HwResetFpga(
    IN PREG_HW reg_hw,
    IN ULONG force_off_line
    )
{
    PORT_RX_ENAB enab;
    PORT_STATUS status;

    enab.value = ReadRegisterUlong(&reg_hw->PORT_RX_ENAB);
    enab.u.reset = 1;
    enab.u.p0_mac_switch = force_off_line;
    WriteRegisterUlong(&reg_hw->PORT_RX_ENAB, enab.value);

    /* wait until reset is completed */
    do {
        KeDelay(MILLI_SEC);
        status.value = ReadRegisterUlong(&reg_hw->PORT_STATUS);
        if (status.u.reset_done == 1)
        {
            break;
        }
    } while (TRUE);
    /* mac force off line */
    if (force_off_line == 1)
    {
        /* mac on */
        enab.value = ReadRegisterUlong(&reg_hw->PORT_RX_ENAB);
        enab.u.p0_mac_switch = 0;
        WriteRegisterUlong(&reg_hw->PORT_RX_ENAB, enab.value);
    }
}

/* ȡ��FPGA�汾 */
ULONG HwGetFpgaVersion(
    IN PREG_HW reg_hw
    )
{
    FPGA_VER v;

    v.value = ReadRegisterUlong(&reg_hw->FPGA_VER);
    return v.u.version & 0xFF; // ����8λ��Ч
}

/* FCID */
VOID HwSetPortFcid(
    IN PREG_HW reg_hw,
    IN ULONG fcid
    )
{
    PORT_CONFIG v;

    v.value = ReadRegisterUlong(&reg_hw->PORT_CONFIG);
    v.u.sid = fcid;
    WriteRegisterUlong(&reg_hw->PORT_CONFIG, v.value);
}

ULONG HwGetPortFcid(
    IN PREG_HW reg_hw
    )
{
    PORT_CONFIG v;

    v.value = ReadRegisterUlong(&reg_hw->PORT_CONFIG);
    return v.u.sid;
}

/* ���� */
VOID HwSetPortCreditNum(
    IN PREG_HW reg_hw,
    IN ULONG credit
    )
{
    PORT_CONFIG v;

    v.value = ReadRegisterUlong(&reg_hw->PORT_CONFIG);
    v.u.credit = credit - 1; /* 0 - base */
    WriteRegisterUlong(&reg_hw->PORT_CONFIG, v.value);
}

ULONG HwGetPortCreditNum(
    IN PREG_HW reg_hw
    )
{
    PORT_CONFIG v;

    v.value = ReadRegisterUlong(&reg_hw->PORT_CONFIG);
    return v.u.credit + 1; /* 0 - base */
}

/* ���� */
VOID HwSetPortSpeed(
    IN PREG_HW reg_hw,
    IN ULONG speed
    )
{
    PORT_CONFIG v;

    v.value = ReadRegisterUlong(&reg_hw->PORT_CONFIG);
    v.u.speed = speed; /* 0 ����Ӧ 1-1Gbps 2-2Gbps */
    WriteRegisterUlong(&reg_hw->PORT_CONFIG, v.value);
}

ULONG HwGetPortSpeed(
    IN PREG_HW reg_hw
    )
{
    PORT_CONFIG v;

    v.value = ReadRegisterUlong(&reg_hw->PORT_CONFIG);
    return v.u.speed; /* 0 ����Ӧ 1-1Gbps 2-2Gbps */
}

/* ���շ���DID����ʹ�� */
VOID HwSetPortDidFilterEnab(
    IN PREG_HW reg_hw,
    IN ULONG did_filter_enab
    )
{
    PORT_CONFIG v;

    v.value = ReadRegisterUlong(&reg_hw->PORT_CONFIG);
    v.u.did_filter_enab = did_filter_enab;
    WriteRegisterUlong(&reg_hw->PORT_CONFIG, v.value);
}

ULONG HwGetPortDidFilterEnab(
    IN PREG_HW reg_hw
    )
{
    PORT_CONFIG v;

    v.value = ReadRegisterUlong(&reg_hw->PORT_CONFIG);
    return v.u.did_filter_enab;
}

/* e_d_tov */
VOID HwSetPortEdtovTime(
    IN PREG_HW reg_hw,
    IN ULONG e_d_tov
    )
{
    PORT_RX_ENAB v;

    v.value = ReadRegisterUlong(&reg_hw->PORT_RX_ENAB);
    v.u.e_d_tov = e_d_tov; /* ��λ�Ǻ��� */
    WriteRegisterUlong(&reg_hw->PORT_RX_ENAB, v.value);
}

ULONG HwGetPortEdtovTime(
    IN PREG_HW reg_hw
    )
{
    PORT_RX_ENAB v;

    v.value = ReadRegisterUlong(&reg_hw->PORT_RX_ENAB);
    return v.u.e_d_tov; /* ��λ�Ǻ��� */
}

/* ����ʹ�� */
VOID HwSetPortRedundantEnab(
    IN PREG_HW reg_hw,
    IN ULONG redundancy_enab
    )
{
    PORT_RX_ENAB v;

    v.value = ReadRegisterUlong(&reg_hw->PORT_RX_ENAB);
    v.u.redundancy_enab = redundancy_enab; /* 0-��ֹ 1-ʹ�� */
    WriteRegisterUlong(&reg_hw->PORT_RX_ENAB, v.value);
}

ULONG HwGetPortRedundantEnab(
    IN PREG_HW reg_hw
    )
{
    PORT_RX_ENAB v;

    v.value = ReadRegisterUlong(&reg_hw->PORT_RX_ENAB);
    return v.u.redundancy_enab;
}

/* �˿ڽ���ʹ�� */
VOID HwSetPortRxEnab(
    IN PREG_HW reg_hw,
    IN ULONG rx_enab
    )
{
    PORT_RX_ENAB v;

    v.value = ReadRegisterUlong(&reg_hw->PORT_RX_ENAB);
    v.u.reset = 0;
    v.u.p0_mac_switch = 0;
    v.u.p0_rx_enab = rx_enab;/*  0-��ֹ 1-ʹ�� */
    WriteRegisterUlong(&reg_hw->PORT_RX_ENAB, v.value);
}

ULONG HwGetPortRxEnab(
    IN PREG_HW reg_hw
    )
{
    PORT_RX_ENAB v;

    v.value = ReadRegisterUlong(&reg_hw->PORT_RX_ENAB);
    return v.u.p0_rx_enab;
}

/* ��ʱ����ʱ�� */
VOID HwSetPortTimeOut(
    IN PREG_HW reg_hw,
    IN ULONG time
    )
{
    TIME_OUT v;

    v.value = 0;
    v.u.time = time; /* ��λ�Ǻ��� */
    WriteRegisterUlong(&reg_hw->TIME_OUT, v.value);
}

ULONG HwGetPortTimeOut(
    IN PREG_HW reg_hw
    )
{
    TIME_OUT v;

    v.value = ReadRegisterUlong(&reg_hw->TIME_OUT);
    return v.u.time; /* ��λ�Ǻ��� */
}

/* ����RTC */
VOID HwRtcControl(
    IN PREG_HW reg_hw,
    IN ULONG global_sync_enab,
    IN ULONG event_period,
    IN ULONG sync_enab,
    IN ULONG rtc_base
    )
{
    RTC_CONTROL v;

    v.value = ReadRegisterUlong(&reg_hw->RTC_CONTROL);
    v.u.global_sync_enab = global_sync_enab;
    v.u.event_period = event_period;
    v.u.p0_sync_enab = sync_enab;
    v.u.p1_sync_enab = sync_enab;
    v.u.rtc_enab = 1;
    v.u.rtc_base = rtc_base;
    WriteRegisterUlong(&reg_hw->RTC_CONTROL, v.value);
}

/* ���ÿ������� */
VOID HwReadRtcPrepare(
    IN PREG_HW reg_hw
    )
{
    RTC_DATE_READ v;

    v.value = 0;
    v.u.snap_shot_cmd = 1;
    WriteRegisterUlong(&reg_hw->RTC_DATE_READ, v.value);
}

/* ����������� */
VOID HwReadRtcFinish(
    IN PREG_HW reg_hw
    )
{
    RTC_DATE_READ v;

    v.value = 0;
    v.u.snap_shot_cmd = 0;
    WriteRegisterUlong(&reg_hw->RTC_DATE_READ, v.value);
}

/* RTC */
UINT64 HwGetRtc(
    IN PREG_HW reg_hw
    )
{
    ULONG h, l;
    UINT64 v;

    l = ReadRegisterUlong(&reg_hw->RTC_READ_LOW);
    h = ReadRegisterUlong(&reg_hw->RTC_READ_HIGH);
    v = ((UINT64)h << 32) | (UINT64)l;

    return v;
}

VOID HwSetRtc(
    IN PREG_HW reg_hw,
    IN UINT64 time
    )
{
    ULONG low, high;

    low = (ULONG)(time & 0xFFFFFFFF);
    high = (ULONG)(time >> 32);
    WriteRegisterUlong(&reg_hw->RTC_WRITE_HIGH, high);
    WriteRegisterUlong(&reg_hw->RTC_WRITE_LOW, low);
}

/* ���ý�������FCID */
VOID HwSetSwFcid(
	IN PREG_HW reg_hw,
	IN UINT32 fcid
	)
{
	KdPrint(("HwSetSwFcid fcid=0x%08x\n", fcid));
	WriteRegisterUlong(&reg_hw->CONFIG_SW_FCID, fcid);
}

/* �ж�λʹ�� */
VOID HwSetIntrptEnable(
    IN PREG_HW reg_hw,
    IN ULONG enab
    )
{
    INTERRUPT_CTRL v;

    v.value = 0;
    v.u.intr_enable_global = enab ? 1 : 0;
    v.u.intr_enable_Rx_IU = enab ? 1 : 0;
    v.u.intr_enable_link_change = 1;
    v.u.pending_link_change = 1;
    v.u.pending_send_bd_empty = 1;
    v.u.pending_Tx_IU = 1;
    v.u.pending_Rx_credit_out = 1;
    v.u.pending_Rx_IU = 1;
    WriteRegisterUlong(&reg_hw->INTERRUPT_CTRL, v.value);
}

/* ��ѹ */
ULONG HwGetVoltage(
    IN PREG_HW reg_hw
    )
{
    PORT_STATUS v;

    v.value = ReadRegisterUlong(&reg_hw->PORT_STATUS);
    return v.u.voltage * 3000 / 4096;
}

/* �¶� */
ULONG HwGetTemperature(
    IN PREG_HW reg_hw
    )
{
    PORT_STATUS v;

    v.value = ReadRegisterUlong(&reg_hw->PORT_STATUS);
    return v.u.temperature * 503975 / 4096 - 273150; /* X1000 */
}

/* ע��Rx�Ļ����� */
VOID HwRegisterRxDmaBuf(
    IN PREG_HW reg_hw,
    IN ULONG index,
    IN ULONG value
    )
{
    INDIRECT_CONTROL v;

    v.value = 0;
    v.u.direct = IDC_DIRECT_RX;
    v.u.address = IDA_RX_LOGIC_BUF_BASE + index;
    WriteIndirectRegisterUlong(reg_hw, v.value, value);
}

/* QDR BUF SIZE */
VOID HwSetQdrBufUnitSize(
    IN PREG_HW reg_hw,
    IN ULONG size
    )
{
    DIV_QDR_BUF_SIZE v;

    v.value = size;
    WriteRegisterUlong(&reg_hw->DIV_QDR_BUF_SIZE, v.value);
}

ULONG HwGetQdrBufUnitSize(
    IN PREG_HW reg_hw
    )
{
    DIV_QDR_BUF_SIZE v;

    v.value = ReadRegisterUlong(&reg_hw->DIV_QDR_BUF_SIZE);
    return v.value;
}

/* ����ÿ��QDR BUF��ʼ��ַ */
VOID HwSetQdrBufStartAddress(
    IN PREG_HW reg_hw,
    IN ULONG start_address
    )
{
    DIV_QDR_BUF_START_ADDR v;

    v.value = start_address;
    WriteRegisterUlong(&reg_hw->DIV_QDR_BUF_START_ADDR, v.value);
}

/* ��FPGAд����CREDIT */
VOID HwPushCreditsToFpga(
    IN PREG_HW reg_hw,
    IN ULONG *credits,
    IN ULONG valid_buf_num
    )
{
    CREDIT v;

    v.u.buf_num_of_1st = credits[0];
    v.u.buf_num_of_2nd = credits[1];
    v.u.buf_num_of_3rd = credits[2];
    v.u.valid_buf_num = valid_buf_num;
    WriteRegisterUlong(&reg_hw->CREDIT, v.value);
}

/* ��ȡ��·�仯�ж�λ */
ULONG HwGetLinkChangePending(
    IN PREG_HW reg_hw
    )
{
    INTERRUPT_CTRL v;

    v.value = ReadRegisterUlong(&reg_hw->INTERRUPT_CTRL);
    return v.u.pending_link_change;
}

/* ֱ�ӼĴ��� */
ULONG ReadRegisterUlong(
    IN PULONG reg
    )
{
    ULONG value;

    value = READ_REGISTER_ULONG(reg);
    return value;
}

VOID WriteRegisterUlong(
    IN PULONG reg,
    IN ULONG value
    )
{
    WRITE_REGISTER_ULONG(reg, value);
}

/* ��ַ�Ĵ��� */
ULONG ReadIndirectRegisterUlong(
    IN PREG_HW reg_hw,
    IN ULONG ic_value
    )
{
    ULONG ret;
    INDIRECT_CONTROL v;

    v.value = ic_value;
    v.u.action = IDC_ACTION_READ;
    WriteRegisterUlong(&reg_hw->INDIRECT_CONTROL, v.value);
    ret = ReadRegisterUlong(&reg_hw->INDIRECT_DATA);
    return ret;
}

VOID WriteIndirectRegisterUlong(
    IN PREG_HW reg_hw,
    IN ULONG ic_value,
    IN ULONG id_value
    )
{
    INDIRECT_CONTROL ic;
    INDIRECT_DATA id;

    ic.value = ic_value;
    id.value = id_value;
    ic.u.action = IDC_ACTION_WRITE;
    WriteRegisterUlong(&reg_hw->INDIRECT_DATA, id.value);
    WriteRegisterUlong(&reg_hw->INDIRECT_CONTROL, ic.value);
}

/* ����Type��ȡͳ����Ϣ */
UINT32 HwGetStatisticsByType(
    IN PREG_HW reg_hw,
    UINT32 type
    )
{
    UINT32 value;
    STATISTICS_CONTROL status;

    status.value = 0;
    status.u.start = 0;
    status.u.type = type;
    KeDelay(MILLI_SEC);
    WriteRegisterUlong(&reg_hw->STATISTICS_CONTROL, status.value);
    KeDelay(MILLI_SEC);
    value = ReadRegisterUlong(&reg_hw->STATISTICS_DATA);
    return value;
}

/* ȡ��ͳ��ֵ */
VOID HwGetStatistics(
    IN PREG_HW reg_hw,
    IN PFPGA_STATISTICS_INFO fsi,
    IN PPORT_STATISTICS_INFO psi
    )
{
    INT32 idx, port_base_addr;
    UINT64 t;
    STATISTICS_CONTROL status;

    // ���ÿ���
    status.value = 0;
    status.u.start = 1;
    WriteRegisterUlong(&reg_hw->STATISTICS_CONTROL, status.value);

    // ע�⣺�������ú����ȴ������̶����������ֵ
    KeDelay(MILLI_SEC);

    // ��FPGAȡ��ͳ������
    t = HwGetStatisticsByType(reg_hw, FPGA_STAT_TYPE_RECV_FRAME_NUM);
    fsi->recvFrameNumTotal += t;

    t = HwGetStatisticsByType(reg_hw, FPGA_STAT_TYPE_RECV_IU_NUM);
    fsi->recvIUNumTotal += t;

    t = HwGetStatisticsByType(reg_hw, FPGA_STAT_TYPE_RECV_ERROR_IU_NUM);
    fsi->recvErrorIUNumTotal += t;

    t = HwGetStatisticsByType(reg_hw, FPGA_STAT_TYPE_RECV_DISCARD_IU_NUM);
    fsi->recvDiscardFrameNumTotal += t;

    t = HwGetStatisticsByType(reg_hw, FPGA_STAT_TYPE_RECV_INVALID_FRAME_NUM);
    fsi->recvInvalidFrameNumTotal += t;

    t = HwGetStatisticsByType(reg_hw, FPGA_STAT_TYPE_SEND_FRAME_NUM);
    fsi->sendFrameNumTotal += t;

    t = HwGetStatisticsByType(reg_hw, FPGA_STAT_TYPE_SEND_IU_NUM);
    fsi->sendIUNumTotal += t;

    for (idx = 0; idx < 2; ++idx)
    {
        if (idx == 0)
        {
            port_base_addr = FPGA_STAT_PORT_0_BASE;
        }
        else
        {
            port_base_addr = FPGA_STAT_PORT_1_BASE;
        }
        t = HwGetStatisticsByType(reg_hw, port_base_addr + PORT_STAT_RX_UNDERSIZE_FRAME);
        psi[idx].RxUndersizeFrameCnt += t;

        t = HwGetStatisticsByType(reg_hw, port_base_addr + PORT_STAT_RX_OVERSIZE_FRAME);
        psi[idx].RxOversizeFrameErrCnt += t;

        t = HwGetStatisticsByType(reg_hw, port_base_addr + PORT_STAT_RX_ALL_FRAME);
        psi[idx].RxAllFrameCnt += t;

        t = HwGetStatisticsByType(reg_hw, port_base_addr + PORT_STAT_RX_VALID_FRAME);
        psi[idx].RxValidFrameCnt += t;

        t = HwGetStatisticsByType(reg_hw, port_base_addr + PORT_STAT_RX_FRAME_LEN);
        psi[idx].RxWordCnt += t;

        t = HwGetStatisticsByType(reg_hw, port_base_addr + PORT_STAT_RX_RRDY);
        psi[idx].RxRRDYCnt += t;

        t = HwGetStatisticsByType(reg_hw, port_base_addr + PORT_STAT_RX_K_ERR);
        psi[idx].RxKErrCnt += t;

        t = HwGetStatisticsByType(reg_hw, port_base_addr + PORT_STAT_LNK_CHG_UP2DWN);
        psi[idx].LinkChgUp2DownCnt += t;

        t = HwGetStatisticsByType(reg_hw, port_base_addr + PORT_STAT_TX_ALL_FRAME);
        psi[idx].TxAllFrameCnt += t;

        t = HwGetStatisticsByType(reg_hw, port_base_addr + PORT_STAT_TX_VALID_FRAME);
        psi[idx].TxValidFrameCnt += t;

        t = HwGetStatisticsByType(reg_hw, port_base_addr + PORT_STAT_TX_FRAME_LEN);
        psi[idx].TxWordCnt += t;

        t = HwGetStatisticsByType(reg_hw, port_base_addr + PORT_STAT_TX_RRDY);
        psi[idx].TxRRDYCnt += t;
    }
}

/* �ֶ��Լ� */
VOID HwManualSelfCheck(
    IN PREG_HW reg_hw,
    IN PFC_BIT_RESULT_MANUAL bitResult
    )
{
    ULONG value, low, high;
    
    bitResult->flash = BIT_SUCCESS;
    bitResult->buffer = BIT_SUCCESS;
    // �¶�
    value = HwGetTemperature(reg_hw);
    low = SC_TEMP_VALUE - SC_TEMP_THRESHOLD;
    high = SC_TEMP_VALUE + SC_TEMP_THRESHOLD;
    if (!(value >= low && value <= high))
    {
        bitResult->temperature = BIT_FAILURE;
    }
    else
    {
        bitResult->temperature = BIT_SUCCESS;
    }
    // ��ѹ
    value = HwGetVoltage(reg_hw);
    low = SC_VOLTAGE_VALUE - SC_VOLTAGE_THRESHOLD;
    high = SC_VOLTAGE_VALUE + SC_VOLTAGE_THRESHOLD;
    if (!(value >= low && value <= high))
    {
        bitResult->voltage = BIT_FAILURE;
    }
    else
    {
        bitResult->voltage = BIT_SUCCESS;
    }
}