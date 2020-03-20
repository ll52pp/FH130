/*++
文件名
    fc_asm.h

描述
    FC ASM 协议
--*/

#ifndef __FC_ASM_H__
#define __FC_ASM_H__

#include "vxworks.h"
#include "endian.h"

#define SOF_SIZE                        4
#define CRC_SIZE                        4
#define EOF_SIZE                        4
#define FC_HEADER_SIZE                  sizeof(FC_HEADER)
#define ASM_HEADER_SIZE                 sizeof(ASM_HEADER)

#define FC_ASM_IU_LENGTH_MAX            (16 * 1024 * 1024) /*ASM IU的最大字节长度*/

/* FC Frame Header full frame = SOF + FC_HEADER + ASM_HEADER + PAYLOAD + CRC + EOF */
typedef struct _FC_HEADER {
    union {
        struct {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
            ULONG r_ctl                   : 8; /* [24:31] : RW R_CTL */
            ULONG did                     : 24;/* [ 0:23] : RW DID */
#else
            ULONG did                     : 24;/* [ 0:23] : RW DID */
            ULONG r_ctl                   : 8; /* [24:31] : RW R_CTL */
#endif
        } u;
        ULONG value;
    } DID_R_CTL;
    
    union {
        struct {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
            ULONG cs_ctl_priority         : 7; /* [25:31] : RW CS_CTL/Priority */
            ULONG preemption   : 1; /* [24]    : RW CS_CTL/Priority */
            ULONG sid                     : 24;/* [ 0:23] : RW SID */
#else
            ULONG sid                     : 24;/* [ 0:23] : RW SID */
            ULONG preemption   : 1; /* [24]    : RW CS_CTL/Priority */
            ULONG cs_ctl_priority         : 7; /* [25:31] : RW CS_CTL/Priority */
#endif
        } u;
        ULONG value;
    } SID_CS_CTL_Priority;
    
    union {
        struct {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
            ULONG type                    : 8; /* [24:31] : RW TYPE */
            ULONG f_ctl                   : 22;/* [ 2:23] : RW F_CTL */
            ULONG fill_byte               : 2; /* [ 0: 1] : RW fill byte 0 1 2 3 */
#else
            ULONG fill_byte               : 2; /* [ 0: 1] : RW fill byte 0 1 2 3 */
            ULONG f_ctl                   : 22;/* [ 2:23] : RW F_CTL */
            ULONG type                    : 8; /* [24:31] : RW TYPE */
#endif
        } u;
        ULONG value;
    } F_CTL_TYPE;
    
    union {
        struct {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
            ULONG seq_id                  : 8; /* [24:31] : RW SEQ_ID */
            ULONG df_ctl                  : 8; /* [16:23] : RW DF_CTL */
            ULONG seq_cnt                 : 16;/* [ 0:15] : RW SEQ_CNT */
#else
            ULONG seq_cnt                 : 16;/* [ 0:15] : RW SEQ_CNT */
            ULONG df_ctl                  : 8; /* [16:23] : RW DF_CTL */
            ULONG seq_id                  : 8; /* [24:31] : RW SEQ_ID */
#endif
        } u;
        ULONG value;
    } SEQ_CNT_DF_CTL_SEQ_ID;
    
    union {
        struct {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
            ULONG ox_id                   : 16;/* [16:31] : RW OX_ID */
            ULONG rx_id                   : 16;/* [ 0:15] : RW RX_ID */
#else
            ULONG rx_id                   : 16;/* [ 0:15] : RW RX_ID */
            ULONG ox_id                   : 16;/* [16:31] : RW OX_ID */
#endif
        } u;
        ULONG value;
    } RX_ID_OX_ID;
    ULONG Parameter;                           /* [0:31] : RW Parameter */
} FC_HEADER, *PFC_HEADER;

typedef union _RAW_OX_ID {
    struct {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
        USHORT mode                       : 1; /* 0-RAW 1-BLOCK */
        USHORT channel_id                 : 7; /* 0-127 */
        USHORT index                      : 8; /* 0-255 software inc */
#else
        USHORT index                      : 8; /* 0-255 software inc */
        USHORT channel_id                 : 7; /* 0-127 */
        USHORT mode                       : 1; /* 0-RAW 1-BLOCK */
#endif
    } u;
    USHORT value;
} RAW_OX_ID, *PRAW_OX_ID;

typedef union _BLOCK_OX_ID {
    struct {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
        USHORT mode                       : 1; /* [   15] : RW 0-RAW 1-BLOCK */
        USHORT channel_id                 : 4; /* [11:14] : RW 0-16 */
        USHORT index                      : 11;/* [ 0:10] : RW 0-2047 fpga inc */
#else
        USHORT index                      : 11;/* [ 0:10] : RW 0-2047 fpga inc */
        USHORT channel_id                 : 4; /* [11:14] : RW 0-16 */
        USHORT mode                       : 1; /* [   15] : RW 0-RAW 1-BLOCK */
#endif
    } u;
    USHORT value;
} BLOCK_OX_ID, *PBLOCK_OX_ID;

typedef struct _ASM_HEADER {
    ULONG MESSAGE_ID;                          /* [ 0:31] : RW MESSAGE ID */
    ULONG RESERVE_SECURITY;                    /* [ 0:31] : RW Reserved Security */
    ULONG RESERVE0;                            /* [ 0:31] : RW Reserved */
    union {
        struct {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
            ULONG l                       : 1; /* [    31] : RW L */
            ULONG Priority                : 7; /* [ 24:30] : RW Priority */
            ULONG Length                  : 24;/* [ 0: 23] : RW Message Payload Length(Bytes) */
#else
            ULONG Length                  : 24;/* [ 0: 23] : RW Message Payload Length(Bytes) */
            ULONG Priority                : 7; /* [ 24:30] : RW Priority */
            ULONG l                       : 1; /* [    31] : RW L */
#endif
        } u;
        ULONG value;
    } L_PRIORITY_LENGTH;
} ASM_HEADER, *PASM_HEADER;

typedef struct _FC_ASM {
    FC_HEADER fc_header;
    ASM_HEADER asm_header;
} FC_ASM, *PFC_ASM;

#endif  /* __FC_ASM_H__ */

