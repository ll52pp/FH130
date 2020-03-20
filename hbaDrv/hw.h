#ifndef __HW_H__
#define __HW_H__

#include <vxworks.h>
#include "hba.h"
#include "fc_asm.h"
#include "endian.h"

/******************************************************************************
* 常量定义                                                                    *
******************************************************************************/
#define HOST_READ                      0
#define HOST_WRITE                     1

#define IDC_DIRECT_RX                  0
#define IDC_DIRECT_TX                  1
#define IDC_ACTION_READ                0
#define IDC_ACTION_WRITE               1

#define HASH_SEED                      0x0
#define HASH_BIT_FREE                  0xEEFFFFFF

#define RAW_MODE                       0
#define ASM_MODE                       1
#define RX_INACTIVE                    0
#define RX_ACTIVE                      1

/* TX fc asm header */
#define FA_IDX_RSV0                    0x0
#define FA_IDX_RSV1                    0x1
#define FA_IDX_DID                     0x2
#define FA_IDX_SID                     0x3
#define FA_IDX_FCTL                    0x4
#define FA_IDX_SEQ_ID_SEQ_CNT          0x5
#define FA_IDX_OXID_RXID               0x6
#define FA_IDX_PARAMETER               0x7
#define FA_IDX_MESSAGEID               0x8
#define FA_IDX_SECURITY                0x9
#define FA_IDX_RSV2                    0xA

/* offset of indirect register */
#define IDA_TX_FC_ASM_HEADER_BASE      0x0
#define IDA_TX_LOGIC_BUF_BASE          0x1000
#define IDA_RX_LOGIC_BUF_BASE          0x0
#define IDA_RX_HASH_TAB_BASE           0x1000

#define IDA_RX_ACTIVE_BASE             0x1400
#define IDA_RX_RAW_ACTIVE_BASE         0x1410
#define IDA_RX_LOGIC_BUF_SIZE_BASE     0x1411
#define IDA_RX_CHANNEL_MAP_TABLE_BASE  0x1500
#define IDA_RX_PRIORITY_BASE           0x1700
#define IDA_OX_ID_INIT_BASE            0x1800
#define IDA_ELS_CHANNEL_BASE           0x1900
#define IDA_SWITCH_ELS_CHANNEL_BASE    0x1920

#define INCRMENT_RESET_CREDIT          0x8

#define LSI_RECV_FRAM_NUM                        0x1  /*1  接收帧数*/
#define LSI_RECV_IU_NUM                             0x2  /*2  接收IU个数*/
#define LSI_RECV_IU_ERR_NUM                         0x3  /*3  接收错误帧数 IU标记不匹配/CRC错误/其他错误，帧头错误等*/
#define LSI_RECV_IU_DISCARD_NUM                  0x4  /*4  接收丢弃的IU个数 接收端配置了丢弃标记后，发生的丢弃的IU个数*/
#define LSI_RECV_IU_INVALID_NUM                  0x5  /*5  接收无效的帧数 ASMID没有配置过，但是收到了*/
#define LSI_SEND_FRAME_NUM                       0xB  /*11 发送帧数*/
#define LSI_SEND_IU_NUM                             0xC  /*12 发送IU个数*/


/* reset时是否将链路强制下线，hwResetFpga 使用的参数 */
#define FORCE_OFFLINE        1
#define NO_FORCE_OFFLINE    0

/******************************************************************************
* 寄存器的联合体描述定义                                                      *
******************************************************************************/
typedef union
{
    struct
    {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
        ULONG reserve : 16;/* [16:31] : RW reserve */
        ULONG version : 16;/* [0:15] : RO fpga version -- fpga version*/
#else
        ULONG version : 16;/* [ 0:15] : RO fpga version -- fpga version*/
        ULONG reserve : 16;/* [16:31] : RW reserve */
#endif            
    } u;
    ULONG value;
} FPGA_VER;

typedef union
{
    struct
    {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
        ULONG gtx_loopback    : 1; /* [31   ] : RW GTX loop back     --  */
        ULONG did_filter_enab : 1; /* [30   ] : RW did filter enable -- 0-enable 1-disable */
        ULONG speed           : 2; /* [28:29] : RW speed             -- 00 auto sense 01 1Gbps 10 2Gbps 11 4Gbps */
        ULONG credit          : 4; /* [24:27] : RW credit            -- set 0～15=>1～16 number of credit */
        ULONG sid             : 24;/* [ 0:23] : RW sid               -- self id */
#else
        ULONG sid             : 24;/* [ 0:23] : RW sid               -- self id */
        ULONG credit          : 4; /* [24:27] : RW credit            -- set 0～15=>1～16 number of credit */
        ULONG speed           : 2; /* [28:29] : RW speed             -- 00 auto sense 01 1Gbps 10 2Gbps 11 4Gbps */
        ULONG did_filter_enab : 1; /* [30   ] : RW did filter enable -- 0-enable 1-disable */
        ULONG gtx_loopback    : 1; /* [31   ] : RW GTX loop back     --  */
#endif        
    } u;
    ULONG value;
} PORT_CONFIG;

