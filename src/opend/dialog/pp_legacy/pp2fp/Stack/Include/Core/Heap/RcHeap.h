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
* Heap memory, generally throughout the entire system.
* It is also possible to create \ref fos_Memory_Pools "private heaps".
*
* \section Heap_Config Heap Configuration
*
* The heap is initialized during \ref RsRun.h "system startup" when \ref RcHeapInit is called.
* It uses the application-defined \ref RcHeapConfig structure, which defines the heap memory area(s) to use and heap options.
* The following example configures a 1 Kbyte heap with default options.
*
* \code
* rsuint32 heap[0x400/sizeof(rsuint32)]; // Declare heap memory area, 32-bit aligned.
*
* RS_CONST RcHeapConfigType RcHeapConfig =
* {
*   RCHEAP(heap),
*   RCHEAP(0), // Terminator.
* };
* \endcode
*
* The heap size is unlimited, but a single heap block may limited by \ref RC_HEAP_MAX_BLOCK_SIZE.
*
* <hr>
*
* \section Heap_Protection Heap Protection
*
* When the \ref core_os "Fusion RTOS" is used, the heap is protected with a \ref fos_Mutexes "mutex".
* Otherwise the heap is not protected.
*
* The heap cannot be used from interrupt service routines.
*
* <hr>
*
* \section Heap_Alignment Heap Alignment
*
* The heap implementation honors \ref RS_ALIGN_SIZE, i.e. it is guaranteed that
* the pointer returned from e.g. \ref RcHeapAllocEx points to a properly aligned address.
*
* The heap implementation requires that the heap area is aligned correctly. The easiest way to
* ensure alignment is to declare the heap area as an rsuint32 array. See example in \ref Heap_Config.
*
* <hr>
*
* \section Heap_Implementation Heap Implementation
* The core offers two heap implementations to choose from, and it is also possible
* to use a private (user-defined) heap implementation.
*
* <UL>
* <LI>The \em standard heap implementation is good for the typical RAM-challenged embedded system.</LI>
* <LI>The \em <a href="http://www.fourmilab.ch/bget/">BGET</a> heap typically implementation provides better performance when sufficient RAM is available.</LI>
* </UL>
*
* The heap implementation is selected a compile time by setting RC_HEAP_IMPLEMENTATION to either
* \ref RHI_STANDARD, \ref RHI_BGET or \ref RHI_USER.
* The mapping of the general heap functions (RcHeapxx) to a specific heap implementation
* is done in <i>Include/Core/Heap/RcHeap.cpp</i>.
*
* <hr>
*
* \section Heap_malloc malloc() and free()
*
* Define RC_HEAP_ENABLE_MALLOC if you want \em malloc(), \em calloc() and \em free() to use the system heap.
*
* <hr>
*
* \section Heap_newdel operator new and delete
*
* Define RC_HEAP_ENABLE_NEWDEL if you want <i>operator new</i> and <i>operator delete</i> to use the system heap.
*
* Define RC_HEAP_ENABLE_NOTHROW if you want the \em nothrow variant of <i>operator new</i> to use the system heap.
*
* <hr>
*
*/


#ifndef RC_HEAP_H
#define RC_HEAP_H

/****************************************************************************
*                               Include files
****************************************************************************/

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/** \name Values for RC_HEAP_IMPLEMENTATION
* Defines the heap implementation to use. */
//@{
#define RHI_USER      0 /*!< Use user-defined heap implementation. */
#define RHI_STANDARD  1 /*!< Use standard heap implementation. */
#define RHI_BGET      2 /*!< Use BGET heap implementation. */
#define RHI_TLSF      3 /*!< Use TLSF heap implementation. */
#define RHI_STDLIB    4 /*!< Map RcHeapAlloc etc. to stdlib.h functions (malloc etc). */
//@}

/** \name Default Heap implementation
*/
//@{
#ifndef RC_HEAP_IMPLEMENTATION
  #define RC_HEAP_IMPLEMENTATION RHI_STANDARD
