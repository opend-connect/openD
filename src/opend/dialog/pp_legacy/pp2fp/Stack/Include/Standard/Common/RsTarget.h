/*
 * Copyright (c) by RTX A/S, Denmark
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of RTX A/S nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */
/*! \file
* Core, CPU and tool configuration. Also see \ref core_config.
*/


#ifndef RS_TARGET_H
#define RS_TARGET_H

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/** \name Values for RS_TARGET_FAMILY
* Defines the target CPU family.
* CPU is the target CPU in a general sense.
* It can be an actual CPU (e.g. CR16C, Blackfin, ARM) or another OS platform (e.g. Windows, Linux). */
//@{
#define RSTF_CR16C    1 /*!< NSC CR16C CPU. */
#define RSTF_BLACKFIN 2 /*!< Analog Blackfin DSPs. */
#define RSTF_ARM      3 /*!< ARM CPU's. */
#define RSTF_AVR      4 /*!< Atmel AVR CPU's. */
#define RSTF_WINDOWS  5 /*!< Microsoft Win32 or Win64. */
#define RSTF_LINUX    6 /*!< Desktop or Embedded Linux. */
#define RSTF_GENERIC  7 /*!< Generic (headers only). */
//@}

/** \name Values for RS_TOOL_ID
* Defines the compiler. */
//@{
#define RSTI_IAR      1 /*!< IAR Systems. */
#define RSTI_NSC      2 /*!< National Semiconductor. */
#define RSTI_ADS      3 /*!< ARM Development Suite. */
#define RSTI_MSVC     4 /*!< Microsoft Visual C++. */
#define RSTI_BCB      5 /*!< Borland C++ Builder. */
#define RSTI_ANALOG   6 /*!< Analog Visual DSP. */
#define RSTI_GNU      7 /*!< GNU gcc. */
#define RSTI_GENERIC  8 /*!< Generic (headers only). */
//@}

/** \name Values for RS_RTOS_ID
* Defines the \ref core_os. */
//@{
#define RSTS_NONE     1 /*!< Only ROS. */
#define RSTS_FUSION   2 /*!< Both ROS and FOS. */
//@}

/** \name Values for RS_QUEUES
* Defines the ROS mail queue type. */
//@{
#define RSQT_STATIC   1 /*!< ROS mails in static buffers. */
#define RSQT_HEAP     2 /*!< ROS mails in heap. */
//@}

/** \name Values for RS_PROTECTION
* Defines the data protection type (e.g. for heap). */
//@{
#define RSPT_NONE       1 /*!< No data protection. */
#define RSPT_MUTEX      2 /*!< Data is protected using a \ref fos_Mutexes "mutex". */
#define RSPT_INTERRUPT  3 /*!< Data is protected using \ref RsDisableInterrupts and \ref RsEnableInterrupts. */
//@}

/** \name Values for RS_BUILD
* Defines the core build type. */
//@{
#define RSBT_DOC        1 /*!< Build core documentation. */
#define RSBT_SOURCE     2 /*!< Build core source directly with project. */
#define RSBT_HEADERS    3 /*!< Headers only. */
//@}

/** \name Values for RS_SEGINIT_FLAGS
* Defines segment initialization options. Default is all enabled. */
//@{
#define RSSIF_FILL_ISTACK   0x01 /*!< Fill interrupt stack with a known pattern. */
#define RSSIF_FILL_CSTACK   0x02 /*!< Fill C stack with a known pattern. */
#define RSSIF_COPY_RAMCODE  0x04 /*!< Copy ROMCODE segment to RAMCODE segment. */
#define RSSIF_INDEX_BASE    0x08 /*!< Setup index base register. */
#define RSSIF_DATA16        0x10 /*!< (CR16C/gcc) Initialize data16/bss16. */
#define RSSIF_DATA20        0x20 /*!< (CR16C/gcc) Initialize data20/bss20. */
#define RSSIF_DATA24        0x40 /*!< (CR16C/gcc) Initialize data24/bss24. */
#define RSSIF_DATA32        0x80 /*!< (CR16C/gcc) Initialize data32/bss32. */
//@}

/** \name Values for RS_INT_TABLE_WIDTH
* Defines size of CR16C interrupt vector table entries. Default is 32-bit. */
//@{
#define RS_ITW_SHORT        0x1 /*!< Vector table contains 16-bit entries. CFG.ED is 0. */
#define RS_ITW_EXTENDED     0x2 /*!< Vector table contains 32-bit entries. CFG.ED is 1. */
//@}

/****************************************************************************
*                               Include files
****************************************************************************/

#ifndef RS_CONFIG_H
  #include <RsConfig.h>
#endif