typedef union
{
    struct
    {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
        ULONG valid_buf_num   : 2; /* [30:31] : RW valid number of buffers */
        ULONG buf_num_of_3rd  : 10;/* [20:29] : RW buffer number     -- 3rd available buffer number */
        ULONG buf_num_of_2nd  : 10;/* [10:19] : RW buffer number     -- 2nd available buffer number */
        ULONG buf_num_of_1st  : 10;/* [ 0: 9] : RW buffer number     -- 1st available buffer number */
#else
        ULONG buf_num_of_1st  : 10;/* [ 0: 9] : RW buffer number     -- 1st available buffer number */
        ULONG buf_num_of_2nd  : 10;/* [10:19] : RW buffer number     -- 2nd available buffer number */
        ULONG buf_num_of_3rd  : 10;/* [20:29] : RW buffer number     -- 3rd available buffer number */
        ULONG valid_buf_num   : 2; /* [30:31] : RW valid number of buffers */
#endif
    } u;
    ULONG value;
} CREDIT;

typedef union
{
    struct
    {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
    ULONG e_d_tov         :16; /* [16:31] : R E_d_tov value, unit is 1ms */
    ULONG redundancy_enab : 1; /* [15    ]  : R Redundant enable '0' disable '1' enable */
    ULONG discard_enab    : 1; /* [14   ] : RW FPGA initiative discarded enable, '0' disable '1' enable */
    ULONG reserve         :11; /* [ 3:13]  : R reserve */
    ULONG reset           : 1; /* [ 2     ]  : RW fpga reset/unload configure 1-reset/unload fpga self clear */    
    ULONG p0_mac_switch   : 1; /* [ 1     ]  : RW port0 Mac force off -- 0-mac on 1-mac off */
    ULONG p0_rx_enab      : 1; /* [ 0     ]  : RW port0 RX enab       -- port0 rx enable 0-disable rx 1-enable rx */
#else
    ULONG p0_rx_enab      : 1; /* [ 0        ]  : RW port0 RX enab port0 rx enable 0-disable rx 1-enable rx */
    ULONG p0_mac_switch   : 1; /* [ 1        ]  : RW port0 Mac force off 0-mac on 1-mac off */
    ULONG reset           : 1; /* [ 2        ]  : RW fpga reset/unload configure 1-reset/unload fpga self clear */
    ULONG reserve          :11; /* [ 3:13]  : R reserve */ 
    ULONG discard_enab    : 1; /* [14   ] : RW FPGA initiative discarded enable, '0' disable '1' enable */
    ULONG redundancy_enab : 1; /* [15    ]  : R Redundant enable '0' disable '1' enable */
    ULONG e_d_tov         :16; /* [16:31] : R E_d_tov value, unit is 1ms */
#endif
    } u;
    ULONG value;
} PORT_RX_ENAB;

typedef union
{
    struct
    {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
        ULONG raw_flag       : 1; /* [31   ] : RW raw flag            -- 0-not raw 1-raw */
        ULONG channel_num    : 8; /* [23:30] : RW channel number      -- 8bit, max 256 */
        ULONG buf_num        :12; /* [11:22] : RW buffer num          -- 12bit, max 4096 */
        ULONG dma_read_num   :11; /* [ 0:10] : RW number of dma read operation in this buffer, unit in 128 byte */
#else
        ULONG dma_read_num   :11; /* [ 0:10] : RW number of dma read operation in this buffer, unit in 128 byte */
        ULONG buf_num        :12; /* [11:22] : RW buffer num          -- 12bit, max 4096 */
        ULONG channel_num    : 8; /* [23:30] : RW channel number      -- 8bit, max 256 */
        ULONG raw_flag       : 1; /* [31   ] : RW raw flag            -- 0-not raw 1-raw */
#endif
    } u;
    ULONG value;
} DMA_READ_BUF_DESC;

typedef union
{
    struct
    {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
        ULONG reserve          : 12;/* [20:31] : RW reserve */
        ULONG global_sync_enab : 1; /* [19   ] : RW hba global sync enable    -- 0-disable 1-enable */
        ULONG rtc_base         : 1; /* [18   ] : RW rtc base  -- 0-5x  division, used in 1G/2G mode
                                                                 1-10x division, used in 2G/4G mode */
        ULONG p1_sync_enab     : 1; /* [17   ] : RW port1 sync enable   -- 0-disable 1-enable */
        ULONG p0_sync_enab     : 1; /* [16   ] : RW port0 sync enable   -- 0-disable 1-enable */
        ULONG event_period     : 16;/* [ 0:15] : RW event period unit is ms
                                                    Note: The actual event period equals the programmed value plus one.*/
#else
        ULONG event_period     : 16;/* [ 0:15] : RW event period unit is ms
                                                    Note: The actual event period equals the programmed value plus one.*/
        ULONG p0_sync_enab     : 1; /* [16   ] : RW port0 sync enable   -- 0-disable 1-enable */
        ULONG p1_sync_enab     : 1; /* [17   ] : RW port1 sync enable   -- 0-disable 1-enable */
        ULONG rtc_base         : 1; /* [18   ] : RW rtc base  -- 0-5x  division, used in 1G/2G mode
                                                                 1-10x division, used in 2G/4G mode */
        ULONG global_sync_enab : 1; /* [19   ] : RW hba global sync enable    -- 0-disable 1-enable */
        ULONG reserve          : 12;/* [20:31] : RW reserve */
#endif
    } u;
    ULONG value;
} RTC_CONTROL;

