#ifndef __HW_H__
#define __HW_H__

#include <vxworks.h>
#include "hba.h"

/* �������� */
#define IDC_ACTION_READ                       0
#define IDC_ACTION_WRITE                      1
#define IDC_DIRECT_RX                         0
#define RX_INACTIVE                           0
#define RX_ACTIVE                             1
#define IDA_RX_LOGIC_BUF_BASE                 0x0

/* offset of indirect register */
#define IDA_RX_RAW_ACTIVE_BASE                0x1410
#define IDA_OX_ID_INIT_BASE                   0x1800
#define IDA_ELS_CHANNEL_BASE                  0x1900
#define IDA_SWITCH_ELS_CHANNEL_BASE           0x1920

/* �Ĵ������������������� */
typedef union _FPGA_VER 
{
    struct 
    {
#if _BYTE_ORDER == _BIG_ENDIAN
        ULONG reserve : 16;/* [16:31] : RW reserve */
        ULONG version : 16;/* [ 0:15] : RO fpga version -- fpga version*/
#else
        ULONG version : 16;/* [ 0:15] : RO fpga version -- fpga version*/
        ULONG reserve : 16;/* [16:31] : RW reserve */
#endif            
    } u;
    ULONG value;
} FPGA_VER;

typedef union _PORT_CONFIG {
    struct {
#if _BYTE_ORDER == _BIG_ENDIAN
#warning "ligang"
        ULONG reserve         : 1; /* [31   ] : RW reserve           --  */
        ULONG did_filter_enab : 1; /* [30   ] : RW did filter enable -- 0-enable 1-disable */
        ULONG speed           : 2; /* [28:29] : RW speed             -- 00 auto sense 01 1Gbps 10 2Gbps 11 4Gbps */
        ULONG credit          : 4; /* [24:27] : RW credit            -- set 0��15=>1��16 number of credit */
        ULONG sid             : 24;/* [ 0:23] : RW sid               -- self id */
#else
        ULONG sid             : 24;/* [ 0:23] : RW sid               -- self id */
        ULONG credit          : 4; /* [24:27] : RW credit            -- set 0��15=>1��16 number of credit */
        ULONG speed           : 2; /* [28:29] : RW speed             -- 00 auto sense 01 1Gbps 10 2Gbps 11 4Gbps */
        ULONG did_filter_enab : 1; /* [30   ] : RW did filter enable -- 0-enable 1-disable */
        ULONG reserve         : 1; /* [31   ] : RW reserve           --  */
#endif        
    } u;
    ULONG value;
} PORT_CONFIG;

typedef union _CREDIT {
    struct {
#if _BYTE_ORDER == _BIG_ENDIAN
        ULONG valid_buf_num  : 2; /* [30:31] : RW valid number of buffers */
        ULONG buf_num_of_3rd : 10;/* [20:29] : RW buffer number     -- 3rd available buffer number */
        ULONG buf_num_of_2nd : 10;/* [10:19] : RW buffer number     -- 2nd available buffer number */
        ULONG buf_num_of_1st : 10;/* [ 0: 9] : RW buffer number     -- 1st available buffer number */
#else
        ULONG buf_num_of_1st : 10;/* [ 0: 9] : RW buffer number     -- 1st available buffer number */
        ULONG buf_num_of_2nd : 10;/* [10:19] : RW buffer number     -- 2nd available buffer number */
        ULONG buf_num_of_3rd : 10;/* [20:29] : RW buffer number     -- 3rd available buffer number */
        ULONG valid_buf_num  : 2; /* [30:31] : RW valid number of buffers */
#endif
    } u;
    ULONG value;
} CREDIT;