#if (RS_BUILD == RSBT_DOC)
  // Documentation build - all hooks enabled.
  #define RS_HOOK_COLD_START 1 /*!< Must be set in compiler/assember options. Controls \ref RsHookColdStart. Set to 1 to enable, 0 to disable. */
  #define RS_HOOK_WARM_START 1 /*!< Must be set in compiler/assember options. Controls \ref RsHookWarmStart. Set to 1 to enable, 0 to disable. */
  #define RS_HOOK_CACHE_INIT 1 /*!< Must be set in compiler/assember options. Controls \ref RsHookCacheInit. Set to 1 to enable, 0 to disable. */
  #define RS_HOOK_READY 1 /*!< Controls \ref RsHookReady. Set to 1 to enable, 0 to disable. */
  #define RS_HOOK_PRE_TASK 1 /*!< Controls \ref RsHookPreTask. Set to 1 to enable, 0 to disable. */
  #define RS_HOOK_RUNNING 1 /*!< Controls \ref RsHookRunning. Set to 1 to enable, 0 to disable. */
  #define RS_HOOK_EXIT 1 /*!< Controls \ref RsHookExit. Set to 1 to enable, 0 to disable. */
  #define RS_HOOK_PRE_HWI 1 /*!< Must be set in compiler/assember options. Controls \ref RsHookPreHwi. Set to 1 to enable, 0 to disable. */
  #define RS_HOOK_IDLE 1 /*!< Controls \ref RsHookIdle. Set to 1 to enable, 0 to disable. */
  #define RS_HOOK_DEAD 1 /*!< Controls \ref RsHookDead. Set to 1 to enable, 0 to disable. */
  #define RC_HEAP_HOOK_PEAK 1 /*!< Controls \ref RcHeapHookPeak. Set to 1 to enable, 0 to disable. */
  #define RC_HEAP_CHECK 1 /*!< Controls \ref RcHeapCheck. Set to 1 to enable, 0 to disable. */
  #define ROS_HOOK_TIMER_PRE_CHECK 1 /*!< Controls \ref RosHookTimerPreCheck. Set to 1 to enable, 0 to disable. */
  #define ROS_HOOK_MAIL_QUEUE_PRE_CHECK 1 /*!< Controls \ref RosHookMailQueuePreCheck. Set to 1 to enable, 0 to disable. */
  #define ROS_HOOK_MAIL_QUEUE_EMPTY 1 /*!< Controls \ref RosHookMailQueueEmpty. Set to 1 to enable, 0 to disable. */
  #define ROS_HOOK_MAIL_PRE_DELIVERY 1 /*!< Controls \ref RosHookMailPreDelivery. Set to 1 to enable, 0 to disable. */
  #define ROS_HOOK_MAIL_POST_DELIVERY 1 /*!< Controls \ref RosHookMailPostDelivery. Set to 1 to enable, 0 to disable. */
  #define ROS_HOOK_TASK_PRE_INIT 1 /*!< Controls \ref RosHookTaskPreInit. Set to 1 to enable, 0 to disable. */
  #define ROS_HOOK_TIMER_START 1 /*!< Controls \ref RosHookTimerStart. Set to 1 to enable, 0 to disable. */
  #define ROS_HOOK_TIMER_STOP 1 /*!< Controls \ref RosHookTimerStop. Set to 1 to enable, 0 to disable. */
  #define ROS_HOOK_TIMER_VALUE 1 /*!< Controls \ref RosHookTimerValue. Set to 1 to enable, 0 to disable. */
  #define ROS_HOOK_TIMER_EXPIRED 1 /*!< Controls \ref RosHookTimerExpired. Set to 1 to enable, 0 to disable. */
  // Documentation build - all functionality enabled.
  #define RS_DUMP_ASSERT 1 /*!< Controls \ref RsDumpAssert. Set to 1 to enable, 0 to disable. */
  #define RS_DUMP_ERROR 1 /*!< Controls \ref RsDumpError. Set to 1 to enable, 0 to disable. */
  #define RS_IS_DEBUGGER_CONNECTED 1 /*!< Controls \ref RsIsDebuggerConnected. Set to 1 to enable, 0 to disable. */
  #define RS_EXIT 1 /*!< Controls RsExit. Set to 1 to enable, 0 to disable. */
  #define RS_SEG_INIT 1 /*!< Must be set in compiler/assember options. Controls RsSegInit. Set to 1 to enable, 0 to disable. */
  #define RS_READ_PERFORMANCE_COUNTER 1 /*!< Controls RsReadPerformanceCounter. Set to 1 to enable, 0 to disable. */
  #define RS_CTORS_DTORS 1 /*!< Must be set in compiler/assember options. Controls construction/destruction of static C++ objects. */
  #define RS_MAIN 1 /*!< Controls RsMain. Set to 1 to enable Core implementation, 0 to disable. */
  #define RS_UNICOI 1 /*!< Controls unicoi/fusion headers. Set to 1 to include unicoi/fusion headers, 0 to disable. */
  #define RS_SYSHEADERS 1 /*!< Controls system header files. Set to 1 to include system header files, 0 to use project file RsSysHeaders.h. */
  #define RS_ITIMERS 1 /*!< Controls interrupt timers. Set to 1 to enable itimers, 0 to disable. */
