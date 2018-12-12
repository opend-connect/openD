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
* Primary header file, which brings in everything needed.
*/

/** \mainpage OS and Core Reference Manual
* \image html rtxlogo.gif
* <hr>
*
* This document describes the RTX OS and Core, its interfaces, configuration and usage.
* <UL>
* <LI>\subpage relnotes for the various Core versions.</LI>
* <LI>\subpage faq Frequently Asked Questions.</LI>
* <LI>\subpage core_survey provides an overview of the Core.</LI>
* <LI>\subpage folder_structure describes the placement of header files, source code and projects.</LI>
* <LI>\subpage core_config describes core configuration of CPU, compiler and options.</LI>
* <LI>\subpage ros_manual is the reference for the RTX OS.</LI>
* <LI>\subpage fos_manual "FOS (Fusion RTOS)" is the reference for the Fusion RTOS.</LI>
* </UL>
* <hr>
*
* \section Quick_Links_By_Function Quick Links
* <UL>
* <LI>
* Standard:
*   \ref RsStandard.h "types/macros",
*   \ref enum_macros "ENUM macros",
*   \ref RS_FAR_ADR "function/variable modifiers",
*   \ref RsStatusType "status codes".
* </LI>
* <LI>
* Alignment:
*   \ref RS_ALIGN_SIZE "size",
*   \ref RsPaddingSize "padding",
*   \ref struct_packing "struct/union packing".
* </LI>
* <LI>
* Endianess:
*   \ref byte_swapping "byteswapping",
*   \ref endian_macros "conversion macros".
* </LI>
* <LI>
* Misc:
*   \ref RsBitMacros.h "bit macros",
*   \ref RsList.h "linked list",
*   \ref RsRandom.h "random numbers",
* </LI>
* <LI>
* Startup:
*   \ref startup_sequence "sequence",
*   \ref hooks "hooks/callbacks",
*   \ref RsShutdown "shutdown".
* </LI>
* <LI>
* Interrupts:
*   \ref RsLocks.h "disable/enable",
*   \ref isr_table "service routines",
*   \ref cr16c_stacks "stacks".
* </LI>
* <LI>
* Timing:
*   \ref system_timer "system timer",
*   \ref time_measurement "time measurement",
*   \ref performance_measurement "performance counter",
*   \ref rsitimer_usage "interrupt timers".
* </LI>
* <LI>
* Errors:
*   \ref assert_macros "assert",
*   \ref RsError "logging an error",
*   \ref RsStatusType "status codes".
* </LI>
* <LI>
* Heap:
*   \ref Heap_Config "configuration",
*   \ref RcHeapAlloc "allocate/free",
*   \ref RcHeapGetInfo "information/statistics".
* </LI>
* <LI>
* RTX OS:
*   \ref RosTasks.h "tasks and groups",
*   \ref RosMails.h "mails",
*   \ref RosTimers.h "timers",
*   \ref RosHooks.h "hooks/callbacks",
*   \ref ros_manual "reference manual".
* </LI>
* <LI>
* Fusion RTOS:
*   \ref fos_Tasks "tasks/threads",
*   \ref fos_Event_Groups "events",
*   \ref fos_Mutexes "mutexes",
*   \ref fos_Semaphores "semaphores",
*   \ref fos_Software_Interrupts "software interrupts",
*   \ref fos_Software_Timers "timers",
*   \ref fos_Queues "queues",
*   \ref fos_Data_Packets "packet handlers/pools",
*   \ref fos_Mailboxes "mailboxes",
*   \ref fos_Memory_Pools "memory pools",
*   \ref fos_Name_Server "name server",
*   \ref fos_manual "reference manual".
* </LI>
* </UL>
*
* By header file: Click the "Directories" in the tree.
*
* By name: Click the "Globals" in the tree.
* <br><br>
*/

/** \page core_survey Core Survey
*
* The Core is a set of components with the basic modules and functions needed for the majority of embedded systems.
*
* \image html Coresurvey.jpg
*
* It includes:
* <ul>
* <li>Boot code for setting up stacks and initializing segments.</li>
* <li>Error handler.</li>
* <li>Hooks for monitoring and controlling the Core operation.</li>
* <li>Heap memory manager.</li>
* <li>The RTX OS, which is a mail queue oriented OS with timer system.</li>
* <li>The Fusion RTOS, which is a multi-threaded OS with preemption.</li>
* <li>Startup and shutdown state machine.</li>
* <li>Performance and Power Management.</li>
* </ul>
*
* The Core is is extensively configurable at compile time. Some configuration is done using const tables in the application code.<br><br>
*/

