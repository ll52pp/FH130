#include "..\fc_api.h"
#define MB_NODE1_FCID 0x10000
#define MB_NODE2_FCID 0x10001
#define MB_NODE3_FCID 0x10002

#define TEST_FC_ASM_IU_LENGTH_MAX   (16 * 1024 * 1024) /*ASM IU的最大字节长度*/


/*配置表*/
BLUE_PRINT gBluePrint[1] =
{
    {
        /*第[0]个蓝图*/
        {
            /*第[0]个配置块*/
/***************************************NCT***************************************/
            {
                /*端口配置*/
                {
                    "NC",               /* 本地端口的名称 */
                    MB_NODE1_FCID,           /* 本地port_id */
                    1,                  /* 端口类型 1-ASM */
                    8,                  /* 信用 */
                    FC_NET_ROLE_NC,           /* 端口的网络管理角色*/
                    FC_NET_CLK_SYNC_ROLE_SERVER_MASTER,/* 时钟同步角色*/
                    /*100 * 60 * 1000*/1500,               /* WDT定时周期*/
                    /*50 * 60 * 1000*/500,                /* WDT加载周期*/
                    100,                /* 时钟同步周期 */
                    256,                  /* 非数据块发送消息的总数 */
                    256,                  /* 非数据块接收消息的总数 */
                    0,                  /* 数据块发送消息的总数 */
                    0,                  /* 数据块接收消息的总数 */
                },
                {
                    {
                        "to_nrt", /*消息名称*/
                        1,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        2,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        3,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        4,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        5,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        6,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        7,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        8,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        9,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        10,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        11,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        12,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        13,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        14,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        15,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        16,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        17,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        18,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        19,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        20,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        21,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        22,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        23,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        24,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        25,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        26,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        27,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        28,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        29,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        30,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        31,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        32,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        33,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        34,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        35,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        36,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        37,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        38,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        39,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        40,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        41,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        42,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        43,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        44,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        45,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        46,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        47,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        48,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        49,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        50,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        51,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        52,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        53,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        54,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        55,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        56,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        57,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        58,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        59,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        60,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        61,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        62,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        63,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        64,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        65,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        66,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        67,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        68,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        69,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        70,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        71,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        72,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        73,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        74,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        75,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        76,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        77,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        78,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        79,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        80,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        81,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        82,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        83,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        84,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        85,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        86,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        87,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        88,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        89,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        90,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        91,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        92,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        93,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        94,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        95,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        96,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        97,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        98,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        99,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        100,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        101,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        102,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        103,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        104,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        105,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        106,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        107,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        108,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        109,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        110,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        111,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        112,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        113,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        114,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        115,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        116,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        117,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        118,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        119,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        120,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        121,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        122,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        123,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        124,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        125,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        126,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        127,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        128,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        129,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        130,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        131,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        132,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        133,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        134,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        135,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        136,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        137,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        138,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        139,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        140,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        141,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        142,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        143,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        144,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        145,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        146,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        147,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        148,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        149,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        150,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        151,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        152,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        153,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        154,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        155,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        156,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        157,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        158,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        159,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        160,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        161,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        162,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        163,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        164,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        165,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        166,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        167,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        168,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        169,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        170,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        171,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        172,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        173,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        174,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        175,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        176,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        177,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        178,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        179,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        180,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        181,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        182,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        183,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        184,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        185,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        186,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        187,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        188,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        189,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        190,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        191,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        192,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        193,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        194,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        195,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        196,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        197,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        198,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        199,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        200,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        201,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        202,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        203,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        204,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        205,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        206,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        207,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        208,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        209,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        210,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        211,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        212,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        213,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        214,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        215,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        216,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        217,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        218,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        219,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        220,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        221,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        222,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        223,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        224,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        225,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        226,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        227,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        228,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        229,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        230,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        231,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        232,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        233,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        234,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        235,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        236,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        237,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        238,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        239,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        240,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        241,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        242,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        243,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        244,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        245,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        246,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        247,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        248,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        249,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        250,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        251,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        252,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        253,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        254,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        255,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        256,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE1_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                },
                {
                    {
                        "from_nct", /*消息名称*/
                        1,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        2,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        3,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        4,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        5,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        6,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        7,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        8,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        9,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        10,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        11,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        12,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        13,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        14,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        15,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        16,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        17,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        18,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        19,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        20,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        21,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        22,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        23,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        24,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        25,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        26,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        27,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        28,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        29,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        30,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        31,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        32,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        33,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        34,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        35,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        36,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        37,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        38,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        39,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        40,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },                    
                    {
                        "from_nct", /*消息名称*/
                        41,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        42,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        43,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        44,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        45,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        46,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        47,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        48,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        49,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        50,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        51,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        52,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        53,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        54,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        55,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        56,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        57,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        58,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        59,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        60,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        61,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        62,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        63,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        64,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        65,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        66,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        67,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        68,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        69,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        70,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        71,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        72,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        73,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        74,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        75,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        76,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        77,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        78,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        79,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        80,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        81,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        82,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        83,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        84,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        85,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        86,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        87,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        88,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        89,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        90,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        91,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        92,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        93,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        94,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        95,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        96,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        97,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        98,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        99,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        100,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        101,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        102,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        103,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        104,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        105,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        106,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        107,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        108,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        109,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        110,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        111,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        112,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        113,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        114,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        115,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        116,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        117,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        118,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        119,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        120,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        121,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        122,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        123,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        124,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        125,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        126,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        127,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        128,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        129,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        130,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        131,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        132,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        133,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        134,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        135,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        136,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        137,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        138,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        139,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        140,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        141,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        142,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        143,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        144,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        145,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        146,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        147,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        148,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        149,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        150,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        151,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        152,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        153,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        154,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        155,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        156,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        157,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        158,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        159,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        160,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        161,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        162,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        163,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        164,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        165,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        166,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        167,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        168,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        169,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        170,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        171,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        172,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        173,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        174,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        175,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        176,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        177,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        178,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        179,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        180,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        181,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        182,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        183,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        184,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        185,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        186,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        187,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        188,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        189,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        190,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        191,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        192,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        193,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        194,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        195,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        196,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        197,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        198,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        199,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        200,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        201,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        202,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        203,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        204,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        205,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        206,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        207,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        208,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        209,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        210,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        211,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        212,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        213,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        214,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        215,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        216,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        217,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        218,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        219,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        220,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        221,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        222,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        223,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        224,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        225,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        226,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        227,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        228,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        229,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        230,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        231,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        232,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        233,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        234,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        235,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        236,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        237,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        238,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        239,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        240,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        241,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        242,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        243,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        244,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        245,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        246,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        247,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        248,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        249,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        250,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        251,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        252,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        253,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        254,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        255,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        256,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                },
            },
/***************************************BNCT***************************************/
            {
                /*端口配置*/
                {
                    "BNC",              /* 本地端口的名称 */
                    MB_NODE2_FCID,           /* 本地port_id */
                    1,                  /* 端口类型 1-ASM */
                    8,                  /* 信用 */
                    FC_NET_ROLE_BNC,           /* 端口的网络管理角色*/
                    FC_NET_CLK_SYNC_ROLE_CLIENT,/* 时钟同步角色*/
                    /*10*60*1000*/1500,               /* WDT定时周期*/
                    500,                /* WDT加载周期*/
                    100,                /* 时钟同步周期 */
                    256,                  /* 非数据块发送消息的总数 */
                    256,                  /* 非数据块接收消息的总数 */
                    0,                  /* 数据块发送消息的总数 */
                    0,                  /* 数据块接收消息的总数 */
                },
                
                {
                    {
                        "to_nrt", /*消息名称*/
                        1,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        2,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        3,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        4,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        5,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        6,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        7,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        8,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        9,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        10,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        11,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        12,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        13,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        14,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        15,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        16,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        17,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        18,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        19,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        20,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        21,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        22,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        23,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        24,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        25,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        26,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        27,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        28,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        29,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        30,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        31,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        32,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        33,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        34,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        35,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        36,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        37,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        38,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        39,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        40,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        41,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        42,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        43,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        44,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        45,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        46,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        47,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        48,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        49,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        50,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        51,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        52,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        53,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        54,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        55,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        56,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        57,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        58,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        59,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        60,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        61,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        62,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        63,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        64,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        65,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        66,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        67,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        68,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        69,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        70,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        71,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        72,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        73,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        74,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        75,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        76,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        77,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        78,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        79,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        80,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        81,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        82,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        83,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        84,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        85,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        86,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        87,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        88,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        89,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        90,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        91,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        92,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        93,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        94,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        95,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        96,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        97,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        98,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        99,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        100,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        101,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        102,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        103,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        104,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        105,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        106,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        107,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        108,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        109,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        110,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        111,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        112,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        113,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        114,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        115,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        116,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        117,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        118,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        119,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        120,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        121,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        122,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        123,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        124,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        125,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        126,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        127,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        128,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        129,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        130,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        131,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        132,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        133,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        134,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        135,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        136,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        137,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        138,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        139,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        140,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        141,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        142,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        143,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        144,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        145,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        146,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        147,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        148,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        149,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        150,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        151,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        152,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        153,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        154,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        155,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        156,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        157,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        158,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        159,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        160,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        161,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        162,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        163,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        164,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        165,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        166,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        167,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        168,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        169,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        170,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        171,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        172,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        173,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        174,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        175,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        176,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        177,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        178,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        179,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        180,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        181,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        182,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        183,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        184,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        185,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        186,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        187,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        188,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        189,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        190,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        191,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        192,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        193,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        194,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        195,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        196,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        197,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        198,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        199,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        200,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        201,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        202,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        203,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        204,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        205,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        206,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        207,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        208,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        209,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        210,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        211,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        212,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        213,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        214,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        215,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        216,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        217,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        218,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        219,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        220,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        221,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        222,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        223,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        224,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        225,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        226,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        227,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        228,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        229,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        230,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        231,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        232,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        233,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        234,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        235,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        236,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        237,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        238,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        239,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        240,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        241,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        242,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        243,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        244,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        245,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        246,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        247,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        248,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        249,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        250,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        251,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        252,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        253,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        254,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        255,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        256,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE3_FCID,  /*消息的目的ASM端口port_id*/
                    },
                },
                {
                    {
                        "from_nct", /*消息名称*/
                        1,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        2,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        3,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        4,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        5,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        6,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        7,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        8,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        9,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        10,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        11,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        12,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        13,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        14,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        15,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        16,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        17,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        18,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        19,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        20,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        21,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        22,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        23,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        24,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        25,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        26,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        27,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        28,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        29,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        30,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        31,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        32,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        33,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        34,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        35,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        36,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        37,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        38,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        39,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        40,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        41,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        42,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        43,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        44,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        45,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        46,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        47,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        48,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        49,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        50,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        51,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        52,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        53,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        54,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        55,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        56,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        57,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        58,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        59,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        60,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        61,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        62,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        63,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        64,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        65,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        66,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        67,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        68,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        69,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                       70,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        71,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        72,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        73,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        74,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        75,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        76,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        77,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        78,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        79,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        80,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        81,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        82,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        83,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        84,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        85,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        86,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        87,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        88,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        89,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        90,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        91,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        92,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        93,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        94,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        95,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        96,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        97,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        98,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        99,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        100,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        101,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        102,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        103,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        104,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        105,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        106,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        107,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        108,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        109,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        110,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        111,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        112,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        113,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        114,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        115,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        116,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        117,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        118,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        119,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        120,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        121,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        122,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        123,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        124,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        125,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        126,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        127,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        128,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        129,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        130,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        131,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        132,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        133,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        134,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        135,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        136,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        137,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        138,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        139,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        140,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        141,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        142,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        143,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        144,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        145,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        146,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        147,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        148,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        149,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        150,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        151,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        152,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        153,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        154,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        155,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        156,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        157,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        158,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        159,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        160,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        161,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        162,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        163,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        164,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        165,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        166,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        167,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        168,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        169,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        170,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        171,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        172,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        173,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        174,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        175,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        176,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        177,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        178,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        179,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        180,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        181,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        182,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        183,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        184,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        185,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        186,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        187,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        188,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        189,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        190,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        191,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        192,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        193,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        194,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        195,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        196,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        197,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        198,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        199,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        200,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        201,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        202,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        203,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        204,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        205,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        206,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        207,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        208,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        209,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        210,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        211,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        212,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        213,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        214,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        215,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        216,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        217,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        218,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        219,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        220,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        221,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        222,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        223,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        224,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        225,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        226,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        227,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        228,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        229,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        230,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        231,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        232,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        233,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        234,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        235,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        236,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        237,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        238,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        239,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        240,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        241,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        242,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        243,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        244,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        245,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        246,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        247,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        248,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        249,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        250,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        251,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        252,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        253,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        254,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        255,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        256,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE3_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                },
            },
/***************************************NRT***************************************/
            {
                /*端口配置*/
                {
                    "NRT",              /* 本地端口的名称 */
                    MB_NODE2_FCID,           /* 本地port_id */
                    1,                  /* 端口类型 1-ASM */
                    8,                  /* 信用 */
                    FC_NET_ROLE_NRT,           /* 端口的网络管理角色*/
                    FC_NET_CLK_SYNC_ROLE_CLIENT,/* 时钟同步角色*/
                    100*60*1000/*2500*/,               /* WDT定时周期*/
                    50*60*1000/*500*/,                /* WDT加载周期*/
                    100,                /* 时钟同步周期 */
                    256,                  /* 非数据块发送消息的总数 */
                    256,                  /* 非数据块接收消息的总数 */
                    0,                  /* 数据块发送消息的总数 */
                    0,                  /* 数据块接收消息的总数 */
                },
                {
                    {
                        "to_nrt", /*消息名称*/
                        1,           /*消息ID*/
                        MSG_TYPE_URGENCY_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_3,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        2,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        3,           /*消息ID*/
                        MSG_TYPE_URGENCY_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        4,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        5,           /*消息ID*/
                        MSG_TYPE_EVENT_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_2,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        6,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        7,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        8,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        9,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        10,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        11,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        12,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        13,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        14,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        15,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        16,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        17,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        18,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        19,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        20,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        21,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        22,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        23,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        24,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        25,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        26,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        27,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        28,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        29,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        30,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        31,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        32,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        33,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        34,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        35,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        36,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        37,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        38,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        39,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        40,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        41,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        42,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        43,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        44,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        45,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        46,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        47,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        48,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        49,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        50,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        51,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        52,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        53,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        54,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        55,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        56,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        57,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        58,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        59,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        60,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        61,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        62,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        63,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        64,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        65,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        66,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        67,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        68,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        69,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        70,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        71,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        72,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        73,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        74,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        75,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        76,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        77,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        78,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        79,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        80,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        81,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        82,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        83,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        84,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        85,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        86,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        87,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        88,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        89,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        90,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        91,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        92,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        93,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        94,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        95,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        96,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        97,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        98,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        99,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        100,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        101,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        102,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        103,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        104,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        105,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        106,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        107,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        108,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        109,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        110,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        111,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        112,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        113,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        114,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        115,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        116,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        117,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        118,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        119,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        120,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        121,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        122,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        123,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        124,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        125,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        126,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        127,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        128,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        129,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        130,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        131,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        132,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        133,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        134,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        135,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        136,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        137,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        138,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        139,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        140,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        141,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        142,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        143,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        144,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        145,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        146,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        147,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        148,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        149,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        150,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        151,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        152,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        153,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        154,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        155,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        156,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        157,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        158,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        159,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        160,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        161,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        162,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        163,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        164,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        165,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        166,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        167,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        168,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        169,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        170,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        171,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        172,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        173,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        174,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        175,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        176,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        177,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        178,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        179,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        180,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        181,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        182,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        183,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        184,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        185,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        186,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        187,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        188,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        189,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        190,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        191,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        192,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        193,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        194,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        195,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        196,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        197,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        198,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        199,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        200,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        201,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        202,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        203,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        204,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        205,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        206,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        207,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        208,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        209,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        210,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        211,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        212,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        213,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        214,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        215,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        216,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        217,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        218,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        219,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        220,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        221,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        222,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        223,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        224,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        225,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        226,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        227,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        228,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        229,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        230,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        231,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        232,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        233,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        234,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        235,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        236,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        237,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        238,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        239,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        240,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        241,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        242,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        243,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        244,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        245,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        246,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        247,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        248,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        249,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        250,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        251,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        252,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        253,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        254,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        255,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                    {
                        "to_nrt", /*消息名称*/
                        256,           /*消息ID*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型*/
                        PRIORITY_LEVEL_0,         /*消息优先级*/
                        MB_NODE2_FCID,  /*消息的源ASM端口port_id*/
                        MB_NODE1_FCID,  /*消息的目的ASM端口port_id*/
                    },
                },
                
                {
                    {
                        "from_nct", /*消息名称*/
                        1,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        2,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        3,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        4,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        5,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        6,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        7,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        8,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        9,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        10,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        11,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        12,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        13,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        14,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        15,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        16,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        17,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        18,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        19,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        20,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        21,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        22,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        23,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        24,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        25,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        26,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        27,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        28,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        29,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        30,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        31,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        32,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        33,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        34,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        35,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        36,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        37,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        38,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        39,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        40,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        41,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        42,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        43,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        44,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        45,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        46,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        47,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        48,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        49,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        50,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        51,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        52,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        53,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        54,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        55,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        56,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        57,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        58,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        59,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        60,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        61,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        62,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        63,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        64,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        65,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        66,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        67,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        68,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        69,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        70,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        71,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        72,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        73,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        74,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        75,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        76,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        77,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        78,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        79,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        80,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        81,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        82,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        83,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        84,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        85,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        86,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        87,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        88,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        89,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        90,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        91,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        92,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        93,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        94,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        95,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        96,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        97,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        98,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        99,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        100,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        101,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        102,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        103,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        104,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        105,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        106,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        107,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        108,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        109,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        110,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        111,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        112,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        113,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        114,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        115,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        116,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        117,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        118,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        119,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        120,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        121,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        122,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        123,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        124,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        125,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        126,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        127,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        128,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        129,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        130,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        131,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        132,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        133,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        134,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        135,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        136,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        137,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        138,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        139,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        140,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        141,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        142,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        143,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        144,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        145,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        146,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        147,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        148,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        149,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        150,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        151,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        152,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        153,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        154,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        155,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        156,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        157,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        158,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        159,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        160,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        161,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        162,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        163,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        164,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        165,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        166,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        167,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        168,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        169,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        170,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        171,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        172,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        173,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        174,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        175,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        176,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        177,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        178,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        179,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        180,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        181,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        182,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        183,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        184,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        185,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        186,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        187,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        188,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        189,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        190,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        191,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        192,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        193,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        194,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        195,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        196,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        197,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        198,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        199,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        200,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        201,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        202,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        203,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        204,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        205,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        206,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        207,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        208,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        209,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        210,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        211,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        212,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        213,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        214,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        215,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        216,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        217,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        218,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        219,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        220,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        221,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        222,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        223,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        224,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        225,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        226,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        227,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        228,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        229,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        230,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        231,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        232,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        233,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        234,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        235,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        236,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        237,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        238,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        239,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        240,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        241,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        242,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        243,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        244,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        245,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        246,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        247,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        248,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        249,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        250,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        251,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        252,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        253,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        254,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        255,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                    {
                        "from_nct", /*消息名称*/
                        256,         /*消息ID*/
                        TEST_FC_ASM_IU_LENGTH_MAX,      /* 长度*/
                        MSG_TYPE_STREAM_MSG,         /*消息类型  事件*/
                        MB_NODE1_FCID,  /* 消息的源ASM端口port_id */
                        1          /*消息非刷新输出标志*/
                    },
                },
            },
        },
    },
};


