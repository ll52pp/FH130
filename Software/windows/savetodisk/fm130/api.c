#include "precomp.h"

///////////////////////////////////////////////////////////////////////////////
// �豸����ӿ�
///////////////////////////////////////////////////////////////////////////////
//
// ���豸
//
FCUINT FCM_DevOpen(
    FCHANDLE *hDev,
    FCUINT DevId
    )
{
    int t_ret, enum_device_flag, get_io_handle_flag, ioctrl_dev_open_flag;
    FCINT ret;
    BOOL b_ret;
    DWORD bytes;
    ULONG inbuf_len, outbuf_len;
    PDEV_INFO di;
    HANDLE h;
    DEV_OPEN_REQ req;
    DEV_OPEN_RESP resp;

    // ������
    if (hDev == NULL)
    {
        return FC_INVALID_PARAMETER;
    }

    if (!(DevId >= 0 && DevId < DEV_NUM_MAX))
    {
        return FC_INVALID_PARAMETER;
    }
    enum_device_flag = 0;
    get_io_handle_flag = 0; 
    ioctrl_dev_open_flag = 0;
    di = NULL;
    *hDev = NULL;

    do
    {
        // ö���豸
        t_ret = EnumDevice();
        if (t_ret)
        {
            ret = FC_ENUM_DEV_FAILED;
            break;
        }
        enum_device_flag = 1;

        // ����ָ�����豸
        di = GetDevInfoByNumber(DevId);
        if (di == NULL)
        {
            ret = FC_GET_DEV_INFO_FAILED;
            break;
        }

        if (di->state != ECS_NONE)
        {
            ret = FC_INVALID_DEV_STATE;
            break;
        }

        // ȡ�����������豸�ľ��
        t_ret = GetIoHandle(di);
        if (t_ret)
        {
            ret = FC_GET_IO_HANDLE_FAILED;
            break;
        }
        h = di->io.ioctrl;

        // ���ʹ��豸������
        inbuf_len = sizeof(DEV_OPEN_REQ);
        outbuf_len = sizeof(DEV_OPEN_RESP);
        memset(&req, 0, sizeof(DEV_OPEN_REQ));
        memset(&resp, 0, sizeof(DEV_OPEN_RESP));
        req.reserve = 0;
        b_ret = DeviceIoControl(h, IOCTL_DEV_OPEN, &req, inbuf_len, &resp, outbuf_len, &bytes, NULL);
        if (!b_ret)
        {
            ret = FC_DEV_IOCTRL_FAILED;
            break;
        }

        if (resp.result == IO_CTRL_RESP_NG)
        {
            ret = FC_IOCTRL_RESP_NG;
            break;
        }

        *hDev = (FCHANDLE)di;
        // ���ÿ���״̬
        di->state = ECS_OPEN;
        ret = FC_SUCCESS;
    } while (FALSE);

    if (ret)
    {
        if (enum_device_flag == 1)
        {
            InitDevManager();
        }
    }

    return ret;
}

//
// �ر��豸
//
FCUINT FCM_DevClose(
    FCHANDLE hDev
    )
{
    FCUINT ret;
    BOOL b_ret;
    DWORD bytes;
    ULONG inbuf_len, outbuf_len;
    PDEV_INFO di;
    HANDLE h;
    DEV_CLOSE_REQ req;
    DEV_CLOSE_RESP resp;

    // ������
    if (hDev == NULL)
    {
        return FC_INVALID_PARAMETER;
    }

    di = (PDEV_INFO)hDev;
    h = di->io.ioctrl;
    if (h == INVALID_HANDLE_VALUE)
    {
        return FC_INVALID_HANDLE;
    }

    // �������״̬��ECS_NONE,���عرճɹ�
    if (di->state == ECS_NONE)
    {
        return FC_SUCCESS;
    }

    // ȡ���Ѿ�ע����жϴ���
    ret = FCM_DevUnRegMsgHandler(hDev);
    if (ret)
    {
        return ret;
    }
    ret = FCM_DevUnRegEvtHandler(hDev);
    if (ret)
    {
        return ret;
    }

    // ���͹ر��豸������
    inbuf_len = sizeof(DEV_CLOSE_REQ);
    outbuf_len = sizeof(DEV_CLOSE_RESP);
    memset(&req, 0, sizeof(DEV_CLOSE_REQ));
    memset(&resp, 0, sizeof(DEV_CLOSE_RESP));
    req.reserve = 0;
    b_ret = DeviceIoControl(h, IOCTL_DEV_CLOSE, &req, inbuf_len, &resp, outbuf_len, &bytes, NULL);
    if (!b_ret)
    {
        return FC_DEV_IOCTRL_FAILED;
    }

    if (resp.result == IO_CTRL_RESP_NG)
    {
        // ʧ��
        return FC_IOCTRL_RESP_NG;
    }

    di->reserve = 0xFFFF;
    CloseIoHandle(di);

    // �޸Ŀ���״̬
    di->state = ECS_NONE;
    return FC_SUCCESS;
}