#endif

#if (RS_BUILD == RSBT_HEADERS)
  // Headers only.
  #define RS_OVERRIDE_AUTO_TOOLID
  #define RS_TARGET_FAMILY RSTF_GENERIC
  #define RS_TOOL_ID RSTI_GENERIC
  #ifndef RS_TARGET_INC_H
    #define RS_TARGET_INC_H
    #define RS_SET_PACKING 1
    typedef unsigned rsuintsz;
    typedef unsigned RsIntStatusType;
    typedef unsigned RsRaType;
  #endif
#endif

// Set defaults - all functionality and hooks enabled.
#ifndef RS_HOOK_COLD_START
  #define RS_HOOK_COLD_START 1
#endif
#ifndef RS_HOOK_WARM_START
  #define RS_HOOK_WARM_START 1
#endif
#ifndef RS_HOOK_CACHE_INIT
  #define RS_HOOK_CACHE_INIT 0
#endif
#ifndef RS_HOOK_READY
  #define RS_HOOK_READY 1
#endif
#ifndef RS_HOOK_PRE_TASK
  #define RS_HOOK_PRE_TASK 1
#endif
#ifndef RS_HOOK_RUNNING
  #define RS_HOOK_RUNNING 1
#endif
#ifndef RS_HOOK_EXIT
  #define RS_HOOK_EXIT 1
#endif
#ifndef RS_HOOK_PRE_HWI
  #define RS_HOOK_PRE_HWI 1
#endif
#ifndef RS_HOOK_IDLE
  #define RS_HOOK_IDLE 1
#endif
#ifndef RS_HOOK_DEAD
  #define RS_HOOK_DEAD 1
#endif
#ifndef RC_HEAP_HOOK_PEAK
  #define RC_HEAP_HOOK_PEAK 1
#endif
#ifndef RC_HEAP_CHECK
  #define RC_HEAP_CHECK 1
#endif
#ifndef ROS_HOOK_TIMER_PRE_CHECK
  #define ROS_HOOK_TIMER_PRE_CHECK 1
#endif
#ifndef ROS_HOOK_MAIL_QUEUE_PRE_CHECK
  #define ROS_HOOK_MAIL_QUEUE_PRE_CHECK 0
#endif
#ifndef ROS_HOOK_MAIL_QUEUE_EMPTY
  #define ROS_HOOK_MAIL_QUEUE_EMPTY 1
#endif
#ifndef ROS_HOOK_MAIL_PRE_DELIVERY
  #define ROS_HOOK_MAIL_PRE_DELIVERY 1
#endif
#ifndef ROS_HOOK_MAIL_POST_DELIVERY
  #define ROS_HOOK_MAIL_POST_DELIVERY 1
#endif
#ifndef ROS_HOOK_TASK_PRE_INIT
  #define ROS_HOOK_TASK_PRE_INIT 1
#endif
#ifndef ROS_HOOK_TIMER_START
  #define ROS_HOOK_TIMER_START 1
#endif
#ifndef ROS_HOOK_TIMER_STOP
  #define ROS_HOOK_TIMER_STOP 1
#endif
#ifndef ROS_HOOK_TIMER_VALUE
  #define ROS_HOOK_TIMER_VALUE 0
#endif
#ifndef ROS_HOOK_TIMER_EXPIRED
  #define ROS_HOOK_TIMER_EXPIRED 0
#endif
#ifndef RS_DUMP_ASSERT
  #define RS_DUMP_ASSERT 1
#endif
#ifndef RS_DUMP_ERROR
  #define RS_DUMP_ERROR 1
#endif
#ifndef RS_IS_DEBUGGER_CONNECTED
  #define RS_IS_DEBUGGER_CONNECTED 1
#endif
#ifndef RS_READ_PERFORMANCE_COUNTER
  #define RS_READ_PERFORMANCE_COUNTER 1
#endif
#ifndef RS_EXIT
  #define RS_EXIT 1
#endif
#ifndef RS_SEG_INIT
  #define RS_SEG_INIT 1