typedef union
{
    struct
    {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
        ULONG temperature : 12;/* [20:31] : RO fpga temperature */
        ULONG voltage     : 12;/* [ 8:19] : RO fpga voltage */
        ULONG reserve     : 5; /* [ 2: 7] : RW reserve */
        ULONG resetCplt   : 1; /* [ 2: 7] : reset unload configure finished, 0-not finished 1-finished */
        ULONG p1_status   : 1; /* [ 1   ] : RO port1 status -- 0-loss of sync 1-sync */
        ULONG p0_status   : 1; /* [ 0   ] : RO port0 status -- 0-loss of sync 1-sync */
#else
        ULONG p0_status   : 1; /* [ 0   ] : RO port0 status -- 0-loss of sync 1-sync */
        ULONG p1_status   : 1; /* [ 1   ] : RO port1 status -- 0-loss of sync 1-sync */
        ULONG resetCplt   : 1; /* [ 2: 7] : reset unload configure finished, 0-not finished 1-finished */
        ULONG reserve     : 5; /* [ 2: 7] : RW reserve */
        ULONG voltage     : 12;/* [ 8:19] : RO fpga voltage */
        ULONG temperature : 12;/* [20:31] : RO fpga temperature */
#endif
    } u;
    ULONG value;
} PORT_STATUS;

typedef union
{
    struct
    {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
        ULONG action  : 1;  /* [31   ] : RW action   -- 0-read operation 1-write operation */
        ULONG port    : 1;  /* [30   ] : RW port num -- 0-port 0 1-port 1 */
        ULONG direct  : 1;  /* [29   ] : RW direct   -- 0-RX 1-TX */
        ULONG reserve : 13; /* [16:28] : RW reserve */
        ULONG address : 16; /* [ 0:15] : RW address */
#else
        ULONG address : 16; /* [ 0:15] : RW address */
        ULONG reserve : 13; /* [16:28] : RW reserve */
        ULONG direct  : 1;  /* [29   ] : RW direct   -- 0-RX 1-TX */
        ULONG port    : 1;  /* [30   ] : RW port num -- 0-port 0 1-port 1 */
        ULONG action  : 1;  /* [31   ] : RW action   -- 0-read operation 1-write operation */
#endif        
    } u;
    ULONG value;
} INDIRECT_CONTROL;

typedef union
{
    struct 
    {
        ULONG data : 32; /* [ 0:32] : RW data */
    } u;
    ULONG value;
} INDIRECT_DATA;

typedef union
{
    struct
    {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
        ULONG reserve     : 20;/* [10:31] RW reserve */
        ULONG value       : 10;/* [ 0: 9] RW rtc high bit [32:41] */
#else
        ULONG value       : 10;/* [ 0: 9] RW rtc high bit [32:41] */
        ULONG reserve     : 20;/* [10:31] RW reserve */
#endif
    } u;
    ULONG value;
} RTC_WRITE_HIGH;

typedef union
{
    ULONG value; /* [ 0:31] RW rtc low bit [ 0:31] */
} RTC_WRITE_LOW;

typedef union
{
    struct
    {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
        ULONG reserve     : 20;/* [10:31] RW reserve */
        ULONG value       : 10;/* [ 0: 9] RW rtc high bit [32:41] */
#else
        ULONG value       : 10;/* [ 0: 9] RW rtc high bit [32:41] */
        ULONG reserve     : 20;/* [10:31] RW reserve */
#endif
    } u;
    ULONG value;
} RTC_READ_HIGH;

typedef union
{
    ULONG value; /* [ 0:31] RW rtc low bit [ 0:31] */
} RTC_READ_LOW;

typedef union
{
    struct
    {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
        ULONG start       : 1;  /* [   31] RW  set 1 start statistic, self clear */
        ULONG reserve     : 25; /* [ 4:30] RW */
        ULONG type        : 6;  /* [ 0: 3] RW 0-cur timestamp 32'b~41'b
                                               1-cur timestamp 0'b~31'b
                                               2-recv word num
                                               3-recv idle num
                                               4-recv frame num
                                               5-recv word num
                                               6-recv idle num
                                               7-recv frame num */
#else
        ULONG type        : 6;  /* [ 0: 3] RW 0-cur timestamp 32'b~41'b
                                               1-cur timestamp 0'b~31'b
                                               2-recv word num
                                               3-recv idle num
                                               4-recv frame num
                                               5-recv word num
                                               6-recv idle num
                                               7-recv frame num */
        ULONG reserve     : 25; /* [ 4:30] RW */
        ULONG start       : 1;  /* [   31] RW  set 1 start statistic, self clear */
#endif
    } u;
    ULONG value;
} STATISTICS_CONTROL;

typedef union
{
    ULONG value; /* [ 0:31] : RW data of statistics */
} STATISTICS_DATA;

typedef union
{
    struct
    {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
        ULONG wr_flash       : 1; /* [31   ] :RW write flash enable  -- 1-enable 0-disable */
        ULONG wr_flash_debug : 1; /* [30   ] :RW */
        ULONG rd_flash       : 1; /* [29   ] :RW read flash enable  -- 1-enable 0-disable */
        ULONG rd_flash_debug : 1; /* [28   ] :RW */
        ULONG reserve        : 4; /* [24:27] :RW */
        ULONG flash_addr     : 24;/* [ 0:23] :RW */        
#else
        ULONG flash_addr     : 24;/* [ 0:23] :RW */
        ULONG reserve        : 4; /* [24:27] :RW */
        ULONG rd_flash_debug : 1; /* [28   ] :RW */
        ULONG rd_flash       : 1; /* [29   ] :RW read flash enable  -- 1-enable 0-disable */
        ULONG wr_flash_debug : 1; /* [30   ] :RW */
        ULONG wr_flash       : 1; /* [31   ] :RW write flash enable  -- 1-enable 0-disable */
#endif
    } u;
    ULONG value;
} FLASH_ADDR_CONTROL;

