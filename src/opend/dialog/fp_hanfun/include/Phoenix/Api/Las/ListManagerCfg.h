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

#ifndef LIST_MANAGER_CFG_H
#define LIST_MANAGER_CFG_H

/****************************************************************************
*                               Include files
****************************************************************************/
//#include <BmcCfg/DectCfg.h>
//#include <NwkSwitch/SwNwkPiCfg.h>

/****************************************************************************
*                              Macro definitions
****************************************************************************/
#define LM_SORT_AFTER_TASK_INIT FALSE    //Sorting after init initialized

#define LM_MAX_NUMBER_LENGTH (22 * XCHARBYTES)
#define LM_MAX_NAME_LENGTH   (16 * XCHARBYTES)

#define LM_ENABLE_LAS_CONTENT   // Enable LAS specific list content

/****************************************************************************
* Contacts settings
****************************************************************************/
#define LM_CONTACT_INCLUDED /*If defined an conatact list is included.*/
#ifdef LM_CONTACT_INCLUDED
  #define LM_MAX_CONTACT_ITEMS            20

  #define LM_MAX_NO_OF_CONTACT_NUMBERS     4
  #define LM_MAX_CONTACT_NUMBER_ATTRIBUTE_LENGTH   2     //This includes both the length of the length field plus the attributes.
  #define LM_MAX_CONTACT_ADD_ATTRIBUTE_LENGTH     32

  #define LM_MAX_CONTACT_LENGTH (sizeof(LmHeaderType) + \
                                 RSOFFSETOF(LmContactType,Data) + \
                                 LM_MAX_CONTACT_ADD_ATTRIBUTE_LENGTH + \
                                 LM_MAX_NAME_LENGTH + \
                                 (\
                                  (LM_MAX_NUMBER_LENGTH + LM_MAX_CONTACT_NUMBER_ATTRIBUTE_LENGTH) * LM_MAX_NO_OF_CONTACT_NUMBERS)\
                                 )
  #define LM_PRESENCE_INCLUDED         FALSE // If TRUE, presence is enabled
  #define LM_CONTACT_GROUP             FALSE // If TRUE, Groups is enabled
  #define LM_MAX_GROUP_ITEMS           1
  #define LM_MAX_CON_GRP_ATTRIB_LENGTH 10     // Maximum length of a filter group attrubute

  #define LM_CONTACT_SPEED_DIAL          FALSE // If TRUE, Speed dial is enabled
  #define LM_MAX_SPEED_DIAL_NUMBER_ITEMS 1
  #define LM_LENGTH_OF_SPEEDDIAL_NUMBERS 1
#endif

/****************************************************************************
* Call Log settings
****************************************************************************/
#define LM_CALL_LOG_INCLUDED /*If defined a call log list is included.*/
#ifdef LM_CALL_LOG_INCLUDED
  #define LM_MAX_CALL_LOG_ITEMS           10

  #define LM_MAX_CALL_LOG_NUMBER_ATTRIBUTE_LENGTH   1     //This includes both the length of the length field plus the attributes.
  #define LM_MAX_CALL_LOG_ADD_ATTRIBUTE_LENGTH     32

  #define LM_CALL_LOG_QUICKFILTER      // If defined, Item filtering will be done on the value stored in the sorted list in ram (only one byte)
  //#define LM_CALL_LOG_SORT           // If defined, The order is not stored in EEPROM, but sorted at power up according to time stamp.
  //#define LM_CALL_LOG_SEARCH         // If defined, A call log sorted after number is created
  //#define LM_CALL_LOG_SAVE_ALL_CALLS // If defined, all calls are saved seperatly (NoOfMissedCalls is always 1)

  #define LM_MAX_CALL_LOG_LENGTH (sizeof(LmHeaderType) + RSOFFSETOF(LmCallLogType,Data) + LM_MAX_CALL_LOG_ADD_ATTRIBUTE_LENGTH + LM_MAX_NAME_LENGTH + LM_MAX_CALL_LOG_NUMBER_ATTRIBUTE_LENGTH + LM_MAX_NUMBER_LENGTH)
#endif


/****************************************************************************
* Contacts 1 settings
****************************************************************************/
/*If defined an additional conatact list is included.*/
//#define LM_CONTACT_1_INCLUDED
#ifdef LM_CONTACT_1_INCLUDED
  #define LM_MAX_CONTACT_1_ITEMS          10
  #define LM_MAX_CON_1_GROUP_ITEMS        10

  #define LM_CONTACT_1_WILDCHAR_SEARCH                 //Wild char search is enabled.
  #define LM_WILDCHAR '*'                              //Definition of wild char
