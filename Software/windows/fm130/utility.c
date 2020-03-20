#include "precomp.h"

///////////////////////////////////////////////////////////////////////////////
// ���ܺ���
///////////////////////////////////////////////////////////////////////////////

//
// ö���豸
//
int EnumDevice()
{
    int idx, errid;
    errno_t errno;
    UINT ret;
    DWORD requiredSize;
    BOOLEAN status;
    const GUID *guid;

    HDEVINFO hDevInfo;
    SP_DEVICE_INTERFACE_DATA DeviceInterfaceData;
    PSP_DEVICE_INTERFACE_DETAIL_DATA pDeviceInterfaceDetail;
    SP_DEVINFO_DATA DeviceInfoData;
    PDEV_INFO devInfo;

    ret = 0;
    if (gDevManager.flag == 1)
    {
        return ret;
    }

    InitDevManager();
    devInfo = gDevManager.devInfo;
    guid = &GUID_DEVINTERFACE_FM130;
    idx = 0;
    do
    {
        PDEV_INFO d;
        d = &devInfo[idx];

        hDevInfo = SetupDiGetClassDevs(guid, NULL, NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
        if (hDevInfo == INVALID_HANDLE_VALUE)
        {
            ret = HERR_GUID_INVALID;
            break;
        }

        DeviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
        DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
        pDeviceInterfaceDetail = NULL;

        while (SetupDiEnumDeviceInterfaces(hDevInfo, NULL, guid, idx, &DeviceInterfaceData))
        {
            SetupDiGetDeviceInterfaceDetail(hDevInfo, &DeviceInterfaceData, NULL, 0, &requiredSize, NULL);
            errid = GetLastError();
            if (errid != ERROR_INSUFFICIENT_BUFFER)
            {
                ret = HERR_INSUFFICIENT_RESOURCE;
                break;
            }
            pDeviceInterfaceDetail = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(requiredSize);
            if (!pDeviceInterfaceDetail)
            {
                ret = HERR_MALLOC_FAILED;
                break;
            }
            __try
            {
                pDeviceInterfaceDetail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
                status = SetupDiGetDeviceInterfaceDetail(hDevInfo, &DeviceInterfaceData, pDeviceInterfaceDetail, requiredSize, NULL, &DeviceInfoData);
                if (!status)
                {
                    FREE_AND_NULL(pDeviceInterfaceDetail);
                    ret = HERR_GET_INTERFACE_FAILED;
                    break;
                }
                errno = _tcscpy_s(d->path, MAX_PATH, pDeviceInterfaceDetail->DevicePath);
                if (errno)
                {
                    ret = HERR_COPY_DATA_FAILED;
                    break;
                }
                // ��ʼ�����ĳ�Ա
                d->number = idx;
            }
            __finally
            {
                FREE_AND_NULL(pDeviceInterfaceDetail);
            }
            ++idx;
            if (idx > 0)
            {
                break;
            }
        }
    } while (FALSE);
    if (hDevInfo != INVALID_HANDLE_VALUE)
    {
        SetupDiDestroyDeviceInfoList(hDevInfo);
    }

    if (ret)
    {
        // ��ʼ��ʧ�ܣ��豸�������ָ�Ϊ��ʼֵ
        InitDevManager();
    }
    else
    {
        // ��ʼ���ɹ�
        if (idx == 0)
        {
            // û���ҵ��豸
            ret = HERR_NO_FOUND_DEVICE;
        }
        else
        {
            gDevManager.flag = 1;
        }
    }

    return ret;
}

// ȡ�ö�д���Ƶľ��
int GetIoHandle(PDEV_INFO di)
{
    int ret;
    HANDLE h;

    assert(di != NULL);
    ret = 0;
    if ((di->io.read != INVALID_HANDLE_VALUE)
        && (di->io.write != INVALID_HANDLE_VALUE)
        && (di->io.ioctrl != INVALID_HANDLE_VALUE))
    {
        return ret;
    }

    do
    {
        // read
        h = CreateFile(di->path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING, NULL);
        if (h == INVALID_HANDLE_VALUE)
		{
            ret = HERR_GET_READ_HANDLE_FAILED;
            break;
        }
        di->io.read = h;

        // write
        h = CreateFile(di->path, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING, NULL);
        if (h == INVALID_HANDLE_VALUE)
		{
            ret = HERR_GET_WRITE_HANDLE_FAILED;
            break;
        }
        di->io.write = h;

        // ioctrl
        h = CreateFile(di->path, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING, NULL);
        if (h == INVALID_HANDLE_VALUE)
		{
            ret = HERR_GET_IOCTRL_HANDLE_FAILED;
            break;
        }
        di->io.ioctrl = h;
    } while (FALSE);

    if (ret)
    {
        CloseIoHandle(di);
    }
    return ret;
}

// �������ȡ���豸��Ϣ
PDEV_INFO GetDevInfoByNumber(int number)
{
    PDEV_INFO di;

    di = &gDevManager.devInfo[number];
    if (di->path[0] == 0xFFFF) return NULL;
    if (di->number != number) return NULL;
    return di;
}

// ��ʼ���豸����
VOID InitDevManager()
{
    int idx;
    PDEV_INFO devInfo;
    PDEV_MANAGER m;

    m = &gDevManager;
    m->flag = 0;
    devInfo = gDevManager.devInfo;
    for (idx = 0; idx < DEV_NUM_MAX; ++idx)
    {
        PDEV_INFO d;
        d = &devInfo[idx];
        d->number = 0xFFFF;
        d->reserve = 0xFFFF;
        memset(d->path, 0xFF, sizeof(TCHAR) * MAX_PATH);
        d->io.read = INVALID_HANDLE_VALUE;
        d->io.write = INVALID_HANDLE_VALUE;
        d->io.ioctrl = INVALID_HANDLE_VALUE;

        d->int_recv_event = INVALID_HANDLE_VALUE;
        d->int_recv_thread = INVALID_HANDLE_VALUE;
        d->int_recv_func = NULL;
        d->int_recv_cbn = NULL;
        d->int_evt_event = INVALID_HANDLE_VALUE;
        d->int_evt_thread = INVALID_HANDLE_VALUE;
        d->int_evt_func = NULL;
        d->int_evt_cbn = NULL;

        d->state = ECS_NONE;
    }
}

// �ر��豸�������
VOID CloseIoHandle(PDEV_INFO di)
{
    if (di == NULL)
    {
        return;
    }
    CLOSE_HANDLE_AND_INVALID(di->io.read);
    CLOSE_HANDLE_AND_INVALID(di->io.write);
    CLOSE_HANDLE_AND_INVALID(di->io.ioctrl);
}

// �����жϽ��մ���
int IntRecvStart(PDEV_INFO di, FC_NP_RECV_FUNCPTR func)
{
    FCUINT ret;
    UINT t_id;

    assert(di != NULL && func != NULL);

    do
    {
        // ���ûص�����
        di->int_recv_func = func;
        // �����ź�
        di->int_recv_event = CreateEvent(NULL, FALSE, FALSE, NULL);
        assert(di->int_recv_event != INVALID_HANDLE_VALUE);
        if (di->int_recv_event == INVALID_HANDLE_VALUE)
        {
            ret = FC_DEV_CREATE_EVENT_FAILED;
            break;
        }
        // �����߳�
        di->int_recv_ctrl = THREAD_CTRL_RUN;
        di->int_recv_thread = (HANDLE)_beginthreadex(NULL, 0, IntRecvCallBack, di, 0, &t_id);
        assert(di->int_recv_thread != INVALID_HANDLE_VALUE);
        if (di->int_recv_thread == INVALID_HANDLE_VALUE)
        {
            ret = FC_DEV_START_THREAD_FAILED;
            break;
        }
        ret = FC_SUCCESS;
    } while (FALSE);

    if (ret)
    {
        IntRecvStop(di);
    }

    return ret;
}

// ֹͣ�жϽ��մ���
int IntRecvStop(PDEV_INFO di)
{
    DWORD reason;

    assert(di != NULL);
    di->int_recv_ctrl = THREAD_CTRL_STOP;
    if (di->int_recv_event != INVALID_HANDLE_VALUE)
    {
        assert(di->int_recv_thread != INVALID_HANDLE_VALUE);
        SetEvent(di->int_recv_event);
    }
    if (di->int_recv_thread != INVALID_HANDLE_VALUE)
    {
        reason = WaitForSingleObject(di->int_recv_thread, 2000);
        assert(reason == WAIT_OBJECT_0);
        if (reason != WAIT_OBJECT_0)
        {
            return FC_DEV_STOP_THREAD_FAILED;
        }
        di->int_recv_thread = INVALID_HANDLE_VALUE;
    }
    di->int_recv_func = NULL;
    CLOSE_HANDLE_AND_INVALID(di->int_recv_event);
    return FC_SUCCESS;
}

// �����ж���Ϣ����
int IntEvtStart(PDEV_INFO di, FC_INT_FUNCPTR func)
{
    FCUINT ret;
    UINT t_id;

    assert(di != NULL && func != NULL);

    do
    {
        // ���ûص�����
        di->int_evt_func = func;
        // �����ź�
        di->int_evt_event = CreateEvent(NULL, FALSE, FALSE, NULL);
        assert(di->int_evt_event != INVALID_HANDLE_VALUE);
        if (di->int_evt_event == INVALID_HANDLE_VALUE)
        {
            ret = FC_DEV_CREATE_EVENT_FAILED;
            break;
        }
        // �����߳�
        di->int_evt_ctrl = THREAD_CTRL_RUN;
        di->int_evt_thread = (HANDLE)_beginthreadex(NULL, 0, IntEvtCallBack, di, 0, &t_id);
        assert(di->int_evt_thread != INVALID_HANDLE_VALUE);
        if (di->int_evt_thread == INVALID_HANDLE_VALUE)
        {
            ret = FC_DEV_START_THREAD_FAILED;
            break;
        }
        ret = FC_SUCCESS;
    } while (FALSE);

    if (ret)
    {
        IntEvtStop(di);
    }

    return ret;
}

// ֹͣ�ж���Ϣ����
int IntEvtStop(PDEV_INFO di)
{
    DWORD reason;

    assert(di != NULL);
    di->int_evt_ctrl = THREAD_CTRL_STOP;
    if (di->int_evt_event != INVALID_HANDLE_VALUE)
    {
        assert(di->int_evt_thread != INVALID_HANDLE_VALUE);
        SetEvent(di->int_evt_event);
    }
    if (di->int_evt_thread != INVALID_HANDLE_VALUE)
    {
        reason = WaitForSingleObject(di->int_evt_thread, 2000);
        assert(reason == WAIT_OBJECT_0);
        if (reason != WAIT_OBJECT_0)
        {
            return FC_DEV_STOP_THREAD_FAILED;
        }
    }
    di->int_evt_func = NULL;
    CLOSE_HANDLE_AND_INVALID(di->int_evt_event);

    return FC_SUCCESS;
}

// �жϽ��մ���ص�����
UINT CALLBACK IntRecvCallBack(PVOID context)
{
    int r3_index, length;
    DWORD reason;
    char *buf;
    FCHANDLE hDev;
    PDEV_INFO di;
    PR_CTRL r_ctrl;
    PCBN_INT_RECV_CONTEXT cbn;

    di = (PDEV_INFO)context;
    hDev = (FCHANDLE)context;
    cbn = di->int_recv_cbn;

    while (TRUE)
    {
        // �ȴ��ź�
        reason = WaitForSingleObject(di->int_recv_event, INFINITE);
        // 1 �ж��Ƿ���Ҫֹͣ����
        if (di->int_recv_ctrl == THREAD_CTRL_STOP)
        {
            break;
        }
        // 2 �жϷ���ֵ
        if (reason != WAIT_OBJECT_0)
        {
            Sleep(100);
            continue;
        }
        // ����ź�״̬
        ResetEvent(di->int_recv_event);

        // ������ϢID���ص��û�ע������
        while (TRUE)
        {
			assert(cbn->r3_index != cbn->r0_index);
            // ����r3_index��ֵ
            r3_index = (cbn->r3_index + 1) % INT_RECV_BLOCK_MAX;
            if (r3_index == cbn->r0_index)
            {
				// ����ȫ����ȡ���ˣ����µȴ��ź�
                break;
            }
            cbn->r3_index = r3_index;
            buf = (char *)cbn->block[r3_index];
            r_ctrl = (PR_CTRL)(buf - sizeof(R_CTRL));
            length = r_ctrl->r0.u.length;

            // �ص�Ӧ�ò�ע��Ĵ�������
            if (di->int_recv_func)
            {
                di->int_recv_func(hDev, buf, length);
            }
			// ����
			cbn->block[r3_index] = 0;
        }
    }
    return 0;
}

// �ж��¼�����ص�����
UINT CALLBACK IntEvtCallBack(PVOID context)
{
    int idx, count;
    FCHANDLE hDev;
    DWORD reason;
    PDEV_INFO di;
    PCBN_INT_EVT_CONTEXT cbn;
    PCBN_EVT_DESC desc;
    

    di = (PDEV_INFO)context;
    hDev = (FCHANDLE)context;
    cbn = di->int_evt_cbn;
    count = INT_EVT_TYPE_MAX;

    while (TRUE)
    {
        // �ȴ������������ź�
        reason = WaitForSingleObject(di->int_evt_event, INFINITE);
        // 1 �ж��Ƿ���Ҫֹͣ����
        if (di->int_evt_ctrl == THREAD_CTRL_STOP)
        {
            break;
        }
        // 2 �жϷ���ֵ
        if (reason != WAIT_OBJECT_0)
        {
            Sleep(100);
            continue;
        }
        if (cbn == NULL)
        {
            // Ϊʲô�ᵽ���
            if (di->int_evt_event != INVALID_HANDLE_VALUE)
            {
                // ����ź�
                ResetEvent(di->int_evt_event);
            }
            continue;
        }

        // �����ж�֪ͨ���ص��û���ע������
        if (InterlockedCompareExchange(&cbn->flag, INT_CONTEXT_USE, INT_CONTEXT_IDLE) != INT_CONTEXT_IDLE)
        {
            assert(FALSE);
        }
        for (idx = 0; idx < count; ++idx)
        {
            desc = &cbn->desc[idx];
            if (desc->int_code == 0)
            {
                continue;
            }
            if (di->int_evt_func)
            {
                di->int_evt_func(hDev, desc->int_code, desc->param[0]);
            }
            // �ж�������
            desc->int_code = 0;
        }
        // ����ź�
        ResetEvent(di->int_evt_event);
        // �ָ�������״̬����������ʹ��
        if (InterlockedCompareExchange(&cbn->flag, INT_CONTEXT_IDLE, INT_CONTEXT_USE) != INT_CONTEXT_USE)
        {
            assert(FALSE);
        }
    }

    return 0;
}