#endif
//@}

/** \name Heap flags/options.
* Values for the RcHeapFlagsType type, which is used as parameter to \ref RcHeapAllocEx and \ref RcHeapReallocEx. */
//@{
#ifndef RC_HEAP_FLAG_FILL_ALLOC
  #define RC_HEAP_FLAG_FILL_ALLOC 0 /*!< Fill allocated blocks with a known pattern. (Valid for \ref RcHeapConfig only). */
#endif
#ifndef RC_HEAP_FLAG_FILL_FREE
  #define RC_HEAP_FLAG_FILL_FREE 0 /*!< Fill free blocks with a known pattern. (Valid for \ref RcHeapConfig only). */
#endif
#ifndef RC_HEAP_FLAG_TAIL_CHECK
  #define RC_HEAP_FLAG_TAIL_CHECK 1  /*!< Check for writes beyound the end of the block. (Valid for \ref RcHeapConfig only). */
#endif
//@}

/** \name Allocation flags/options.
* Values for the RcHeapFlagsType type, which is used as parameter to \ref RcHeapAllocEx and \ref RcHeapReallocEx. */
//@{
#define RHF_NULL_ON_FULL 0x01  /*!< Return null if an allocation request cannot be satisfied. (Valid for RcHeapAllocEx and RcHeapReallocEx only). */
//@}

/** \name Values for RC_HEAP_MAX_BLOCK_SIZE
* Defines the maximum size for a heap block. */
//@{
#define RHB_64K_BLOCKS  1 /*!< A heap block can be maximum 64K. This is the default. */
#define RHB_4G_BLOCKS   2 /*!< A heap block can be maximum 4G. */

#ifndef RC_HEAP_MAX_BLOCK_SIZE
  #define RC_HEAP_MAX_BLOCK_SIZE RHB_64K_BLOCKS /*!< Default maximum block size. */
#endif
//@}

/** \name RC_MULTIPLE_HEAPS
* Selects whether multiple heap areas are used. Default disabled. */
//@{
#ifndef RC_MULTIPLE_HEAPS
  #define RC_MULTIPLE_HEAPS 0 /*!< Set to 1 to enable multiple heaps. */
#endif
//@}

#define RCHEAP(heap) {heap,sizeof(heap)} /*!< For creating entries in the \ref RcHeapConfig structure. */

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

#if (RC_HEAP_MAX_BLOCK_SIZE == RHB_64K_BLOCKS)
typedef rsuint16 RcHeapSizeType; /*!< Type used for the size field for individual heap blocks. */
typedef rsuintsz RcHeapTotalType; /*!< Type used for the size field for total counters. */
#endif
#if (RC_HEAP_MAX_BLOCK_SIZE == RHB_4G_BLOCKS)
typedef rsuint32 RcHeapSizeType; /*!< Type used for the size field for individual heap blocks. */
typedef rsuint32 RcHeapTotalType; /*!< Type used for the size field for total counters. */
#endif
typedef rsuint8 RcHeapFlagsType; /*!< For RHF_xx flags. */

/// Heap statistics.
typedef struct
{
  RcHeapTotalType CurrentBytes;  /*!< Number of bytes currently allocated, including block headers and padding. */
  RcHeapTotalType PeakBytes;  /*!< Peak number of bytes allocated, including block headers and padding. */
} RcHeapStatType;

/// Heap configuration
typedef struct
{
  void* Address; /*!< Starting address for the heap area. Must be properly aligned. */
  RcHeapTotalType Size; /*!< Size of the heap area. */
} RcHeapConfigType;

/****************************************************************************
*                           Global variables/const
****************************************************************************/

RS_BEGIN_EXTERN_C

/// Heap configuration, set by the application. See \ref Heap_Config "heap configuration".
extern RS_CONST RcHeapConfigType RcHeapConfig[];