typedef union _PORT_RX_ENAB {
    struct {
#if _BYTE_ORDER == _BIG_ENDIAN
    ULONG e_d_tov         :16; /* [16:31] : R E_d_tov value, unit is 1ms */
    ULONG redundancy_enab : 1; /* [15   ] : R Redundant enable '0' disable '1' enable */
    ULONG reserve         :12; /* [ 3:14] : R reserve */     
    ULONG reset           : 1; /* [ 2   ] : RW stop�Ժ�qdr buffer�� */
    ULONG p0_mac_switch   : 1; /* [ 1   ] : RW port0 Mac force off -- 0-mac on 1-mac off */
    ULONG p0_rx_enab      : 1; /* [ 0   ] : RW port0 RX enab       -- port0 rx enable 0-disable rx 1-enable rx */
#else
    ULONG p0_rx_enab      : 1; /* [ 0    ]  : RW port0 RX enab port0 rx enable 0-disable rx 1-enable rx */
    ULONG p0_mac_switch   : 1; /* [ 1   ]  : RW port0 Mac force off 0-mac on 1-mac off */
    ULONG reset           : 1; /* [ 2   ] : RW stop�Ժ�qdr buffer�� */
    ULONG reserve         :12; /* [ 3:14]  : R reserve */ 
    ULONG redundancy_enab : 1; /* [15   ]  : R Redundant enable '0' disable '1' enable */
    ULONG e_d_tov         :16; /* [16:31] : R E_d_tov value, unit is 1ms */
#endif
    } u;
    ULONG value;
} PORT_RX_ENAB;

typedef union _TIME_OUT {
    struct {
#if _BYTE_ORDER == _BIG_ENDIAN
    ULONG reserve :16; /* [16:31] : RW reserve*/
    ULONG time    :16; /* [ 0:15] : RW ��ʱʱ�䣬��λ�Ǻ��� */
#else
    ULONG time    :16; /* [ 0:15] : RW ��ʱʱ�䣬��λ�Ǻ��� */
    ULONG reserve :16; /* [16:31] : RW reserve*/
#endif
    } u;
    ULONG value;
} TIME_OUT;

typedef union _RTC_CONTROL {
    struct {
#if _BYTE_ORDER == _BIG_ENDIAN
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
        ULONG rtc_base         : 1; /* [18   ] : RW rtc base            -- 0-5x  division, used in 1G/2G mode
                                                                           1-10x division, used in 2G/4G mode */
        ULONG global_sync_enab : 1; /* [19   ] : RW hba global sync enable -- 0-disable 1-enable */
        ULONG reserve          : 12;/* [20:31] : RW reserve */
#endif
    } u;
    ULONG value;
} RTC_CONTROL;

typedef union _PORT_STATUS {
    struct {
#if _BYTE_ORDER == _BIG_ENDIAN
        ULONG temperature   : 12;/* [20:31] : RO fpga temperature */
        ULONG voltage       : 12;/* [ 8:19] : RO fpga voltage */
        ULONG reserve       : 4; /* [ 4: 7] : RW reserve */
        ULONG qdr_buf_empty : 1; /* [ 3   ] : RO wait qdr buffer is empty */
        ULONG reset_done    : 1; /* [ 2   ] : RO reset done */
        ULONG p1_status     : 1; /* [ 1   ] : RO port1 status -- 0-loss of sync 1-sync */
        ULONG p0_status     : 1; /* [ 0   ] : RO port0 status -- 0-loss of sync 1-sync */
#else
        ULONG p0_status     : 1; /* [ 0   ] : RO port0 status -- 0-loss of sync 1-sync */
        ULONG p1_status     : 1; /* [ 1   ] : RO port1 status -- 0-loss of sync 1-sync */
        ULONG reset_done    : 1; /* [ 2   ] : RO reset done */
        ULONG qdr_buf_empty : 1; /* [ 3   ] : RO wait qdr buffer is empty */
        ULONG reserve       : 4; /* [ 4: 7] : RW reserve */
        ULONG voltage       : 12;/* [ 8:19] : RO fpga voltage */
        ULONG temperature   : 12;/* [20:31] : RO fpga temperature */
#endif
    } u;
    ULONG value;
} PORT_STATUS;

typedef union _INDIRECT_CONTROL 
{
    struct 
    {
#if _BYTE_ORDER==_BIG_ENDIAN
        ULONG action   : 1;  /* [31   ] : RW action   -- 0-read operation 1-write operation */
        ULONG reserve0 : 1;  /* [30   ] : RW reserve */
        ULONG direct   : 1;  /* [29   ] : RW direct   -- 0-RX 1-TX */
        ULONG reserve1 : 13; /* [16:28] : RW reserve */
        ULONG address  : 16; /* [ 0:15] : RW address */
#else
        ULONG address  : 16; /* [ 0:15] : RW address */
        ULONG reserve1 : 13; /* [16:28] : RW reserve */
        ULONG direct   : 1;  /* [29   ] : RW direct   -- 0-RX 1-TX */
        ULONG reserve0 : 1;  /* [30   ] : RW reserve */
        ULONG action   : 1;  /* [31   ] : RW action   -- 0-read operation 1-write operation */
#endif        
    } u;
    ULONG value;
} INDIRECT_CONTROL;