#endif
#ifndef RS_SEGINIT_FLAGS
  #define RS_SEGINIT_FLAGS (RSSIF_DATA32 | RSSIF_DATA24 | RSSIF_DATA20 | RSSIF_DATA16 | RSSIF_INDEX_BASE | RSSIF_COPY_RAMCODE | RSSIF_FILL_CSTACK | RSSIF_FILL_ISTACK) /*!< Defines segment initialization options. Default is all enabled. */
#endif
#ifndef RS_ISRS_ADR
  #define RS_ISRS_ADR const /*!< Controls placement of \ref RsIsrs. Set to empty to place \ref RsIsrs in RAM. */
#endif
#ifndef RS_INT_TABLE_WIDTH
  #define RS_INT_TABLE_WIDTH RS_ITW_EXTENDED /*!< Defines size of CR16C interrupt vector table entries. Default is 32-bit. */
#endif
#ifndef RS_CTORS_DTORS
  #define RS_CTORS_DTORS 1
#endif
#ifndef RS_MAIN
  #define RS_MAIN 1
#endif
#ifndef RS_RTOS_ID
  #define RS_RTOS_ID RSTS_NONE
#endif
#ifdef RS_UNICOI
  #if (RS_UNICOI == 0)
    #ifdef FOS_ENABLE_TIMERS
      #undef FOS_ENABLE_TIMERS
    #endif
  #endif
#else
  #if (RS_RTOS_ID == RSTS_NONE)
    #ifdef FOS_ENABLE_TIMERS
      #define RS_UNICOI 1
    #else
      #define RS_UNICOI 0
    #endif
  #endif
  #if (RS_RTOS_ID == RSTS_FUSION)
    #define RS_UNICOI 1
  #endif
#endif
#ifndef RS_ITIMERS
  #if (RS_RTOS_ID == RSTS_FUSION)
    #define RS_ITIMERS 0
  #endif
#endif
#ifndef RS_ITIMERS
  #ifdef FOS_ENABLE_TIMERS
    #define RS_ITIMERS 0
  #else
    #define RS_ITIMERS 1
  #endif
#endif
#ifdef FOS_ENABLE_TIMERS
  #if (RS_ITIMERS == 1)
    !error Pick either fosTimers or RsITimers.
  #endif
#endif
#ifndef RS_SYSHEADERS
  #define RS_SYSHEADERS 1
#endif

#ifndef RS_OVERRIDE_AUTO_TOOLID
  #ifdef __IAR_SYSTEMS_ICC__
    #define RS_TOOL_ID RSTI_IAR
    #ifdef __ICCCR16C__
      #define RS_TARGET_FAMILY RSTF_CR16C
    #endif
    #ifdef __ICCAVR__
      #define RS_TARGET_FAMILY RSTF_AVR
    #endif
    #ifdef __ICCARM__
      #define RS_TARGET_FAMILY RSTF_ARM
    #endif
  #endif
  #ifdef __NSC_CRCC__
    #define RS_TOOL_ID RSTI_NSC
    #define RS_TARGET_FAMILY RSTF_CR16C
  #endif
  #ifdef _MSC_VER
    #define RS_TOOL_ID RSTI_MSVC
    #define RS_TARGET_FAMILY RSTF_WINDOWS
  #endif
  #ifdef __BORLANDC__
    #define RS_TOOL_ID RSTI_BCB
    #define RS_TARGET_FAMILY RSTF_WINDOWS
  #endif
  #ifndef RS_TOOL_ID
    #ifdef __GNUC__
      #define RS_TOOL_ID RSTI_GNU
      #define RS_TARGET_FAMILY RSTF_LINUX
    #endif
  #endif
#endif

#if (RS_TARGET_FAMILY == RSTF_CR16C)
  #if (RS_TOOL_ID == RSTI_IAR)
    #include <Standard/CR16C/Iar.h>
  #endif
  #if (RS_TOOL_ID == RSTI_NSC)
    #include <Standard/CR16C/Gcc.h>
  #endif
  #if (RS_TOOL_ID == RSTI_GNU)
    #include <Standard/CR16C/Gcc.h>
  #endif
#endif
#if (RS_TARGET_FAMILY == RSTF_WINDOWS)
  #if (RS_TOOL_ID == RSTI_MSVC)
    #include <Standard/Windows/Msvc.h>
  #endif
  #if (RS_TOOL_ID == RSTI_BCB)
    #include <Standard/Windows/Bcb.h>
  #endif
#endif
#if (RS_TARGET_FAMILY == RSTF_LINUX)
  #if (RS_TOOL_ID == RSTI_GNU)
    #include <Standard/Linux/gcc.h>
  #endif
#endif
#if (RS_TARGET_FAMILY == RSTF_BLACKFIN)
  #if (RS_TOOL_ID == RSTI_ANALOG)
    #include <Standard/Blackfin/vdsp.h>
  #endif
