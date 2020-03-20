#ifndef __HW_H__
#define __HW_H__

///////////////////////////////////////////////////////////////////////////////
// 硬件相关
///////////////////////////////////////////////////////////////////////////////
#define IDC_ACTION_READ                       0
#define IDC_ACTION_WRITE                      1
#define IDC_DIRECT_RX                         0
#define RX_INACTIVE                           0
#define RX_ACTIVE                             1
#define IDA_RX_LOGIC_BUF_BASE                 0x0

///////////////////////////////////////////////////////////////////////////////
// 寄存器的联合体描述定义
///////////////////////////////////////////////////////////////////////////////
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

typedef union _PORT_CONFIG
{
    struct
    {
#if _BYTE_ORDER == _BIG_ENDIAN
        ULONG reserve         : 1; /* [31   ] : RW reserve           --  */
        ULONG did_filter_enab : 1; /* [30   ] : RW did filter enable -- 0-enable 1-disable */
        ULONG speed           : 2; /* [28:29] : RW speed             -- 00 auto sense 01 1Gbps 10 2Gbps 11 4Gbps */
        ULONG credit          : 4; /* [24:27] : RW credit            -- set 0～15=>1～16 number of credit */
        ULONG sid             : 24;/* [ 0:23] : RW sid               -- self id */
#else
        ULONG sid             : 24;/* [ 0:23] : RW sid               -- self id */
        ULONG credit          : 4; /* [24:27] : RW credit            -- set 0～15=>1～16 number of credit */
        ULONG speed           : 2; /* [28:29] : RW speed             -- 00 auto sense 01 1Gbps 10 2Gbps 11 4Gbps */
        ULONG did_filter_enab : 1; /* [30   ] : RW did filter enable -- 0-enable 1-disable */
        ULONG reserve         : 1; /* [31   ] : RW reserve           --  */
#endif        
    } u;
    ULONG value;
} PORT_CONFIG;