typedef union _INDIRECT_DATA
{
    ULONG value;
} INDIRECT_DATA;

typedef union _QDR_DLY_DBG0
{
    struct 
    {
#if _BYTE_ORDER == _BIG_ENDIAN
        ULONG reserve0           : 5;/* [16:31] RW reserve */
        ULONG data_dly_inc       : 1;/* [15   ] RW data_dly_inc */
        ULONG data_dly_dec       : 1;/* [14   ] RW data_dly_dec */
        ULONG data_dly_rst       : 1;/* [13   ] RW data_dly_rst */
        ULONG data_dly_tap_value : 5;/* [ 8:12] RW data_dly_tap_value */
        ULONG cq_dly_inc         : 1;/* [ 7   ] RW cq_dly_inc */
        ULONG cq_dly_dec         : 1;/* [ 6   ] RW cq_dly_dec */
        ULONG cq_dly_rst         : 1;/* [ 5   ] RW cq_dly_rst */
        ULONG cq_dly_tap_value   : 5;/* [ 0: 4] RW cq_dly_tap_value */
#else
        ULONG cq_dly_tap_value   : 5;/* [ 0: 4] RW cq_dly_tap_value */
        ULONG cq_dly_rst         : 1;/* [ 5   ] RW cq_dly_rst */
        ULONG cq_dly_dec         : 1;/* [ 6   ] RW cq_dly_dec */
        ULONG cq_dly_inc         : 1;/* [ 7   ] RW cq_dly_inc */
        ULONG data_dly_tap_value : 5;/* [ 8:12] RW data_dly_tap_value */
        ULONG data_dly_rst       : 1;/* [13   ] RW data_dly_rst */
        ULONG data_dly_dec       : 1;/* [14   ] RW data_dly_dec */
        ULONG data_dly_inc       : 1;/* [15   ] RW data_dly_inc */                
        ULONG reserve0           : 5;/* [16:31] RW reserve */
#endif
    } u;
    ULONG value;
} QDR_DLY_DBG0;

typedef union _RTC_WRITE_HIGH {
    struct {
#if _BYTE_ORDER == _BIG_ENDIAN
        ULONG reserve : 22;/* [10:31] RW reserve */
        ULONG value   : 10;/* [ 0: 9] RW rtc high bit [32:41] */
#else
        ULONG value   : 10;/* [ 0: 9] RW rtc high bit [32:41] */
        ULONG reserve : 22;/* [10:31] RW reserve */
#endif
    } u;
    ULONG value;
} RTC_WRITE_HIGH;

typedef union _RTC_WRITE_LOW {
    ULONG value; /* [ 0:31] RW rtc low bit [ 0:31] */
} RTC_WRITE_LOW;

typedef union _RTC_READ_HIGH {
    struct {
#if _BYTE_ORDER == _BIG_ENDIAN
        ULONG reserve : 22;/* [10:31] RW reserve */
        ULONG value   : 10;/* [ 0: 9] RW rtc high bit [32:41] */
#else
        ULONG value   : 10;/* [ 0: 9] RW rtc high bit [32:41] */
        ULONG reserve : 22;/* [10:31] RW reserve */
#endif
    } u;
    ULONG value;
} RTC_READ_HIGH;

typedef union _RTC_READ_LOW {
    ULONG value; /* [ 0:31] RW rtc low bit [ 0:31] */
} RTC_READ_LOW;

