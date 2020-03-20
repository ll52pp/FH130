#include "..\fc_api.h"
#define MB_NODE1_FCID 0x10000
#define MB_NODE2_FCID 0x10001
#define MB_NODE3_FCID 0x10002

#define TEST_FC_ASM_IU_LENGTH_MAX   (16 * 1024 * 1024) /*ASM IU������ֽڳ���*/


/*���ñ�*/
BLUE_PRINT gBluePrint[1] =
{
    {
        /*��[0]����ͼ*/
        {
            /*��[0]�����ÿ�*/
/***************************************NCT***************************************/
            {
                /*�˿�����*/
                {
                    "NC",               /* ���ض˿ڵ����� */
                    MB_NODE1_FCID,           /* ����port_id */
                    1,                  /* �˿����� 1-ASM */
                    8,                  /* ���� */
                    FC_NET_ROLE_NC,           /* �˿ڵ���������ɫ*/
                    FC_NET_CLK_SYNC_ROLE_SERVER_MASTER,/* ʱ��ͬ����ɫ*/
                    /*100 * 60 * 1000*/1500,               /* WDT��ʱ����*/
                    /*50 * 60 * 1000*/500,                /* WDT��������*/
                    100,                /* ʱ��ͬ������ */
                    256,                  /* �����ݿ鷢����Ϣ������ */
                    256,                  /* �����ݿ������Ϣ������ */
                    0,                  /* ���ݿ鷢����Ϣ������ */
                    0,                  /* ���ݿ������Ϣ������ */
                },
                {
                    {
                        "to_nrt", /*��Ϣ����*/
                        1,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        2,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        3,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        4,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        5,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        6,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        7,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        8,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        9,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        10,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        11,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        12,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        13,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        14,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        15,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        16,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        17,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        18,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        19,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        20,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        21,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        22,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        23,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        24,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        25,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        26,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        27,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        28,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        29,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        30,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        31,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        32,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        33,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        34,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        35,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        36,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        37,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        38,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        39,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        40,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        41,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        42,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        43,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        44,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        45,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        46,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        47,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        48,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        49,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        50,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        51,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        52,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        53,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        54,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        55,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        56,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        57,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        58,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        59,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        60,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        61,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        62,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        63,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        64,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        65,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        66,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        67,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        68,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        69,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        70,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        71,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        72,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        73,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        74,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        75,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        76,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        77,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        78,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        79,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        80,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        81,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        82,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        83,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        84,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        85,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        86,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        87,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        88,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        89,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        90,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        91,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        92,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        93,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        94,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        95,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        96,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        97,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        98,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        99,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        100,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        101,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        102,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        103,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        104,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        105,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        106,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        107,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        108,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        109,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        110,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        111,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        112,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        113,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        114,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        115,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        116,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        117,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        118,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        119,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        120,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        121,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        122,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        123,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        124,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        125,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        126,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        127,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        128,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        129,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        130,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        131,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        132,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        133,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        134,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        135,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        136,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        137,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        138,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        139,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        140,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        141,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        142,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        143,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        144,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        145,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        146,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        147,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        148,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        149,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        150,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        151,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        152,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        153,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        154,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        155,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        156,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        157,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        158,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        159,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        160,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        161,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        162,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        163,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        164,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        165,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        166,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        167,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        168,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        169,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        170,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        171,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        172,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        173,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        174,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        175,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        176,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        177,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        178,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        179,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        180,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        181,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        182,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        183,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        184,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        185,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        186,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        187,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        188,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        189,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        190,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        191,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        192,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        193,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        194,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        195,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        196,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        197,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        198,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        199,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        200,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        201,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        202,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        203,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        204,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        205,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        206,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        207,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        208,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        209,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        210,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        211,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        212,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        213,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        214,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        215,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        216,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        217,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        218,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        219,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        220,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        221,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        222,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        223,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        224,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        225,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        226,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        227,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        228,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        229,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        230,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        231,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        232,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        233,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        234,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        235,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        236,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        237,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        238,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        239,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        240,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        241,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        242,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        243,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        244,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        245,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        246,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        247,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        248,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        249,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        250,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        251,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        252,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        253,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        254,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        255,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        256,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                },
                {
                    {
                        "from_nct", /*��Ϣ����*/
                        1,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        2,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        3,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        4,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        5,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        6,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        7,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        8,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        9,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        10,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        11,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        12,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        13,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        14,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        15,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        16,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        17,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        18,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        19,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        20,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        21,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        22,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        23,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        24,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        25,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        26,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        27,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        28,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        29,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        30,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        31,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        32,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        33,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        34,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        35,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        36,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        37,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        38,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        39,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        40,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },                    
                    {
                        "from_nct", /*��Ϣ����*/
                        41,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        42,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        43,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        44,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        45,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        46,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        47,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        48,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        49,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        50,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        51,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        52,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        53,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        54,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        55,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        56,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        57,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        58,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        59,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        60,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        61,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        62,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        63,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        64,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        65,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        66,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        67,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        68,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        69,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        70,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        71,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        72,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        73,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        74,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        75,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        76,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        77,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        78,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        79,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        80,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        81,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        82,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        83,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        84,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        85,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        86,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        87,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        88,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        89,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        90,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        91,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        92,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        93,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        94,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        95,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        96,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        97,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        98,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        99,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        100,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        101,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        102,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        103,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        104,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        105,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        106,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        107,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        108,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        109,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        110,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        111,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        112,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        113,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        114,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        115,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        116,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        117,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        118,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        119,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        120,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        121,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        122,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        123,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        124,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        125,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        126,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        127,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        128,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        129,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        130,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        131,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        132,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        133,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        134,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        135,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        136,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        137,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        138,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        139,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        140,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        141,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        142,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        143,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        144,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        145,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        146,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        147,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        148,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        149,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        150,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        151,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        152,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        153,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        154,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        155,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        156,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        157,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        158,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        159,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        160,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        161,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        162,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        163,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        164,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        165,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        166,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        167,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        168,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        169,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        170,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        171,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        172,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        173,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        174,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        175,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        176,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        177,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        178,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        179,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        180,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        181,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        182,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        183,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        184,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        185,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        186,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        187,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        188,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        189,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        190,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        191,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        192,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        193,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        194,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        195,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        196,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        197,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        198,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        199,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        200,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        201,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        202,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        203,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        204,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        205,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        206,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        207,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        208,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        209,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        210,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        211,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        212,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        213,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        214,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        215,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        216,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        217,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        218,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        219,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        220,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        221,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        222,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        223,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        224,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        225,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        226,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        227,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        228,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        229,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        230,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        231,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        232,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        233,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        234,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        235,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        236,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        237,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        238,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        239,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        240,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        241,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        242,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        243,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        244,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        245,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        246,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        247,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        248,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        249,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        250,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        251,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        252,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        253,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        254,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        255,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        256,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                },
            },
/***************************************BNCT***************************************/
            {
                /*�˿�����*/
                {
                    "BNC",              /* ���ض˿ڵ����� */
                    MB_NODE2_FCID,           /* ����port_id */
                    1,                  /* �˿����� 1-ASM */
                    8,                  /* ���� */
                    FC_NET_ROLE_BNC,           /* �˿ڵ���������ɫ*/
                    FC_NET_CLK_SYNC_ROLE_CLIENT,/* ʱ��ͬ����ɫ*/
                    /*10*60*1000*/1500,               /* WDT��ʱ����*/
                    500,                /* WDT��������*/
                    100,                /* ʱ��ͬ������ */
                    256,                  /* �����ݿ鷢����Ϣ������ */
                    256,                  /* �����ݿ������Ϣ������ */
                    0,                  /* ���ݿ鷢����Ϣ������ */
                    0,                  /* ���ݿ������Ϣ������ */
                },
                
                {
                    {
                        "to_nrt", /*��Ϣ����*/
                        1,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        2,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        3,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        4,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        5,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        6,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        7,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        8,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        9,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        10,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        11,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        12,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        13,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        14,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        15,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        16,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        17,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        18,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        19,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        20,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        21,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        22,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        23,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        24,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        25,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        26,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        27,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        28,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        29,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        30,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        31,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        32,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        33,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        34,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        35,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        36,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        37,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        38,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        39,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        40,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        41,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        42,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        43,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        44,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        45,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        46,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        47,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        48,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        49,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        50,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        51,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        52,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        53,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        54,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        55,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        56,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        57,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        58,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        59,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        60,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        61,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        62,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        63,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        64,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        65,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        66,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        67,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        68,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        69,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        70,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        71,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        72,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        73,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        74,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        75,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        76,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        77,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        78,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        79,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        80,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        81,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        82,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        83,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        84,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        85,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        86,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        87,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        88,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        89,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        90,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        91,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        92,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        93,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        94,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        95,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        96,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        97,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        98,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        99,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        100,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        101,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        102,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        103,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        104,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        105,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        106,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        107,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        108,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        109,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        110,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        111,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        112,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        113,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        114,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        115,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        116,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        117,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        118,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        119,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        120,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        121,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        122,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        123,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        124,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        125,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        126,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        127,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        128,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        129,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        130,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        131,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        132,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        133,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        134,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        135,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        136,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        137,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        138,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        139,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        140,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        141,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        142,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        143,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        144,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        145,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        146,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        147,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        148,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        149,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        150,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        151,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        152,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        153,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        154,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        155,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        156,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        157,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        158,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        159,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        160,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        161,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        162,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        163,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        164,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        165,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        166,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        167,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        168,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        169,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        170,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        171,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        172,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        173,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        174,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        175,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        176,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        177,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        178,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        179,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        180,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        181,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        182,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        183,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        184,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        185,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        186,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        187,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        188,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        189,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        190,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        191,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        192,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        193,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        194,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        195,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        196,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        197,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        198,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        199,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        200,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        201,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        202,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        203,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        204,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        205,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        206,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        207,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        208,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        209,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        210,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        211,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        212,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        213,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        214,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        215,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        216,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        217,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        218,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        219,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        220,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        221,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        222,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        223,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        224,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        225,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        226,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        227,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        228,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        229,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        230,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        231,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        232,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        233,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        234,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        235,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        236,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        237,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        238,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        239,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        240,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        241,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        242,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        243,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        244,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        245,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        246,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        247,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        248,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        249,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        250,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        251,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        252,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        253,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        254,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        255,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        256,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                },
                {
                    {
                        "from_nct", /*��Ϣ����*/
                        1,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        2,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        3,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        4,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        5,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        6,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        7,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        8,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        9,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        10,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        11,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        12,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        13,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        14,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        15,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        16,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        17,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        18,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        19,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        20,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        21,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        22,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        23,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        24,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        25,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        26,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        27,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        28,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        29,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        30,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        31,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        32,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        33,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        34,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        35,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        36,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        37,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        38,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        39,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        40,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        41,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        42,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        43,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        44,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        45,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        46,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        47,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        48,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        49,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        50,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        51,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        52,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        53,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        54,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        55,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        56,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        57,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        58,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        59,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        60,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        61,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        62,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        63,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        64,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        65,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        66,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        67,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        68,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        69,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                       70,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        71,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        72,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        73,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        74,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        75,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        76,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        77,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        78,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        79,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        80,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        81,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        82,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        83,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        84,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        85,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        86,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        87,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        88,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        89,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        90,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        91,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        92,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        93,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        94,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        95,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        96,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        97,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        98,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        99,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        100,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        101,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        102,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        103,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        104,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        105,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        106,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        107,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        108,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        109,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        110,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        111,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        112,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        113,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        114,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        115,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        116,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        117,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        118,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        119,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        120,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        121,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        122,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        123,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        124,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        125,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        126,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        127,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        128,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        129,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        130,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        131,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        132,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        133,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        134,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        135,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        136,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        137,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        138,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        139,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        140,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        141,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        142,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        143,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        144,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        145,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        146,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        147,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        148,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        149,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        150,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        151,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        152,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        153,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        154,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        155,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        156,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        157,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        158,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        159,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        160,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        161,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        162,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        163,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        164,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        165,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        166,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        167,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        168,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        169,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        170,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        171,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        172,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        173,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        174,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        175,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        176,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        177,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        178,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        179,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        180,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        181,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        182,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        183,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        184,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        185,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        186,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        187,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        188,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        189,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        190,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        191,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        192,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        193,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        194,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        195,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        196,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        197,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        198,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        199,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        200,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        201,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        202,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        203,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        204,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        205,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        206,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        207,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        208,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        209,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        210,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        211,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        212,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        213,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        214,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        215,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        216,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        217,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        218,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        219,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        220,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        221,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        222,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        223,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        224,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        225,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        226,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        227,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        228,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        229,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        230,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        231,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        232,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        233,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        234,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        235,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        236,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        237,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        238,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        239,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        240,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        241,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        242,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        243,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        244,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        245,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        246,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        247,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        248,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        249,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        250,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        251,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        252,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        253,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        254,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        255,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        256,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                },
            },
/***************************************NRT***************************************/
            {
                /*�˿�����*/
                {
                    "NRT",              /* ���ض˿ڵ����� */
                    MB_NODE2_FCID,           /* ����port_id */
                    1,                  /* �˿����� 1-ASM */
                    8,                  /* ���� */
                    FC_NET_ROLE_NRT,           /* �˿ڵ���������ɫ*/
                    FC_NET_CLK_SYNC_ROLE_CLIENT,/* ʱ��ͬ����ɫ*/
                    100*60*1000/*2500*/,               /* WDT��ʱ����*/
                    50*60*1000/*500*/,                /* WDT��������*/
                    100,                /* ʱ��ͬ������ */
                    256,                  /* �����ݿ鷢����Ϣ������ */
                    256,                  /* �����ݿ������Ϣ������ */
                    0,                  /* ���ݿ鷢����Ϣ������ */
                    0,                  /* ���ݿ������Ϣ������ */
                },
                {
                    {
                        "to_nrt", /*��Ϣ����*/
                        1,           /*��ϢID*/
                        MSG_TYPE_URGENCY_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_3,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        2,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        3,           /*��ϢID*/
                        MSG_TYPE_URGENCY_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        4,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        5,           /*��ϢID*/
                        MSG_TYPE_EVENT_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_2,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        6,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        7,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        8,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        9,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        10,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        11,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        12,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        13,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        14,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        15,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        16,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        17,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        18,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        19,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        20,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        21,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        22,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        23,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        24,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        25,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        26,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        27,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        28,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        29,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        30,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        31,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        32,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        33,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        34,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        35,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        36,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        37,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        38,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        39,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        40,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        41,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        42,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        43,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        44,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        45,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        46,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        47,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        48,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        49,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        50,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        51,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        52,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        53,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        54,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        55,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        56,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        57,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        58,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        59,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        60,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        61,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        62,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        63,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        64,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        65,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        66,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        67,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        68,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        69,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        70,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        71,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        72,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        73,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        74,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        75,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        76,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        77,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        78,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        79,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        80,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        81,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        82,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        83,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        84,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        85,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        86,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        87,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        88,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        89,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        90,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        91,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        92,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        93,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        94,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        95,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        96,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        97,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        98,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        99,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        100,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        101,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        102,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        103,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        104,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        105,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        106,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        107,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        108,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        109,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        110,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        111,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        112,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        113,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        114,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        115,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        116,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        117,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        118,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        119,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        120,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        121,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        122,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        123,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        124,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        125,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        126,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        127,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        128,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        129,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        130,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        131,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        132,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        133,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        134,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        135,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        136,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        137,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        138,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        139,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        140,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        141,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        142,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        143,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        144,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        145,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        146,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        147,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        148,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        149,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        150,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        151,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        152,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        153,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        154,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        155,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        156,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        157,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        158,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        159,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        160,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        161,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        162,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        163,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        164,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        165,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        166,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        167,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        168,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        169,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        170,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        171,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        172,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        173,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        174,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        175,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        176,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        177,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        178,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        179,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        180,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        181,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        182,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        183,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        184,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        185,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        186,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        187,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        188,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        189,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        190,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        191,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        192,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        193,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        194,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        195,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        196,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        197,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        198,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        199,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        200,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        201,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        202,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        203,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        204,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        205,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        206,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        207,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        208,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        209,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        210,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        211,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        212,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        213,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        214,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        215,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        216,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        217,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        218,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        219,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        220,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        221,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        222,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        223,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        224,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        225,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        226,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        227,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        228,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        229,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        230,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        231,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        232,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        233,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        234,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        235,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        236,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        237,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        238,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        239,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        240,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        241,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        242,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        243,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        244,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        245,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        246,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        247,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        248,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        249,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        250,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        251,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        252,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        253,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        254,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        255,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "to_nrt", /*��Ϣ����*/
                        256,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                },
                
                {
                    {
                        "from_nct", /*��Ϣ����*/
                        1,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        2,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        3,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        4,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        5,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        6,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        7,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        8,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        9,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        10,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        11,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        12,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        13,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        14,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        15,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        16,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        17,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        18,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        19,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        20,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        21,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        22,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        23,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        24,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        25,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        26,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        27,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        28,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        29,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        30,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        31,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        32,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        33,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        34,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        35,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        36,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        37,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        38,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        39,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        40,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        41,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        42,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        43,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        44,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        45,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        46,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        47,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        48,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        49,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        50,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        51,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        52,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        53,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        54,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        55,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        56,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        57,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        58,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        59,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        60,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        61,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        62,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        63,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        64,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        65,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        66,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        67,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        68,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        69,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        70,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        71,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        72,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        73,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        74,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        75,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        76,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        77,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        78,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        79,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        80,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        81,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        82,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        83,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        84,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        85,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        86,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        87,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        88,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        89,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        90,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        91,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        92,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        93,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        94,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        95,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        96,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        97,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        98,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        99,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        100,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        101,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        102,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        103,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        104,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        105,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        106,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        107,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        108,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        109,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        110,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        111,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        112,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        113,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        114,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        115,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        116,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        117,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        118,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        119,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        120,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        121,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        122,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        123,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        124,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        125,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        126,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        127,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        128,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        129,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        130,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        131,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        132,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        133,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        134,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        135,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        136,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        137,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        138,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        139,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        140,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        141,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        142,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        143,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        144,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        145,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        146,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        147,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        148,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        149,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        150,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        151,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        152,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        153,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        154,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        155,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        156,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        157,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        158,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        159,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        160,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        161,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        162,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        163,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        164,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        165,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        166,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        167,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        168,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        169,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        170,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        171,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        172,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        173,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        174,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        175,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        176,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        177,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        178,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        179,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        180,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        181,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        182,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        183,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        184,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        185,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        186,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        187,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        188,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        189,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        190,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        191,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        192,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        193,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        194,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        195,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        196,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        197,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        198,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        199,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        200,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        201,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        202,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        203,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        204,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        205,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        206,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        207,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        208,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        209,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        210,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        211,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        212,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        213,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        214,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        215,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        216,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        217,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        218,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        219,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        220,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        221,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        222,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        223,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        224,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        225,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        226,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        227,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        228,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        229,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        230,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        231,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        232,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        233,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        234,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        235,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        236,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        237,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        238,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        239,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        240,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        241,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        242,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        243,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        244,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        245,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        246,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        247,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        248,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        249,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        250,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        251,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        252,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        253,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        254,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        255,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "from_nct", /*��Ϣ����*/
                        256,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                },
            },
        },
    },
};


