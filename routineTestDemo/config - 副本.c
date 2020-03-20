#include "..\fc_api.h"

/*
1 �ڵ�1 FCID=0x0100000 ����1 ��ΪNCT ����2��ͨ��(BNC NRT) ����2��ͨ��(BNC NRT)
2 �ڵ�2 FCID=0x0100001 ����1 ��ΪBNC ����1��ͨ��(NCT) ����1��ͨ��(NCT)
3 �ڵ�3 FCID=0x0100002 ����1 ��ΪNRT ����1��ͨ��(NCT) ����1��ͨ��(NCT)
4 �ڵ�4 FCID=0x0100003 ����1 ���ڲ����Ի���ͨ���շ��ֽ�������ȷ�Ժ����ܣ���ΪNCT ����2��ͨ�� ����2��ͨ��
*/

#define MB_NODE1_FCID 0x010000
#define MB_NODE2_FCID 0x010001
#define MB_NODE3_FCID 0x010002
#define MB_NODE4_FCID 0x010003

#if 1/*jin.liu 20180307*/
#define MAX_MSG_LENGTH_1    (4088)
#define MAX_MSG_LENGTH_2    (4*1024*1024)/*(4*1024*1024)*/
#define MAX_MSG_LENGTH_3    (16*1024*1024)
#define MAX_MSG_LENGTH  MAX_MSG_LENGTH_3

#define PRIORITY_DIFF_1 (MSG_TYPE_STREAM_MSG)/*(FC_MSG_TYPE_RAW)*/
#define PRIORITY_DIFF_2 (MSG_TYPE_STREAM_MSG)/*(FC_MSG_TYPE_EVENT)*/

#define TEST_FC_ASM_IU_LENGTH_MAX   (16 * 1024 * 1024) /*ASM IU������ֽڳ���*/
#endif

BLUE_PRINT gBluePrint[1] =
{
    {
    /*��[0]����ͼ*/
        {
            /*��[0]�����ÿ�*/
            {
    /***************************************NCT***************************************/
                /*�˿�����*/
                {
                    "NC",               /* ���ض˿ڵ����� */
                    MB_NODE1_FCID,           /* ����port_id */
                    1,                  /* �˿����� 1-ASM */
                    8,                  /* ���� */
                    FC_NET_ROLE_NC,           /* �˿ڵ���������ɫ*/
                    FC_NET_CLK_SYNC_ROLE_SERVER_MASTER,/* ʱ��ͬ����ɫ*/
                    150,               /* WDT��ʱ����*/
                    50,                /* WDT��������*/
                    50,                /* ʱ��ͬ������ */
                    2,                  /* �����ݿ鷢����Ϣ������ */
                    2,                  /* �����ݿ������Ϣ������ */
                    0,                  /* ���ݿ鷢����Ϣ������ */
                    0,                  /* ���ݿ������Ϣ������ */
                },
                {
                    {
                        "NC2BNC", /*��Ϣ����*/
                        1,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE2_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "NC2NRT", /*��Ϣ����*/
                        2,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE3_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                },
                {
                    {
                        "BNC2NC", /*��Ϣ����*/
                        3,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE2_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "NRT2NC", /*��Ϣ����*/
                        4,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE3_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                },
            },
            /*��[1]�����ÿ�*/
            {
    /***************************************BNCT***************************************/
                /*�˿�����*/
                {
                    "BNC",               /* ���ض˿ڵ����� */
                    MB_NODE2_FCID,           /* ����port_id */
                    1,                  /* �˿����� 1-ASM */
                    8,                  /* ���� */
                    FC_NET_ROLE_BNC,           /* �˿ڵ���������ɫ*/
                    FC_NET_CLK_SYNC_ROLE_CLIENT,/* ʱ��ͬ����ɫ*/
                    150,               /* WDT��ʱ����*/
                    50,                /* WDT��������*/
                    50,                /* ʱ��ͬ������ */
                    1,                  /* �����ݿ鷢����Ϣ������ */
                    1,                  /* �����ݿ������Ϣ������ */
                    0,                  /* ���ݿ鷢����Ϣ������ */
                    0,                  /* ���ݿ������Ϣ������ */
                },
                {
                    {
                        "BNC2NC", /*��Ϣ����*/
                        3,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE2_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                },
                {
                    {
                        "NC2BNC", /*��Ϣ����*/
                        1,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                },
            },
            /*��[2]�����ÿ�*/
            {
    /***************************************NRT***************************************/
                /*�˿�����*/
                {
                    "NRT",               /* ���ض˿ڵ����� */
                    MB_NODE3_FCID,           /* ����port_id */
                    1,                  /* �˿����� 1-ASM */
                    8,                  /* ���� */
                    FC_NET_ROLE_NRT,           /* �˿ڵ���������ɫ*/
                    FC_NET_CLK_SYNC_ROLE_CLIENT,/* ʱ��ͬ����ɫ*/
                    250,               /* WDT��ʱ����*/
                    50,                /* WDT��������*/
                    50,                /* ʱ��ͬ������ */
                    1,                  /* �����ݿ鷢����Ϣ������ */
                    1,                  /* �����ݿ������Ϣ������ */
                    0,                  /* ���ݿ鷢����Ϣ������ */
                    0,                  /* ���ݿ������Ϣ������ */
                },
                {
                    {
                        "NRT2NC", /*��Ϣ����*/
                        4,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE3_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE1_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                },
                {
                    {
                        "NC2NRT", /*��Ϣ����*/
                        2,           /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE1_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        1,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                },
            },
            /*��[3]�����ÿ�*/
            {
    /***************************************NCT RING***************************************/
                /*�˿�����*/
                {
                    "NCT_RING",               /* ���ض˿ڵ����� */
                    MB_NODE4_FCID,           /* ����port_id */
                    1,                  /* �˿����� 1-ASM */
                    8,                  /* ���� */
                    FC_NET_ROLE_NC,           /* �˿ڵ���������ɫ*/
                    FC_NET_CLK_SYNC_ROLE_SERVER_MASTER,/* ʱ��ͬ����ɫ*/
                    150,               /* WDT��ʱ����*/
                    50,                /* WDT��������*/
                    50,                /* ʱ��ͬ������ */
                    2,                  /* �����ݿ鷢����Ϣ������ */
                    2,                  /* �����ݿ������Ϣ������ */
                    0,                  /* ���ݿ鷢����Ϣ������ */
                    0,                  /* ���ݿ������Ϣ������ */
                },
                {
                    {
                        "NC2NC", /*��Ϣ����*/
                        1,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE4_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE4_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                    {
                        "NC2NC", /*��Ϣ����*/
                        2,           /*��ϢID*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����*/
                        PRIORITY_LEVEL_0,         /*��Ϣ���ȼ�*/
                        MB_NODE4_FCID,  /*��Ϣ��ԴASM�˿�port_id*/
                        MB_NODE4_FCID,  /*��Ϣ��Ŀ��ASM�˿�port_id*/
                    },
                },
                {
                    {
                        "NC2NC", /*��Ϣ����*/
                        1,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE4_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                    {
                        "NC2NC", /*��Ϣ����*/
                        2,         /*��ϢID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* ����*/
                        MSG_TYPE_STREAM_MSG,         /*��Ϣ����  �¼�*/
                        MB_NODE4_FCID,  /* ��Ϣ��ԴASM�˿�port_id */
                        1          /*��Ϣ��ˢ�������־*/
                    },
                },

            },
        },
    },
};
