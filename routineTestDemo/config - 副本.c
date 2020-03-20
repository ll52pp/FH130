#include "..\fc_api.h"

/*
1 节点1 FCID=0x0100000 方案1 作为NCT 发送2个通道(BNC NRT) 接收2个通道(BNC NRT)
2 节点2 FCID=0x0100001 方案1 作为BNC 发送1个通道(NCT) 接收1个通道(NCT)
3 节点3 FCID=0x0100002 方案1 作为NRT 发送1个通道(NCT) 接收1个通道(NCT)
4 节点4 FCID=0x0100003 方案1 用于测试自环多通道收发字节数的正确性和性能，作为NCT 发送2个通道 接收2个通道
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

#define TEST_FC_ASM_IU_LENGTH_MAX   (16 * 1024 * 1024) /*ASM IU的最大字节长度*/
#endif

BLUE_PRINT gBluePrint[1] =
{
    {
    /*第[0]个蓝图*/
        {
            /*第[0]个配置块*/
            {
    /***************************************NCT***************************************/
                /*端口配置*/
                {
                    "NC",               /* 本地端口的名称 */
                    MB_NODE1_FCID,           /* 本地port_id */
                    1,                  /* 端口类型 1-ASM */
                    8,                  /* 信用 */
                    FC_NET_ROLE_NC,           /* 端口的网络管理角色*/
                    FC_NET_CLK_SYNC_ROLE_SERVER_MASTER,/* 时钟同步角色*/
                    150,               /* WDT定时周期*/
                    50,                /* WDT加载周期*/
                    50,                /* 时钟同步周期 */
                    2,                  /* 非数据块发送消息的总数 */
                    2,                  /* 非数据块接收消息的总数 */
                    0,                  /* 数据块发送消息的总数 */
                    0,                  /* 数据块接收消息的总数 */
                },
                {
                    {
                        "NC2BNC", /*消息名称*/
                        1,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE2_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "NC2NRT", /*消息名称*/
                        2,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                },
                {
                    {
                        "BNC2NC", /*消息名称*/
                        3,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE2_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "NRT2NC", /*消息名称*/
                        4,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                },
            },
            /*第[1]个配置块*/
            {
    /***************************************BNCT***************************************/
                /*端口配置*/
                {
                    "BNC",               /* 本地端口的名称 */
                    MB_NODE2_FCID,           /* 本地port_id */
                    1,                  /* 端口类型 1-ASM */
                    8,                  /* 信用 */
                    FC_NET_ROLE_BNC,           /* 端口的网络管理角色*/
                    FC_NET_CLK_SYNC_ROLE_CLIENT,/* 时钟同步角色*/
                    150,               /* WDT定时周期*/
                    50,                /* WDT加载周期*/
                    50,                /* 时钟同步周期 */
                    1,                  /* 非数据块发送消息的总数 */
                    1,                  /* 非数据块接收消息的总数 */
                    0,                  /* 数据块发送消息的总数 */
                    0,                  /* 数据块接收消息的总数 */
                },
                {
                    {
                        "BNC2NC", /*消息名称*/
                        3,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                },
                {
                    {
                        "NC2BNC", /*消息名称*/
                        1,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                },
            },
            /*第[2]个配置块*/
            {
    /***************************************NRT***************************************/
                /*端口配置*/
                {
                    "NRT",               /* 本地端口的名称 */
                    MB_NODE3_FCID,           /* 本地port_id */
                    1,                  /* 端口类型 1-ASM */
                    8,                  /* 信用 */
                    FC_NET_ROLE_NRT,           /* 端口的网络管理角色*/
                    FC_NET_CLK_SYNC_ROLE_CLIENT,/* 时钟同步角色*/
                    250,               /* WDT定时周期*/
                    50,                /* WDT加载周期*/
                    50,                /* 时钟同步周期 */
                    1,                  /* 非数据块发送消息的总数 */
                    1,                  /* 非数据块接收消息的总数 */
                    0,                  /* 数据块发送消息的总数 */
                    0,                  /* 数据块接收消息的总数 */
                },
                {
                    {
                        "NRT2NC", /*消息名称*/
                        4,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE3_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                },
                {
                    {
                        "NC2NRT", /*消息名称*/
                        2,           /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        1,  /*消息的目的ASM端口port_id*/
                    },
                },
            },
            /*第[3]个配置块*/
            {
    /***************************************NCT RING***************************************/
                /*端口配置*/
                {
                    "NCT_RING",               /* 本地端口的名称 */
                    MB_NODE4_FCID,           /* 本地port_id */
                    1,                  /* 端口类型 1-ASM */
                    8,                  /* 信用 */
                    FC_NET_ROLE_NC,           /* 端口的网络管理角色*/
                    FC_NET_CLK_SYNC_ROLE_SERVER_MASTER,/* 时钟同步角色*/
                    150,               /* WDT定时周期*/
                    50,                /* WDT加载周期*/
                    50,                /* 时钟同步周期 */
                    2,                  /* 非数据块发送消息的总数 */
                    2,                  /* 非数据块接收消息的总数 */
                    0,                  /* 数据块发送消息的总数 */
                    0,                  /* 数据块接收消息的总数 */
                },
                {
                    {
                        "NC2NC", /*消息名称*/
                        1,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE4_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE4_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "NC2NC", /*消息名称*/
                        2,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE4_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE4_FCID,  /*消息的目的ASM端口port_id*/
                    },
                },
                {
                    {
                        "NC2NC", /*消息名称*/
                        1,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE4_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "NC2NC", /*消息名称*/
                        2,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE4_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                },

            },
        },
    },
};