typedef union
{
    struct
    {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
        ULONG intr_enable_global         : 1; /* [31] : RW */
        ULONG intr_enable_link_change     : 1; /* [30] : RW */
        ULONG intr_enable_send_bd_empty : 1; /* [29] : RW */
        ULONG intr_enable_Tx_IU         : 1; /* [28] : RW */
        ULONG intr_enable_Rx_credit_out    : 1; /* [27] : RW */
        ULONG intr_enable_Rx_IU         : 1; /* [26] : RW */
        ULONG reserved                    : 21;/* [5:25] : RW */
        ULONG pending_link_change        : 1; /* [4] : RW */
        ULONG pending_send_bd_empty        : 1; /* [3] : RW */
        ULONG pending_Tx_IU                : 1; /* [2] : RW */
        ULONG pending_Rx_credit_out        : 1; /* [1] : RW */
        ULONG pending_Rx_IU                : 1; /* [0] : RW */
        
#else
        ULONG pending_Rx_IU                : 1; /* [0] : RW */
        ULONG pending_Rx_credit_out        : 1; /* [1] : RW */
        ULONG pending_Tx_IU                : 1; /* [2] : RW */
        ULONG pending_send_bd_empty        : 1; /* [3] : RW */
        ULONG pending_link_change        : 1; /* [4] : RW */
        ULONG reserved                    : 21;/* [5:25] : RW */
        ULONG intr_enable_Rx_IU         : 1; /* [26] : RW */
        ULONG intr_enable_Rx_credit_out    : 1; /* [27] : RW */
        ULONG intr_enable_Tx_IU         : 1; /* [28] : RW */
        ULONG intr_enable_send_bd_empty : 1; /* [29] : RW */
        ULONG intr_enable_link_change     : 1; /* [30] : RW */        
        ULONG intr_enable_global         : 1; /* [31] : RW */        
#endif
    } u;
    ULONG value;
} INTERRUPT;

typedef union
{
    struct
    {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
        ULONG voltage       : 32; /* [ 0:31] : RW */
#else
        ULONG voltage       : 32; /* [ 0:31] : RW */
#endif
    } u;
    ULONG value;
} VOLTAGE;

typedef union
{
    struct
    {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
        ULONG temperature   : 32; /* [ 0:31] : RW */
#else
        ULONG temperature   : 32; /* [ 0:31] : RW */
#endif
    } u;
    ULONG value;
} TEMPERATURE;

typedef union
{
    struct
    {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
        ULONG reserve       : 8; /* [24:31] : RW reserve */
        ULONG sid           : 24;/* [ 0:23] : RW sid */
#else
        ULONG sid           : 24;/* [ 0:23] : RW sid */
        ULONG reserve       : 8; /* [24:31] : RW reserve */
#endif
    } u;
    ULONG value;
} SID;

/* CARRIER_RTC_CTRL */  /* 20171108 */
typedef union _CARRIER_RTC_CTRL {
    struct {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
        ULONG carrier_rtc_enb : 1;           /* [31   ] : RW Carrier RTC Enable */
        ULONG mode            : 1;           /* [30   ] : RW MODE  1:sever   0:client */
        ULONG pluse_duty      : 30;          /* [0: 29] : RW Pluse Duty,unit 100ns */
#else
        ULONG pluse_duty      : 30;          /* [0: 29] : RW Pluse Duty,unit 100ns */
        ULONG mode            : 1;           /* [30   ] : RW MODE  1:sever   0:client */
        ULONG carrier_rtc_enb : 1;           /* [31   ] : RW Carrier RTC Enable */
#endif
    } u;
    ULONG value;
} CARRIER_RTC_CTRL;