/****************************************************************************
*                             Function prototypes
****************************************************************************/
#if 0//def NATALIE_V11
#include <stdio.h>
#include <stdlib.h>
RS_C_INLINE void* RcHeapAllocEx(RcHeapSizeType Size, RcHeapFlagsType Flags) {return malloc(Size);};
RS_C_INLINE void* RcHeapReallocEx(void* Block, RcHeapSizeType Size, RcHeapFlagsType Flags) { return realloc(Block, Size); }
RS_C_INLINE void RcHeapFree(void* Block) { free(Block); }

#endif
/** \cond internal */
#ifndef RC_HEAP_BLOCK_TIMESTAMPS
  #define RC_HEAP_BLOCK_TIMESTAMPS 0
#endif
#if (RC_HEAP_MAX_BLOCK_SIZE == RHB_64K_BLOCKS)
  #if (RC_HEAP_BLOCK_TIMESTAMPS == 1)
    !error This combination is not possible.
  #endif
#endif
#if (RC_MULTIPLE_HEAPS == 1)
  #if (RC_HEAP_IMPLEMENTATION != RHI_STANDARD)
    !error This combination is not possible.
  #endif
#endif
#if (RC_HEAP_IMPLEMENTATION == RHI_STDLIB)
  #ifdef RC_HEAP_ENABLE_MALLOC
    !error This combination is not possible.
  #endif
#endif
#ifndef RC_INLINE_HEAP_FUNCTIONS
  #if (RC_HEAP_IMPLEMENTATION == RHI_USER)
    #define RC_INLINE_HEAP_FUNCTIONS 0
  #else
    #define RC_INLINE_HEAP_FUNCTIONS 1
  #endif
#endif
#if (RC_INLINE_HEAP_FUNCTIONS == 1)
void* RcHeapAlloc(RcHeapSizeType Size);
void* RcHeapAllocZ(RcHeapSizeType Size);
void* RcHeapRealloc(void* Block, RcHeapSizeType Size);
#endif
/** \endcond */

#if (RC_INLINE_HEAP_FUNCTIONS == 0)

/** \name Heap memory.
*/
//@{
/// Initialize the heap.
void RcHeapInit(void);

/// Check the consistency of the heap and all blocks, and merges free blocks.
/** \return TRUE when all blocks have been checked (or no checks needed), FALSE if more blocks are to be checked. */
rsbool RcHeapCheck(void);
//@}

/** \name Heap blocks.
*/
//@{
/// Allocate heap memory.
/** \param Size number of bytes requested. Zero is not allowed.
* \return Pointer to the block. */
void* RcHeapAlloc(RcHeapSizeType Size);

/// Allocate heap memory and zero.
/** \param Size number of bytes requested. Zero is not allowed.
* \return Pointer to the block. */
void* RcHeapAllocZ(RcHeapSizeType Size);

/// Allocate heap memory.
/** \param Size number of bytes requested. Zero is not allowed.
* \param Flags The following flags are allowed for this function: \ref RHF_NULL_ON_FULL. */
void* RcHeapAllocEx(RcHeapSizeType Size, RcHeapFlagsType Flags);

/// Reallocate heap memory (expand or shrink).
/** \param Block Pointer to heap block. Null is allowed.
* \param Size number of bytes requested. Zero is not allowed.
* \return Pointer to the modified block. */
void* RcHeapRealloc(void* Block, RcHeapSizeType Size);

/// Reallocate heap memory (expand or shrink).
/** \param Block Pointer to heap block. Null is allowed.
* \param Size number of bytes requested. Zero is not allowed.
* \param Flags The following flags are allowed for this function: \ref RHF_NULL_ON_FULL.
* \return Pointer to the modified block. */
void* RcHeapReallocEx(void* Block, RcHeapSizeType Size, RcHeapFlagsType Flags);

/// Free heap memory.
/** \param Block Pointer to heap block. */
void RcHeapFree(void* Block);

