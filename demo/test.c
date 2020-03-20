INT32 g_exit = 0, g_msg_id, g_send_len;
SEM_ID g_sem;

void test()
{
	INT32 id;
	FCUINT ret, devId;
	FCHANDLE hDev;

	do
	{
		devId = 0;
		hDev = NULL;
		ret = FC_NP_Open(&hDev, devId); if (ret) break;
		ret = FC_NP_Close(hDev); if (ret) break;
		ret = FC_NP_ConfigMode(hDev, CONFIG_MODE_PROJECT); if (ret) break;
		ret = FC_NP_LoadConfig(hDev, 0, 0); if (ret) break;

		g_msg_id = 1;
		g_send_len = 1024;
		g_send_sem = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
		g_recv_sem = semBCreate(SEM_Q_FIFO, SEM_EMPTY);

		id = taskSpawn("TS_SEND", 100, 0, 40960, SendTask, (int)ddc, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		if (id == ERROR)
		{
			ret = FC_FAILURE;
			break;
		}

		id = taskSpawn("TS_RECV", 100, 0, 40960, RecvTask, (int)ddc, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		if (id == ERROR)
		{
			ret = FC_FAILURE;
			break;
		}

		while (g_exit == 0) taskDelay(10);
	} while (0);

	if (ret)
	{
		printf("ret=x0%08x\n", ret);
	}
	
	FC_NP_DevClose(hDev);
}

/*发送任务回调*/
int SendTask(VOID *context)
{
	FCINT send_count;
	FCUINT ret, msgId, nLen;
	FCUCHAR *pMsg;
	FCHANDLE hDev;

	hDev = (FCHANDLE)context;
	pMsg = malloc(16 * 1024 * 1024);
	if (pMsg == null)
	{
		return ERROR;
	}

	while (g_exit == 0)
	{
		semTake(g_recv_sem, WAIT_FOREVER);
		if (g_exit == 1) break;

		msgId = g_msg_id;
		nLen = g_send_len;
		ret = FC_NP_SendMsg(hDev, msgId, pMsg, nLen);
		if (ret)
		{
			taskDelay(10);
			continue;
		}

		semGive(g_send_sem);
	}

	return OK;
}

/*接收任务回调*/
int HbaDemoRecvTask(VOID *context)
{
	FCINT send_count;
	FCUINT ret, msgId, nLen;
	FCUCHAR *pMsg;
	FCHANDLE hDev;

	hDev = (FCHANDLE)context;
	pMsg = malloc(16 * 1024 * 1024);
	if (pMsg == null)
	{
		return ERROR;
	}

	semGive(g_recv_sem);

	while (g_exit == 0)
	{
		semTake(g_send_sem, WAIT_FOREVER);
		if (g_exit == 1) break;

		msgId = g_msg_id;
		nLen = g_send_len;
		ret = FC_NP_RecvMsg(hDev, msgId, pMsg, &nLen);
		if (ret)
		{
			taskDelay(10);
			continue;
		}

		semGive(g_recv_sem);
	}

	return OK;
}

void exit()
{
	g_exit = 1;
	semGive(g_send_sem);
	semGive(g_recv_sem);
}