/* 寄存器定义 */
typedef struct
{
    ULONG FPGA_VER;
       /* offset  : 0x00
       [16:31] : RW reserve                   -- reserve
       [ 0:15] : RO fpga version              -- fpga version */
    ULONG PORT_CONFIG;
    /* offset  : 0x04
       [   31] : RW GTX loopback              -- 
       [   30] : RW did filter enable         -- 0-enable 1-disable default '1'
       [28:29] : RW speed                     -- 00 auto sense 01 1Gbps 10 2Gbps 11 4Gbps
       [24:27] : RW credit                    -- set 0000'b～1111'b=>1～16 number of credit default '1'
       [ 0:23] : RW sid                       -- self id default '0' */
       ULONG P0_CREDIT;
    /* offset  : 0x08
       [30:31] : RW valid number of buffers:[ 0, 3]
       [20:29] : RW 3rd available buffer number
       [10:19] : RW 2nd available buffer number
       [ 0: 9] : RW 1st available buffer number */
    ULONG PORT_RX_ENAB;
    /* offset  : 0x0C
       [16:31] : E_d_tov value, 单位为1ms
       [15    ] : Redundant enable '1'    使能'0'不使能
       [ 3:14] : reserve   
       [ 2     ] : RW reset/unload configure -- 1 reset fpag, self clear
       [ 1     ] : RW port0 Mac force off       -- 0-mac on 1-mac off
       [ 0     ] : RW port0 RX enab             -- port0 rx enable 0-disable rx 1-enable rx*/
    ULONG DMA_READ_BUF_DESC_0;
    /* offset  : 0x10
       [31   ] : RW raw flag                  -- 0-not raw 1-raw
       [23:30] : RW channel number     -- 8bit, max 256
       [11:22] : RW buffer num                -- 12bit, max 4096
       [ 0:10] : RW number of dma read operation in this buffer, unit in 128 byte */
    ULONG RTC_CONTROL;
    /* offset  : 0x14
       [20:31] : RW reserve
       [19   ] : RW Hba card hba global sync enable    -- 0-disable 1-enable
       [18   ] : RW rtc base         -- 0-5x division,used in 1G/2G mode
                                                 1-10x division,used in 2G/4G mode
       [17    ] : RW port1 sync enable          -- 0-disable 1-enable
       [16    ] : RW port0 sync enable          -- 0-disable 1-enable
       [ 0:15] : RW event period unit is ms
                    Note: The actual event period equals the programmed value plus one.
       */
    ULONG PORT_STATUS;
    /* offset  : 0x18
       [20:31] : RO fpga temperature     -- 
       [ 8:19] : RO fpga voltage             -- 
       [ 3: 7] : RW reserve                    -- reserve
       [ 2   ] : RO reset/unload configure done -- 0-not done 1-done
       [ 1   ] : RO port1 status              -- 0-loss of sync 1-sync
       [ 0   ] : RO port0 status              -- 0-loss of sync 1-sync */
    ULONG INDIRECT_CONTROL;
    /* offset  : 0x1C
       [31   ] : RW direct flag               -- 0-host read 1-host write
       [30   ] : RW port num                  -- 0-port 0 1-port 1
       [29   ] : RW direct                    -- 0-RX 1-TX
       [16:28] : RW reserve
       [ 0:15] : RW address */
    ULONG INDIRECT_DATA;
    /* offset  : 0x20
       [ 0:31] : RW data*/
       ULONG P1_CREDIT;
    /* offset  : 0x24
       [30:31] : RW valid number of buffers:[ 0, 3]
       [20:29] : RW 3rd available buffer number
       [10:19] : RW 2nd available buffer number
       [ 0: 9] : RW 1st available buffer number */
    ULONG RTC_WRITE_HIGH;
    /* offset  : 0x28
       [10:31] : RW reserve
       [ 0: 9] : RW rtc high bit [32:41] */
    ULONG RTC_WRITE_LOW;
    /* offset  : 0x2C
       [ 0:31] : RW rtc low bit [ 0:31] */
    ULONG RTC_READ_HIGH;
    /* offset  : 0x30
       [10:31] : RW reserve
       [ 0: 9] : RW rtc high bit [32:41] */
    ULONG RTC_READ_LOW;
    /* offset  : 0x34
       [ 0:31] : RW rtc low bit [ 0:31] */
    ULONG STATISTICS_CONTROL;
    /* offset  : 0x38
       [31   ] : RW start statistic           -- RW set 1 start statistic, self clear
       [ 4:30] : RW reserve
       [ 0: 3] : RW type of statistic         -- 0-cur timestamp low [ 0:31]
                                                 1-recv word num
                                                 2-recv idle num
                                                 3-recv frame num
                                                 4-recv iu num
                                                 5-reserved
                                                 6-reserved
                                                 7-reserved
                                                 
                                                 8-cur timestamp high [32:41]
                                                 9-send word num
                                                 10-send idle num
                                                 11-send frame num
                                                 12-send iu num
                                                 13-reserved
                                                 14-reserved
                                                 15-reserved
                                                 */
    ULONG STATISTICS_DATA;
    /* offset  : 0x3C
       [ 0:31] : RW data of statistics */
       ULONG P2_CREDIT;
    /* offset  : 0x40
       [30:31] : RW valid number of buffers:[ 0, 3]
       [20:29] : RW 3rd available buffer number
       [10:19] : RW 2nd available buffer number
       [ 0: 9] : RW 1st available buffer number */
       ULONG P3_CREDIT;
    /* offset  : 0x44
       [30:31] : RW valid number of buffers:[ 0, 3]
       [20:29] : RW 3rd available buffer number
       [10:19] : RW 2nd available buffer number
       [ 0: 9] : RW 1st available buffer number */
    ULONG FLASH_ADDR_CONTROL;
    /* offset  : 0x48
       [31   ] : RW wr_flash                  -- write flash enable 1-enable 0-disable
       [30   ] : RW wr_flash_debug
       [29   ] : RW rd_flash                  -- read flash enable 1-enable 0-disable
       [28   ] : RW rd_flash_debug
       [24:27] : RW reserve
       [ 0:23] : RW flash_addr */
    ULONG INTERRUPT_CTRL;
    /* offset  : 0x4C
        [31 ]:    Global intr enable
        [30 ]:    Link change intr enable
        [29 ]:    所有发送bd fifo空中断使能
        [28 ]:    Tx IU intr enable
        [27 ]:    任何一个优先级无信用中断使能
        [26 ]:    Rx IU intr enable
        [25~5 ]:reserved
        [4 ]:    Link change intr pending
        [3 ]:    所有发送bd fifo空中断发生
        [2 ]:    Tx IU intr pending
        [1 ]:    任何一个优先级无信用中断发生
        [0 ]:    Rx IU intr pending

 */
    ULONG RTC_DATE_WRITE;    /* offset : 0x50  1.19.    RTC天数配置寄存器 */
    ULONG RTC_DATE_READ;     /* offset : 0x54  1.20.    RTC天数实时寄存器 */
    ULONG DMA_READ_BUF_DESC_1;
    /* offset  : 0x58
       [31   ] : RW raw flag                  -- 0-not raw 1-raw
       [23:30] : RW channel number     -- 8bit, max 256
       [11:22] : RW buffer num                -- 12bit, max 4096
       [ 0:10] : RW number of dma read operation in this buffer, unit in 128 byte */
    ULONG DMA_READ_BUF_DESC_2;
    /* offset  : 0x5C
       [31   ] : RW raw flag                  -- 0-not raw 1-raw
       [23:30] : RW channel number     -- 8bit, max 256
       [11:22] : RW buffer num                -- 12bit, max 4096
       [ 0:10] : RW number of dma read operation in this buffer, unit in 128 byte */
    ULONG DMA_READ_BUF_DESC_3;
    /* offset  : 0x60
     [31     ] : RW raw flag                  -- 0-not raw 1-raw
     [23:30] : RW channel number       -- 8bit, max 256
     [11:22] : RW buffer num                  -- 12bit, max 4096
     [ 0:10] : RW number of dma read operation in this buffer, unit in 128 byte */
    ULONG SWITCH_SID;
    /* offset  : 0x64
       [24:31] : RW reserve
     [ 0:23] : RW sid */
    ULONG RESERVE_0x68;    /* offset : 0x68 */
    ULONG RESERVE_0x6C;       /* offset : 0x6C */
    ULONG CARRIER_RTC_CTRL;   /* 20171108  */
    /* offset : 0x70 CARRIER_RTC 同步配置寄存器
       [0: 29] : RW Pluse Duty,unit 100ns 
       [30   ] : RW MODE  1:sever   0:client 
       [31   ] : RW Carrier RTC Enable  */
} REG_HW;

