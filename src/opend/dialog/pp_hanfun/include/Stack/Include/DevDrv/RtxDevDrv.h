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
 *//*! \file
* Primary header file, which brings in everything needed to implement RTX devicer interface.
*/

/** @defgroup devdrvclasses Available Device Driver Classes
*/

/** @defgroup devdrivers Available Device Drivers
*/

/** \mainpage RTX Device Driver Interface Refrence Manual
* \image html rtxlogo.gif
* <hr>
*
* The aim of this document is to give a description of the RTX Device Driver architecture and a usage guide to device drivers.
* This document enables software engineers to implement and use device drivers.
* <UL>
* <LI>\subpage devdrv_faq Frequently Asked Questions.</LI>
* <LI>\subpage devdrv_survey provides an overview of the device driver concepts.</LI>
* <LI>\subpage devdrv_rtx_devdrv_design provides an overview of the RTX device driver design.</LI>
* <LI>\subpage devdrv_folder_structure describes the placement of header files, source code and projects.</LI>
* <LI>\subpage devdrv_manager Device Driver Manager (DDM) and options.</LI>
* </UL>
* <hr>
* \section Interface Interface
* <UL>
* <LI>\subpage devdrv_cdi Control Data Interface (CDI)</LI>
* </UL>
* <hr>
*
* \section Quick_Links_By_Function Quick Links
* <UL>
*  <LI>\link devdrvclasses Device Driver Classes \endlink - Complete list of all device driver classes.</LI>
*  <LI>\link devdrivers Device Drivers \endlink - Complete list of all device drivers available in this project.</LI>
* </UL>
* <hr>
*
* By header file: Click the "Directories" in the tree.
*
* By name: Click the "Globals" in the tree.
* <br><br>
*/

/** \page devdrv_survey Device Driver Survey
* <h2>Introduction to device drivers</h2>
* The main purpose of device drivers is to decouple application code from hardware idiosyncrasies.
* Generally, device drivers are usually divided into two categories: character and block device drivers,
* each with it's own characteristics:
*
* <strong>Character based drivers:</strong>
* <UL>
* <LI>Read/write of a single character at a time</LI>
* <LI>Sequential access</LI>
* <LI>Support for text and binary modes (optional)</LI>
* </UL>
*
* <strong>Block based drivers:</strong>
* <UL>
* <LI>Read/write of multiple characters at a time</LI>
* <LI>Random access.</LI>
* <LI>Support for files and folders (optional)</LI>
* </UL>
* <strong>Both types have a common set of features:</strong>
*
* <UL>
* <LI>A standardized interface.</LI>
* <LI>Each driver type supports one hardware type.</LI>
* <LI>Each driver instance supports one hardware unit.</LI>
* <LI>Usually drivers are identified by name, i.e. each driver has a unique name stored internally,
* and the application/OS accesses the driver by referring to the name.</LI>
* </UL>
* In most operating systems device drivers interact with the OS rather than the application.
* This allows the application to treat device drivers as files, creating simpler and more flexible access to devices.
*
* <h2>Introduction to the RTX Device Driver architecture</h2>
* The RTX Device Driver architecture supports only one type of driver, which is a mix of the character and block based types.
* This greatly simplifies device driver implementation. RTX Device Drivers all share the this set of features:
*
* <ul>
* <li>Support for single as well as blocks of data.</li>
* <li>Support for sequential and random access.</li>
* <li>A very simple common set of operations that will suit most drivers, and which may be extended for more advanced drivers.</li>
* <li>Support for runtime driver assignment.</li>
* <li>No support for files and folders (although individual drivers may implement it).</li>
* <li>Mandatory interrupt decoupling. </li>
* <li>Registerable callback functions.</li>
* <li>Common status codes that may be extended by individual drivers.</li>
* <li>Support for nestable drivers, i.e. drivers may call drivers. </li>
* <li>Device drivers may be called by application code as well as by the OS.</li>
* </ul>
*
* All device drivers share a basic interface, which specifies how to require the interface of a specific driver and how to
* communicate with it. On top of this basic interface is another interface, called the class interface, which is defined
* by the class to which the specific driver belongs. The class interface defines the commands and data structures used by a class.
* See section 10.1 for a description of device driver classes and the class interface.

* \image html devdrv_arch.png
*
*
* The Irq and Hardware interfaces are implementation defined and will not be discussed here.
* The ControlData interface (CDI) is the interface used by the client code to access the driver.
* The Callback interface is used by the driver to call into the client code when an event has occurred.
* The OS interface is used by the driver to request the OS to call the driver at a later time.
*
*/