/** \page folder_structure Folder Structure
*
* Each of the folders are described in the following sections.
* <pre>
*(root)
*  \ref include_folder/
*    \ref include_standard_folder/
*    \ref include_core_folder/
*  \ref components_folder/
*    \ref components_core_sys_folder/
*    \ref components_drivers_folder/
*    \ref components_services_folder/
*    \ref components_apps_folder/
*  \ref projects_folder/
*  \ref mapping_folder/
*  \ref tools_folder/ </pre>
* <hr>
*
* \section include_folder Include
* General header files and headers for components. This folder must be in the compiler's include path.
*
* \subsection include_standard_folder Include/Standard
* Standard types for the target CPU and compiler.
* CPU is meant in a general sense; It can be an actual CPU (e.g. CR16, Blackfin, ARM) or another OS platform (e.g. Windows, Linux).<br>
*
* <p><tt>Include/Standard/RtxStandard.h</tt> includes all other basic header files with standard types, macros etc.
*
* <p>Header files for a specific CPU/compiler are placed at <tt>Standard/<i>CPU/compiler.h</i></tt>.<br>
* Example for CR16C CPU and IAR+NSC compilers:
* <pre>
* (root)
*   Include/
*     Standard/
*       CR16C/
*         Iar.h
*         Gcc.h </pre> </p>
* <p><tt>Include/Standard/Common</tt> contains header files common to all CPU/compiler types.</p>
*
* \subsection include_core_folder Include/Core
* <p><tt>Include/Core</tt> contains header files for the Core modules (Heap, ROS etc.).</p>
* <p><tt>Include/Core/RtxCore.h</tt> includes all standard header files as well as ROS and FOS headers. The majority of c/cpp files has this file as the first (and often only) include file.</p>
*
* <hr>
*
* \section components_core_sys_folder Core/Sys
*
* Contains VCS nodes for getting the Core, and for including the relevant Core components into the project build.
*
* The node <tt>Components/Core/Sys/All</tt> is used to fetch the Core components for all available targets.
*
* \subsection sys_core_folder Core
* <p>Build nodes for a specific CPU/compiler are placed at <tt>Core/Sys/<i>CPU/compiler</i></tt>.<br>
* Example for CR16C CPU and IAR+GCC compilers:
* <pre>
* (root)
*   Components/
*     Core/
*       Sys/
*         CR16C/
*           IAR/
*           GCC/</pre> </p>
* <hr>
*
* \section components_folder Components
* This is the primary source code repository.
*
* \section components_drivers_folder Drivers
* Source code for device drivers.
*
* \section components_services_folder Services
* Source code for services.
*
* \section components_apps_folder Applications
* Source code for services.
* <hr>
*
* \section projects_folder Projects
* Application/product specific project files and source code.
* <hr>
*
* \section mapping_folder Mapping
* Contains header and source files for mapping of legacy source code for use with the Core.
* <hr>
*
* \section tools_folder Tools
* Compilers and other build tools.
*/


#ifndef RTX_CORE_H
#define RTX_CORE_H

/****************************************************************************
*                               Include files
****************************************************************************/

/** \name Core version
* Defines the current version of the Core.
* The high byte is the major version and the low byte is the minor version. */
//@{
#define RTX_CORE_VERSION 0x0436 /*!< Core version. */
//@}

#ifndef RTX_STANDARD_H
  #include <Standard/RtxStandard.h>
#endif
#if (RS_BUILD != RSBT_HEADERS)
  #include <Core/Heap/RcHeap.h>
  #include <Core/ROS/RosTypes.h>
  #include <Core/ROS/RosTasks.h>
  #include <Core/ROS/RosMails.h>
  #include <Core/ROS/RosTimers.h>
  #include <Core/ROS/RosHooks.h>
  #include <Core/ROS/RosInline.h>
#endif

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/****************************************************************************
*                           Global variables/const
****************************************************************************/

/****************************************************************************
*                             Function prototypes
****************************************************************************/

#endif

// EOF.