#endif


/****************************************************************************
* calendar settings
****************************************************************************/
/*If defined, calendar event entries can be stored.*/
//#define LM_ICAL_EVENT_INCLUDED
#ifdef LM_ICAL_EVENT_INCLUDED
  #define LM_MAX_ICAL_EVENT_ITEMS  10

  #define LM_MAX_ICAL_EVENT_SUMMARY_LENGTH      (32 * XCHARBYTES)
  #define LM_MAX_ICAL_EVENT_LOCATION_LENGTH     (32 * XCHARBYTES)
  #define LM_MAX_ICAL_EVENT_ATTRIBUTES_LENGTH   (32 * XCHARBYTES)

  #define LM_MAX_ICAL_EVENT_LENGTH  (sizeof(LmHeaderType) + RSOFFSETOF(LmCalendarType,Data) + LM_MAX_ICAL_EVENT_SUMMARY_LENGTH + LM_MAX_ICAL_EVENT_LOCATION_LENGTH+LM_MAX_ICAL_EVENT_ATTRIBUTES_LENGTH)

  #define LM_ICAL_EVENT_SORT         //The order is not stored in EEPROM, but sorted at power up according to time stamp.

  #define LM_ICAL_ALARM_INCLUDED // If included a list of sorted alarms will be maintained

#endif


/****************************************************************************
* SMS settings
****************************************************************************/
//#define LM_SMS_INCLUDED /*If defined, SMS entries can be stored.*/
#if defined LM_SMS_INCLUDED
  #define LM_MAX_SMS_ITEMS               10

  #define LM_MAX_SMS_ADD_ATTRIBUTE_LENGTH   (32 * XCHARBYTES)
  #define LM_MAX_SMS_BODY_LENGTH            (160 * XCHARBYTES)
  #define LM_MAX_SMS_ADDRESS_LENGTH         (32 * XCHARBYTES)

  #define LM_MAX_SMS_LENGTH  (sizeof(LmHeaderType)+RSOFFSETOF(LmSmsType,Data)+LM_MAX_SMS_ADD_ATTRIBUTE_LENGTH+LM_MAX_SMS_BODY_LENGTH+LM_MAX_SMS_ADDRESS_LENGTH)
  #define LM_SMS_SORT         //The order is not stored in EEPROM, but sorted at power up according to time stamp.
#endif


/****************************************************************************
* System Settings settings
****************************************************************************/
#define LM_SYSTEM_SETTINGS_INCLUDED /*If defined, System Settings entries can be stored.*/
#if defined LM_SYSTEM_SETTINGS_INCLUDED
  #define LM_MAX_SYSTEM_SETTINGS_ITEMS        1
  #define LM_MAX_SS_PIN_CODE_LENGTH           8

  #define LM_MAX_SS_IP_ADDRESS_LENGTH       16  // IPv4 = 4 bytes, IPv6 = 16 bytes
  #define LM_MAX_SS_VERSION_NR_LENGTH       14  // Size of each versionnumber in bytes
  #define LM_MAX_SS_ADDATTRIBUTES_LENGTH    0   // Size of Additionam Attributes in bytes (currently not used)

  #define LM_MAX_SS_LENGTH (sizeof(LmHeaderType) + RSOFFSETOF(LmSystemSettingsType,Data) + LM_MAX_SS_ADDATTRIBUTES_LENGTH + (4 * LM_MAX_SS_IP_ADDRESS_LENGTH) + (3 * LM_MAX_SS_VERSION_NR_LENGTH))
#endif