/** \page devdrv_rtx_devdrv_design RTX device driver design
* \section devdrv_device_drv_classes Device driver classes
* A class is a collection of drivers that share the same set of commands and data structures, and has similar functionalities.
* The purpose of grouping device drivers in class is to allow the client to switch drivers by simply calling a different
* GetDeviceDriverInterface function. An example could be a class containing UART and SPI bus drivers.
* An application could thus change from a platform using a UART to another one using SPI by simply calling another GetDeviceDriverInterface
* function, as the class definition guarantees that the two drivers will be exchangeable.
*
* For this to work properly all drivers of the class must comply with the class interface.
* In order to enforce this, the class interface is defined entirely by the class, not by the device driver that is a member of the class.
*
* A class must define all commands and data structures used by members of the class.
* It is not allowed to redefine commands and/or structures defined by the basic interface.
*
* \section devdrv_callback_interface Callback interface
* It is possible for a device driver to call functions in the client by using call-back functions.
* The client code must register a call-back function in the driver by use of the RegisterCallback command.
* The call is always done in application context, i.e. the client code does not need to worry about interrupt protection.
* A device driver may offer subscribing to any number of callback functions, and it is also allowed (but not required)
* to support multiple subscriptions to a callback function.
* It may even omit the CallBack interface completely, in this case the RegisterCallBack must return DRV_ERR_UNSUPPORTED.
* It is also allowed to redefine the callback interface by implementing a new function for registering callback functions.
* If this is done the mandatory RegisterCallBack must return  DRV_ERR_UNSUPPORTED.
* It is not allowed to reimplement the mandatory RegisterCallBack using different types.
* The context argument contains the value supplied to the RegisterCallback command when the callback is registered.
* This can be used to have one callback function support multiple drivers.
*
* \section dev_drv_require_cdi Require CDI
* In order to support run-time assignment, a mechanism for requiring the ControlData interface has been devised.
* Every device driver must provide a function that returns a pointer to the ControlData interface.
* This pointer is of a driver defined type, which must be defined as a structure containing function pointers
* to all the commands supported by the driver.
* The function to obtain the ControlData interface is defined like this:
* <tt>const DrvCdiType* GetDeviceDriverInterface(void);</tt>
* As this function is the only public function in the device driver, the function name and the return type must be prefixed
* with the name of the driver to avoid colliding with similar functions and types in other drivers.
* Our imaginary driver Foo must thus export this function:
* \code
* typedef struct Foo_DrvCdiType
* {
*    DrvCdiType 		Cdi;
*    DoSomethingPtrType 	DoSomething;
*    DoSomeMorePtrType 	DoSomeMore;
* } Foo_DrvCdiType;
*
*const Foo_DrvCdiType* Foo_GetDeviceDriverInterface(void);
* \endcode
*
* \section devdrv_multi_instance_handling Multi instance handling
* A class may support multiple instances of the same driver. If so a handle to the instance must be obtained from the driver
* before the driver is initialized. This is known as opening the driver, and is done by calling HandleInstance with the DRV_INST_OPEN * command.
* The handle will then be returned to the client or an error issued. The handle must be specified in all subsequent calls to the driver functions.
*
* If the driver supports releasing an instance again it must also handle the DRV_INST_CLOSE command, otherwise it must return DRV_ERR_UNSUPPORTED.
*
* If the driver does not support multiple instances HandleInstance() must return DRV_ERR_UNSUPPORTED.
*
*
* \section devdrv_error_handling Error handling
* \subsection devdrv_error_global Global errors
* Global errors are errors that prevent the driver from working, e.g. if the hardware is malfunctioning or already in use.
* Global errors are reported in the DrvStatusType returned by GetDrvInfo(). The information in the DrvStatusType is synchronized
* to the error, i.e. the error is reported by GetDrvInfo() continuously until the error disappears.
* \subsection devdrv_error_loca Local errors
* Local errors are errors that occur in, and is local to, a member function, e.g. unknown command or buffer full.
* Local errors are not reported by GetDrvInfo(), but a driver may choose to return DRV_ERR_GLOBAL_ERROR if there was no local errors and a global error exists.
*
* \section dev_drv_intf_consistency Securing consistiency between client and driver
* Drivers may be delivered to customers as binaries, which results in a possible mismatch between the interface used when compiling
* the driver and the interface used by the client code. To prevent this the client must specify the version of the interface used
* when initializing the driver. This is done by using the predefined macro DRV_CLASS_XXX_IF_VERSION (where XXX is the name of the class)
* when calling Init(). IF the versions does not match the return value from Init() will be DRV_ERR_INTERFACE_MISMATCH.
* The macro is defined in the headerfile of the class, and must be updated whenever the class interface changes.
* The DRV_CLASS_XXX_IF_VERSION macro is composed from the version of the ControlData interface in the major part of the number,
* and the version number of the class interface in the minor number.
* Generally, the interface versions should match, i.e. have the same versions numbers. However, it is also possible for a driver
* to implement other schemes, like major version number must match, or v1.5 works with v1.5 and v1.7 but not v1.6.
*
* \section devdrv_design_impl Implementation
* The figure below shows a typical design of a device driver. Please note that this design is not mandatory, any driver is allowed to use a different design as long as it complies with the interface specifications. For example, a driver that uses polling will probably use a different design.
*
* \image html devdrv_implemenation.png
* \subsection	devdrv_design_cmd_dist Command distribution
* The command distribution is responsible for calling the corresponding command handler. It is handled entirely by the compiler.
* \subsection	devdrv_design_cmd_handling Command handling
* The command handlers are responsible for handling incoming commands. Every handler is able to interact with the device using the hardware interface, and to schedule a callback.
* \subsection	devdrv_design_callback	CallBack handler
* The CallBack handler is responsible for the handling of subscriptions to callback functions, as well as for making the actual callbacks when triggered by the OS interface.
* \subsection	devdrv_design_irq IRQ handler
* The IRQ handler is responsible for accessing the device as a response to an interrupt, e.g. transferring data between the buffer and the device. It may also request an OS callback via the OS interface if the driver needs more processing time in application context, e.g. if a callback to the client is required to transfer data to or from the application.

*/