typedef union _STATISTICS_CONTROL {
    struct {
#if _BYTE_ORDER == _BIG_ENDIAN
        ULONG start    : 1;  /* [   31] RW  set 1 start statistic, self clear */
        ULONG reserve  : 25; /* [ 4:30] RW */
        ULONG type     : 6;  /* [ 0: 3] RW 0-cur timestamp 32'b~41'b
                                               1-cur timestamp 0'b~31'b
                                               2-recv word num
                                               3-recv idle num
                                               4-recv frame num
                                               5-recv word num
                                               6-recv idle num
                                               7-recv frame num */
#else
        ULONG type     : 6;  /* [ 0: 3] RW 0-cur timestamp 32'b~41'b
                                               1-cur timestamp 0'b~31'b
                                               2-recv word num
                                               3-recv idle num
                                               4-recv frame num
                                               5-recv word num
                                               6-recv idle num
                                               7-recv frame num */
        ULONG reserve  : 25; /* [ 4:30] RW */
        ULONG start    : 1;  /* [   31] RW  set 1 start statistic, self clear */
#endif
    } u;
    ULONG value;
} STATISTICS_CONTROL;

typedef union _STATISTICS_DATA {
    ULONG value; /* [ 0:31] : RW data of statistics */
} STATISTICS_DATA;

typedef union _DIV_QDR_BUF_SIZE {
    ULONG value; /* [ 0:31] : RW divided qdr buffer size unit is 4096 bytes */
} DIV_QDR_BUF_SIZE;

typedef union _DIV_QDR_BUF_START_ADDR {
    ULONG value; /* [ 0:31] : RW buffer start address, for fpga usage */
} DIV_QDR_BUF_START_ADDR;

