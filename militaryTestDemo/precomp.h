
#ifdef ACORES653

#include <sysTypes.h>
#include <acoreos.h>
#include <pciConfigLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tasks.h>
#include <sem.h>
#include <archMmu.h>

#else

#include <vxWorks.h>
#include <cacheLib.h>
#include <pciConfigLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <logLib.h>
#include <taskLib.h>
#include <semLib.h>
#include <tickLib.h>
#include <wdLib.h>
#include <vxLib.h>
#include <rebootLib.h>
#include <intLib.h>
#include <ftpLib.h>

#endif

#include "..\fc_api.h"
#include "..\endian.h"
#include "..\hba.h"
#include "..\utils.h"
#include "..\list.h"
#include "..\hba_els.h"
#include "..\hw.h"
#include "..\hba_time.h"
#include "..\spi.h"
#include "..\hba_flash.h"