/** \page devdrv_folder_structure Folder Structure
*
* Each of the folders are described in the following sections.
* <pre>
*(root)
*  \ref include_folder/
*    \ref include_devdrv_folder/
*      \ref include_devdrv_classes_folder/
*  \ref components_folder/
*    \ref components_devdrv_folder/
*      \ref components_devdrv_classes_folder/
* </pre>
* <hr>
*
* \section include_folder Include
* General header files and headers for components. This folder must be in the compiler's include path.
*
* \subsection include_devdrv_folder Include/DevDrv
* Root folder for device driver classes, and home of the overala RTX Device driver interface header.
*
* \subsection include_devdrv_classes_folder Include/DevDrv/Classes
* This folder contaion varous device driver classes sub folder, that each handles as specidifc class of device driver.f c/cpp files has this file as the first (and often only) include file.</p>
* <hr>
*
* \section components_folder Components
* This is the primary source code repository, where implementation files are located.
*
* \section components_devdrv_folder Components/DevDrv
* Home of all device driver implementations.
*
* \section components_devdrv_classes_folder Components/DevDrv/Classes
* Each subfolder in this folder holds implementation of hard ware specifc driver, based on the class interface described in the \ref include_devdrv_folder
*
* \page devdrv_survey Device Driver Survey
* <h2>Introduction to device drivers</h2>
* The main purpose of device drivers is to decouple application code from hardware idiosyncrasies.
* Generally, device drivers are usually divided into two categories: character and block device drivers,
* each with it's own characteristics:
*
* <strong>Character based drivers:</strong>
* <UL>
* <LI>Read/write of a single character at a time</LI>
* <LI>Sequential access</LI>
* <LI>Support for text and binary modes (optional)</LI>
* </UL>
*
* <strong>Block based drivers:</strong>
* <UL>
* <LI>Read/write of multiple characters at a time</LI>
* <LI>Random access.</LI>
* <LI>Support for files and folders (optional)</LI>
* </UL>
* <strong>Both types have a common set of features:</strong>
*
* \page devdrv_cdi Control Data Interface (CDI)
* The ControlData interface consists of a set of functions, one for each command supported by the driver.
* Some are mandatory and must exists in all drivers as specified in this document. Others are specific to single calls of drivers.
* The name of the functions are implementation defined, as the functions are local to the driver
* and the names need thus not be known outside the driver, only the prototypes must be known.
*
* All non-mandatory member functions of the ControlData interface must return either status information
* in an \ref DrvErrorType or some other suitable data as defined by the class.
* The mandatory member functions must be implemented as specified in this document.
*
* \code
* typedef struct DrvCdiType
* {
*   DrvCmdInitPtrType                   Init;
*   DrvCmdGetDrvInfoPtrType             GetDrvInfo;
*   DrvCmdRegisterCallbackPtrType       RegisterCallback;
*   DrvHandleInstancePtrType            HandleInstance;
*   DrvTestPtrType                      Test;
*   DrvSimulatePtrType                  Simulate;
*   DrvIoCtrlPtrType                    IoCtrl;
*   // extended interface
*   DrvCmdLoadPtrType                   Load;
*   DrvCmdSetSuspendStatePtrType        SetSuspendState;
*   DrvCmdLoadPtrType                   Unload;
*
* }  DrvCdiType;
* \endcode
*
*/


