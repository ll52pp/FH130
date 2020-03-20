#ifndef __RESPONSE_H__
#define __RESPONSE_H__


#ifdef __cpluscplus
extern "C" {
#endif

    /* 响应包的payload最大字节数 */
#define RESP_PAYLOAD_MAX (128 * 1024)

    typedef struct _RESPONSE_NODE
    {
        int asmid;
        int length;
        char payload[RESP_PAYLOAD_MAX];
    } RESPONSE_NODE, *PRESPONSE_NODE;

    int GetResponseNodeById(int asmid, RESPONSE_NODE **node);

#if defined(__FH130_SYTLE_AUTO_TEST_DEMO__)
extern BLUE_PRINT gBluePrint[];
#elif defined(__FH180_SYTLE_AUTO_TEST_DEMO__)
extern FC_BLUE_PRINT gBluePrint;
#endif    

#ifdef __cpluscplus
}
#endif

#endif
