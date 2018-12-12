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
* Header file for the general part of the system clock manager.
*/

/** \mainpage System Clock Manager
* \image html rtxlogo.gif
* <hr>
*
* The system clock manager controls clock resources that are shared between multiple devices and/or software components,
* with the primary purpose of reducing power consumption by shutting down or reducing clock signals that are not in use.
*
* Software components request resources by calling functions in the System Clock Manager, which then decides when to increase or reduce clocks.
*
* <hr>
* \section CPU_Clock_Management CPU Clock Management
*
* The primary resource is the CPU clock, which is requested by calling \ref ScCpuRequest.
* A software component typically increases the CPU clock to \ref SCS_ACTIVE when there is some work to do,
* and decreases to \ref SCS_SLEEP when done.
*
* \code
* void f(void)
* {
*   ScCpuRequest(SCU_APP1, SCS_ACTIVE);
*   ...
*   ScCpuRequest(SCU_APP1, SCS_SLEEP);
* }
* \endcode
*
* The resource states are implemented using bitsets (i.e. one bit for each \ref ScCpuUserIdType), so it is possible to request the same state multiple times,
* and it is possible to jump directly from one state to another without going through intermediate states.
*
* The CPU clock is mapped to a set of \ref ScCpuState's, with diffences in the clock frequency when the CPU is active and waiting for interrupts,
* and different accuracy of the timer system.
*
* The following table shows the relation between CPU state, clocks, interrupt latency and system tick.
* <table>
* <tr> <td><b>CPU state     </td> <td>Clock (working)</td> <td>Divider (waiting)</td> <td>Clock (waiting)</td> <td>Interrupt latency</td> <td>System Tick</b></td> </tr>
* <tr> <td> \ref SCS_BOOST  </td> <td>Max            </td> <td>1                </td> <td>Max            </td> <td>Minimum          </td> <td>1 ms           </td> </tr>
* <tr> <td> \ref SCS_ACTIVE </td> <td>10.368 MHz     </td> <td>16               </td> <td>648 kHz        </td> <td>Low              </td> <td>10 ms          </td> </tr>
* <tr> <td> \ref SCS_IDLE   </td> <td>10.368 MHz     </td> <td>128              </td> <td>81 kHz         </td> <td>Medium           </td> <td>50..80 ms      </td> </tr>
* <tr> <td> \ref SCS_SLEEP  </td> <td>10.368 MHz     </td> <td>128              </td> <td>81 kHz         </td> <td>High             </td> <td>160..640 ms    </td> </tr>
* </table>
*
* The following table shows the clock dividers applied when the CPU is waiting.
* <table>
* <tr> <td><b>CPU state     </td> <td>XDIV</td> <td>HCLK_DIV     </td> <td>HCLK_PRE</td> <td>Total</td> <td>Comments</b></td> </tr>
* <tr> <td> \ref SCS_BOOST  </td> <td>1   </td> <td>1 or 2 (note)</td> <td>1       </td> <td>1    </td> <td>Maximum. The actual clock depends on whether the PLL is on or off.</td> </tr>
* <tr> <td> \ref SCS_ACTIVE </td> <td>1   </td> <td>1            </td> <td>16      </td> <td>16   </td> <td>Normal active mode with some power saving when the CPU is waiting.</td> </tr>
* <tr> <td> \ref SCS_IDLE   </td> <td>1   </td> <td>8            </td> <td>16      </td> <td>128  </td> <td>Normal idle mode with good power savings.</td> </tr>
* <tr> <td> \ref SCS_SLEEP  </td> <td>16  </td> <td>8            </td> <td>1       </td> <td>128  </td> <td>Entire clock tree is divided i.e. some devices are not usable.</td> </tr>
* </table>
* \note HCLK_DIV is set so HCLK never exceeds 82.944 MHz.
*
* <hr>
*
* This document and the information contained is property of RTX Telecom A/S, Denmark.
* Unauthorized copying is not allowed. The information in this document is believed to
* be correct at the time of writing. RTX Telecom A/S reserves the right at any time to
* change said content, circuitry and specifications.<br><br>
*/


#ifndef SYSCLOCK_H
#define SYSCLOCK_H