/****************************************************************************
*                               Include files
****************************************************************************/

#ifndef RTXDEVDRV_H
#define RTXDEVDRV_H

#include <Core/RtxCore.h>

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/// This value may be used as argument to functions that requires an instance
/// handle if the driver does not support multiple instances.
#define DRV_INSTANCE_NONE 0xFF

/// The version of the mandatory interface. This is, when combined with the
/// version of the class interface, used to check for interface mismatch
/// between the driver and the client code.
#define DRV_BASECLASS_IF_VERSION   0x01

/** \cond internal */
#ifndef DRVMETHOD_GETDRVINFO_ENABLED
  #define DRVMETHOD_GETDRVINFO_ENABLED 1
#endif
#if (DRVMETHOD_GETDRVINFO_ENABLED == 1)
  #define DRVMETHOD_GETDRVINFO(f) f,
#else
  #define DRVMETHOD_GETDRVINFO(f)
#endif

#ifndef DRVMETHOD_REGISTERCALLBACK_ENABLED
  #define DRVMETHOD_REGISTERCALLBACK_ENABLED 1
#endif
#if (DRVMETHOD_REGISTERCALLBACK_ENABLED == 1)
  #define DRVMETHOD_REGISTERCALLBACK(f) f,
#else
  #define DRVMETHOD_REGISTERCALLBACK(f)
#endif

#ifndef DRVMETHOD_HANDLEINSTANCE_ENABLED
  #define DRVMETHOD_HANDLEINSTANCE_ENABLED 1