#endif
#if (RS_TARGET_FAMILY == RSTF_ARM)
  #if (RS_TOOL_ID == RSTI_IAR)
    #include <Standard/ARM/Iar.h>
  #endif
  #if (RS_TOOL_ID == RSTI_GNU)
    #include <Standard/ARM/Gcc.h>
  #endif
#endif

#ifndef RS_TARGET_INC_H
  #error: Missing/unknown RS_TARGET_FAMILY and/or RS_TOOL_ID!
#endif

#endif

/** \page core_config Core Configuration
*
* The \ref core_makefile is used to setup basic configuration.
* A set of \#define's are used for fine-grain configuration, see \ref core_defines.
*
* <hr>
*
* \section core_makefile Core Makefile
* The Core makefile is used to select a core configuration and set appropriate macros.
* It is intended to be included by project makefiles as follows:
* <pre>
* CB_TYPE=src
* CB_OS=fos
* CB_QUEUES=static
* CB_PROTECTION=mutex
* CB_ALIGN=a2
* CB_MODEL=mm
* include $(WORK)Include\\Standard\\Common\\RsTarget.gmk</pre>
*
* <table border="1" cellpadding="4">
*   <tr><th>Variable</th>               <th>Values</th>           <th>\#define</th>                 <th>Description</th> </tr>
*   <tr><td><tt>CB_TYPE</tt></td>       <td><tt>src</tt></td>     <td><tt>RS_BUILD</tt></td>        <td>Core is built from source directly with the project.</td>  </tr>
*   <tr><td><tt>CB_OS</tt></td>         <td><tt>ros</tt><br>
*                                           <tt>fos</tt></td>     <td><tt>RS_RTOS_ID</tt></td>      <td>Selects OS: ROS only, or both ROS and FOS.</td>  </tr>
*   <tr><td><tt>CB_QUEUES</tt></td>     <td><tt>static</tt><br>
*                                           <tt>heap</tt></td>    <td><tt>RS_QUEUES</tt></td>       <td>Selects queue type for ROS mails:<br>
*                                                                                                       <tt>static</tt>: Use a static buffer for mails. This is the normal setting.<br>
*                                                                                                       <tt>heap</tt>: Use the heap for mails. This is slower, and <tt>CB_PROTECTION=ints</tt> is likely also needed.</td>  </tr>
*   <tr><td><tt>CB_PROTECTION</tt></td> <td><tt>none</tt><br>
*                                           <tt>mutex</tt><br>
*                                           <tt>ints</tt></td>    <td><tt>RS_PROTECTION</tt></td>   <td>Selects protection for the heap:<br>
*                                                                                                       <tt>none</tt>: The heap is not protected. This is the normal setting if <tt>CB_OS=ros</tt>.<br>
*                                                                                                       <tt>mutex</tt>: The heap is protected using a \ref fos_Mutexes "mutex". This is the normal setting if <tt>CB_OS=fos</tt>.<br>
*                                                                                                       <tt>ints</tt>: The heap is protected using \ref RsDisableInterrupts and \ref RsEnableInterrupts. This setting can be used with <tt>CB_QUEUES=heap</tt>.</td>  </tr>
*   <tr><td><tt>CB_ALIGN</tt></td>      <td><tt>a1</tt><br>
*                                           <tt>a2</tt><br>
*                                           <tt>a4</tt><br>
*                                           <tt>a8</tt></td>      <td><tt>RS_SET_PACKING</tt></td>  <td>Sets packing/alignment of structures and variables to 1..8 bytes.</td>  </tr>
*   <tr><td><tt>CB_MODEL</tt></td>      <td><tt>ms</tt><br>
*                                           <tt>mm</tt><br>
*                                           <tt>ml</tt><br>
*                                           <tt>mi</tt><br>
*                                           <tt>mf</tt></td>      <td>-</td>                        <td>Selects memory model: Small, medium, large, indexed or flat.</td>  </tr>
*   <tr><td><tt>CB_CODE</tt></td>       <td><tt>(Segment name)</tt>
*                                                                 <td>-</td>                        <td>Optional setting for selecting a segment name for placement of frequently used Core assembler functions (e.g. RsMemcpy) in fast memory.
*                                                                                                       The segment name is typically RAMCODE.
*                                                                                                       </td>  </tr>
* </table>
*
* <hr>
*
* \section core_os Operating System
* The OS is defined by RS_RTOS_ID, which can be \ref RSTS_NONE (only ROS available) or \ref RSTS_FUSION (Both ROS and FOS available).
* The correct value is set automatically by the \ref core_makefile, by setting <tt>CB_OS</tt> to <tt>ros</tt> or <tt>fos</tt>.
*
* <hr>
*
* \section core_align Alignment
* The Core is built for 1, 2, 4 or 8 bytes alignment.
* One or more of these may be available, depending on the alignment relevant for the target CPU.
* The \ref core_makefile is used to select the desired alignment.
*
* <hr>
*
* \section core_model Memory Model
* The Core is built for small, medium, large or flat memory model.
* One or more of these may be available, depending on the memory models relevant for the target CPU.
* The \ref core_makefile is used to select the desired memory model.
*
* <hr>
*
* \section core_queues Mail Queues
* The queue type for ROS mails is defined by RS_QUEUES, which can be \ref RSQT_STATIC (static buffers) or \ref RSQT_HEAP (use the system heap).
* The correct value is set automatically by the \ref core_makefile, by setting <tt>CB_QUEUES</tt> to <tt>static</tt> or <tt>heap</tt>.
*
* <hr>
*
* \section core_protection Data Protection
* The protection for internal Core data is defined by RS_PROTECTION, which can be \ref RSPT_NONE (unprotected), \ref RSPT_MUTEX (protected by a mutex) or \ref RSPT_INTERRUPT (disable/enable interrupts).
* The correct value is set automatically by the \ref core_makefile, by setting <tt>CB_PROTECTION</tt> to <tt>none</tt>, <tt>mutex</tt> or <tt>ints</tt>.
*
* <hr>
*
* \section core_defines Compile Time Configuration
*
* The following \#define's are used for fine-grain configuration.
* These must be set in the project <tt>makefile</tt>.
*
*
* <table border="1" cellpadding="4">
*   <tr><th>\#define</th>                                   <th>Values</th>           <th>Description</th> </tr>
*   <tr><td><tt>FOS_START_ON_INT_STACK</tt></td>            <td><tt>0</tt></td>       <td>Informs that the system boots on the interrupt stack.</td>  </tr>
*   <tr><td><tt>\ref RS_HOOK_COLD_START</tt></td>           <td><tt>0/1</tt></td>     <td>Selects if \ref RsHookColdStart should be called.</td>  </tr>
*   <tr><td><tt>\ref RS_HOOK_WARM_START</tt></td>           <td><tt>0/1</tt></td>     <td>Selects if \ref RsHookWarmStart should be called.</td>  </tr>
*   <tr><td><tt>\ref RS_SEG_INIT</tt></td>                  <td><tt>0/1</tt></td>     <td>Selects if RsSegInit should be called.</td>  </tr>
*   <tr><td><tt>\ref RS_HOOK_CACHE_INIT</tt></td>           <td><tt>0/1</tt></td>     <td>Selects if \ref RsHookCacheInit should be called.</td>  </tr>
*   <tr><td><tt>\ref RS_HOOK_READY</tt></td>                <td><tt>0/1</tt></td>     <td>Selects if \ref RsHookReady should be called.</td>  </tr>
*   <tr><td><tt>\ref RS_HOOK_PRE_TASK</tt></td>             <td><tt>0/1</tt></td>     <td>Selects if \ref RsHookPreTask should be called.</td>  </tr>
*   <tr><td><tt>\ref RS_HOOK_RUNNING</tt></td>              <td><tt>0/1</tt></td>     <td>Selects if \ref RsHookRunning should be called.</td>  </tr>
*   <tr><td><tt>\ref RS_HOOK_PRE_HWI</tt></td>              <td><tt>0/1</tt></td>     <td>Selects if \ref RsHookPreHwi should be called.</td>  </tr>
*   <tr><td><tt>\ref RS_HOOK_IDLE</tt></td>                 <td><tt>0/1</tt></td>     <td>Selects if \ref RsHookIdle should be called.</td>  </tr>
*   <tr><td><tt>\ref RS_HOOK_EXIT</tt></td>                 <td><tt>0/1</tt></td>     <td>Selects if \ref RsHookExit should be called.</td>  </tr>
*   <tr><td><tt>\ref RS_EXIT</tt></td>                      <td><tt>0/1</tt></td>     <td>Selects if RsExit should be called.</td>  </tr>
*   <tr><td><tt>\ref RS_HOOK_DEAD</tt></td>                 <td><tt>0/1</tt></td>     <td>Selects if \ref RsHookDead should be called.</td>  </tr>
*   <tr><td><tt>\ref RS_DUMP_ASSERT</tt></td>               <td><tt>0/1</tt></td>     <td>Selects if \ref RsDumpAssert should be called.</td>  </tr>
*   <tr><td><tt>\ref RS_DUMP_ERROR</tt></td>                <td><tt>0/1</tt></td>     <td>Selects if \ref RsDumpError should be called.</td>  </tr>
*   <tr><td><tt>\ref RS_IS_DEBUGGER_CONNECTED</tt></td>     <td><tt>0/1</tt></td>     <td>Selects if \ref RsIsDebuggerConnected is available.</td>  </tr>
*   <tr><td><tt>RS_CHECK_CALL_FROM_ISR</tt></td>            <td><tt>0/1</tt></td>     <td>Selects if heap and ROS timer functions checks interrupt state.</td>  </tr>
*   <tr><td><tt>\ref ROS_HOOK_MAIL_QUEUE_PRE_CHECK</tt></td><td><tt>0/1</tt></td>     <td>Selects if \ref RosHookMailQueuePreCheck should be called.</td>  </tr>
*   <tr><td><tt>\ref ROS_HOOK_MAIL_QUEUE_EMPTY</tt></td>    <td><tt>0/1</tt></td>     <td>Selects if \ref RosHookMailQueueEmpty should be called.</td>  </tr>
*   <tr><td><tt>\ref ROS_HOOK_MAIL_PRE_DELIVERY</tt></td>   <td><tt>0/1</tt></td>     <td>Selects if \ref RosHookMailPreDelivery should be called.</td>  </tr>
*   <tr><td><tt>\ref ROS_HOOK_MAIL_POST_DELIVERY</tt></td>  <td><tt>0/1</tt></td>     <td>Selects if \ref RosHookMailPostDelivery should be called.</td>  </tr>
*   <tr><td><tt>\ref ROS_HOOK_TASK_PRE_INIT</tt></td>       <td><tt>0/1</tt></td>     <td>Selects if \ref RosHookTaskPreInit should be called.</td>  </tr>
*   <tr><td><tt>\ref ROS_HOOK_TIMER_PRE_CHECK</tt></td>     <td><tt>0/1</tt></td>     <td>Selects if \ref RosHookTimerPreCheck should be called.</td>  </tr>
*   <tr><td><tt>\ref ROS_HOOK_TIMER_START</tt></td>         <td><tt>0/1</tt></td>     <td>Selects if \ref RosHookTimerStart should be called.</td>  </tr>
*   <tr><td><tt>\ref ROS_HOOK_TIMER_STOP</tt></td>          <td><tt>0/1</tt></td>     <td>Selects if \ref RosHookTimerStop should be called.</td>  </tr>
*   <tr><td><tt>\ref ROS_HOOK_TIMER_VALUE</tt></td>         <td><tt>0/1</tt></td>     <td>Selects if \ref RosHookTimerValue should be called.</td>  </tr>
*   <tr><td><tt>\ref ROS_HOOK_TIMER_EXPIRED</tt></td>       <td><tt>0/1</tt></td>     <td>Selects if \ref RosHookTimerExpired should be called.</td>  </tr>
*   <tr><td><tt>\ref RS_READ_PERFORMANCE_COUNTER</tt></td>  <td><tt>0/1</tt></td>     <td>Selects if \ref RsReadPerformanceCounter is available.</td>  </tr>
*   <tr><td><tt>RC_HEAP_IMPLEMENTATION</tt></td>            <td><tt>0..3</tt></td>    <td>Selects heap implementation.</td>  </tr>
*   <tr><td><tt>RC_HEAP_MAX_BLOCK_SIZE</tt></td>            <td><tt>1/2</tt></td>     <td>Selects maximum size of a heap block.</td>  </tr>
*   <tr><td><tt>\ref RC_HEAP_CHECK</tt></td>                <td><tt>0/1</tt></td>     <td>Selects if \ref RcHeapCheck should be called.</td>  </tr>
*   <tr><td><tt>\ref RC_HEAP_HOOK_PEAK</tt></td>            <td><tt>0/1</tt></td>     <td>Selects if \ref RcHeapHookPeak should be called.</td>  </tr>
*   <tr><td><tt>RC_HEAP_ENABLE_MALLOC</tt></td>             <td><tt>0</tt></td>       <td>Routes <tt>malloc</tt>, <tt>calloc</tt> and <tt>free</tt> to the selected heap implementation.</td>  </tr>
*   <tr><td><tt>RC_HEAP_ENABLE_NEWDEL</tt></td>             <td><tt>0</tt></td>       <td>Routes <tt>operator new</tt> and <tt>operator delete</tt> to the selected heap implementation.</td>  </tr>
*   <tr><td><tt>RC_HEAP_ENABLE_NOTHROW</tt></td>            <td><tt>0</tt></td>       <td>Routes <tt>operator new nothrow</tt> to the selected heap implementation.</td>  </tr>
*   <tr><td><tt>RS_FASTCODE_SEG</tt></td>                   <td><tt>(Segment name)</tt></td>       <td>Optional placement of frequently used Core functions in fast memory.<br>Segment name is typically RAMCODE.</td>  </tr>
*   <tr><td><tt>RS_FASTDATA_ADR</tt></td>                   <td><tt>(Variable modifier)</tt></td>  <td>Optional placement of frequently used Core variables in fast memory.<br>Variable modifier is typically __data16.</td>  </tr>
*   <tr><td><tt>RS_DATA_ADR</tt></td>                       <td><tt>(Variable modifier)</tt></td>  <td>Optional placement of Core variables in specific memory.<br>Variable modifier is typically __data16 or __data32.</td>  </tr>
*   <tr><td><tt>\ref RS_SEGINIT_FLAGS</tt></td>             <td><tt>0x7</tt></td>     <td>Defines segment initialization options.</td>  </tr>
*   <tr><td><tt>RS_ISRS_ADR</tt></td>                       <td><tt>(Variable modifier)</tt></td>  <td>Optional placement of \ref RsIsrs in specific memory.<br>Default is const, typically set to empty to place \ref RsIsrs in RAM.</td>  </tr>
*   <tr><td><tt>\ref RS_INT_TABLE_WIDTH</tt></td>           <td><tt>1/2</tt></td>     <td>Defines size of CR16C interrupt vector table entries. Default is 32-bit.</td>  </tr>
*   <tr><td><tt>\ref RS_CTORS_DTORS</tt></td>               <td><tt>0/1</tt></td>     <td>Selects if constructors/destructors of static C++ objects should be called.</td>  </tr>
*   <tr><td><tt>\ref RS_MAIN</tt></td>                      <td><tt>0/1</tt></td>     <td>Selects if RsMain should be implemented by Core.</td>  </tr>
*   <tr><td><tt>\ref RS_UNICOI</tt></td>                    <td><tt>0/1</tt></td>     <td>Selects if include unicoi/fusion headers should be included.</td>  </tr>
*   <tr><td><tt>\ref RS_ITIMERS</tt></td>                   <td><tt>0/1</tt></td>     <td>Selects if interrupt timers should be implemented by Core.</td>  </tr>
*   <tr><td><tt>\ref RS_SYSHEADERS</tt></td>                <td><tt>0/1</tt></td>     <td>Selects if include system header files should be included.</td>  </tr>
* </table>
*
* <hr>
*
* \section project_makefile Project Makefile
*
* The following lists the full set of Core configuration \#define's, with everything enabled.
*
* <pre>
* -DFOS_START_ON_INT_STACK \
* -DRS_HOOK_COLD_START=1 \
* -DRS_HOOK_WARM_START=1 \
* -DRS_SEG_INIT=1 \
* -DRS_HOOK_CACHE_INIT=1 \
* -DRS_HOOK_READY=1 \
* -DRS_HOOK_PRE_TASK=1 \
* -DRS_HOOK_RUNNING=1 \
* -DRS_HOOK_PRE_HWI=1 \
* -DRS_HOOK_IDLE=1 \
* -DRS_HOOK_EXIT=1 \
* -DRS_EXIT=1 \
* -DRS_HOOK_DEAD=1 \
* -DRS_DUMP_ASSERT=1 \
* -DRS_DUMP_ERROR=1 \
* -DRS_IS_DEBUGGER_CONNECTED=1 \
* -DRS_CTORS_DTORS=1 \
* -DRS_MAIN=1 \
* -DRS_UNICOI=1 \
* -DRS_SYSHEADERS=1 \
* -DRS_ITIMERS=1 \
* -DROS_HOOK_MAIL_QUEUE_PRE_CHECK=1 \
* -DROS_HOOK_MAIL_QUEUE_EMPTY=1 \
* -DROS_HOOK_MAIL_PRE_DELIVERY=1 \
* -DROS_HOOK_MAIL_POST_DELIVERY=1 \
* -DROS_HOOK_TASK_PRE_INIT=1 \
* -DROS_HOOK_TIMER_PRE_CHECK=1 \
* -DROS_HOOK_TIMER_START=1 \
* -DROS_HOOK_TIMER_STOP=1 \
* -DROS_HOOK_TIMER_VALUE=1 \
* -DROS_HOOK_TIMER_EXPIRED=1 \
* -DRS_READ_PERFORMANCE_COUNTER=1 \
* -DRC_HEAP_IMPLEMENTATION=1 \
* -DRC_HEAP_MAX_BLOCK_SIZE=1 \
* -DRC_HEAP_CHECK=1 \
* -DRC_HEAP_HOOK_PEAK=1 \
* -DRC_HEAP_ENABLE_MALLOC \
* -DRC_HEAP_ENABLE_NEWDEL \
* -DRC_HEAP_ENABLE_NOTHROW \
*</pre>
*
*/

// End of file.