/// Get heap block size.
/** \param Block Pointer to heap block.
* \return Size of block. */
RcHeapSizeType RcHeapGetBlockSize(void* Block);

/// Check if block points to a valid heap block.
/** \param Block Pointer to heap block.
* \return TRUE if valid, FALSE otherwise. */
rsbool RcHeapBlockValid(void* Block);

/// Override return address that was stored when the block was allocated.
/** \param Block Pointer to heap block. Null is allowed.
* \param RA New return address to store. */
void RcHeapSetRa(void* Block, RsRaType RA);
//@}

/** \name Heap statistics.
*/
//@{

/// Get heap usage.
/** \param Total Pointer to variable that receives the total heap size.
* \param FreeBytes Pointer to variable that receives the current number of free bytes. */
void RcHeapGetInfo(RcHeapTotalType* Total, RcHeapTotalType* FreeBytes);

/// Get heap statistics.
/** \param Stats Pointer to variable that receives the heap statistics. */
void RcHeapGetStats(RcHeapStatType* Stats);

/// Set heap statistics.
/** \param Stats Pointer to variable with the new heap statistics. */
void RcHeapSetStats(RcHeapStatType* Stats);
//@}

#endif

/// Free heap memory and nullify pointer.
/** The following code fragment is commonly found throughout a system: <pre>
* if (p)
* {
*   RcHeapFree(p);
*   p = NULL;
* } </pre>
* It can be replaced with:
* <pre>
* RcHeapFreePtr(&p); </pre>
* \param Block Pointer to heap block pointer. */
void RcHeapFreePtr(void** Block);

#if (RC_HEAP_HOOK_PEAK == 1)
/// Hook for monitoring heap peaks. This function is called when \ref RC_HEAP_HOOK_PEAK is set to 1.
/** \param NewPeak Pointer to variable with the new peak heap values. */
void RcHeapHookPeak(RcHeapStatType* NewPeak);
#else
  #define RcHeapHookPeak !disabled
#endif

/** \cond internal */
#if (RC_HEAP_IMPLEMENTATION == RHI_USER)
#ifdef NATALIE_V11
#if (RC_INLINE_HEAP_FUNCTIONS == 1)
#include <stdio.h>
#include <stdlib.h>
RS_C_INLINE void* RcHeapAllocEx(RcHeapSizeType Size, RcHeapFlagsType Flags) {return malloc(Size);};
RS_C_INLINE void* RcHeapReallocEx(void* Block, RcHeapSizeType Size, RcHeapFlagsType Flags) { return realloc(Block, Size); }
RS_C_INLINE void RcHeapFree(void* Block) { free(Block); }
#endif //(RC_INLINE_HEAP_FUNCTIONS == 1)
#endif
#endif//(RC_HEAP_IMPLEMENTATION == RHI_USER)

#if (RC_HEAP_IMPLEMENTATION == RHI_STANDARD)
// Prototypes for standard heap implementation.
void RcStdHeapInit(void);
rsbool RcStdHeapCheck(void);
void* RcStdHeapAllocEx(RcHeapSizeType Size, RcHeapFlagsType Flags, RsRaType ra);
void* RcStdHeapReallocEx(void* Block, RcHeapSizeType Size, RcHeapFlagsType Flags);
void RcStdHeapFree(void* Block);
RcHeapSizeType RcStdHeapGetBlockSize(void* Block);
rsbool RcStdHeapBlockValid(void* Block);
void RcStdHeapSetRa(void* Block, RsRaType RA);
void RcStdHeapGetInfo(RcHeapTotalType* Total, RcHeapTotalType* FreeBytes);
void RcStdHeapGetStats(RcHeapStatType* Stats);
void RcStdHeapSetStats(RcHeapStatType* Stats);
#if (RC_MULTIPLE_HEAPS == 0 && RC_HEAP_MAX_BLOCK_SIZE == RHB_4G_BLOCKS && RC_HEAP_BLOCK_TIMESTAMPS == 1)
typedef rsbool RcStdHeapEnumeratorType(void* Context, RcHeapSizeType Size, RsRaType RA, RsTimerTickType Timestamp, rsuint8* Data);
void RcStdHeapEnum(RcStdHeapEnumeratorType* Enumerator, void* Context);
void RcStdHeapClearTs(void);
#endif