//
// ʹ���豸
//
FCUINT FCM_DevEnable(
    FCHANDLE hDev,
    FCUINT fcid,
    FCUINT credit_num,
	FCUINT speed
    )
{
    BOOL b_ret;
    DWORD bytes;
    ULONG inbuf_len, outbuf_len;
    DEV_ENAB_REQ req;
    DEV_ENAB_RESP resp;
    PDEV_INFO di;
    HANDLE h;

    // ������
    if (hDev == NULL)
    {
        return FC_INVALID_PARAMETER;
    }

    di = (PDEV_INFO)hDev;
    h = di->io.ioctrl;
    if (h == INVALID_HANDLE_VALUE)
    {
        return FC_INVALID_HANDLE;
    }

    // ����״̬����ȷ
    if (di->state != ECS_OPEN)
    {
        return FC_INVALID_DEV_STATE;
    }

    // ���ͼ���FC�ڵ����ASM��������
    inbuf_len = sizeof(DEV_ENAB_REQ);
    outbuf_len = sizeof(DEV_ENAB_RESP);
    memset(&req, 0, sizeof(DEV_ENAB_REQ));
    memset(&resp, 0, sizeof(DEV_ENAB_RESP));

    req.credit_num = credit_num;
    //req.speed = DEV_CONFIG_SPEED;
	req.speed = speed;
    req.did_filter_enab = DEV_CONFIG_DID_FILTER_ENAB;
    req.e_d_tov = DEV_CONFIG_E_D_TOV;
    req.redundant_enab = DEV_CONFIG_REDUNDANT_ENAB;
    req.time_out = DEV_CONFIG_TIME_OUT;
    req.qdr_buf_unit_size = DEV_CONFIG_QDR_BUF_UNIT_SIZE;
	req.sw_fcid = SW_FCID;
    b_ret = DeviceIoControl(h, IOCTL_DEV_ENAB, &req, inbuf_len, &resp, outbuf_len, &bytes, NULL);
    if (!b_ret)
    {
        return FC_DEV_IOCTRL_FAILED;
    }

    if (resp.result == IO_CTRL_RESP_NG)
    {
        // ʧ��
        return FC_IOCTRL_RESP_NG;
    }
    di->state = ECS_CONFIG;
    return FC_SUCCESS;
}

//
// ��λ�豸
//
FCUINT FCM_DevReset(
    FCHANDLE hDev
    )
{
    BOOL b_ret;
    DWORD bytes;
    ULONG inbuf_len, outbuf_len;
    PDEV_INFO di;
    HANDLE h;
    DEV_RESET_REQ req;
    DEV_RESET_RESP resp;

    // ������
    if (hDev == NULL)
    {
        return FC_INVALID_PARAMETER;
    }

    di = (PDEV_INFO)hDev;
    h = di->io.ioctrl;
    if (h == INVALID_HANDLE_VALUE)
    {
        return FC_INVALID_HANDLE;
    }
    if (di->state == ECS_MONITOR)
    {
        return FC_DEV_STATE_MONITOR;
    }
    if (di->state == ECS_NONE)
    {
        return FC_INVALID_DEV_STATE;
    }
    // ���͸�λ����
    inbuf_len = sizeof(DEV_RESET_REQ);
    outbuf_len = sizeof(DEV_RESET_RESP);
    memset(&req, 0, sizeof(DEV_RESET_REQ));
    memset(&resp, 0, sizeof(DEV_RESET_RESP));
    req.reserve = 0;
    b_ret = DeviceIoControl(h, IOCTL_DEV_RESET, &req, inbuf_len, &resp, outbuf_len, &bytes, NULL);
    if (!b_ret)
    {
        return FC_DEV_IOCTRL_FAILED;
    }

    if (resp.result == IO_CTRL_RESP_NG)
    {
        // ʧ��
        return FC_IOCTRL_RESP_NG;
    }
    di->state = ECS_OPEN;
    return FC_SUCCESS;
}

//
// ��ȡ�豸��N�˿�״̬
//
FCUINT FCM_DevGetState(
    FCHANDLE hDev,
    FCUINT *state
    )
{
    BOOL b_ret;
    DWORD bytes;
    ULONG inbuf_len, outbuf_len;
    PDEV_INFO di;
    HANDLE h;
    DEV_GET_STATE_REQ req;
    DEV_GET_STATE_RESP resp;

    // ������
    if (hDev == NULL)
    {
        return FC_INVALID_PARAMETER;
    }

    di = (PDEV_INFO)hDev;
    h = di->io.ioctrl;
    if (h == INVALID_HANDLE_VALUE)
    {
        return FC_INVALID_HANDLE;
    }
    if (di->state == ECS_NONE)
    {
        return FC_INVALID_DEV_STATE;
    }
    inbuf_len = sizeof(DEV_GET_STATE_REQ);
    outbuf_len = sizeof(DEV_GET_STATE_RESP);
    memset(&req, 0, sizeof(DEV_GET_STATE_REQ));
    memset(&resp, 0, sizeof(DEV_GET_STATE_RESP));
    req.reserve = 0;
    b_ret = DeviceIoControl(h, IOCTL_DEV_GET_STATE, &req, inbuf_len, &resp, outbuf_len, &bytes, NULL);
    if (!b_ret)
    {
        return FC_DEV_IOCTRL_FAILED;
    }

    if (resp.result == IO_CTRL_RESP_NG)
    {
        return FC_IOCTRL_RESP_NG;
    }

    if (resp.p0_status == PORT_LINK_UP || resp.p1_status == PORT_LINK_UP)
    {
        *state = PORT_LINK_UP;
    }
    else
    {
        *state = PORT_LINK_DOWN;
    }
    return FC_SUCCESS;
}