/* hash相关的定义 */
/* 64位地址 : 低32位是asmid 高24位是fcid 最高8位保留 */
typedef union
{
    struct
    {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
        UINT32 b63 : 1;
        UINT32 b62 : 1;
        UINT32 b61 : 1;
        UINT32 b60 : 1;
        UINT32 b59 : 1;
        UINT32 b58 : 1;
        UINT32 b57 : 1;
        UINT32 b56 : 1;
        UINT32 b55 : 1;
        UINT32 b54 : 1;
        UINT32 b53 : 1;
        UINT32 b52 : 1;
        UINT32 b51 : 1;
        UINT32 b50 : 1;
        UINT32 b49 : 1;
        UINT32 b48 : 1;
        UINT32 b47 : 1;
        UINT32 b46 : 1;
        UINT32 b45 : 1;
        UINT32 b44 : 1;
        UINT32 b43 : 1;
        UINT32 b42 : 1;
        UINT32 b41 : 1;
        UINT32 b40 : 1;
        UINT32 b39 : 1;
        UINT32 b38 : 1;
        UINT32 b37 : 1;
        UINT32 b36 : 1;
        UINT32 b35 : 1;
        UINT32 b34 : 1;
        UINT32 b33 : 1;
        UINT32 b32 : 1;
        
        UINT32 b31 : 1;
        UINT32 b30 : 1;
        UINT32 b29 : 1;
        UINT32 b28 : 1;
        UINT32 b27 : 1;
        UINT32 b26 : 1;
        UINT32 b25 : 1;
        UINT32 b24 : 1;
        UINT32 b23 : 1;
        UINT32 b22 : 1;
        UINT32 b21 : 1;
        UINT32 b20 : 1;
        UINT32 b19 : 1;
        UINT32 b18 : 1;
        UINT32 b17 : 1;
        UINT32 b16 : 1;
        UINT32 b15 : 1;
        UINT32 b14 : 1;
        UINT32 b13 : 1;
        UINT32 b12 : 1;
        UINT32 b11 : 1;
        UINT32 b10 : 1;
        UINT32 b9  : 1;
        UINT32 b8  : 1;
        UINT32 b7  : 1;
        UINT32 b6  : 1;
        UINT32 b5  : 1;
        UINT32 b4  : 1;
        UINT32 b3  : 1;
        UINT32 b2  : 1;
        UINT32 b1  : 1;
        UINT32 b0  : 1;        
#else
        UINT64 b0  : 1;
        UINT64 b1  : 1;
        UINT64 b2  : 1;
        UINT64 b3  : 1;
        UINT64 b4  : 1;
        UINT64 b5  : 1;
        UINT64 b6  : 1;
        UINT64 b7  : 1;
        UINT64 b8  : 1;
        UINT64 b9  : 1;
        UINT64 b10 : 1;
        UINT64 b11 : 1;
        UINT64 b12 : 1;
        UINT64 b13 : 1;
        UINT64 b14 : 1;
        UINT64 b15 : 1;
        UINT64 b16 : 1;
        UINT64 b17 : 1;
        UINT64 b18 : 1;
        UINT64 b19 : 1;
        UINT64 b20 : 1;
        UINT64 b21 : 1;
        UINT64 b22 : 1;
        UINT64 b23 : 1;
        UINT64 b24 : 1;
        UINT64 b25 : 1;
        UINT64 b26 : 1;
        UINT64 b27 : 1;
        UINT64 b28 : 1;
        UINT64 b29 : 1;
        UINT64 b30 : 1;
        UINT64 b31 : 1;
        UINT64 b32 : 1;
        UINT64 b33 : 1;
        UINT64 b34 : 1;
        UINT64 b35 : 1;
        UINT64 b36 : 1;
        UINT64 b37 : 1;
        UINT64 b38 : 1;
        UINT64 b39 : 1;
        UINT64 b40 : 1;
        UINT64 b41 : 1;
        UINT64 b42 : 1;
        UINT64 b43 : 1;
        UINT64 b44 : 1;
        UINT64 b45 : 1;
        UINT64 b46 : 1;
        UINT64 b47 : 1;
        UINT64 b48 : 1;
        UINT64 b49 : 1;
        UINT64 b50 : 1;
        UINT64 b51 : 1;
        UINT64 b52 : 1;
        UINT64 b53 : 1;
        UINT64 b54 : 1;
        UINT64 b55 : 1;
        UINT64 b56 : 1;
        UINT64 b57 : 1;
        UINT64 b58 : 1;
        UINT64 b59 : 1;
        UINT64 b60 : 1;
        UINT64 b61 : 1;
        UINT64 b62 : 1;
        UINT64 b63 : 1;
#endif
    } u;
    
    struct
    {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN    
        ULONG high;
        ULONG low;        
#else
        ULONG low;
        ULONG high;
#endif
    } part;
    UINT64 value;
} HASH_64_BIT;

