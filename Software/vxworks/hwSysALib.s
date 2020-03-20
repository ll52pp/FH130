#define _ASMLANGUAGE
#include <vxWorks.h>
#include <sysLib.h>
#include <regs.h>
#include <asm.h>

/* defines */



/* globals */


	FUNC_EXPORT(hwSysPciInLong)
	FUNC_EXPORT(hwSysPciOutLong)
	


/*****************************************************************************
*
* sysPciInLong - reads a long (32-bit big-endian) from PCI Config Space.
*
* This function reads a long from a specified PCI Config Space (little-endian)
* address.
*
* RETURNS:
* Returns 32 bit data from the specified register.  Note that for PCI systems
* if no target responds, the data returned to the CPU will be 0xffffffff.

* ULONG hwSysPciInLong
*	(
*	ULONG *	pAddr,		/@ Virtual addr to read from @/
*	)

*/

FUNC_BEGIN(hwSysPciInLong)
	eieio			/* Sync I/O operation */
	lwbrx	p0, r0, p0	/* Read and swap from PCI space */
	bclr	20, 0		/* Return to caller */
FUNC_END(hwSysPciInLong)




/******************************************************************************
*
* sysPciOutLong - writes a long (32-bit big-endian) to PCI Config Space.
*
* This function writes a long to a specified PCI Config Space (little-endian)
* address.
*
* RETURNS: N/A

* VOID hwSysPciOutLong
*	(
*	ULONG *	pAddr,		/@ Virtual addr to write to	@/
*	ULONG	data		/@ Data to be written		@/
*	)

*/

FUNC_BEGIN(hwSysPciOutLong)
	stwbrx	p1, r0, p0	/* Write big-endian long to little-endian */
	mr	p0, p1		/* PCI space */
	bclr	20, 0		/* Return to caller */
FUNC_END(hwSysPciOutLong)