//
// ��ȡ�豸��N�˿ڰ汾��
//
FCUINT FCM_DevGetVersion(
    FCHANDLE hDev,
    FCUINT *version
    )
{
    BOOL b_ret;
    DWORD bytes;
    ULONG inbuf_len, outbuf_len;
    PDEV_INFO di;
    HANDLE h;
    DEV_GET_VERSION_REQ req;
    DEV_GET_VERSION_RESP resp;

    // ������
    if (hDev == NULL)
    {
        return FC_INVALID_PARAMETER;
    }

    di = (PDEV_INFO)hDev;
    h = di->io.ioctrl;
    if (h == INVALID_HANDLE_VALUE)
    {
        return FC_INVALID_HANDLE;
    }

    // ����״̬����ȷ
    if (di->state == ECS_NONE)
    {
        return FC_INVALID_DEV_STATE;
    }

    // ���ͻ�ȡ�汾������
    inbuf_len = sizeof(DEV_GET_VERSION_REQ);
    outbuf_len = sizeof(DEV_GET_VERSION_RESP);
    memset(&req, 0, sizeof(DEV_GET_VERSION_REQ));
    memset(&resp, 0, sizeof(DEV_GET_VERSION_RESP));
    req.reserve = 0;
    b_ret = DeviceIoControl(h, IOCTL_DEV_GET_VERSION, &req, inbuf_len, &resp, outbuf_len, &bytes, NULL);
    if (!b_ret)
    {
        return FC_DEV_IOCTRL_FAILED;
    }

    if (resp.result == IO_CTRL_RESP_NG)
    {
        return FC_IOCTRL_RESP_NG;
    }
    // ���汾 ���汾 FPGA�汾 �����汾
    *version = (LIB_MAJOR_VER << 24) | (LIB_MINOR_VER << 16) | ((resp.fpga_version & 0xFF) << 8) | resp.drier_version;
    return FC_SUCCESS;
}

//
// ע���жϽ��ջص�����
//
FCUINT FCM_DevRegMsgHandler(
    FCHANDLE hDev,
    FC_NP_RECV_FUNCPTR func
    )
{
    int int_recv_start_flag;
    FCUINT ret;
    BOOL b_ret;
    DWORD bytes;
    ULONG inbuf_len, outbuf_len;
    PDEV_INFO di;
    HANDLE h;
    DEV_REG_RECV_HANDLER_REQ req;
    DEV_REG_RECV_HANDLER_RESP resp;

    // ������
    if (hDev == NULL)
    {
        return FC_INVALID_PARAMETER;
    }

    di = (PDEV_INFO)hDev;
    h = di->io.ioctrl;
    if (h == INVALID_HANDLE_VALUE)
    {
        return FC_INVALID_HANDLE;
    }

    // ����״̬����ȷ
    if (di->state == ECS_MONITOR)
    {
        return FC_DEV_STATE_MONITOR;
    }
    if (di->state == ECS_NONE)
    {
        return FC_INVALID_DEV_STATE;
    }

    int_recv_start_flag = 0;
    do
    {
        ret = IntRecvStart(di, func);
        if (ret)
        {
            break;
        }
        int_recv_start_flag = 1;

        inbuf_len = sizeof(DEV_REG_RECV_HANDLER_REQ);
        outbuf_len = sizeof(DEV_REG_RECV_HANDLER_RESP);
        memset(&req, 0, sizeof(DEV_REG_RECV_HANDLER_REQ));
        memset(&resp, 0, sizeof(DEV_REG_RECV_HANDLER_RESP));
		req.handle_event = di->int_recv_event;
        b_ret = DeviceIoControl(h, IOCTL_DEV_REG_RECV_HANDLER, &req, inbuf_len, &resp, outbuf_len, &bytes, NULL);
        if (!b_ret)
        {
            ret = FC_DEV_IOCTRL_FAILED;
            break;
        }

        if (resp.result == IO_CTRL_RESP_NG)
        {
            ret = FC_IOCTRL_RESP_NG;
            break;
        }
        di->int_recv_cbn = resp.context;
        ret = FC_SUCCESS;
    } while (FALSE);

    if (ret)
    {
        if (int_recv_start_flag == 1)
        {
            ret = IntRecvStop(di);
            assert(ret == FC_SUCCESS);
            di->int_recv_cbn = NULL;
        }
    }
    return ret;
}