// Map heap functions to standard heap implementation.
#if (RC_INLINE_HEAP_FUNCTIONS == 1)
RS_C_INLINE void RcHeapInit(void) { RcStdHeapInit(); }
RS_C_INLINE rsbool RcHeapCheck(void) { return RcStdHeapCheck(); }
RS_C_INLINE void* RcHeapAllocEx(RcHeapSizeType Size, RcHeapFlagsType Flags) { return RcStdHeapAllocEx(Size, Flags, 0); }
RS_C_INLINE void* RcHeapReallocEx(void* Block, RcHeapSizeType Size, RcHeapFlagsType Flags) { return RcStdHeapReallocEx(Block, Size, Flags); }
RS_C_INLINE void RcHeapFree(void* Block) { RcStdHeapFree(Block); }
RS_C_INLINE RcHeapSizeType RcHeapGetBlockSize(void* Block) { return RcStdHeapGetBlockSize(Block); }
RS_C_INLINE rsbool RcHeapBlockValid(void* Block) { return RcStdHeapBlockValid(Block); }
RS_C_INLINE void RcHeapSetRa(void* Block, RsRaType RA) { RcStdHeapSetRa(Block, RA); }
RS_C_INLINE void RcHeapGetInfo(RcHeapTotalType* Total, RcHeapTotalType* FreeBytes) { RcStdHeapGetInfo(Total, FreeBytes); }
RS_C_INLINE void RcHeapGetStats(RcHeapStatType* Stats) { RcStdHeapGetStats(Stats); }
RS_C_INLINE void RcHeapSetStats(RcHeapStatType* Stats) { RcStdHeapSetStats(Stats); }
#endif // (RC_INLINE_HEAP_FUNCTIONS == 1)
#if (RC_INLINE_HEAP_FUNCTIONS == 0)
#define RcHeapInit RcStdHeapInit
#define RcHeapCheck RcStdHeapCheck
#define RcHeapAllocEx(Size, Flags) RcStdHeapAllocEx(Size, Flags, 0)
#define RcHeapReallocEx(Block, Size, Flags) RcStdHeapReallocEx(Block, Size, Flags)
#define RcHeapFree(Block) RcStdHeapFree(Block)
#define RcHeapGetBlockSize RcStdHeapGetBlockSize
#define RcHeapBlockValid RcStdHeapBlockValid
#define RcHeapSetRa RcStdHeapSetRa
#define RcHeapGetInfo RcStdHeapGetInfo
#define RcHeapGetStats RcStdHeapGetStats
#define RcHeapSetStats RcStdHeapSetStats
#endif // (RC_INLINE_HEAP_FUNCTIONS == 1)
#endif // (RC_HEAP_IMPLEMENTATION == RHI_STANDARD)

#if (RC_HEAP_IMPLEMENTATION == RHI_BGET)
// Prototypes for BGET heap implementation.
void RcBGetHeapInit(void);
rsbool RcBGetHeapCheck(void);
void* RcBGetHeapAllocEx(RcHeapSizeType Size, RcHeapFlagsType Flags, RsRaType ra);
void* RcBGetHeapReallocEx(void* Block, RcHeapSizeType Size, RcHeapFlagsType Flags);
void RcBGetHeapFree(void* Block);
RcHeapSizeType RcBGetHeapGetBlockSize(void* Block);
rsbool RcBGetHeapBlockValid(void* Block);
void RcBGetHeapSetRa(void* Block, RsRaType RA);
void RcBGetHeapGetInfo(RcHeapTotalType* Total, RcHeapTotalType* FreeBytes);
void RcBGetHeapGetStats(RcHeapStatType* Stats);
void RcBGetHeapSetStats(RcHeapStatType* Stats);
void RcBGetHeapClearTs(void);