/****************************************************************************
* Line Settings settings
****************************************************************************/
#define LM_LINE_SETTINGS_INCLUDED /*If defined, Line Settings entries can be stored.*/
#if defined LM_LINE_SETTINGS_INCLUDED
  #define LM_MAX_LS_ITEMS        4

  #define LM_MAX_LS_LINENAME_LENGTH       (LM_MAX_NAME_LENGTH)
  #define LM_MAX_LS_ADD_ATTRIBUTES_LENGTH 10

  // Defining maximum size of Permanent CLIR
  #define LM_MAX_LS_PERMANENTCLIR_ATTRIBUTES             0 // currently not used
  #define LM_MAX_LS_PERMANENTCLIR_ACTIVATIONCODE_LENGTH 10 // Maximum lenght of the activation/deactivation code
  #define LM_MAX_LS_PERMANENTCLIR_LENGTH (RSOFFSETOF(LmLsPermanentClirNumberType, Data) + LM_MAX_LS_PERMANENTCLIR_ATTRIBUTES + LM_MAX_LS_PERMANENTCLIR_ACTIVATIONCODE_LENGTH*2)

  // Defining maximum size of Call Forward
  #define LM_MAX_LS_CF_ATTRIBUTES              0 // currently not used
  #define LM_MAX_LS_CF_ACTIVATIONCODE_LENGTH  10 // Maximum lenght of the activation/deactivation code
  #define LM_MAX_LS_CF_NUMBER_LENGTH          LM_MAX_NUMBER_LENGTH // Maximum length of the call forward number
  #define LM_MAX_LS_CALLFORWARD_LENGTH (RSOFFSETOF(LmLsCallForwardNumberType, Data) + LM_MAX_LS_CF_ATTRIBUTES + LM_MAX_LS_PERMANENTCLIR_ACTIVATIONCODE_LENGTH*2 + LM_MAX_LS_CF_NUMBER_LENGTH)

  // Defining maximum size of Blocked numbers
  #define LM_MAX_LS_BLOCKED_NUMBER_ITEMS      3
  #define LM_MAX_LS_BLOCKED_NUMBER_ATTRIBUTES 2
  #define LM_MAX_LS_BLOCKED_NUMBER_LENGTH     (LM_MAX_LS_BLOCKED_NUMBER_ITEMS * (RSOFFSETOF(LmNumberType, Data) + LM_MAX_LS_BLOCKED_NUMBER_ATTRIBUTES + LM_MAX_NUMBER_LENGTH ))

  // Defining maximum size of one Line Settings entry
  #define LM_MAX_LS_LENGTH (sizeof(LmHeaderType) + RSOFFSETOF(LmLineSettingsType,Data) + LM_MAX_LS_ADD_ATTRIBUTES_LENGTH + LM_MAX_LS_LINENAME_LENGTH + LM_MAX_LS_PERMANENTCLIR_LENGTH + LM_MAX_LS_CALLFORWARD_LENGTH*3 + LM_MAX_LS_BLOCKED_NUMBER_LENGTH)
#endif

/****************************************************************************
* Internal Names settings
****************************************************************************/
#define LM_INTERNAL_NAMES_INCLUDED /*If defined, Internal Names entries can be stored.*/
#if defined LM_INTERNAL_NAMES_INCLUDED
  #define LM_MAX_INT_NAMES_ITEMS        22

  #define LM_MAX_INT_NAMES_ADD_ATTRIBUTES_LENGTH  10
  #define LM_MAX_INT_NAMES_NAME_LENGTH            (LM_MAX_NAME_LENGTH)

  #define LM_MAX_INT_NAMES_LENGTH (sizeof(LmHeaderType) + RSOFFSETOF(LmInternalNamesType,Data) + LM_MAX_INT_NAMES_ADD_ATTRIBUTES_LENGTH + LM_MAX_INT_NAMES_NAME_LENGTH)
#endif

/****************************************************************************
* Subscription settings
****************************************************************************/
#define LM_SUBSCRIPTION_INCLUDED /*If defined, Subscription entries can be stored.*/
#if defined LM_SUBSCRIPTION_INCLUDED
  #define LM_MAX_SUBSCRIPTION_ITEMS                  PROJCFG_FP_NUMBER_OF_ENROLLMENTS
  #define LM_SUBSCRIPTION_ULE_REFERENCEID_OFFSET     NR_OF_HANDSETS
  #define LM_MAX_SUBSCRIPTION_ADD_ATTRIBUTES_LENGTH  sizeof(SubscriptionAddAtttributesType)

  #define LM_MAX_SUBSCRIPTION_LENGTH (sizeof(LmHeaderType) + RSOFFSETOF(LmSubscriptionType,Data) + LM_MAX_SUBSCRIPTION_ADD_ATTRIBUTES_LENGTH)
#endif

//Define this to the largest item type
#define LM_MAX_ITEM_LENGTH LM_MAX_SS_LENGTH

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/* Sorted index number of an entry in a list.
   LM_UNDEFINED_INDEX_NUMBER means that the number is undefined */
typedef rsuint8 LmIndexNumberType;

/* Unique reference number to an entry in a list.
   LM_UNDEFINED_REFERENCEID means that the number is undefined */
typedef rsuint8 LmReferenceIdType;

//Use mail interface
#ifdef MODULE_TEST_LISTMANAGER
  #define LISTMANAGER_MAILIF_USED
#else
  //Uncomment this when the mail interface is not used
//  #define LISTMANAGER_MAILIF_USED
#endif

/****************************************************************************
*                           Global variables/const
****************************************************************************/


/****************************************************************************
*                             Function prototypes
****************************************************************************/


#endif