//
// ע���жϽ��ջص�����
//
FCUINT FCM_DevUnRegMsgHandler(
    FCHANDLE hDev
    )
{
    FCUINT ret;
    BOOL b_ret;
    DWORD bytes;
    ULONG inbuf_len, outbuf_len;
    PDEV_INFO di;
    HANDLE h;
    DEV_UNREG_RECV_HANDLER_REQ req;
    DEV_UNREG_RECV_HANDLER_RESP resp;

    // ������
    if (hDev == NULL)
    {
        return FC_INVALID_PARAMETER;
    }

    di = (PDEV_INFO)hDev;
    h = di->io.ioctrl;
    if (h == INVALID_HANDLE_VALUE)
    {
        return FC_INVALID_HANDLE;
    }

    // ����״̬����ȷ
    if (di->state == ECS_MONITOR)
    {
        return FC_DEV_STATE_MONITOR;
    }
    if (di->state == ECS_NONE)
    {
        return FC_INVALID_DEV_STATE;
    }

    do
    {
        inbuf_len = sizeof(DEV_UNREG_RECV_HANDLER_REQ);
        outbuf_len = sizeof(DEV_UNREG_RECV_HANDLER_RESP);
        memset(&req, 0, sizeof(DEV_UNREG_RECV_HANDLER_REQ));
        memset(&resp, 0, sizeof(DEV_UNREG_RECV_HANDLER_RESP));
        req.reserve = 0;
        b_ret = DeviceIoControl(h, IOCTL_DEV_UNREG_RECV_HANDLER, &req, inbuf_len, &resp, outbuf_len, &bytes, NULL);
        if (!b_ret)
        {
            ret = FC_DEV_IOCTRL_FAILED;
            break;
        }

        if (resp.result == IO_CTRL_RESP_NG)
        {
            ret = FC_IOCTRL_RESP_NG;
            break;
        }

        ret = IntRecvStop(di);
        assert(ret == FC_SUCCESS);
        di->int_recv_cbn = NULL;
    } while (FALSE);

    return ret;
}

//
// ע���¼��жϻص�����
//
FCUINT FCM_DevRegEvtHandler(
    FCHANDLE hDev,
    FC_INT_FUNCPTR func
    )
{
    int int_evt_start_flag;
    FCUINT ret, t_ret;
    BOOL b_ret;
    DWORD bytes;
    ULONG inbuf_len, outbuf_len;
    PDEV_INFO di;
    HANDLE h;
    DEV_REG_EVT_HANDLER_REQ req;
    DEV_REG_EVT_HANDLER_RESP resp;

    // ������
    if (hDev == NULL)
    {
        return FC_INVALID_PARAMETER;
    }

    di = (PDEV_INFO)hDev;
    h = di->io.ioctrl;
    if (h == INVALID_HANDLE_VALUE)
    {
        return FC_INVALID_HANDLE;
    }

    // ����״̬����ȷ
    if (di->state == ECS_MONITOR)
    {
        return FC_DEV_STATE_MONITOR;
    }
    if (di->state == ECS_NONE)
    {
        return FC_INVALID_DEV_STATE;
    }

    int_evt_start_flag = 0;
    do
    {
        ret = IntEvtStart(di, func);
        if (ret)
        {
            break;
        }
        int_evt_start_flag = 1;

        inbuf_len = sizeof(DEV_REG_EVT_HANDLER_REQ);
        outbuf_len = sizeof(DEV_REG_EVT_HANDLER_RESP);
        memset(&req, 0, sizeof(DEV_REG_EVT_HANDLER_REQ));
        memset(&resp, 0, sizeof(DEV_REG_EVT_HANDLER_RESP));
        req.handle_event = di->int_evt_event;
        b_ret = DeviceIoControl(h, IOCTL_DEV_REG_EVT_HANDLER, &req, inbuf_len, &resp, outbuf_len, &bytes, NULL);
        if (!b_ret)
        {
            ret = FC_DEV_IOCTRL_FAILED;
            break;
        }

        if (resp.result == IO_CTRL_RESP_NG)
        {
            ret = FC_IOCTRL_RESP_NG;
            break;
        }
        di->int_evt_cbn = resp.context;
        ret = FC_SUCCESS;
    } while (FALSE);

    if (ret)
    {
        if (int_evt_start_flag == 1)
        {
            t_ret = IntEvtStop(di);
            assert(t_ret == FC_SUCCESS);
            di->int_evt_cbn = NULL;
        }
    }

    return ret;
}