// Map heap functions to BGET heap implementation.
#if (RC_INLINE_HEAP_FUNCTIONS == 1)
RS_C_INLINE void RcHeapInit(void) { RcBGetHeapInit(); }
RS_C_INLINE rsbool RcHeapCheck(void) { return RcBGetHeapCheck(); }
RS_C_INLINE void* RcHeapAllocEx(RcHeapSizeType Size, RcHeapFlagsType Flags) { return RcBGetHeapAllocEx(Size, Flags, 0); }
RS_C_INLINE void* RcHeapReallocEx(void* Block, RcHeapSizeType Size, RcHeapFlagsType Flags) { return RcBGetHeapReallocEx(Block, Size, Flags); }
RS_C_INLINE void RcHeapFree(void* Block) { RcBGetHeapFree(Block); }
RS_C_INLINE RcHeapSizeType RcHeapGetBlockSize(void* Block) { return RcBGetHeapGetBlockSize(Block); }
RS_C_INLINE rsbool RcHeapBlockValid(void* Block) { return RcBGetHeapBlockValid(Block); }
RS_C_INLINE void RcHeapSetRa(void* Block, RsRaType RA) { RcBGetHeapSetRa(Block, RA); }
RS_C_INLINE void RcHeapGetInfo(RcHeapTotalType* Total, RcHeapTotalType* FreeBytes) { RcBGetHeapGetInfo(Total, FreeBytes); }
RS_C_INLINE void RcHeapGetStats(RcHeapStatType* Stats) { RcBGetHeapGetStats(Stats); }
RS_C_INLINE void RcHeapSetStats(RcHeapStatType* Stats) { RcBGetHeapSetStats(Stats); }
#endif // (RC_INLINE_HEAP_FUNCTIONS == 1)
#endif // (RC_HEAP_IMPLEMENTATION == RHI_BGET)

#if (RC_HEAP_IMPLEMENTATION == RHI_TLSF)
// Prototypes for TLSF heap implementation.
void RcTlsfHeapInit(void);
rsbool RcTlsfHeapCheck(void);
void* RcTlsfHeapAllocEx(RcHeapSizeType Size, RcHeapFlagsType Flags, RsRaType ra);
void* RcTlsfHeapReallocEx(void* Block, RcHeapSizeType Size, RcHeapFlagsType Flags);
void RcTlsfHeapFree(void* Block);
RcHeapSizeType RcTlsfHeapGetBlockSize(void* Block);
rsbool RcTlsfHeapBlockValid(void* Block);
void RcTlsfHeapSetRa(void* Block, RsRaType RA);
void RcTlsfHeapGetInfo(RcHeapTotalType* Total, RcHeapTotalType* FreeBytes);
void RcTlsfHeapGetStats(RcHeapStatType* Stats);
void RcTlsfHeapSetStats(RcHeapStatType* Stats);