#endif
#if (DRVMETHOD_HANDLEINSTANCE_ENABLED == 1)
  #define DRVMETHOD_HANDLEINSTANCE(f) f,
#else
  #define DRVMETHOD_HANDLEINSTANCE(f)
#endif

#ifndef DRVMETHOD_TEST_ENABLED
  #define DRVMETHOD_TEST_ENABLED 1
#endif
#if (DRVMETHOD_TEST_ENABLED == 1)
  #define DRVMETHOD_TEST(f) f,
#else
  #define DRVMETHOD_TEST(f)
#endif

#ifndef DRVMETHOD_SIMULATE_ENABLED
  #define DRVMETHOD_SIMULATE_ENABLED 1
#endif
#if (DRVMETHOD_SIMULATE_ENABLED == 1)
  #define DRVMETHOD_SIMULATE(f) f,
#else
  #define DRVMETHOD_SIMULATE(f)
#endif

#ifndef DRVMETHOD_IOCTRL_ENABLED
  #define DRVMETHOD_IOCTRL_ENABLED 1
#endif
#if (DRVMETHOD_IOCTRL_ENABLED == 1)
  #define DRVMETHOD_IOCTRL(f) f,
#else
  #define DRVMETHOD_IOCTRL(f)
#endif

#ifndef DRVMETHOD_LOAD_ENABLED
  #define DRVMETHOD_LOAD_ENABLED 1
#endif
#if (DRVMETHOD_LOAD_ENABLED == 1)
  #define DRVMETHOD_LOAD(f) f,
#else
  #define DRVMETHOD_LOAD(f)
#endif

#ifndef DRVMETHOD_SETSUSPEND_ENABLED
  #define DRVMETHOD_SETSUSPEND_ENABLED 1
#endif
#if (DRVMETHOD_SETSUSPEND_ENABLED == 1)
  #define DRVMETHOD_SETSUSPEND(f) f,
#else
  #define DRVMETHOD_SETSUSPEND(f)
#endif

#ifndef DRVMETHOD_UNLOAD_ENABLED
  #define DRVMETHOD_UNLOAD_ENABLED 1
#endif
#if (DRVMETHOD_UNLOAD_ENABLED == 1)
  #define DRVMETHOD_UNLOAD(f) f,
#else
  #define DRVMETHOD_UNLOAD(f)
#endif

/** \endcond */

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/// This type reflects the global status of the driver: ok, error or busy.
/// Please note that the Reserved bits may not be used. The ErrorCode
/// field is only valid if the Error bit is set.
typedef union
{
  rsuint16 Value;                 /*!<  integer status code value  */
  struct
  {
    rsbitfield Busy        :  1;  /*!<  Driver is busy  */
    rsbitfield Reserved1   :  1;  /*!<  Reserved  */
    rsbitfield Reserved2   :  1;  /*!<  Reserved  */
    rsbitfield Reserved3   :  1;  /*!<  Reserved  */
    rsbitfield Reserved4   :  1;  /*!<  Reserved  */
    rsbitfield Reserved5   :  1;  /*!<  Reserved  */
    rsbitfield Reserved6   :  1;  /*!<  Reserved  */
    rsbitfield Error       :  1;  /*!<  Reserved  */
    rsbitfield ErrorCode   :  8;  /*!<  Reserved  */
  };
} DrvStatusType;

/// This type is used for the return value from member functions that returns an error code. The type does not define the actual errorcodes, see \ref DrvErrorValueType
typedef rsuint8 DrvErrorType;