//
// ע���¼��жϻص�����
//
FCUINT FCM_DevUnRegEvtHandler(
    FCHANDLE hDev
    )
{
    FCUINT ret;
    BOOL b_ret;
    DWORD bytes;
    ULONG inbuf_len, outbuf_len;
    PDEV_INFO di;
    HANDLE h;
    DEV_UNREG_EVT_HANDLER_REQ req;
    DEV_UNREG_EVT_HANDLER_RESP resp;

    // ������
    if (hDev == NULL)
    {
        return FC_INVALID_PARAMETER;
    }

    di = (PDEV_INFO)hDev;
    h = di->io.ioctrl;
    if (h == INVALID_HANDLE_VALUE)
    {
        return FC_INVALID_HANDLE;
    }

    // ����״̬����ȷ
    if (di->state == ECS_MONITOR)
    {
        return FC_DEV_STATE_MONITOR;
    }
    if (di->state == ECS_NONE)
    {
        return FC_INVALID_DEV_STATE;
    }

    do
    {
        inbuf_len = sizeof(DEV_UNREG_EVT_HANDLER_REQ);
        outbuf_len = sizeof(DEV_UNREG_EVT_HANDLER_RESP);
        memset(&req, 0, sizeof(DEV_UNREG_EVT_HANDLER_REQ));
        memset(&resp, 0, sizeof(DEV_UNREG_EVT_HANDLER_RESP));
        req.reserve = 0;
        b_ret = DeviceIoControl(h, IOCTL_DEV_UNREG_EVT_HANDLER, &req, inbuf_len, &resp, outbuf_len, &bytes, NULL);
        if (!b_ret)
        {
            ret = FC_DEV_IOCTRL_FAILED;
            break;
        }

        if (resp.result == IO_CTRL_RESP_NG)
        {
            ret = FC_IOCTRL_RESP_NG;
            break;
        }

        ret = IntEvtStop(di);
        assert(ret == FC_SUCCESS);
        di->int_evt_cbn = NULL;
    } while (FALSE);

    return ret;
}

//
// ȡ��ͳ����Ϣ
//
FCUINT FCM_GetNStatistics(
    FCHANDLE hDev,
    PORT_STATISTICS_INFO *stat
    )
{
    BOOL b_ret;
    DWORD bytes;
    ULONG inbuf_len, outbuf_len;
    PDEV_INFO di;
    HANDLE h;
    DEV_GET_STATISTICS_REQ req;
    DEV_GET_STATISTICS_RESP resp;

    // ������
    if (hDev == NULL)
    {
        return FC_INVALID_PARAMETER;
    }

    di = (PDEV_INFO)hDev;
    h = di->io.ioctrl;
    if (h == INVALID_HANDLE_VALUE)
    {
        return FC_INVALID_HANDLE;
    }

    inbuf_len = sizeof(DEV_GET_STATISTICS_REQ);
    outbuf_len = sizeof(DEV_GET_STATISTICS_RESP);
    memset(&req, 0, sizeof(DEV_GET_STATISTICS_REQ));
    memset(&resp, 0, sizeof(DEV_GET_STATISTICS_RESP));

    req.reserve = 0;
    b_ret = DeviceIoControl(h, IOCTL_DEV_GET_STATISTICS, &req, inbuf_len, &resp, outbuf_len, &bytes, NULL);
    if (!b_ret)
    {
        return FC_DEV_IOCTRL_FAILED;
    }

    if (resp.result == IO_CTRL_RESP_NG)
    {
        return FC_IOCTRL_RESP_NG;
    }
    memcpy(stat, &resp.info, sizeof(PORT_STATISTICS_INFO) * 2);
    return FC_SUCCESS;
}

//
// �����豸��N�˿�BIT����
//
FCUINT FCM_IBit(
    FCHANDLE hDev,
    FC_BIT_RESULT_MANUAL *bitResult
    )
{
    BOOL b_ret;
    DWORD bytes;
    ULONG inbuf_len, outbuf_len;
    PDEV_INFO di;
    HANDLE h;
    DEV_IBIT_REQ req;
    DEV_IBIT_RESP resp;

    // ������
    if (hDev == NULL)
    {
        return FC_INVALID_PARAMETER;
    }

    di = (PDEV_INFO)hDev;
    h = di->io.ioctrl;
    if (h == INVALID_HANDLE_VALUE)
    {
        return FC_INVALID_HANDLE;
    }

    inbuf_len = sizeof(DEV_IBIT_REQ);
    outbuf_len = sizeof(DEV_IBIT_RESP);
    memset(&req, 0, sizeof(DEV_IBIT_REQ));
    memset(&resp, 0, sizeof(DEV_IBIT_RESP));

    req.reserve = 0;
    b_ret = DeviceIoControl(h, IOCTL_DEV_IBIT, &req, inbuf_len, &resp, outbuf_len, &bytes, NULL);
    if (!b_ret)
    {
        return FC_DEV_IOCTRL_FAILED;
    }

    if (resp.result == IO_CTRL_RESP_NG)
    {
        return FC_IOCTRL_RESP_NG;
    }
    bitResult->flash = resp.flash;
    bitResult->buffer = resp.buffer;
    bitResult->temperature = resp.temperature;
    bitResult->voltage = resp.voltage;
    return FC_SUCCESS;
}

