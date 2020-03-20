/*++

Module Name:

    Trace.h

Abstract:

    Header file for the debug tracing related function defintions and macros.

Environment:

    Kernel mode

--*/

//
// Define the tracing flags.
//
// Tracing GUID - 8da91e4a-3ab3-45d4-bfb0-7e5141abc1d0
//

#define WPP_CONTROL_GUIDS                                              \
    WPP_DEFINE_CONTROL_GUID(                                           \
        hbaTraceGuid, (8da91e4a,3ab3,45d4,bfb0,7e5141abc1d0),          \
        WPP_DEFINE_BIT(MYDRIVER_ALL_INFO)                              \
        WPP_DEFINE_BIT(TRACE_DRIVER)                                   \
        WPP_DEFINE_BIT(TRACE_DEVICE)                                   \
        WPP_DEFINE_BIT(TRACE_QUEUE)                                    \
	    WPP_DEFINE_BIT(DBG_INIT)             /* bit  0 = 0x00000001 */ \
	    WPP_DEFINE_BIT(DBG_CREATE_CLOSE)     /* bit  1 = 0x00000002 */ \
	    WPP_DEFINE_BIT(DBG_READ)             /* bit  2 = 0x00000004 */ \
	    WPP_DEFINE_BIT(DBG_WRITE)            /* bit  3 = 0x00000008 */ \
	    WPP_DEFINE_BIT(DBG_IOCTLS)           /* bit  4 = 0x00000010 */ \
	    WPP_DEFINE_BIT(DBG_DPC)              /* bit  5 = 0x00000020 */ \
	    WPP_DEFINE_BIT(DBG_INTERRUPT)        /* bit  6 = 0x00000040 */ \
	    WPP_DEFINE_BIT(DBG_HW_ACCESS)        /* bit  7 = 0x00000080 */ \
	    WPP_DEFINE_BIT(DBG_PNP)              /* bit  8 = 0x00000100 */ \
	    WPP_DEFINE_BIT(DBG_POWER)            /* bit  9 = 0x00000200 */ \
	    WPP_DEFINE_BIT(DBG_WMI)              /* bit 10 = 0x00000400 */ \
    )

#define WPP_FLAG_LEVEL_LOGGER(flag, level)                             \
    WPP_LEVEL_LOGGER(flag)

#define WPP_FLAG_LEVEL_ENABLED(flag, level)                            \
    (WPP_LEVEL_ENABLED(flag) &&                                        \
    WPP_CONTROL(WPP_BIT_ ## flag).Level >= level)

#define WPP_LEVEL_FLAGS_LOGGER(lvl,flags)                              \
    WPP_LEVEL_LOGGER(flags)
               
#define WPP_LEVEL_FLAGS_ENABLED(lvl, flags)                            \
    (WPP_LEVEL_ENABLED(flags) && WPP_CONTROL(WPP_BIT_ ## flags).Level >= lvl)

//
// This comment block is scanned by the trace preprocessor to define our
// Trace function.
//
// begin_wpp config
// FUNC Trace{FLAG=MYDRIVER_ALL_INFO}(LEVEL, MSG, ...);
// FUNC TraceEvents(LEVEL, FLAGS, MSG, ...);
// end_wpp
//