typedef union
{
    struct 
    {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
        UCHAR b7 : 1;
        UCHAR b6 : 1;
        UCHAR b5 : 1;
        UCHAR b4 : 1;
        UCHAR b3 : 1;
        UCHAR b2 : 1;
        UCHAR b1 : 1;
        UCHAR b0 : 1;
#else
        UCHAR b0 : 1;
        UCHAR b1 : 1;
        UCHAR b2 : 1;
        UCHAR b3 : 1;
        UCHAR b4 : 1;
        UCHAR b5 : 1;
        UCHAR b6 : 1;
        UCHAR b7 : 1;
#endif
    } u;
    UCHAR value;
} HASH_VALUE;

/* 端口信息 */
typedef union
{
    struct 
    {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
        ULONG gtx_loopback    : 1; /* [31   ] : RW GTX loop back     */    
        ULONG did_filter_enab : 1; /* [30   ] : RW did filter enable -- 0-enable 1-disable */
        ULONG speed           : 2; /* [28:29] : RW speed             -- 00 auto sense 01 1Gbps 10 2Gbps 11 4Gbps */
        ULONG credit          : 4; /* [24:27] : RW credit            -- set 0～15=>1～16 number of credit */
        ULONG sid             : 24;/* [ 0:23] : RW sid               -- self id */
#else

        ULONG sid             : 24;/* [ 0:23] : RW sid               -- self id */
        ULONG credit          : 4; /* [24:27] : RW credit            -- set 0～15=>1～16 number of credit */
        ULONG speed           : 2; /* [28:29] : RW speed             -- 00 auto sense 01 1Gbps 10 2Gbps 11 4Gbps */
        ULONG did_filter_enab : 1; /* [30   ] : RW did filter enable -- 0-enable 1-disable */
        ULONG gtx_loopback    : 1; /* [31   ] : RW GTX loop back     */
#endif        
    } u;
    ULONG value;
} PORT_INFO;

/* 通道信息 */
/* 写FLASH */
typedef struct
{
    ULONG direct;
    ULONG bitLen;
    ULONG addr;
    ULONG value1; /* low 32 */
    ULONG value2; /* high 32 */
} BURN_FLASH_REQ;

typedef struct
{
    ULONG result; /* 0-ok 1-ng */
    ULONG addr;
    ULONG value1; /* low 32 */
    ULONG value2; /* high 32 */
} BURN_FLASH_RESP, *PBURN_FLASH_RESP;

/******************************************************************************
* 接口函数                                                                    *
******************************************************************************/
/* 时间延时 */
void hw_delay(FCUINT CycleTime);

/* 创建通道 */
int hwCreateChannel(REG_HW *reg_hw, int direct, int mode, unsigned int index, int priority, int asmid, int fcid, int msg_recover);

/* 设置通道激活/非激活 */
void hwSetChannelActiveMode(REG_HW *reg_hw, ULONG mode, ULONG index, ULONG active);

/* 清除所有接收通道的配置 */
void hwClearAllChannel(REG_HW *reg_hw);

/* 设置端口的FCID */
void hwSetPortFcid(REG_HW *reg_hw, int credit);

/* 获取端口的FCID */
int hwGetPortFcid(REG_HW *reg_hw);

/* 设置端口的速率 */
void hwSetPortSpeed(REG_HW *reg_hw, int credit);

/* 获取端口的速率 */
int hwGetPortSpeed(REG_HW *reg_hw);

/*设置端口的DID过滤使能*/
void hwSetPortDidFilterEnab(REG_HW *reg_hw, int did_filter_enab);

/*获取端口的DID过滤使能*/
int hwGetPortDidFilterEnab(REG_HW *reg_hw);

/* 设置端口的信用 */
void hwSetPortCredit(REG_HW *reg_hw, int credit);

/* 获取端口的信用 */
int hwGetPortCredit(REG_HW *reg_hw);

/* 设置端口的回环 */
void hwSetPortGtxLoopBack(REG_HW *reg_hw, int gtx_loopback);

/* 获取端口的回环 */
int hwGetPortGtxLoopBack(REG_HW *reg_hw);