//
// ��ȡ�豸�¶�
//
FCUINT FCM_GetTemp(
    FCHANDLE hDev,
    FCUINT *temperature
    )
{
    BOOL b_ret;
    DWORD bytes;
    ULONG inbuf_len, outbuf_len;
    PDEV_INFO di;
    HANDLE h;
    DEV_GET_TEMPERATURE_REQ req;
    DEV_GET_TEMPERATURE_RESP resp;

    // ������
    if (hDev == NULL)
    {
        return FC_INVALID_PARAMETER;
    }

    di = (PDEV_INFO)hDev;
    h = di->io.ioctrl;
    if (h == INVALID_HANDLE_VALUE)
    {
        return FC_INVALID_HANDLE;
    }

    // ����IO����
    inbuf_len = sizeof(DEV_GET_TEMPERATURE_REQ);
    outbuf_len = sizeof(DEV_GET_TEMPERATURE_RESP);
    memset(&req, 0, sizeof(DEV_GET_TEMPERATURE_REQ));
    memset(&resp, 0, sizeof(DEV_GET_TEMPERATURE_RESP));

    req.reserve = 0;
    b_ret = DeviceIoControl(h, IOCTL_DEV_GET_TEMPERATURE, &req, inbuf_len, &resp, outbuf_len, &bytes, NULL);
    if (!b_ret)
    {
        return FC_DEV_IOCTRL_FAILED;
    }

    if (resp.result == IO_CTRL_RESP_NG)
    {
        return FC_IOCTRL_RESP_NG;
    }

    *temperature = resp.temperature;
    return FC_SUCCESS;
}

//
// ��ȡ�豸��ѹ
//
FCUINT FCM_GetVoltage(
    FCHANDLE hDev,
    FCUINT *voltage
    )
{
    BOOL b_ret;
    DWORD bytes;
    ULONG inbuf_len, outbuf_len;
    PDEV_INFO di;
    HANDLE h;
    DEV_GET_VOLTAGE_REQ req;
    DEV_GET_VOLTAGE_RESP resp;

    // ������
    if (hDev == NULL)
    {
        return FC_INVALID_PARAMETER;
    }

    di = (PDEV_INFO)hDev;
    h = di->io.ioctrl;
    if (h == INVALID_HANDLE_VALUE)
    {
        return FC_INVALID_HANDLE;
    }

    // ����IO����
    inbuf_len = sizeof(DEV_GET_VOLTAGE_REQ);
    outbuf_len = sizeof(DEV_GET_VOLTAGE_RESP);
    memset(&req, 0, sizeof(DEV_GET_VOLTAGE_REQ));
    memset(&resp, 0, sizeof(DEV_GET_VOLTAGE_RESP));

    req.reserve = 0;
    b_ret = DeviceIoControl(h, IOCTL_DEV_GET_VOLTAGE, &req, inbuf_len, &resp, outbuf_len, &bytes, NULL);
    if (!b_ret)
    {
        return FC_DEV_IOCTRL_FAILED;
    }

    if (resp.result == IO_CTRL_RESP_NG)
    {
        return FC_IOCTRL_RESP_NG;
    }

    *voltage = resp.voltage;
    return FC_SUCCESS;
}