/// DrvErrorType is an 8-bit enum, which defines the error codes used
/// by the ControlData interface.
/// It defines the error codes that are common to all device drivers.
/// A driver class may append its own error codes to the values defined in DrvErrorType, like this:
/// \code
/// typedef enum
/// {
///   DRV_ERR_CLASS_FOO_TITANIC_SUNK = DRV_ERR_FIRST_CLASS_DEFINED_ERROR,
///	  DRV_ERR_CLASS_FOO_CHALLENGER_EXPLODED,
/// }ENUM8(DrvErrorClassFooType);
/// \endcode
typedef enum
{
   DRV_ERR_NONE,                             /*!<  No problems, all went well  */
   DRV_ERR_BUSY,                             /*!<  The driver is busy and not able to process the request  */
   DRV_ERR_BUFFER_OVERRUN,                   /*!<  A buffer overrun happened  */
   DRV_ERR_GLOBAL_ERROR,                     /*!<  A major error occurred  */
   DRV_ERR_INTERFACE_MISMATCH,               /*!<  The driver was compiled with an incompatible version of the
                                              *    interface compared to the interface used by the caller */
   DRV_ERR_UNSUPPORTED,                      /*!<  Functionality not supported */
   DRV_ERR_RANGE_ERROR,                      /*!<  Something, e.g. a parameter, was outside the legal range */
   DRV_ERR_NO_RESOURCES,                     /*!<  Error occured due to no resources */
   DRV_ERR_COMMON_ERROR_COUNT,			     /*!<  Defined the number of common defined error id's	 	 */
   DRV_ERR_FIRST_CLASS_DEFINED_ERROR = 0x80  /*!<  Reserve room for expanding the common error codes */
}  DrvErrorValueType;


/// This type defines the existing classes
typedef enum
{
   DRV_CLASS_NONE,          /*!< Nodriver class  */
   DRV_CLASS_SERCOM,        /*!< Serial Communication driver class  */
   DRV_CLASS_ADC,           /*!< ADC driver class  */
   DRV_CLASS_SIMPLESPI,     /*!< Simple Spi port driver class  */
   DRV_CLASS_GEN2DSPCORE,   /*!< Sitel GEN2DSP driver class  */
   DRV_CLASS_PSTNLINE,      /*!< PSTN line driver class  */
   DRV_CLASS_PCM,           /*!< Pcm port driver driver class  */
   DRV_CLASS_CODEC,         /*!< audio codec driver class  */
   DRV_CLASS_PORT,          /*!< port driver class  */
   DRV_CLASS_I2C,           /*!< i2c driver class  */
   DRV_CLASS_DISPLAY,       /*!< Standard display driver */
   DRV_CLASS_FLASH,         /*!< Generic flash driver. Compatible with TamDrv Mk2 */
   DRV_CLASS_KEYBOARD,      /*!< Keyboard driver class */
   DRV_CLASS_NVS,           /*!< Nvs driver class*/
   DRV_CLASS_SYSCLK,        /*!< System Clock driver class */
   DRV_CLASS_ULP,           /*!< ULP driver class  */
   DRV_CLASS_DSC2,          /*!< DSC2 driver class  */  

   DRV_CLASS_COUNT
}  RSENUM8(DrvClassIdType);


/// This type holds the id of the driver. The actual values are defined in
/// the class header files.
typedef rsuint8 DrvIdType;

/// This type is used to hold version info in the major.minor format.
typedef rsuint16 DrvVersionType;


/// This type holds information regarding the driver
typedef struct DrvInfoType
{
   DrvClassIdType ClassId;				/*!< Incicates the class id of the driver */
   DrvIdType DrvId;						/*!< Implementation reference id */
   DrvVersionType DriverVersion;		/*!< Driver version number */
   DrvVersionType InterfaceVersion;		/*!< Driver interface version, this should be used to cross check interface version with driver client   */
   rsuint8 MaxInstanceCount;			/*!< Max allowed instances for this driver  */
   rsuint8 CurrentInstanceCount;		/*!< Number of current active instances  */
}  DrvInfoType;

/// The context value used in the callback interface, to parse a context value, in case of multiple instances
typedef rsuint8 DrvContextType;