typedef union _FLASH_ADDR_CONTROL {
    struct {
#if _BYTE_ORDER == _BIG_ENDIAN
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

typedef union _INTERRUPT {
    struct {
#if _BYTE_ORDER == _BIG_ENDIAN
        ULONG intr_enable_global        : 1; /* [31  ] : RW */
        ULONG intr_enable_link_change   : 1; /* [30  ] : RW */
        ULONG intr_enable_send_bd_empty : 1; /* [29  ] : RW */
        ULONG intr_enable_Tx_IU         : 1; /* [28  ] : RW */
        ULONG intr_enable_Rx_credit_out : 1; /* [27  ] : RW */
        ULONG intr_enable_Rx_IU         : 1; /* [26  ] : RW */
        ULONG reserved                  : 21;/* [5:25] : RW */
        ULONG pending_link_change       : 1; /* [4   ] : RW */
        ULONG pending_send_bd_empty     : 1; /* [3   ] : RW */
        ULONG pending_Tx_IU             : 1; /* [2   ] : RW */
        ULONG pending_Rx_credit_out     : 1; /* [1   ] : RW */
        ULONG pending_Rx_IU             : 1; /* [0   ] : RW */
        
#else
        ULONG pending_Rx_IU             : 1; /* [0   ] : RW */
        ULONG pending_Rx_credit_out     : 1; /* [1   ] : RW */
        ULONG pending_Tx_IU             : 1; /* [2   ] : RW */
        ULONG pending_send_bd_empty     : 1; /* [3   ] : RW */
        ULONG pending_link_change       : 1; /* [4   ] : RW */
        ULONG reserved                  : 21;/* [5:25] : RW */
        ULONG intr_enable_Rx_IU         : 1; /* [26  ] : RW */
        ULONG intr_enable_Rx_credit_out : 1; /* [27  ] : RW */
        ULONG intr_enable_Tx_IU         : 1; /* [28  ] : RW */
        ULONG intr_enable_send_bd_empty : 1; /* [29  ] : RW */
        ULONG intr_enable_link_change   : 1; /* [30  ] : RW */
        ULONG intr_enable_global        : 1; /* [31  ] : RW */
#endif
    } u;
    ULONG value;
} INTERRUPT;

typedef union _RTC_DATE_WRITE {
    ULONG value; /* RTC�������üĴ��� */
} RTC_DATE_WRITE;

typedef union _RTC_DATE_READ {
    struct {
#if _BYTE_ORDER == _BIG_ENDIAN
        ULONG snap_shot_cmd : 1; /* [31   ] : RW snap shot command 1-�������� */
        ULONG reserve       : 15;/* [16:30] : RO reserve */
        ULONG real_time_day : 16;/* [ 0:15] : RO real time day */
#else
        ULONG real_time_day : 16;/* [ 0:15] : RO real time day */
        ULONG reserve       : 15;/* [16:30] : RO reserve */
        ULONG snap_shot_cmd : 1; /* [31   ] : RW snap shot command 1-�������� */
#endif
    } u;
    ULONG value;
} RTC_DATE_READ;

typedef union _SFP_RX_DBG {
    struct {
#if _BYTE_ORDER == _BIG_ENDIAN
        ULONG dat_in_byte   : 8; /* [24:31] : RO DAT_IN_BYTE */
        ULONG sop_in_cnt    : 4; /* [20:23] : RO SOP_IN_CNT */
        ULONG eop_in_cnt    : 4; /* [16:19] : RO EOP_IN_CNT */
        ULONG dat_out_byte  : 8; /* [ 8:15] : RO DAT_OUT_BYTE */
        ULONG sop_out_cnt   : 4; /* [ 4: 7] : RO SOP_OUT_CNT */
        ULONG eop_out_cnt   : 4; /* [ 0: 3] : RO EOP_OUT_CNT */
#else
        ULONG eop_out_cnt   : 4; /* [ 0: 3] : RO EOP_OUT_CNT */
        ULONG sop_out_cnt   : 4; /* [ 4: 7] : RO SOP_OUT_CNT */
        ULONG dat_out_byte  : 8; /* [ 8:15] : RO DAT_OUT_BYTE */
        ULONG eop_in_cnt    : 4; /* [16:19] : RO EOP_IN_CNT */
        ULONG sop_in_cnt    : 4; /* [20:23] : RO SOP_IN_CNT */        
        ULONG dat_in_byte   : 8; /* [24:31] : RO DAT_IN_BYTE */
#endif
    } u;
    ULONG value;
} SFP_RX_DBG;

/* �Ĵ������� */
typedef struct _REG_HW {
    ULONG FPGA_VER;
       /* offset  : 0x00
       [16:31] : RW reserve           -- reserve
       [ 0:15] : RO fpga version      -- fpga version */
    ULONG PORT_CONFIG;
    /* offset  : 0x04
       [   31] : RW reserve           -- 
       [   30] : RW did filter enable -- 0-enable 1-disable default '1'
       [28:29] : RW speed             -- 00 auto sense 01 1Gbps 10 2Gbps 11 4Gbps
       [24:27] : RW credit            -- set 0000'b��1111'b=>1��16 number of credit default '1'
       [ 0:23] : RW sid               -- self id default '0' */
       ULONG CREDIT;
    /* offset  : 0x08
       [30:31] : RW valid number of buffers:[1, 3]
       [20:29] : RW 3rd available buffer number
       [10:19] : RW 2nd available buffer number
       [ 0: 9] : RW 1st available buffer number */
    ULONG PORT_RX_ENAB;
    /* offset  : 0x0C
       [16:31] : E_d_tov value, ��λΪ1ms
       [15   ] : Redundant enable       --1-ʹ�� 0-��ʹ��
       [ 3:14] : reserve   
       [ 2   ] : RW cpu soft reset
       [ 1   ] : RW port0 Mac force off -- 0-mac on 1-mac off
       [ 0   ] : RW port0 RX enab       -- port0 rx enable 0-disable rx 1-enable rx
                    ���������(����1)��ֹͣ(����0)*/
    ULONG TIME_OUT;
    /* offset  : 0x10
       [16:31] : RW reserve
       [ 0:15] : RW ��ʱʱ�䣬��λ�Ǻ��� */
    ULONG RTC_CONTROL;
    /* offset  : 0x14
       [20:31] : RW reserve
       [19   ] : RW Hba card hba global sync enable -- 0-disable 1-enable
       [18   ] : RW rtc base           -- 0- 5x division,used in 1G/2G mode
                                          1-10x division,used in 2G/4G mode
       [17   ] : RW port1 sync enable  -- 0-disable 1-enable
       [16   ] : RW port0 sync enable  -- 0-disable 1-enable
       [ 0:15] : RW event period unit is ms
                    Note: The actual event period equals the programmed value plus one.*/
    ULONG PORT_STATUS;
    /* offset  : 0x18
       [20:31] : RO fpga temperature
       [ 8:19] : RO fpga voltage
       [ 4: 7] : RW reserve            -- reserve
       [ 3   ] : RO stop�Ժ�QDR Buffer��
       [ 2   ] : RO reset done
       [ 1   ] : RO port1 status       -- 0-loss of sync 1-sync
       [ 0   ] : RO port0 status       -- 0-loss of sync 1-sync */
    ULONG INDIRECT_CONTROL;
    /* offset  : 0x1C
       [31   ] : RW direct flag        -- 0-host read 1-host write
       [30   ] : RW reserve
       [29   ] : RW direct             -- 0-RX 1-TX
       [16:28] : RW reserve
       [ 0:15] : RW address */
    ULONG INDIRECT_DATA;
    /* offset  : 0x20
       [ 0:31] : RW data*/
       ULONG QDR_DLY_DBG0;
    /* offset  : 0x24
       [16:31] : RW reserve
       [15   ] : RW data_dly_inc
       [14   ] : RW data_dly_dec
       [13   ] : RW data_dly_rst
       [ 8:12] : RW data_dly_tap_value
       [ 7   ] : RW cq_dly_inc
       [ 6   ] : RW cq_dly_dec
       [ 5   ] : RW cq_dly_rst
       [ 0: 4] : RW cq_dly_tap_value
       */
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
       [ 6:30] : RW reserve
       [ 0: 5] : RW type of statistic         -- 0-cur timestamp low [ 0:31]
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
       [ 0:31] : RO data of statistics */
    ULONG DIV_QDR_BUF_SIZE;
    /* offset  : 0x40
       [ 0:31] : RW divided qdr buffer size unit is 4096 bytes*/
   ULONG DIV_QDR_BUF_START_ADDR;
    /* offset  : 0x44
       [ 0:31] : RW buffer start address, for fpga usage*/
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
       [31   ] : RW Global intr enable
       [30   ] : RW Link change intr enable
       [29   ] : RW ���з���bd fifo���ж�ʹ��
       [28   ] : RW Tx IU intr enable
       [27   ] : RW �κ�һ�����ȼ��������ж�ʹ��
       [26   ] : RW Rx IU intr enable
       [ 5:25] : RW reserved
       [ 4   ] : RW Link change intr pending
       [ 3   ] : RW ���з���bd fifo���жϷ���
       [ 2   ] : RW Tx IU intr pending
       [ 1   ] : RW �κ�һ�����ȼ��������жϷ���
       [ 0   ] : RW Rx IU intr pending*/
    ULONG RTC_DATE_WRITE;
    /* offset : 0x50 RTC�������üĴ��� */
    ULONG RTC_DATE_READ;
    /* offset : 0x54 RTC����ʵʱ�Ĵ���
       [31   ] : RW snap shot command 1-��������
       [16:30] : RO reserve
       [ 0:15] : RO real time day*/
    ULONG RESERVE_0x58;    /* offset : 0x58 */
    ULONG RESERVE_0x5C;    /* offset : 0x5C */
    ULONG RESERVE_0x60;    /* offset : 0x60 */
    ULONG RESERVE_0x64;    /* offset : 0x64 */
    ULONG SFP_RX_DBG;
    /* offset : 0x68 SFP_RX���ԼĴ���
       [24:31] : RO DAT_IN_BYTE
       [20:23] : RO SOP_IN_CNT
       [16:19] : RO EOP_IN_CNT
       [ 8:15] : RO DAT_OUT_BYTE
       [ 4: 7] : RO SOP_OUT_CNT
       [ 0: 3] : RO EOP_OUT_CNT */
} REG_HW, *PREG_HW;

/* ��FPGA�����Ŀ������� */
/* RX ���� */
typedef union _R0 {
    struct {
        ULONG length;
    } u;
    ULONG value;
} R0;

typedef union _R1 {
    struct {
#if _BYTE_ORDER == _BIG_ENDIAN
        ULONG reserve      : 24;/* [ 8:31] : RW reserve */
        ULONG channel_num : 8; /* [ 0:    7] : RW channel num */
#else        
        ULONG channel_num : 8; /* [ 0:  7] : RW channel num */
        ULONG reserve     : 24;/* [ 8:31] : RW reserve */
#endif
    } u;
    ULONG value;
} R1;

typedef struct _R_CTRL {
    R0 r0;
    R1 r1;
} R_CTRL, *PR_CTRL;

/*----------------------------�ӿں���-----------------------------*/
/* ȡ�ö˿ڵ�״̬ */
int hwGetPortStatus(PREG_HW reg_hw, int *portStatus, int portCount);
/* ȡ��QDR��������״̬ */
int hwGetQdrBufferEmpty(PREG_HW reg_hw);
/* ȡ��reset�Ľ�� */
int hwGetSoftResetDone(PREG_HW reg_hw);
/* ����cpu soft reset */
void hwSetSoftReset(PREG_HW reg_hw);
/* ��ȡFPGA�汾��Ϣ */
int hwGetFpgaVersion(PREG_HW reg_hw);
/* �˿ڵ�FCID */
void hwSetPortFcid(PREG_HW reg_hw, int fcid);
int hwGetPortFcid(PREG_HW reg_hw);
/* ���� */
void hwSetPortCreditNum(PREG_HW reg_hw, int credit);
int hwGetPortCreditNum(PREG_HW reg_hw);
/* ���� 0 ����Ӧ 1-1Gbps 2-2Gbps */
void hwSetPortSpeed(PREG_HW reg_hw, int speed);
int hwGetPortSpeed(PREG_HW reg_hw);
/* ���շ���DID����ʹ�� */
void hwSetPortDidFilterEnab(PREG_HW reg_hw, int did_filter_enab);
int hwGetPortDidFilterEnab(PREG_HW reg_hw);
/* e_d_tovʱ�䣬��λ�Ǻ��� */
void hwSetPortEdtovTime(PREG_HW reg_hw, int e_d_tov);
int hwGetPortEdtovTime(PREG_HW reg_hw);
/* ����ʹ�� 0-��ֹ 1-ʹ�� */
void hwSetPortRedundantEnab(PREG_HW reg_hw, int redundancy_enab);
int hwGetPortRedundantEnab(PREG_HW reg_hw);
/* ��ʱ���ǵ�ʱ�䣬��λ�Ǻ��� */
void hwSetPortTimeOut(PREG_HW reg_hw, int time);
int hwGetPortTimeOut(PREG_HW reg_hw);
/* ���ÿ�������λ */
void hwReadRtcPrepare(PREG_HW reg_hw);
/* �����������λ */
void hwReadRtcFinish(PREG_HW reg_hw);
/* ��ȡRTC */
UINT64 hwGetRtc(PREG_HW reg_hw);
/*д��RTC */
void hwSetRtc(PREG_HW reg_hw, UINT32 high, UINT32 low);
/* ��ȡ���� */
UINT32 hwGetDate(PREG_HW reg_hw);
/* д������ */
void hwSetDate(PREG_HW reg_hw, UINT32 date);
/* ʹ��/��ֹ�ж�λ */
void hwSetIntrptEnable(PREG_HW reg_hw, int enab);
/* ��ȡ��ѹ */
int hwGetVoltage(PREG_HW reg_hw);
/* ��ȡ�¶� */
int hwGetTemperature(PREG_HW reg_hw);
/* ע��Rx�Ļ����� */
void hwRegisterRxDmaBuf(PREG_HW reg_hw, int index, int value);
 /* ����Qdr buffer size */
void  hwQdrConfigBufferSize(PREG_HW reg_hw, int size);
 /* ����ÿ��Qdr buffer�Ŀ�ʼ��ַ  */
void hwQdrConfigBufferStartAddress(PREG_HW reg_hw, int start_address);
/* ��FPGAд����CREDIT */
void hwPushCreditsToFpga(PREG_HW reg_hw, INT32 *credits, INT32 valid_buf_num);
/* ��ȡ��·�仯�ж�λ */
int hwGetLinkChangePending(PREG_HW reg_hw);
/* ���Ĵ��� */
ULONG ReadRegisterUlong(ULONG* reg);
/* д�Ĵ��� */
void WriteRegisterUlong(ULONG* reg, ULONG value);
/* ����ַ�Ĵ��� */
ULONG ReadIndirectRegisterUlong(PREG_HW reg_hw, ULONG ic_value);
/* д��ַ�Ĵ��� */
void WriteIndirectRegisterUlong(PREG_HW reg_hw, ULONG ic_value, ULONG id_value);

#endif /* __HW_H__ */