/****************************************************************************
*                               Include files
****************************************************************************/

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/// General resource state type, used for both CPU and devices.
typedef enum
{
  SCS_OFF,    /*!< Power off. */
  SCS_SLEEP,  /*!< Reduced functionality and/or reduced clock. */
  SCS_IDLE,   /*!< Resource is idle. */
  SCS_ACTIVE, /*!< Resource is in use. */
  SCS_BOOST,  /*!< Resource is in high-performance mode. */
  SCS_MAX
} ScStateType;

/// CPU user ID's.
typedef enum
{
  SCU_NOUSER    = 0,        /*!< Internal. */
  SCU_APP1      = RSBIT0,   /*!< Application/task 1. */
  SCU_APP2      = RSBIT1,   /*!< Application/task 2. */
  SCU_APP3      = RSBIT2,   /*!< Application/task 3. */
  SCU_MAC       = RSBIT3,   /*!< MAC layer. */
  SCU_DSP       = RSBIT4,   /*!< DSP. */
  SCU_UART      = RSBIT5,   /*!< UART driver. */
  SCU_USB       = RSBIT6,   /*!< USB driver. */
  SCU_EEPROM    = RSBIT7,   /*!< EEPROM driver. */
  SCU_DISPLAY   = RSBIT8,   /*!< Display driver. */
  SCU_AUDIO     = RSBIT9,   /*!< Audio driver. */
  SCU_BATTERY   = RSBIT10,  /*!< Battery/charging control. */
  SCU_TRACE     = RSBIT11,  /*!< Trace system. */
  SCU_KEYBOARD  = RSBIT12,  /*!< Keyboard driver. */
  SCU_DEVICE1   = RSBIT13,  /*!< Device 1. */
  SCU_DEVICE2   = RSBIT14,  /*!< Device 2. */
  SCU_ISP       = RSBIT15,  /*!< In-System Programming (FWU). */
  SCU_MAX
} ScCpuUserIdType;

/** \cond internal */
typedef union
{
  rsuint16 Value;
  struct
  {
    rsbitfield APP1     : 1;
    rsbitfield APP2     : 1;
    rsbitfield APP3     : 1;
    rsbitfield MAC      : 1;
    rsbitfield DSP      : 1;
    rsbitfield UART     : 1;
    rsbitfield USB      : 1;
    rsbitfield EEPROM   : 1;
    rsbitfield DISPLAY  : 1;
    rsbitfield AUDIO    : 1;
    rsbitfield BATTERY  : 1;
    rsbitfield TRACE    : 1;
    rsbitfield KEYBOARD : 1;
    rsbitfield DEVICE1  : 1;
    rsbitfield DEVICE2  : 1;
    rsbitfield ISP      : 1;
  };
} ScCpuUserMaskType;
/** \endcond */

/****************************************************************************
*                           Global variables/const
****************************************************************************/

RS_BEGIN_EXTERN_C

/// Current CPU state. See \ref CPU_Clock_Management.
extern ScStateType ScCpuState;

/****************************************************************************
*                             Function prototypes
****************************************************************************/

/// Initialize system clock manager module. Should be called from e.g. RsHookPreInit().
void ScInit(void);

/// CPU resource request.
/** \param UserId User ID.
* \param State New CPU state: \ref SCS_SLEEP, \ref SCS_IDLE, \ref SCS_ACTIVE or \ref SCS_BOOST. */
void ScCpuRequest(ScCpuUserIdType UserId, ScStateType State);

/// UART resource request. Called from UART driver.
/** \param State New UART state: \ref SCS_OFF, \ref SCS_SLEEP or \ref SCS_ACTIVE. */
void ScUart1Request(ScStateType State);

/// Display resource request. Called from display driver.
/** \param State New display state: \ref SCS_OFF, \ref SCS_SLEEP or \ref SCS_ACTIVE. */
void ScDisplayRequest(ScStateType State);

/// EEPROM resource request. Called from EEPROM driver.
/** \param State New EEPROM state: \ref SCS_OFF, \ref SCS_SLEEP or \ref SCS_ACTIVE. */
void ScEepromRequest(ScStateType State);

RS_END_EXTERN_C

#endif

// End of file.