typedef union _CREDIT
{
    struct
    {
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

typedef union _PORT_RX_ENAB
{
    struct
    {
#if _BYTE_ORDER == _BIG_ENDIAN
        ULONG e_d_tov         : 16;/* [16:31] : R E_d_tov value, unit is 1ms */
        ULONG redundancy_enab : 1; /* [15   ] : R Redundant enable '0' disable '1' enable */
        ULONG reserve         : 12;/* [ 3:14] : R reserve */
        ULONG reset           : 1; /* [ 2   ] : RW stop以后，qdr buffer空 */
        ULONG p0_mac_switch   : 1; /* [ 1   ] : RW port0 Mac force off -- 0-mac on 1-mac off */
        ULONG p0_rx_enab      : 1; /* [ 0   ] : RW port0 RX enab       -- port0 rx enable 0-disable rx 1-enable rx */
#else
        ULONG p0_rx_enab      : 1; /* [ 0   ] : RW port0 RX enab port0 rx enable 0-disable rx 1-enable rx */
        ULONG p0_mac_switch   : 1; /* [ 1   ] : RW port0 Mac force off 0-mac on 1-mac off */
        ULONG reset           : 1; /* [ 2   ] : RW stop以后，qdr buffer空 */
        ULONG reserve         : 12;/* [ 3:14] : R reserve */
        ULONG redundancy_enab : 1; /* [15   ] : R Redundant enable '0' disable '1' enable */
        ULONG e_d_tov         : 16;/* [16:31] : R E_d_tov value, unit is 1ms */
#endif
    } u;
    ULONG value;
} PORT_RX_ENAB;

typedef union _TIME_OUT
{
    struct
    {
#if _BYTE_ORDER == _BIG_ENDIAN
        ULONG reserve : 16; /* [16:31] : RW reserve*/
        ULONG time    : 16; /* [ 0:15] : RW 超时时间，单位是毫秒 */
#else
        ULONG time    : 16; /* [ 0:15] : RW 超时时间，单位是毫秒 */
        ULONG reserve : 16; /* [16:31] : RW reserve*/
#endif
    } u;
    ULONG value;
} TIME_OUT;

typedef union _RTC_CONTROL
{
    struct
    {
#if _BYTE_ORDER == _BIG_ENDIAN
        ULONG reserve          : 11;/* [21:31] : RW reserve */
        ULONG rtc_enab         : 1; /* [20   ] : RW write rtc enable -- 0-disable 1-enable */
        ULONG global_sync_enab : 1; /* [19   ] : RW hba global sync enable    -- 0-disable 1-enable */
        ULONG rtc_base         : 1; /* [18   ] : RW rtc base -- 0-5x  division, used in 1G/2G mode
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
        ULONG rtc_base         : 1; /* [18   ] : RW rtc base -- 0-5x  division, used in 1G/2G mode
                                                                1-10x division, used in 2G/4G mode */
        ULONG global_sync_enab : 1; /* [19   ] : RW hba global sync enable -- 0-disable 1-enable */
        ULONG rtc_enab         : 1; /* [20   ] : RW write rtc enable -- 0-disable 1-enable */
        ULONG reserve          : 11;/* [21:31] : RW reserve */
#endif
    } u;
    ULONG value;
} RTC_CONTROL;

typedef union _PORT_STATUS
{
    struct 
    {
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

typedef union _RTC_WRITE_HIGH
{
    struct
    {
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

typedef union _RTC_WRITE_LOW
{
    ULONG value; /* [ 0:31] RW rtc low bit [ 0:31] */
} RTC_WRITE_LOW;

typedef union _RTC_READ_HIGH
{
    struct
    {
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

typedef union _RTC_READ_LOW
{
    ULONG value; /* [ 0:31] RW rtc low bit [ 0:31] */
} RTC_READ_LOW;

typedef union _STATISTICS_CONTROL
{
    struct
    {
#if _BYTE_ORDER == _BIG_ENDIAN
        ULONG start   : 1;  /* [   31] RW set 1 start statistic, self clear */
        ULONG reserve : 25; /* [ 4:30] RW */
        ULONG type    : 6;  /* [ 0: 3] RW 0-cur timestamp 32'b~41'b
                                          1-cur timestamp 0'b~31'b
                                          2-recv word num
                                          3-recv idle num
                                          4-recv frame num
                                          5-recv word num
                                          6-recv idle num
                                          7-recv frame num */
#else
        ULONG type    : 6;  /* [ 0: 3] RW 0-cur timestamp 32'b~41'b
                                          1-cur timestamp 0'b~31'b
                                          2-recv word num
                                          3-recv idle num
                                          4-recv frame num
                                          5-recv word num
                                          6-recv idle num
                                          7-recv frame num */
        ULONG reserve : 25; /* [ 4:30] RW */
        ULONG start   : 1;  /* [   31] RW set 1 start statistic, self clear */
#endif
    } u;
    ULONG value;
} STATISTICS_CONTROL;

typedef union _STATISTICS_DATA
{
    ULONG value; /* [ 0:31] : RW data of statistics */
} STATISTICS_DATA;

typedef union _DIV_QDR_BUF_SIZE
{
    ULONG value; /* [ 0:31] : RW divided qdr buffer size unit is 4096 bytes */
} DIV_QDR_BUF_SIZE;

typedef union _DIV_QDR_BUF_START_ADDR
{
    ULONG value; /* [ 0:31] : RW buffer start address, for fpga usage */
} DIV_QDR_BUF_START_ADDR;

typedef union _FLASH_ADDR_CONTROL
{
    struct
    {
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

typedef union _INTERRUPT_CTRL
{
    struct
    {
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
} INTERRUPT_CTRL;

typedef union _RTC_DATE_WRITE
{
    ULONG value; /* RTC天数配置寄存器 */
} RTC_DATE_WRITE;

typedef union _RTC_DATE_READ
{
    struct
    {
#if _BYTE_ORDER == _BIG_ENDIAN
        ULONG snap_shot_cmd : 1; /* [31   ] : RW snap shot command 1-启动快照 */
        ULONG reserve       : 15;/* [16:30] : RO reserve */
        ULONG real_time_day : 16;/* [ 0:15] : RO real time day */
#else
        ULONG real_time_day : 16;/* [ 0:15] : RO real time day */
        ULONG reserve       : 15;/* [16:30] : RO reserve */
        ULONG snap_shot_cmd : 1; /* [31   ] : RW snap shot command 1-启动快照 */
#endif
    } u;
    ULONG value;
} RTC_DATE_READ;

typedef union _SFP_RX_DBG
{
    struct
    {
#if _BYTE_ORDER == _BIG_ENDIAN
        ULONG dat_in_byte  : 8; /* [24:31] : RO DAT_IN_BYTE */
        ULONG sop_in_cnt   : 4; /* [20:23] : RO SOP_IN_CNT */
        ULONG eop_in_cnt   : 4; /* [16:19] : RO EOP_IN_CNT */
        ULONG dat_out_byte : 8; /* [ 8:15] : RO DAT_OUT_BYTE */
        ULONG sop_out_cnt  : 4; /* [ 4: 7] : RO SOP_OUT_CNT */
        ULONG eop_out_cnt  : 4; /* [ 0: 3] : RO EOP_OUT_CNT */
#else
        ULONG eop_out_cnt  : 4; /* [ 0: 3] : RO EOP_OUT_CNT */
        ULONG sop_out_cnt  : 4; /* [ 4: 7] : RO SOP_OUT_CNT */
        ULONG dat_out_byte : 8; /* [ 8:15] : RO DAT_OUT_BYTE */
        ULONG eop_in_cnt   : 4; /* [16:19] : RO EOP_IN_CNT */
        ULONG sop_in_cnt   : 4; /* [20:23] : RO SOP_IN_CNT */
        ULONG dat_in_byte  : 8; /* [24:31] : RO DAT_IN_BYTE */
#endif
    } u;
    ULONG value;
} SFP_RX_DBG;

/* 寄存器定义 */
typedef struct _REG_HW
{
    ULONG FPGA_VER;
    /* offset  : 0x00
    [16:31] : RW reserve      -- reserve
    [ 0:15] : RO fpga version -- fpga version */
    ULONG PORT_CONFIG;
    /* offset  : 0x04
    [   31] : RW reserve           --
    [   30] : RW did filter enable -- 0-enable 1-disable default '1'
    [28:29] : RW speed             -- 00 auto sense 01 1Gbps 10 2Gbps 11 4Gbps
    [24:27] : RW credit            -- set 0000'b～1111'b=>1～16 number of credit default '1'
    [ 0:23] : RW sid               -- self id default '0' */
    ULONG CREDIT;
    /* offset  : 0x08
    [30:31] : RW valid number of buffers:[1, 3]
    [20:29] : RW 3rd available buffer number
    [10:19] : RW 2nd available buffer number
    [ 0: 9] : RW 1st available buffer number */
    ULONG PORT_RX_ENAB;
    /* offset  : 0x0C
    [16:31] : E_d_tov value, unit 1ms
    [15   ] : Redundant enable --1-使能 0-不使能
    [ 3:14] : reserve
    [ 2   ] : RW cpu soft reset
    [ 1   ] : RW port0 Mac force off -- 0-mac on 1-mac off
    [ 0   ] : RW port0 RX enab -- port0 rx enable 0-disable rx 1-enable rx
    软件的启动(设置1)和停止(设置0)*/
    ULONG TIME_OUT;
    /* offset  : 0x10
    [16:31] : RW reserve
    [ 0:15] : RW timeout, unit 1ms */
    ULONG RTC_CONTROL;
    /* offset  : 0x14
    [21:31] : RW reserve
    [20   ] : RW rtc write enable -- 0-disable 1-enable
    [19   ] : RW Hba card hba global sync enable -- 0-disable 1-enable
    [18   ] : RW rtc base -- 0-5x  division,used in 1G/2G mode
                             1-10x division,used in 2G/4G mode
    [17   ] : RW port1 sync enable -- 0-disable 1-enable
    [16   ] : RW port0 sync enable -- 0-disable 1-enable
    [ 0:15] : RW event period unit is ms
                 Note: The actual event period equals the programmed value plus one.*/
    ULONG PORT_STATUS;
    /* offset  : 0x18
    [20:31] : RO fpga temperature
    [ 8:19] : RO fpga voltage
    [ 4: 7] : RW reserve  -- reserve
    [ 3   ] : RO stop以后，QDR Buffer空
    [ 2   ] : RO reset done
    [ 1   ] : RO port1 status -- 0-loss of sync 1-sync
    [ 0   ] : RO port0 status -- 0-loss of sync 1-sync */
    ULONG INDIRECT_CONTROL;
    /* offset  : 0x1C
    [31   ] : RW direct flag  -- 0-host read 1-host write
    [30   ] : RW reserve
    [29   ] : RW direct       -- 0-RX 1-TX
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
    [31   ] : RW start statistic   -- RW set 1 start statistic, self clear
    [ 6:30] : RW reserve
    [ 0: 5] : RW type of statistic --
                 0-cur timestamp low [ 0:31]
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
    [31   ] : RW wr_flash -- write flash enable 1-enable 0-disable
    [30   ] : RW wr_flash_debug
    [29   ] : RW rd_flash -- read flash enable 1-enable 0-disable
    [28   ] : RW rd_flash_debug
    [24:27] : RW reserve
    [ 0:23] : RW flash_addr */
    ULONG INTERRUPT_CTRL;
    /* offset  : 0x4C
    [31   ] : RW Global intr enable
    [30   ] : RW Link change intr enable
    [29   ] : RW 所有发送bd fifo空中断使能
    [28   ] : RW Tx IU intr enable
    [27   ] : RW 任何一个优先级无信用中断使能
    [26   ] : RW Rx IU intr enable
    [ 5:25] : RW reserved
    [ 4   ] : RW Link change intr pending
    [ 3   ] : RW 所有发送bd fifo空中断发生
    [ 2   ] : RW Tx IU intr pending
    [ 1   ] : RW 任何一个优先级无信用中断发生
    [ 0   ] : RW Rx IU intr pending*/
    ULONG RTC_DATE_WRITE;
    /* offset : 0x50 RTC天数配置寄存器 */
    ULONG RTC_DATE_READ;
    /* offset : 0x54 RTC天数实时寄存器
    [31   ] : RW snap shot command 1-启动快照
    [16:30] : RO reserve
    [ 0:15] : RO real time day*/
    ULONG RESERVE_0x58;    /* offset : 0x58 */
    ULONG RESERVE_0x5C;    /* offset : 0x5C */
    ULONG RESERVE_0x60;    /* offset : 0x60 */
	ULONG CONFIG_SW_FCID;  /* offset : 0x64  switch fcid */
    ULONG SFP_RX_DBG;
    /* offset : 0x68 SFP_RX调试寄存器
    [24:31] : RO DAT_IN_BYTE
    [20:23] : RO SOP_IN_CNT
    [16:19] : RO EOP_IN_CNT
    [ 8:15] : RO DAT_OUT_BYTE
    [ 4: 7] : RO SOP_OUT_CNT
    [ 0: 3] : RO EOP_OUT_CNT */
} REG_HW, *PREG_HW;

/*----------------------------接口函数-----------------------------*/
/* 取得端口状态 */
VOID HwGetPortStatus(
    IN PREG_HW reg_hw,
    IN ULONG *portStatus,
    IN INT32 portCount
);

/* 取得QDR缓冲区状态 */
ULONG HwGetQdrBufState(
    IN PREG_HW reg_hw
);

/* 复位FPGA */
VOID HwResetFpga(
    IN PREG_HW reg_hw,
    IN ULONG force_off_line
);

/* 获取FPGA版本 */
ULONG HwGetFpgaVersion(
    IN PREG_HW reg_hw
);

/* FCID */
VOID HwSetPortFcid(
    IN PREG_HW reg_hw,
    IN ULONG fcid
);

/* FCID */
ULONG HwGetPortFcid(
    IN PREG_HW reg_hw
);

/* 信用 */
VOID HwSetPortCreditNum(
    IN PREG_HW reg_hw,
    IN ULONG credit
);

ULONG HwGetPortCreditNum(
    IN PREG_HW reg_hw
);

/* 速率 */
VOID HwSetPortSpeed(
    IN PREG_HW reg_hw,
    IN ULONG speed
);

ULONG HwGetPortSpeed(
    IN PREG_HW reg_hw
);

/* 接收方向DID过滤使能 */
VOID HwSetPortDidFilterEnab(
    IN PREG_HW reg_hw,
    IN ULONG did_filter_enab
);

ULONG HwGetPortDidFilterEnab(
    IN PREG_HW reg_hw
);

/* e_d_tov */
VOID HwSetPortEdtovTime(
    IN PREG_HW reg_hw,
    IN ULONG e_d_tov
);

ULONG HwGetPortEdtovTime(
    IN PREG_HW reg_hw
);

/* 冗余使能 */
VOID HwSetPortRedundantEnab(
    IN PREG_HW reg_hw,
    IN ULONG redundancy_enab
);

ULONG HwGetPortRedundantEnab(
    IN PREG_HW reg_hw
);

/* 端口接收使能 */
VOID HwSetPortRxEnab(
    IN PREG_HW reg_hw,
    IN ULONG rx_enab
);

ULONG HwGetPortRxEnab(
    IN PREG_HW reg_hw
);

/* 超时覆盖时间 */
VOID HwSetPortTimeOut(
    IN PREG_HW reg_hw,
    IN ULONG time
);

ULONG HwGetPortTimeOut(
    IN PREG_HW reg_hw
);

/* 控制RTC */
VOID HwRtcControl(
    IN PREG_HW reg_hw,
    IN ULONG global_sync_enab,
    IN ULONG event_period,
    IN ULONG sync_enab,
    IN ULONG rtc_base
);

/* 设置快照命令 */
VOID HwReadRtcPrepare(
    IN PREG_HW reg_hw
);

/* 清除快照命令 */
VOID HwReadRtcFinish(
    IN PREG_HW reg_hw
);

/* RTC */
UINT64 HwGetRtc(
    IN PREG_HW reg_hw
);

VOID HwSetRtc(
    IN PREG_HW reg_hw,
    IN UINT64 ns
);

/* 配置交换机的FCID */
VOID HwSetSwFcid(
	IN PREG_HW reg_hw,
	IN UINT32 fcid
	);

/* 中断位使能 */
VOID HwSetIntrptEnable(
    IN PREG_HW reg_hw,
    IN ULONG enab
);

/* 电压 */
ULONG HwGetVoltage(
    IN PREG_HW reg_hw
);

/* 温度 */
ULONG HwGetTemperature(
    IN PREG_HW reg_hw
);

/* 注册Rx的缓冲区 */
VOID HwRegisterRxDmaBuf(
    IN PREG_HW reg_hw,
    IN ULONG index,
    IN ULONG value
);

/* 配置QDR BUF SIZE */
VOID HwSetQdrBufUnitSize(
    IN PREG_HW reg_hw,
    IN ULONG size
);

ULONG HwGetQdrBufUnitSize(
    IN PREG_HW reg_hw
);

/* 配置每个QDR BUF开始地址 */
VOID HwSetQdrBufStartAddress(
    IN PREG_HW reg_hw,
    IN ULONG start_address
);

/* 向FPGA写入多个CREDIT */
VOID HwPushCreditsToFpga(
    IN PREG_HW reg_hw,
    IN ULONG *credits,
    IN ULONG valid_buf_num
);

/* 获取链路变化中断位 */
ULONG HwGetLinkChangePending(
    IN PREG_HW reg_hw
);

/* 直接寄存器 */
ULONG ReadRegisterUlong(
    IN PULONG reg
);

VOID WriteRegisterUlong(
    IN PULONG reg,
    IN ULONG value
);

/* 间址寄存器 */
ULONG ReadIndirectRegisterUlong(
    IN PREG_HW reg_hw,
    IN ULONG ic_value
);

VOID WriteIndirectRegisterUlong(
    IN PREG_HW reg_hw,
    IN ULONG ic_value,
    IN ULONG id_value
);

/* 根据Type获取统计信息 */
UINT32 HwGetStatisticsByType
(
    IN PREG_HW reg_hw,
    UINT32 type
);

/* 取得统计值 */
VOID HwGetStatistics(
    IN PREG_HW reg_hw,
    IN PFPGA_STATISTICS_INFO fsi,
    IN PPORT_STATISTICS_INFO psi
);

/* 手动自检 */
VOID HwManualSelfCheck(
    IN PREG_HW reg_hw,
    IN PFC_BIT_RESULT_MANUAL bitResult
);

EVT_WDF_DEVICE_PREPARE_HARDWARE EvtDevicePrepareHardware;
EVT_WDF_DEVICE_RELEASE_HARDWARE EvtDeviceReleaseHardware;
EVT_WDF_INTERRUPT_ISR EvtInterruptIsr;
EVT_WDF_INTERRUPT_DPC EvtInterruptDpc;
EVT_WDF_INTERRUPT_ENABLE EvtInterruptEnable;
EVT_WDF_DEVICE_D0_ENTRY_POST_INTERRUPTS_ENABLED EvtDeviceD0EntryPostInterruptsEnabled;
EVT_WDF_DEVICE_D0_EXIT_PRE_INTERRUPTS_DISABLED EvtDeviceD0ExitPreInterruptsDisabled;
EVT_WDF_INTERRUPT_DISABLE EvtInterruptDisable;

#ifdef ALLOC_PRAGMA
#pragma alloc_text(PAGE, EvtDevicePrepareHardware)
#pragma alloc_text(PAGE, EvtDeviceReleaseHardware)
#pragma alloc_text(PAGE, EvtDeviceD0EntryPostInterruptsEnabled)
#pragma alloc_text(PAGE, EvtDeviceD0ExitPreInterruptsDisabled)
#endif

#endif /* __HW_H__ */