// Map heap functions to TLSF heap implementation.
#if (RC_INLINE_HEAP_FUNCTIONS == 1)
RS_C_INLINE void RcHeapInit(void) { RcTlsfHeapInit(); }
RS_C_INLINE rsbool RcHeapCheck(void) { return RcTlsfHeapCheck(); }
RS_C_INLINE void* RcHeapAllocEx(RcHeapSizeType Size, RcHeapFlagsType Flags) { return RcTlsfHeapAllocEx(Size, Flags, 0); }
RS_C_INLINE void* RcHeapReallocEx(void* Block, RcHeapSizeType Size, RcHeapFlagsType Flags) { return RcTlsfHeapReallocEx(Block, Size, Flags); }
RS_C_INLINE void RcHeapFree(void* Block) { RcTlsfHeapFree(Block); }
RS_C_INLINE RcHeapSizeType RcHeapGetBlockSize(void* Block) { return RcTlsfHeapGetBlockSize(Block); }
RS_C_INLINE rsbool RcHeapBlockValid(void* Block) { return RcTlsfHeapBlockValid(Block); }
RS_C_INLINE void RcHeapSetRa(void* Block, RsRaType RA) { RcTlsfHeapSetRa(Block, RA); }
RS_C_INLINE void RcHeapGetInfo(RcHeapTotalType* Total, RcHeapTotalType* FreeBytes) { RcTlsfHeapGetInfo(Total, FreeBytes); }
RS_C_INLINE void RcHeapGetStats(RcHeapStatType* Stats) { RcTlsfHeapGetStats(Stats); }
RS_C_INLINE void RcHeapSetStats(RcHeapStatType* Stats) { RcTlsfHeapSetStats(Stats); }
#endif // (RC_INLINE_HEAP_FUNCTIONS == 1)
#endif // (RC_HEAP_IMPLEMENTATION == RHI_TLSF)

#if (RC_HEAP_IMPLEMENTATION == RHI_STDLIB)
// Prototypes for stdlib heap implementation.
void RcStdlibHeapInit(void);
rsbool RcStdlibHeapCheck(void);
void* RcStdlibHeapAllocEx(RcHeapSizeType Size, RcHeapFlagsType Flags, RsRaType ra);
void* RcStdlibHeapReallocEx(void* Block, RcHeapSizeType Size, RcHeapFlagsType Flags);
void RcStdlibHeapFree(void* Block);
RcHeapSizeType RcStdlibHeapGetBlockSize(void* Block);
rsbool RcStdlibHeapBlockValid(void* Block);
void RcStdlibHeapSetRa(void* Block, RsRaType RA);
void RcStdlibHeapGetInfo(RcHeapTotalType* Total, RcHeapTotalType* FreeBytes);
void RcStdlibHeapGetStats(RcHeapStatType* Stats);
void RcStdlibHeapSetStats(RcHeapStatType* Stats);

// Map heap functions to stdlib heap implementation.
#if (RC_INLINE_HEAP_FUNCTIONS == 1)
RS_C_INLINE void RcHeapInit(void) { RcStdlibHeapInit(); }
RS_C_INLINE rsbool RcHeapCheck(void) { return RcStdlibHeapCheck(); }
RS_C_INLINE void* RcHeapAllocEx(RcHeapSizeType Size, RcHeapFlagsType Flags) { return RcStdlibHeapAllocEx(Size, Flags, 0); }
RS_C_INLINE void* RcHeapReallocEx(void* Block, RcHeapSizeType Size, RcHeapFlagsType Flags) { return RcStdlibHeapReallocEx(Block, Size, Flags); }
RS_C_INLINE void RcHeapFree(void* Block) { RcStdlibHeapFree(Block); }
RS_C_INLINE RcHeapSizeType RcHeapGetBlockSize(void* Block) { return RcStdlibHeapGetBlockSize(Block); }
RS_C_INLINE rsbool RcHeapBlockValid(void* Block) { return RcStdlibHeapBlockValid(Block); }
RS_C_INLINE void RcHeapSetRa(void* Block, RsRaType RA) { RcStdlibHeapSetRa(Block, RA); }
RS_C_INLINE void RcHeapGetInfo(RcHeapTotalType* Total, RcHeapTotalType* FreeBytes) { RcStdlibHeapGetInfo(Total, FreeBytes); }
RS_C_INLINE void RcHeapGetStats(RcHeapStatType* Stats) { RcStdlibHeapGetStats(Stats); }
RS_C_INLINE void RcHeapSetStats(RcHeapStatType* Stats) { RcStdlibHeapSetStats(Stats); }
#endif // (RC_INLINE_HEAP_FUNCTIONS == 1)
#endif // (RC_HEAP_IMPLEMENTATION == RHI_STDLIB)
/** \endcond */

RS_END_EXTERN_C

#endif

// End of file.