/// The instance handle type for drivers that supports multiple instances
typedef rsuint8 DrvInstanceHandleType;

/// Basic driver instance commands, used together with \ref DrvCdiType.HandleInstance()
typedef enum
{
   DRV_INST_OPEN,   /*!< Open driver instance  */
   DRV_INST_CLOSE,  /*!< Close driver instance  */
}  DrvInstCmdType;

/// Basic suspend/resume command supported by SetSuspendState()
typedef enum
{
  DRV_SUSPEND_NOT_SUSPENDED, /*!< Driver not suspended  */
  DRV_SUSPEND_SLEEP,         /*!< Suspend driver into sleep mode  */
  DRV_SUSPEND_HIBERNATE      /*!< Suspend driver into hibernate mode  */
} DrvSuspendType;

// Functions pointers to the mandatory interface
/// Initialize and starts the driver. This command must be issued before any other command.
/*!
  \note If using the device driver manager, this function is called via the "rshookready" hook
         - Interrupts are disabled
         - Heap is availableMessages are only send to all input units!
  \param[in] IntfVer \copybrief DrvVersionType.
  \param[in] Instance \copybrief DrvInstanceHandleType.
  \return DrvErrorType \copybrief DrvErrorType. */
  typedef DrvErrorType    (*DrvCmdInitPtrType)          (DrvVersionType IntfVer, DrvInstanceHandleType Instance);

/// Get current driver information.
/*!
  \note Messages are only send to all input units!
  \param[in] info \copybrief DrvInfoType.
  \return DrvErrorType \copybrief DrvErrorType. */
typedef DrvStatusType   (*DrvCmdGetDrvInfoPtrType)    (DrvInfoType* info);

/// This command is used to open and close an instance of the driver.
/*!
  \param[in] Cmd \copybrief DrvInstCmdType.
  \param[in] Instance \copybrief DrvInstanceHandleType.
  \return DrvErrorType \copybrief DrvErrorType . */
typedef DrvErrorType    (*DrvHandleInstancePtrType)   (DrvInstCmdType Cmd,  DrvInstanceHandleType* Instance);

/// Test handle.
/*!
  \param[in] Cmd
  \param[in] CmdData
  \param[in] Instance \copybrief DrvInstanceHandleType.
  \return DrvErrorType \copybrief DrvErrorType . */
typedef DrvErrorType    (*DrvTestPtrType)             (rsuint8 Cmd,  void* CmdData,  DrvInstanceHandleType Instance);

/// Simulate some kind of stimulus in the driver.
/// This function only available in the PC simulation and should not be called during normal operation..
/*!
  \param[in] Cmd A class-defined command that specifies which simulation  functionality to execute
  \param[in] CmdData A pointer to class-defined data.
  \param[in] Instance \copybrief DrvInstanceHandleType.
  \return DrvErrorType \copybrief DrvErrorType . */
typedef DrvErrorType    (*DrvSimulatePtrType)         (rsuint8 Cmd,  void* CmdData,  DrvInstanceHandleType Instance);

/// Callback function prototype
/*!
  \param[in] Event A class-defined set of events.
  \param[in] EventData A class-defined set of data.
  \param[in] Context \copybrief DrvContextType.
  \return DrvErrorType \copybrief DrvErrorType . */
typedef void            (*DrvCallBackFuncPtrType)     (rsuint8 Event, void* EventData, DrvContextType Context, DrvInstanceHandleType Instance);

/// Register a callback function in the driver. The context value is used as an argument to the callback function but is otherwise not used
/*!
  \param[in] CbFunc \copybrief DrvCallBackFuncPtrType.
  \param[in] Context \copybrief DrvContextType.
  \param[in] Instance \copybrief DrvInstanceHandleType.
  \return DrvErrorType \copybrief DrvErrorType . */
typedef DrvErrorType    (*DrvCmdRegisterCallbackPtrType) (DrvCallBackFuncPtrType CbFunc,  DrvContextType Context,  DrvInstanceHandleType Instance);

