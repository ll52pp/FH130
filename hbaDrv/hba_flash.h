#ifndef _HBA_FLASH_H
#define _HBA_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif  /*__cplusplus */

#include "hba.h"

int hbaDevFlashWrite(HBA_DEV_CB *dc, UINT32 Dst, UINT8 * pData, UINT len);
int hbaDevFlashRead(HBA_DEV_CB *dc, UINT32 Dst, UINT8 * pBuffer, UINT len);


#ifdef __cplusplus
}
#endif  /*__cplusplus*/

#endif  /*_HBA_FLASH_H*/