/* 设置端口的接收使能 */
void hwSetPortRxEnab(REG_HW *reg_hw, int enab);

/* 获取端口的接收使能 */
int hwGetPortRxEnab(REG_HW *reg_hw);

/* 设置消息丢弃使能 */
void hwSetDiscardEnab(REG_HW *reg_hw, int enab);

/* 获取消息丢弃使能 */
int hwGetDiscardEnab(REG_HW *reg_hw);

/* 获取FPGA的版本 */
int hwGetFpgaVersion(REG_HW *reg_hw);

/* 获取端口的状态 */
int hwGetPortStatus(REG_HW *reg_hw, int * portStatus, int portCount);

/* 读取电压 */
int hwGetVoltage(REG_HW *reg_hw);

/* 读取温度 */
int hwGetTemperature(REG_HW *reg_hw);

/* 复位FPGA */
void hwResetFpga(REG_HW *reg_hw, int forceOffLine);

/* 注册Tx的缓冲区 */
int hwRegisterTxDmaBuf(REG_HW *reg_hw, int index, int value);

/* 注册Rx的缓冲区 */
int hwRegisterRxDmaBuf(REG_HW *reg_hw, int priority, int index, int value);

/* 注册Rx的缓冲区的大小 */
void hwRegisterRxDmaBufSize(REG_HW *reg_hw, int priority, int buf_size);

/* 关闭/打开接收中断 */
int hwSetIntrptEnable(REG_HW *reg_hw, int bEnable);

/* 获取链路变化中断位 */
int hwGetLinkChangePending(REG_HW *reg_hw);
    
/*设置节点的同步角色*/
void hwSetSyncMode(REG_HW *reg_hw, FCUINT enab);


/* RTC控制 */
void hwRtcControl(REG_HW *reg_hw, int global_sync_enab, int event_period, int sync_enab, int rtc_base);

/*设置时钟同步周期*/
int hwSetClkSyncPeriod(REG_HW *reg_hw, int clkSyncPeriod);

void hwReadRtcPrepare(REG_HW *reg_hw);
void hwReadRtcFinish(REG_HW *reg_hw);

/*取得RTC时间*/
UINT64 hwGetRtc(REG_HW *reg_hw);

/*取得RTC日期*/
UINT32 hwGetDate(REG_HW *reg_hw);

/*设置RTC时间*/
void hwSetRtc(REG_HW *reg_hw,UINT64 time);

/* CARRIER_RTC_CTRL  载板时钟同步配置*/
void hwSetCarrierRTCSyn(REG_HW *reg_hw, int carrier_rtc_enb, int mode, int pluse_duty);

/*设置RTC日期*/
void hwSetDate(REG_HW *reg_hw, UINT32 date);

/*读取本地统计寄存器的值*/
void hwGetLocalStatisticsInfo(REG_HW *reg_hw, LocalStatisticsInfo *lsi);


/* 向FPGA写入BD */
void hwPushBufDesc(REG_HW *reg_hw, int dma_read_num, int buf_num, int channel_num, int priority, int raw_flag);

/* 向FPGA写入CREDIT */
void hwPushCredit(REG_HW *reg_hw, int priority, int buf_num_of_1st, int buf_num_of_2nd, int buf_num_of_3rd, int valid_buf_num);

/* 初始化OX_ID */
void hwInitOxid(REG_HW *reg_hw);

/* 初始化ELS通道和交换机的ELS通道 */
void hwInitElsChannel(REG_HW *reg_hw);

/*设置RAW通道的优先级*/
void SetRawPriority(REG_HW *reg_hw, int priority);

void hwSetRtcControlRxTx(REG_HW *reg_hw, int rx_enab, int tx_enab);

/* 初始化switch_id */
void hwInitSwitchId(REG_HW *reg_hw, ULONG switch_sid);

/* 设置通道的优先级 */
void SetChannelPriority(REG_HW *reg_hw, int index, int priority);

/* 设置hash值 */
UINT32 SetHashValue(REG_HW *reg_hw, ULONG asmid, ULONG fcid, ULONG channel_index);

/* 计算hash值 */
UCHAR Hash(ULONG low, ULONG high);

/* 清空hash表 */
void EmptyHashTable(REG_HW *reg_hw);

/* 初始化ASM头 */
void InitFcAsmHeader(PFC_ASM fc_asm, int asmid, int sid, int did);

void hwSysPciOutLong(ULONG address, ULONG data);

/* 读寄存器 */
ULONG ReadRegisterUlong(ULONG * reg);

/* 写寄存器 */
void WriteRegisterUlong(ULONG * reg, ULONG value);

/* 读间址寄存器 */
ULONG ReadIndirectRegisterUlong(REG_HW *reg_hw, ULONG ic_value);

/* 写间址寄存器 */
void WriteIndirectRegisterUlong(REG_HW *reg_hw, ULONG ic_value, ULONG id_value);

/******************************************************************************
* 调试函数                                                                    *
******************************************************************************/
/* 测试函数 检查hash值设置的是否正确 */
void dbgCheckHashCode(REG_HW *reg_hw, UCHAR hash_value, ULONG asmid, ULONG fcid, ULONG index);

ULONG dbgReadIndirectRegisterUlong(REG_HW *reg_hw, ULONG direct, ULONG address);

void dbgPrintReg(REG_HW *reg_hw);

#endif /* __HW_H__ */


