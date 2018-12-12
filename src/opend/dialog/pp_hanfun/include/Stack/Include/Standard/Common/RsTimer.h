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
*
* \section system_timer System Timer
*
* The core requires the use of a hardware timer to run the various timer systems.
*
* The timer typically runs with a regular interval 1 or 10 ms, but the application may use other intervals as appropriate.
* The application must program the hardware timer (typically in \ref RsHookReady) and implement the ISR for it.
* The ISR typically just clears the hardware interrupt and calls \ref RsTimerTick, specifying the number of ms that has elapsed.
*
* The following is the ISR function for a SC14428, using the TIM1 interrupt with 10 ms interval:
* \code
* RSISR(Timer1Isr)
* {
*   RESET_INT_PENDING_REG = TIM1_INT_PEND;
*   RsTimerTick(10);
* }
* \endcode
*
* <hr>
*
* \section time_measurement Time Measurement
*
* Milli-second time measurement can be done using \ref RsTimerTickCount.<br>
* The actual resolution depends on the application defined hardware time, but it is typically 1 or 10 ms.<br>
* The maximum time measurable with \ref RsTimerTickCount is ~49 days.
*
* Measure how long execution took:
* \code
* void f(void)
* {
*   RsTimerTickType t = RsTimerTickCount;
*   ...
*   execute something.
*   ...
*   t = RsTimerTickCount - t;
*   // t now holds the execution time in ms.
*   ...
* }
* \endcode
*
* Run for a specified time (5 seconds in this example):
* \code
* void f(void)
* {
*   RsTimerTickType t = RsTimerTickCount;
*   while (RsTimerTickCount-t < (5 * RS_T1SEC))
*   {
*     ...
*   }
* }
* \endcode
*
* <hr>
*
* \section performance_measurement Performance Counter
*
* The high-resolution performance counter is read using \ref RsReadPerformanceCounter.
* It is used internally by the Core and Fusion RTOS for performance measurements.
*
* The resolution is RS_PERFORMANCE_TICKS_PER_SECOND and highly dependant on the target system, but is typically 1 us or better.<br>
* The maximum measurable time is ~5 seconds.
*
* \note The performance counter may not be available for the target system. If so, \ref RsReadPerformanceCounter returns 0.
*
* Measure how long execution took:
* \code
* void f(void)
* {
*   RsPerformanceTickType t = RsReadPerformanceCounter();
*   ...
*   execute something.
*   ...
*   t = RsReadPerformanceCounter() - t;
*   // Convert to real time and print.
*   RsPerformanceTimeType time = RsPerformanceTicks2Time(t);
*   if (time & RS_PTIME_MS)
*   {
*     printf("Execution took %u ms.\n", time & ~RS_PTIME_MS);
*   }
*   else
*   {
*     printf("Execution took %u us.\n", time);
*   }
* }
* \endcode
*
* <hr>
*
*/


#ifndef RS_TIMER_H
#define RS_TIMER_H

/****************************************************************************
*                               Include files
****************************************************************************/

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/** \name Timer tick values.
*/
//@{
#define RS_IMMEDIATE 0UL /*!< Expire timer immediately. */
#define RS_T1MS 1UL /*!< For timer values in the range 1 ms to 9 ms. */
#define RS_T10MS 10UL /*!< For timer values in the range 10 ms to 90 ms. */
#define RS_T100MS 100UL /*!< For timer values in the range 100 ms to 900 ms. */
#define RS_T1SEC 1000UL /*!< For timer values 1 second and above. */
//@}

/** \name Default timeSlice value for fosTaskCreate.
*/
//@{
#ifndef RS_DEFAULT_TIMESLICE
  #define RS_DEFAULT_TIMESLICE (4*RS_T10MS) /*!< Default \c timeSlice value for \ref fosTaskCreate. */
#endif
//@}

/** \name Performance/profiling time unit.
*/
//@{
#define RS_PTIME_MS RSBIT15 /*!< For performance/profiling time values (RsPerformanceTimeType). If this bit is set, the time is in milliseconds. If not, the time is in microseconds. */
//@}

#ifndef RS_READ_PERFORMANCE_COUNTER_INLINED
  #define RS_READ_PERFORMANCE_COUNTER_INLINED 0 /*!< Set this to 1 if RsReadPerformanceCounter is inlined (in RsConfig.h). */
#endif
#ifndef RS_READ_PERFORMANCE_T2T_INLINED
  #ifdef RS_C_INLINE
    #define RS_READ_PERFORMANCE_T2T_INLINED 1 /*!< Set this to 1 for inlining of RsPerformanceTicks2Time and RsTime2PerformanceTicks. */
  #else
    #define RS_READ_PERFORMANCE_T2T_INLINED 0 /*!< Set this to 0 to prevent inlining of RsPerformanceTicks2Time and RsTime2PerformanceTicks. */
  #endif
#endif

/** \name RS performance timer configuration.
*/
//@{
#define RS_PERFORMANCE_TICKS_PER_SECOND 10368000
#ifndef RS_PERFORMANCE_TICKS_PER_SECOND
  #define RS_PERFORMANCE_TICKS_PER_SECOND 0 /*!< RS performance timer configuration. */
#endif
//@}

/** \cond internal */
#if (RS_TARGET_FAMILY == RSTF_WINDOWS)
  #define RS_PERFORMANCE_FREQUENCY RsPerformanceFrequency