//
// ��ȡ�豸����״̬
//
FCUINT FCM_GetWorkStatus(
    FCHANDLE hDev,
    FCUINT *status
    )
{
    BOOL b_ret;
    DWORD bytes;
    ULONG inbuf_len, outbuf_len;
    PDEV_INFO di;
    HANDLE h;
    DEV_GET_WORK_STATUS_REQ req;
    DEV_GET_WORK_STATUS_RESP resp;

    // ������
    if (hDev == NULL)
    {
        return FC_INVALID_PARAMETER;
    }

    di = (PDEV_INFO)hDev;
    h = di->io.ioctrl;
    if (h == INVALID_HANDLE_VALUE)
    {
        return FC_INVALID_HANDLE;
    }

    // ����IO����
    inbuf_len = sizeof(DEV_GET_WORK_STATUS_REQ);
    outbuf_len = sizeof(DEV_GET_WORK_STATUS_RESP);
    memset(&req, 0, sizeof(DEV_GET_WORK_STATUS_REQ));
    memset(&resp, 0, sizeof(DEV_GET_WORK_STATUS_RESP));
    req.reserve = 0;
    b_ret = DeviceIoControl(h, IOCTL_DEV_GET_WORK_STATUS, &req, inbuf_len, &resp, outbuf_len, &bytes, NULL);
    if (!b_ret)
    {
        return FC_DEV_IOCTRL_FAILED;
    }

    if (resp.result == IO_CTRL_RESP_NG)
    {
        return FC_IOCTRL_RESP_NG;
    }
    *status = resp.status;
    return FC_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// ͨ�Ź���ӿ�
///////////////////////////////////////////////////////////////////////////////
//
// ���������ݵĻ�����
//
FCUINT FCM_RecvData(
    FCHANDLE hDev,
    void **ppBuffer,
    FCUINT *nLen
    )
{
    BOOL b_ret;
    DWORD bufLen, realLen;
    int buf;
    PDEV_INFO di;
    HANDLE h;

    // ������
    if (hDev == NULL)
    {
        return FC_INVALID_PARAMETER;
    }
    if (ppBuffer == NULL)
    {
        return FC_INVALID_PARAMETER;
    }
    if (nLen == NULL || *nLen == 0 || *nLen < sizeof(INT32))
    {
        return FC_INVALID_PARAMETER;
    }

    di = (PDEV_INFO)hDev;
    h = di->io.read;
    if (h == INVALID_HANDLE_VALUE)
    {
        return FC_INVALID_HANDLE;
    }
	buf = 0;
    bufLen = sizeof(INT32);
    realLen = 0;
    b_ret = ReadFile(h, &buf, bufLen, &realLen, NULL);
    if (!b_ret)
    {
        return FC_DEV_READ_FAILED;
    }
	// ���ص�ַ��Ӧ��
	*(int **)ppBuffer = (int *)buf;
	// ���س��ȸ�Ӧ��
    *nLen = realLen;
    return FC_SUCCESS;
}

//
// �ͷŽ��ջ�����
//
FCUINT FCM_ReleaseBuf(
    FCHANDLE hDev,
    void *pBuffer
    )
{
    BOOL b_ret;
    DWORD bufLen, realLen;
    PDEV_INFO di;
    HANDLE h;
    ULONG buf;
	PR_CTRL r_ctrl;

    // ������
    if (hDev == NULL)
    {
        return FC_INVALID_PARAMETER;
    }
    if (pBuffer == NULL)
    {
        return FC_INVALID_PARAMETER;
    }

    di = (PDEV_INFO)hDev;
    h = di->io.write;
    if (h == INVALID_HANDLE_VALUE)
    {
        return FC_INVALID_HANDLE;
    }
	// ע�⣺��R3������R0��header��ַ�Ĳ���
	//       ����R0���ܱ�֤R3��ַ������Ч��ַ
    // �ҵ�r_ctrl
	r_ctrl = (PR_CTRL)((int)pBuffer - sizeof(R_CTRL));
	// ȡ��header�ĵ�ַ
	buf = r_ctrl->r1.value;
    assert(buf != 0);
    bufLen = sizeof(ULONG);
    realLen = 0;
    b_ret = WriteFile(h, &buf, bufLen, &realLen, NULL);
    if (!b_ret)
    {
        return FC_DEV_WRITE_FAILED;
    }
    return FC_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// ʱͳ����ӿ�
///////////////////////////////////////////////////////////////////////////////
//
// ��ȡ�豸ʱ��
//
FCUINT FCM_TM_GetRtc(
    FCHANDLE hDev,
    FCTime *time
    )
{
    BOOL b_ret;
    DWORD bytes;
    ULONG inbuf_len, outbuf_len;
    PDEV_INFO di;
    HANDLE h;
    DEV_GET_RTC_REQ req;
    DEV_GET_RTC_RESP resp;

    // ������
    if (hDev == NULL)
    {
        return FC_INVALID_PARAMETER;
    }

    if (time == NULL)
    {
        return FC_INVALID_PARAMETER;
    }

    di = (PDEV_INFO)hDev;
    h = di->io.ioctrl;
    if (h == INVALID_HANDLE_VALUE)
    {
        return FC_FAILURE;
    }

    // ���ͻ�ȡFC�ڵ����ʱ�������
    inbuf_len = sizeof(DEV_GET_RTC_REQ);
    outbuf_len = sizeof(DEV_GET_RTC_RESP);
    memset(&req, 0, sizeof(DEV_GET_RTC_REQ));
    memset(&resp, 0, sizeof(DEV_GET_RTC_RESP));

    req.reserve = 0;
    b_ret = DeviceIoControl(h, IOCTL_DEV_GET_RTC, &req, inbuf_len, &resp, outbuf_len, &bytes, NULL);
    if (!b_ret)
    {
        return FC_DEV_IOCTRL_FAILED;
    }

    if (resp.result == IO_CTRL_RESP_NG)
    {
        return FC_IOCTRL_RESP_NG;
    }
    memcpy(time, &resp.time, sizeof(FCTime));
    return FC_SUCCESS;
}

//
// �����豸ʱ��
//
FCUINT FCM_TM_SetRtc(
    FCHANDLE hDev,
    FCTime *time
    )
{
    BOOL b_ret;
    DWORD bytes;
    ULONG inbuf_len, outbuf_len;
    PDEV_INFO di;
    HANDLE h;
    DEV_SET_RTC_REQ req;
    DEV_SET_RTC_RESP resp;

    // ������
    if (hDev == NULL)
    {
        return FC_INVALID_PARAMETER;
    }

    di = (PDEV_INFO)hDev;
    h = di->io.ioctrl;
    if (h == INVALID_HANDLE_VALUE)
    {
        return FC_FAILURE;
    }

    // ��������ʱ������
    inbuf_len = sizeof(DEV_SET_RTC_REQ);
    outbuf_len = sizeof(DEV_SET_RTC_RESP);
    memset(&req, 0, sizeof(DEV_SET_RTC_REQ));
    memset(&resp, 0, sizeof(DEV_SET_RTC_RESP));

    memcpy(&req.time, time, sizeof(FCTime));
    b_ret = DeviceIoControl(h, IOCTL_DEV_SET_RTC, &req, inbuf_len, &resp, outbuf_len, &bytes, NULL);
    if (!b_ret)
    {
        return FC_DEV_IOCTRL_FAILED;
    }

    if (resp.result == IO_CTRL_RESP_NG)
    {
        return FC_IOCTRL_RESP_NG;
    }
    return FC_SUCCESS;
}

//
// ��ʼ���
//
FCUINT FCM_DevStartMonitor(
    FCHANDLE hDev
    )
{
    BOOL b_ret;
    DWORD bytes;
    ULONG inbuf_len, outbuf_len;
    PDEV_INFO di;
    HANDLE h;
    DEV_MONITOR_START_REQ req;
    DEV_MONITOR_START_RESP resp;

    // ������
    if (hDev == NULL)
    {
        return FC_INVALID_PARAMETER;
    }

    di = (PDEV_INFO)hDev;
    h = di->io.ioctrl;
    if (h == INVALID_HANDLE_VALUE)
    {
        return FC_INVALID_HANDLE;
    }

    // ����״̬����ȷ
    if (di->state != ECS_CONFIG)
    {
        return FC_INVALID_DEV_STATE;
    }

    // ���ͼ�ؿ�ʼ������
    inbuf_len = sizeof(DEV_MONITOR_START_REQ);
    outbuf_len = sizeof(DEV_MONITOR_START_RESP);
    memset(&req, 0, sizeof(DEV_MONITOR_START_REQ));
    memset(&resp, 0, sizeof(DEV_MONITOR_START_RESP));

    b_ret = DeviceIoControl(h, IOCTL_DEV_MONITOR_START, &req, inbuf_len, &resp, outbuf_len, &bytes, NULL);
    if (!b_ret)
    {
        return FC_DEV_IOCTRL_FAILED;
    }

    if (resp.result == IO_CTRL_RESP_NG)
    {
        return FC_IOCTRL_RESP_NG;
    }
    return FC_SUCCESS;
}

//
// ֹͣ���
//
FCUINT FCM_DevStopMonitor(
    FCHANDLE hDev
    )
{
    BOOL b_ret;
    DWORD bytes;
    ULONG inbuf_len, outbuf_len;
    PDEV_INFO di;
    HANDLE h;
    DEV_MONITOR_STOP_REQ req;
    DEV_MONITOR_STOP_RESP resp;

    // ������
    if (hDev == NULL)
    {
        return FC_INVALID_PARAMETER;
    }

    di = (PDEV_INFO)hDev;
    h = di->io.ioctrl;
    if (h == INVALID_HANDLE_VALUE)
    {
        return FC_INVALID_HANDLE;
    }

    // ����״̬����ȷ
    if (di->state != ECS_CONFIG)
    {
        return FC_INVALID_DEV_STATE;
    }

    // ���ͼ�ؿ�ʼ������
    inbuf_len = sizeof(DEV_MONITOR_STOP_REQ);
    outbuf_len = sizeof(DEV_MONITOR_STOP_RESP);
    memset(&req, 0, sizeof(DEV_MONITOR_STOP_REQ));
    memset(&resp, 0, sizeof(DEV_MONITOR_STOP_RESP));

    b_ret = DeviceIoControl(h, IOCTL_DEV_MONITOR_STOP, &req, inbuf_len, &resp, outbuf_len, &bytes, NULL);
    if (!b_ret)
    {
        return FC_DEV_IOCTRL_FAILED;
    }

    if (resp.result == IO_CTRL_RESP_NG)
    {
        return FC_IOCTRL_RESP_NG;
    }
    return FC_SUCCESS;
}

//
// ��ӡ�����ĵ�����Ϣ
//
FCUINT FCM_DBG_DrvStastics(
    FCHANDLE hDev
    )
{
    BOOL b_ret;
    DWORD bytes;
    ULONG req, resp, inbuf_len, outbuf_len;
    PDEV_INFO di;
    HANDLE h;

    // ������
    if (hDev == NULL)
    {
        return FC_INVALID_PARAMETER;
    }

    di = (PDEV_INFO)hDev;
    h = di->io.ioctrl;
    if (h == INVALID_HANDLE_VALUE)
    {
        return FC_INVALID_HANDLE;
    }

    // ����״̬����ȷ
    if (di->state != ECS_CONFIG)
    {
        return FC_INVALID_DEV_STATE;
    }

    // ���ͼ�ؿ�ʼ������
    inbuf_len = sizeof(ULONG);
    outbuf_len = sizeof(ULONG);
    req = 0;
    resp = 0;
    b_ret = DeviceIoControl(h, IOCTL_DEV_DBG_STATISTICS, &req, inbuf_len, &resp, outbuf_len, &bytes, NULL);
    if (!b_ret)
    {
        return FC_DEV_IOCTRL_FAILED;
    }
    return FC_SUCCESS;
}