/// Generic control functionality that can pass any data and command to the driver instance
/*!
  \param[in] info \copybrief DrvInstCmdType.
  \param[in] Instance \copybrief DrvInstanceHandleType.
  \return DrvErrorType \copybrief DrvErrorType . */
typedef DrvErrorType    (*DrvIoCtrlPtrType)           (rsuint8 Cmd, void *CmdData, rsuint16 CmdDataLength, DrvInstanceHandleType Instance);

///Loads/Unload  the driver.
/// \note If using the device driver manager, this function is called via "rshookready" hook
///	  - Interrupts are disabled
///   - Heap is available
/*!
  \param[in] Instance \copybrief DrvInstanceHandleType.
  \return DrvErrorType \copybrief DrvErrorType . */
typedef DrvErrorType    (*DrvCmdLoadPtrType)          (DrvInstanceHandleType Instance);

/// Tells the driver about the current suspend state  (sleep/hibernate/not_suspended).
/// Calling set_suspend_state before init is allowed – means that the driver will be initialized in suspend state.
/*!
  \param[in] info \copybrief DrvInstCmdType.
  \param[in] Instance \copybrief DrvInstanceHandleType.
  \param[in] n_Suspend \copybrief DrvSuspendType.
  \return DrvErrorType \copybrief DrvErrorType . */
typedef DrvErrorType    (*DrvCmdSetSuspendStatePtrType) (DrvInstanceHandleType Instance, DrvSuspendType n_Suspend);


/// Common driver interface function table
typedef struct DrvCdiType
{
  DrvCmdInitPtrType                   Init;               /*!< \copybrief DrvCmdInitPtrType  */
  #if (DRVMETHOD_GETDRVINFO_ENABLED == 1)
  DrvCmdGetDrvInfoPtrType             GetDrvInfo;         /*!< \copybrief  DrvCmdGetDrvInfoPtrType       */
  #endif
  #if (DRVMETHOD_REGISTERCALLBACK_ENABLED == 1)
  DrvCmdRegisterCallbackPtrType       RegisterCallback;   /*!< \copybrief  DrvCmdRegisterCallbackPtrType */
  #endif
  #if (DRVMETHOD_HANDLEINSTANCE_ENABLED == 1)
  DrvHandleInstancePtrType            HandleInstance;     /*!< \copybrief  DrvHandleInstancePtrType      */
  #endif
  #if (DRVMETHOD_TEST_ENABLED == 1)
  DrvTestPtrType                      Test;               /*!< \copybrief  DrvTestPtrType                */
  #endif
  #if (DRVMETHOD_SIMULATE_ENABLED == 1)
  DrvSimulatePtrType                  Simulate;           /*!< \copybrief  DrvSimulatePtrType            */
  #endif
  #if (DRVMETHOD_IOCTRL_ENABLED == 1)
  DrvIoCtrlPtrType                    IoCtrl;             /*!< \copybrief  DrvIoCtrlPtrType              */
  #endif
  // extended interface
  #if (DRVMETHOD_LOAD_ENABLED == 1)
  DrvCmdLoadPtrType                   Load;               /*!< \copybrief  DrvCmdLoadPtrType             */
  #endif
  #if (DRVMETHOD_SETSUSPEND_ENABLED == 1)
  DrvCmdSetSuspendStatePtrType        SetSuspendState;    /*!< \copybrief  DrvCmdSetSuspendStatePtrType  */
  #endif
  #if (DRVMETHOD_UNLOAD_ENABLED == 1)
  DrvCmdLoadPtrType                   Unload;             /*!< \copybrief  DrvCmdLoadPtrType             */
  #endif
} DrvCdiType;

/****************************************************************************
*                           Global variables/const
****************************************************************************/

/****************************************************************************
*                             Function prototypes
****************************************************************************/

#endif