#else
  #if (RS_READ_PERFORMANCE_COUNTER == 1)
    #if !defined(RS_PERFORMANCE_TICKS_PER_SECOND) || (RS_PERFORMANCE_TICKS_PER_SECOND == 0)
      !error Missing definition of RS_PERFORMANCE_TICKS_PER_SECOND
    #endif
    #define RS_PERFORMANCE_FREQUENCY RS_PERFORMANCE_TICKS_PER_SECOND
  #endif
#endif
/** \endcond */

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

#ifndef RS_OVERRIDE_TICK_TYPES
  typedef rsuint32 RsTimerTickType; /*!< For timer tick values. 1 tick = 1 ms. */
  typedef rsuint32 RsPerformanceTickType; /*!< For performance/profiling measurement in ticks. */
  typedef rsuint16 RsPerformanceTimeType; /*!< For performance/profiling times in us or ms. */
#endif

/****************************************************************************
*                           Global variables/const
****************************************************************************/

RS_BEGIN_EXTERN_C

/// RS system timer tick counter. 1 tick = 1 ms.
extern RS_FASTDATA_ADR volatile RsTimerTickType RsTimerTickCount;

/// RS system second counter.
extern RS_FASTDATA_ADR rsuint32 RsSecondCount;

/// RS system ticks-to-second counter.
extern RS_FASTDATA_ADR rsuint16 RsTimerTicksThisSecond;

/** \cond internal */
extern RsPerformanceTickType RsPerformanceFrequency;
/** \endcond */

/****************************************************************************
*                             Function prototypes
****************************************************************************/

/** \name RS timer functions.
*/
//@{

/// RS timer ISR.
/** To be called directly from the applications timer ISR.
* \param ElapsedTicks Number of ticks elapsed. 1 tick = 1 ms. */
void RsTimerTick(rsuint16 ElapsedTicks);

#if (RS_READ_PERFORMANCE_COUNTER == 1) && (RS_READ_PERFORMANCE_COUNTER_INLINED == 0)
/// Get performance/profiling counter. This function is called when \ref RS_READ_PERFORMANCE_COUNTER is set to 1.
/** Called from FOS for performance/profiling measurements.
* \return Current performance counter value. */
RsPerformanceTickType RsReadPerformanceCounter(void);
#endif

#if (RS_READ_PERFORMANCE_COUNTER == 1) && (RS_READ_PERFORMANCE_T2T_INLINED == 0)
/// Convert performance/profiling counter to actual time. This function is available when \ref RS_READ_PERFORMANCE_COUNTER is set to 1.
/** \param PerformanceTicks Measured performance ticks to convert.
* \return The actual time for the ticks given. If RS_PTIME_MS is set, the time is in milliseconds. If not, the time is in microseconds. */
RsPerformanceTimeType RsPerformanceTicks2Time(RsPerformanceTickType PerformanceTicks);
#endif

#if (RS_READ_PERFORMANCE_COUNTER == 1) && (RS_READ_PERFORMANCE_T2T_INLINED == 0)
/// Convert actual time to performance/profiling counter ticks. This function is available when \ref RS_READ_PERFORMANCE_COUNTER is set to 1.
/** \param Time Actual time. If RS_PTIME_MS is set, the time is in milliseconds. If not, the time is in microseconds.
* \return Performance ticks. */
RsPerformanceTickType RsTime2PerformanceTicks(RsPerformanceTimeType Time);
#endif

#if (RS_READ_PERFORMANCE_COUNTER == 1)
/// Burn CPU cycles (spin) for a specified time. This function is available when \ref RS_READ_PERFORMANCE_COUNTER is set to 1.
/** \param PerformanceTicks Number of performance ticks to spin. */
void RsBurnCycles(RsPerformanceTickType PerformanceTicks);
#endif

/// Set new \ref RsSecondCount value.
/** \param Value New value for \ref RsSecondCount. */
void RsSetSecondCounter(rsuint32 Value);
//@}

/** \cond internal */
// Deprecated.
#define RsPerformanceTicksPerSecond !deprecated
/** \endcond */

/** \cond internal */
#if (RS_READ_PERFORMANCE_COUNTER == 1) && (RS_READ_PERFORMANCE_T2T_INLINED == 1)
RS_C_INLINE RsPerformanceTimeType RsPerformanceTicks2Time(RsPerformanceTickType PerformanceTicks)
{
  rsuint32 t = (rsuint32)(PerformanceTicks / (RS_PERFORMANCE_FREQUENCY / 1000000UL));
  if (t > 0x8000UL)
  {
    t = (rsuint32)(PerformanceTicks / (RS_PERFORMANCE_FREQUENCY / 1000UL));
    t |= RS_PTIME_MS;
  }
  return (RsPerformanceTimeType)t;
}

RS_C_INLINE RsPerformanceTickType RsTime2PerformanceTicks(RsPerformanceTimeType Time)
{
  RsPerformanceTickType t;
  if (Time & RS_PTIME_MS)
  {
    Time &= ~RS_PTIME_MS;
    t = (RsPerformanceTickType)(Time * (RS_PERFORMANCE_FREQUENCY / 1000UL));
  }
  else
  {
    t = (RsPerformanceTickType)(Time * (RS_PERFORMANCE_FREQUENCY / 1000000UL));
  }
  return t;
}
#endif
/** \endcond */

RS_END_EXTERN_C

#endif

// End of file.

