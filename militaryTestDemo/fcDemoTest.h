#ifndef __FC_DEMOTEST_H__
#define __FC_DEMOTEST_H__

#ifdef __cpluscplus
extern "C" {
#endif

#if 1/*__FH130_AUTO_TEST_DEMO__*/
    #define PROJECT_FH130       (1)
    #define PROJECT_FH180       (2)

    /*����FH130����Ŀ���������в���*/
    #define __AUTO_TEST_PROJECT__       (PROJECT_FH130)         
    /*����FH180����Ŀ���������в���*/
/*    #define __AUTO_TEST_PROJECT__       (PROJECT_FH180)         */

    #if (__AUTO_TEST_PROJECT__ == PROJECT_FH130)
        #define  __FH130_SYTLE_AUTO_TEST_DEMO__
    #elif (__AUTO_TEST_PROJECT__ == PROJECT_FH180)
        #define  __FH180_SYTLE_AUTO_TEST_DEMO__
    #else
        #define  __UNKNOWN_SYTLE_AUTO_TEST_DEMO__
    #endif
    
#define DEMO_MAX_IU_LENGTH       (0x1000000)    /*16M*/
/**************************************************************************************************************
                ����FH130,FH180����Ŀ�궨��,�����ṹ������춼�ϴ�,�ڴ˴���һ������
**************************************************************************************************************/
    #if defined(__FH130_SYTLE_AUTO_TEST_DEMO__)
    
    /*FH130�궨�����ֺ�FH180��һ��,�˴���һ��ת��*/
    #define FC_NET_ROLE_NCT                             FC_NET_ROLE_NC
    #define FC_NET_ROLE_BNCT                           FC_NET_ROLE_BNC

    /*DEMO�ж��붨��*/
    #define DEMO_IC_PORT_LINK_UP                       IC_LINK_STATUS_SUCCESS
    #define DEMO_IC_PORT_LINK_DOWN               IC_LINK_STATUS_FAILED
    #define DEMO_IC_VOLTAGE_GOOD                    IC_VOLTAGE_SUCCESS
    #define DEMO_IC_VOLTAGE_FAILED                      IC_VOLTAGE_FAILED
    #define DEMO_IC_TEMPERATURE_GOOD              IC_TEMP_SUCCESS
    #define DEMO_IC_TEMPERATURE_FAILED              IC_TEMP_FAILED
    #define DEMO_IC_RX_IU_DISCARD                    IC_DISCARD_MSG
    #define DEMO_IC_RX_IU_TIMEOUT                       IC_IU_TIMEOUT
    #define DEMO_IC_RX_IU_LENGTH_INVALID        IC_IU_LENGTH_INVALID
    #define DEMO_IC_NCT_ON_NET                          IC_ELS_RECV_NC_ON_NET
    #define DEMO_IC_ELS_RECV_NC_TIMEOUT                 IC_ELS_RECV_NC_TIMEOUT
    #define DEMO_IC_NET_NODE_STATE_TABLE_CHANGED    IC_NC_CHANGED
    
    #elif defined(__FH180_SYTLE_AUTO_TEST_DEMO__)

    /*DEMO�ж��붨��*/
    #define DEMO_IC_PORT_LINK_UP    IC_PORT_LINK_UP
    #define DEMO_IC_PORT_LINK_DOWN   IC_PORT_LINK_DOWN
    #define DEMO_IC_VOLTAGE_GOOD     IC_VOLTAGE_GOOD
    #define DEMO_IC_VOLTAGE_FAILED           IC_VOLTAGE_FAILED
    #define DEMO_IC_TEMPERATURE_GOOD         IC_TEMPERATURE_GOOD
    #define DEMO_IC_TEMPERATURE_FAILED       IC_TEMPERATURE_FAILED
    #define DEMO_IC_RX_IU_DISCARD                IC_RX_IU_DISCARD
    #define DEMO_IC_RX_IU_TIMEOUT            IC_RX_IU_TIMEOUT
    #define DEMO_IC_RX_IU_LENGTH_INVALID     IC_RX_IU_LENGTH_INVALID
    #define DEMO_IC_NCT_ON_NET                   IC_NCT_ON_NET
    #define DEMO_IC_NET_NODE_STATE_TABLE_CHANGED     IC_NET_NODE_STATE_TABLE_CHANGED
    
    #else
    
    #endif
#endif/*__FH130_AUTO_TEST_DEMO__*/

#ifdef __cpluscplus
}
#endif

#endif  /*__FC_DEMOTEST_H__*/
