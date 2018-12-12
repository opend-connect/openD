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
* Definition of the ApiLas interface.
*/


#ifndef APILAS_H
#define APILAS_H

/****************************************************************************
*                               Include files
****************************************************************************/
/*! The following API files must be included. */
#include <Phoenix/Api/Types/ApiTypes.h>

/****************************************************************************
*                               Macros/Defines
****************************************************************************/
#define PRINT_LAS_INFO(args...) // printf(args)

#define API_LAS_LENGTH_OF_PINCODE 4

#define LAS_DB_ENABLED //Enables external LAS DB
//#define LAS_ENABLED //Enables internal LAS DB
#ifdef LAS_DB_ENABLED
#undef LAS_ENABLED
//#include "Phoenix/FpAppLib/LasDb/libLAapp/ListsApp.h"

#endif
#ifdef LAS_ENABLED
#undef LAS_DB_ENABLED
#endif

//#define dont_trace_las
#ifndef dont_trace_las
#define las_Trace( args... )  	{ char * dest = strstr(__FILE__, "sc1445x_src"); \
								  if(!dest) \
									  dest = strstr(__FILE__, "Phoenix"); \
								  printf( "pid(%d): las_trace %s %s %d: ", getpid(), dest?dest:__FILE__, __FUNCTION__, __LINE__ ); \
								  printf( args ); \
								  printf("\n"); }
#else
#define las_Trace( args... )
#endif

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/


/* Global mail primitives:
  API_LAS_START_SESSION_REQ = 0x5500,
  API_LAS_START_SESSION_CFM = 0x5501,
  API_LAS_END_SESSION_REQ = 0x5502,
  API_LAS_END_SESSION_CFM = 0x5503,
  API_LAS_QUERY_SUPPORTED_ENTRY_FIELDS_REQ = 0x5504,
  API_LAS_QUERY_SUPPORTED_ENTRY_FIELDS_CFM = 0x5505,
  API_LAS_READ_ENTRIES_REQ = 0x5506,
  API_LAS_READ_ENTRIES_CFM = 0x5507,
  API_LAS_EDIT_ENTRY_REQ = 0x5508,
  API_LAS_EDIT_ENTRY_CFM = 0x5509,
  API_LAS_SAVE_ENTRY_REQ = 0x550A,
  API_LAS_SAVE_ENTRY_CFM = 0x550B,
  API_LAS_DELETE_ENTRY_REQ = 0x550C,
  API_LAS_DELETE_ENTRY_CFM = 0x550D,
  API_LAS_DELETE_LIST_REQ = 0x550E,
  API_LAS_DELETE_LIST_CFM = 0x550F,
  API_LAS_SEARCH_ENTRIES_REQ = 0x5510,
  API_LAS_SEARCH_ENTRIES_CFM = 0x5511,
  API_LAS_NEGATIVE_ACKNOWLEDGE_IND = 0x5512,
  API_LAS_DATA_PACKET_IND = 0x5513,
  API_LAS_BASE_RESET_IND = 0x5580,
  API_LAS_STATUS_IND = 0x5581,
  API_LAS_GET_FIELD_PROTECTION_REQ = 0x5582,
  API_LAS_GET_FIELD_PROTECTION_CFM = 0x5583,
  API_LAS_SET_FIELD_PROTECTION_REQ = 0x5584,
  API_LAS_SET_FIELD_PROTECTION_CFM = 0x5585,
  API_LAS_GET_LOCKED_ENTRIES_LIST_REQ = 0x5586,
  API_LAS_GET_LOCKED_ENTRIES_LIST_CFM = 0x5587,
  API_LAS_DB_CLEAR_REQ = 0x55C0,
  API_LAS_DB_CLEAR_CFM = 0x55C1,
The global mail primitives MUST be defined in Global.h! */



/*! This enum defines the different list identifier. */
typedef enum RSENUMTAG(ApiLasListIdType)
{
  API_LAS_SUPPORTED_LISTS         = 0x00, /*!< List of supported lists */
  API_LAS_MISSED_CALLS            = 0x01, /*!< List with missed calls */
  API_LAS_OUTGOING_CALLS          = 0x02, /*!< List with outgoing calls */
  API_LAS_INCOMING_ACCEPTED_CALLS = 0x03, /*!< List with incoming accepted calls */
  API_LAS_ALL_CALLS               = 0x04, /*!< List with all calls */
  API_LAS_CONTACTS                = 0x05, /*!< List with contacts */
  API_LAS_INTERNAL_NAMES          = 0x06, /*!< List with internal PP names */
  API_LAS_DECT_SYSTEM_SETTINGS    = 0x07, /*!< List with DECT system settings */
  API_LAS_LINE_SETTINGS           = 0x08, /*!< List with line settings */
  API_LAS_ALL_INCOMING_CALLS      = 0x09  /*!< List with all incoming calls(includes all
                                             missed and incoming accepted calls) */
} RSENUM8(ApiLasListIdType);

/*! Discriminator. */
typedef enum RSENUMTAG(ApiLasDiscriminatorType)
{
  API_LAS_DISCRIMINATOR_UNDEFINED = 0x00, /*!< Undefined. */
  API_LAS_DISCRIMINATOR_EMC       = 0x01  /*!< EMC. */
} RSENUM8(ApiLasDiscriminatorType);

/*! This enum defines start session reject types to the MMI */
typedef enum RSENUMTAG(ApiLasRejectReasonType)
{
  API_LAS_REJECT_NOT_ENOUGH_RESOURCES       = 0x00, /*!< Not enough resources */
  API_LAS_REJECT_LIST_ALREADY_IN_USE        = 0x01, /*!< List already used by another
                                                       session. */
  API_LAS_REJECT_LIST_NOT_SUPPORTED         = 0x02, /*!< List not supported */
  API_LAS_REJECT_MAX_NR_OF_SESSIONS_REACHED = 0x03, /*!< Maximum number of sessions
                                                       supported by the FP reached */
  API_LAS_REJECT_NO_ERRORS                  = 0xFF  /*!< No errors */
} RSENUM8(ApiLasRejectReasonType);

/*! This enum defines the direction of received list entries. The response
   contains data packets with list entries in order of ascending list index,
   regardless of whether counter indicated forward or backwards and always
   includes the entry with list index=start index. 
    EXAMPLE:  In case 2 entries are requested 'backwards' with start index 5,
   the data packets shall include the entries with indices 4 and 5, with entry
   4 transmitted first. */
typedef enum RSENUMTAG(ApiLasReadDirectionType)
{
  API_LAS_READDIRECTION_FORWARD  = 0x00, /*!< Forward (in ascending list index order) */
  API_LAS_READDIRECTION_BACKWARD = 0x01  /*!< Backward (in descending list index order) */
} RSENUM8(ApiLasReadDirectionType);

/*! Enum definition for ApiLasReadStatusType */
typedef enum RSENUMTAG(ApiLasReadStatusType)
{
  API_LAS_READSTATUS_UNCHANGED = 0x00, /*!< All read entries 'Read status' field shall
                                          be left unchanged */
  API_LAS_READSTATUS_READ      = 0x7F, /*!< All read entries 'Read status' field shall
                                          be reset (i.e. marked as read) */
  API_LAS_READSTATUS_UNREAD    = 0xFF, /*!< All read entries 'Read status' field shall
                                          be set (i.e. marked as unread) */
} RSENUM8(ApiLasReadStatusType);

/*! This enum defines the various match options for search commands */
typedef enum RSENUMTAG(ApiLasSearchOptionType)
{
  API_LAS_SEARCH_EXACT_MATCH          = 0x00, /*!< Exact match with whole target field
                                                 required */
  API_LAS_SEARCH_EXACT_CURRENT_INDEX  = 0x01, /*!< Exact match as with 00H option tried,
                                                 current start index returned if exact match
                                                 fails */
  API_LAS_SEARCH_EXACT_PREVIOUS_INDEX = 0x02  /*!< Exact match as with 00H option tried,
                                                 previous start index returned if exact
                                                 match fails */
} RSENUM8(ApiLasSearchOptionType);

/*! This enum defines the various match options for search commands */
typedef enum RSENUMTAG(ApiLasSearchCaseOptionType)
{
  API_LAS_SEARCH_CASE_INSENSITIVE = 0x00, /*!< Case in-sensitive search required */
  API_LAS_SEARCH_CASE_SENSITIVE   = 0x01  /*!< Case sensitive search required */
} RSENUM8(ApiLasSearchCaseOptionType);

/*! This enum defines various errors codes received from the host */
typedef enum RSENUMTAG(ApiLasNegativeAcknowledgeReasonType)
{
  API_LAS_INVALID_RANGE           = 0x00, /*!< Invalid range */
  API_LAS_ENTRY_NOT_AVAILABLE     = 0x01, /*!< Entry not available */
  API_LAS_INVALID_SESSION_NO      = 0x02, /*!< Invalid session number */
  API_LAS_TEMP_NOT_POSSIBLE       = 0x03, /*!< Temporarily not possible */
  API_LAS_ENTRY_FORMAT_INCORRECT  = 0x04, /*!< Entry format incorrect */
  API_LAS_INVALID_START_INDEX     = 0x05, /*!< Invalid start index */
  API_LAS_PROCEDURE_NOT_SUPPORTED = 0x06, /*!< Procedure not supported */
  API_LAS_PROCEDURE_NOT_ALLOWED   = 0x07, /*!< Procedure not allowed */
  API_LAS_CONTENT_NOT_ACCEPTED    = 0x08, /*!< Content not accepted */
  API_LAS_LIST_FULL               = 0x09, /*!< List full */
  API_LAS_INCORRECT_PIN           = 0x0A, /*!< Incorrect PIN */
  API_LAS_PIN_CODE_REQUIRED       = 0x0B, /*!< PIN code required */
} RSENUM8(ApiLasNegativeAcknowledgeReasonType);

/*! This enum defines various errors codes generated by the API */
typedef enum RSENUMTAG(ApiLasStatusType)
{
  API_LAS_STATUS_INVALID_CONEI                   = 0x00, /*!< No connection available. A
                                                            connection needs to be
                                                            established prior to any LAS
                                                            activity (see ApiCc for further
                                                            dertails). */
                                                         /*!<  */
  API_LAS_STATUS_INVALID_AIR_CMD_RECEIVED        = 0x10, /*!< Invalid command received
                                                            over the air */
  API_LAS_STATUS_INVALID_AIR_ENTRY_DATA_RECEIVED = 0x11, /*!< Invalid entry data
                                                            received over the air */
  API_LAS_STATUS_UNKNOWN_AIR_SESSIONID           = 0x12, /*!< Unknown session id was
                                                            received over the air. */
  API_LAS_STATUS_UNEXPECTED_AIR_DATA_RECEIVED    = 0x13, /*!< Unexpected data received
                                                            over the air. */
  API_LAS_STATUS_AIR_DATA_STORAGE_FULL           = 0x14, /*!< Too much data received
                                                            over the air. */
  API_LAS_STATUS_INVALID_API_CMD                 = 0x20, /*!< Invalid API  parameter in
                                                            command */
  API_LAS_STATUS_INVALID_API_ENTRY_DATA          = 0x21, /*!< Invalid API entry data */
  API_LAS_STATUS_INVALID_API_SESSIONID           = 0x22  /*!< Invalid session id was
                                                            used in API command. */
} RSENUM8(ApiLasStatusType);

/*! This enum defines the different Contact number types. */
typedef enum RSENUMTAG(ApiLasCallTypeType)
{
  API_LAS_CALL_TYPE_UNDEFINED = 0x00, /*!<  */
  API_LAS_CALL_TYPE_MISSED    = 0x01, /*!<  */
  API_LAS_CALL_TYPE_ACCEPTED  = 0x02, /*!<  */
  API_LAS_CALL_TYPE_OUTGOING  = 0x03  /*!<  */
} RSENUM8(ApiLasCallTypeType);

/*! This enum defines the different Contact number types. */
typedef enum RSENUMTAG(ApiLasContactNumberTypeType)
{
  API_LAS_CONTACT_NUMBER_UNDEFINED = 0x00, /*!<  */
  API_LAS_CONTACT_NUMBER_FIXED     = 0x01, /*!<  */
  API_LAS_CONTACT_NUMBER_MOBILE    = 0x02, /*!<  */
  API_LAS_CONTACT_NUMBER_WORK      = 0x03  /*!<  */
} RSENUM8(ApiLasContactNumberTypeType);

/*! This enum defines the allowed call interception states. */
typedef enum RSENUMTAG(ApiLasCallInterceptionTypeType)
{
  API_LAS_CALLINTERCEPTION_NOT_ALLOWED = 0x00, /*!<  */
  API_LAS_CALLINTERCEPTION_ALLOWED     = 0x01  /*!<  */
} RSENUM8(ApiLasCallInterceptionTypeType);

/*! This enum defines the entity which sets date and time for the DECT
   system (PP or FP). */
typedef enum RSENUMTAG(ApiLasClockMasterTypeType)
{
  API_LAS_CLOCKMASTER_FP = 0x00, /*!<  */
  API_LAS_CLOCKMASTER_PP = 0x01  /*!<  */
} RSENUM8(ApiLasClockMasterTypeType);

/*! This enum defines the Base Reset states */
typedef enum RSENUMTAG(ApiLasBaseResetTypeType)
{
  API_LAS_BASERESET_NO  = 0x00, /*!< If at least one DECT system setting, or line
                                   setting, has been set to a non default value, the 'Base
                                   reset' field will be equal to API_LAS_BASERESET_NO.
                                   Any attempt from a Pp to set this parameter to
                                   API_LAS_BASERESET_NO will result in a negative
                                   acknowledgement, with reject reason 'procedure not
                                   allowed'. */
  API_LAS_BASERESET_YES = 0x01  /*!< All DECT system and line settings will be reset to
                                   their default value in the FP. */
} RSENUM8(ApiLasBaseResetTypeType);

/*! This enum defines the IP Address types */
typedef enum RSENUMTAG(ApiLasIpAdrTypeType)
{
  API_LAS_IPADRTYPE_UNDEFINED = 0x00, /*!<  */
  API_LAS_IPADRTYPE_DHCP      = 0x01, /*!<  */
  API_LAS_IPADRTYPE_STATIC    = 0x02  /*!<  */
} RSENUM8(ApiLasIpAdrTypeType);

/*! This enum defines the IP Address format */
typedef enum RSENUMTAG(ApiLasIpAdrFormatType)
{
  API_LAS_IPADRFORMAT_IPV4 = 0x00, /*!<  */
  API_LAS_IPADRFORMAT_IPV6 = 0x01  /*!<  */
} RSENUM8(ApiLasIpAdrFormatType);

/*! This enum defines the No Emission states */
typedef enum RSENUMTAG(ApiLasNoEmissionModeType)
{
  API_LAS_NOEMISSIONMODE_DEACTIVATED = 0x00, /*!< 'No emission mode' deactivated */
  API_LAS_NOEMISSIONMODE_ACTIVATED   = 0x01  /*!< 'No emission mode' activated */
} RSENUM8(ApiLasNoEmissionModeType);

/*! This enum defines the Multiple calls modes */
typedef enum RSENUMTAG(ApiLasMultipleCallModeType)
{
  API_LAS_MULTIPLECALLMODE_SINGLE_CALL   = 0x30, /*!<  */
  API_LAS_MULTIPLECALLMODE_MULTIPLE_CALL = 0x31  /*!<  */
} RSENUM8(ApiLasMultipleCallModeType);

/*! This enum defines the Intrusion calls modes */
typedef enum RSENUMTAG(ApiLasIntrusionCallModeType)
{
  API_LAS_INTRUSIONCALL_NOT_ALLOWED = 0x30, /*!<  */
  API_LAS_INTRUSIONCALL_ALLOWED     = 0x31  /*!<  */
} RSENUM8(ApiLasIntrusionCallModeType);

/*! This enum defined permanent CLIR types */
typedef enum RSENUMTAG(ApiLasPermanentClirTypeType)
{
  API_LAS_PERMANENTCLIR_OFF = 0x30, /*!< CLIR de-activated for all calls */
  API_LAS_PERMANENTCLIR_ON  = 0x31  /*!< CLIR activated for all calls */
} RSENUM8(ApiLasPermanentClirTypeType);

/*! This enum defined call forwarding types */
typedef enum RSENUMTAG(ApiLasCallForwardStateType)
{
  API_LAS_CF_DEACTIVATE = 0x30, /*!< Call forward de-activated for all calls */
  API_LAS_CF_ACTIVATE   = 0x31  /*!< Call forward activated for all calls */
} RSENUM8(ApiLasCallForwardStateType);

/*! This enum defines the country codes supported by the API. Table is
   based on [3] */
typedef enum RSENUMTAG(ApiLasCountryCodeTypeType)
{
  API_LAS_COUNTRY_ID_CANADA                           = 0x0001, /*!< 1 - Canada */
  API_LAS_COUNTRY_ID_PUERTO_RICO                      = 0x0001, /*!< 1 - Puerto Rico */
  API_LAS_COUNTRY_ID_UNITED_STATES                    = 0x0001, /*!< 1 - United States */
  API_LAS_COUNTRY_ID_KAZAKHSTAN                       = 0x0007, /*!< 7 - Kazakhstan */
  API_LAS_COUNTRY_ID_RUSSIA                           = 0x0007, /*!< 7 - Russia */
  API_LAS_COUNTRY_ID_EGYPT                            = 0x0014, /*!< 20 - Egypt */
  API_LAS_COUNTRY_ID_SOUTH_AFRICA                     = 0x001B, /*!< 27 - South Africa */
  API_LAS_COUNTRY_ID_GREECE                           = 0x001E, /*!< 30 - Greece */
  API_LAS_COUNTRY_ID_NETHERLANDS                      = 0x001F, /*!< 31 - Netherlands */
  API_LAS_COUNTRY_ID_BELGIUM                          = 0x0020, /*!< 32 - Belgium */
  API_LAS_COUNTRY_ID_FRANCE                           = 0x0021, /*!< 33 - France */
  API_LAS_COUNTRY_ID_SPAIN                            = 0x0022, /*!< 34 - Spain */
  API_LAS_COUNTRY_ID_HUNGARY                          = 0x0024, /*!< 36 - Hungary */
  API_LAS_COUNTRY_ID_HOLY_SEE                         = 0x0027, /*!< 39 - Holy See
                                                                   (Vatican City) */
  API_LAS_COUNTRY_ID_ITALY                            = 0x0027, /*!< 39 - Italy */
  API_LAS_COUNTRY_ID_ROMANIA                          = 0x0028, /*!< 40 - Romania */
  API_LAS_COUNTRY_ID_SWITZERLAND                      = 0x0029, /*!< 41 - Switzerland */
  API_LAS_COUNTRY_ID_AUSTRIA                          = 0x002B, /*!< 43 - Austria */
  API_LAS_COUNTRY_ID_ISLE_OF_MAN                      = 0x002C, /*!< 44 - Isle of Man */
  API_LAS_COUNTRY_ID_UNITED_KINGDOM                   = 0x002C, /*!< 44 - United Kingdom */
  API_LAS_COUNTRY_ID_DENMARK                          = 0x002D, /*!< 45 - Denmark */
  API_LAS_COUNTRY_ID_SWEDEN                           = 0x002E, /*!< 46 - Sweden */
  API_LAS_COUNTRY_ID_NORWAY                           = 0x002F, /*!< 47 - Norway */
  API_LAS_COUNTRY_ID_POLAND                           = 0x0030, /*!< 48 - Poland */
  API_LAS_COUNTRY_ID_GERMANY                          = 0x0031, /*!< 49 - Germany */
  API_LAS_COUNTRY_ID_PERU                             = 0x0033, /*!< 51 - Peru */
  API_LAS_COUNTRY_ID_MEXICO                           = 0x0034, /*!< 52 - Mexico */
  API_LAS_COUNTRY_ID_CUBA                             = 0x0035, /*!< 53 - Cuba */
  API_LAS_COUNTRY_ID_ARGENTINA                        = 0x0036, /*!< 54 - Argentina */
  API_LAS_COUNTRY_ID_BRAZIL                           = 0x0037, /*!< 55 - Brazil */
  API_LAS_COUNTRY_ID_CHILE                            = 0x0038, /*!< 56 - Chile */
  API_LAS_COUNTRY_ID_COLOMBIA                         = 0x0039, /*!< 57 - Colombia */
  API_LAS_COUNTRY_ID_VENEZUELA                        = 0x003A, /*!< 58 - Venezuela */
  API_LAS_COUNTRY_ID_MALAYSIA                         = 0x003C, /*!< 60 - Malaysia */
  API_LAS_COUNTRY_ID_AUSTRALIA                        = 0x003D, /*!< 61 - Australia */
  API_LAS_COUNTRY_ID_CHRISTMAS_ISLAND                 = 0x003D, /*!< 61 - Christmas
                                                                   Island */
  API_LAS_COUNTRY_ID_COCOS_ISLANDS                    = 0x003D, /*!< 61 - Cocos
                                                                   (Keeling) Islands */
  API_LAS_COUNTRY_ID_INDONESIA                        = 0x003E, /*!< 62 - Indonesia */
  API_LAS_COUNTRY_ID_PHILIPPINES                      = 0x003F, /*!< 63 - Philippines */
  API_LAS_COUNTRY_ID_NEW_ZEALAND                      = 0x0040, /*!< 64 - New Zealand */
  API_LAS_COUNTRY_ID_SINGAPORE                        = 0x0041, /*!< 65 - Singapore */
  API_LAS_COUNTRY_ID_THAILAND                         = 0x0042, /*!< 66 - Thailand */
  API_LAS_COUNTRY_ID_JAPAN                            = 0x0051, /*!< 81 - Japan */
  API_LAS_COUNTRY_ID_SOUTH_KOREA                      = 0x0052, /*!< 82 - South Korea */
  API_LAS_COUNTRY_ID_VIETNAM                          = 0x0054, /*!< 84 - Vietnam */
  API_LAS_COUNTRY_ID_CHINA                            = 0x0056, /*!< 86 - China */
  API_LAS_COUNTRY_ID_TURKEY                           = 0x005A, /*!< 90 - Turkey */
  API_LAS_COUNTRY_ID_INDIA                            = 0x005B, /*!< 91 - India */
  API_LAS_COUNTRY_ID_PAKISTAN                         = 0x005C, /*!< 92 - Pakistan */
  API_LAS_COUNTRY_ID_AFGHANISTAN                      = 0x005D, /*!< 93 - Afghanistan */
  API_LAS_COUNTRY_ID_SRI_LANKA                        = 0x005E, /*!< 94 - Sri Lanka */
  API_LAS_COUNTRY_ID_BURMA                            = 0x005F, /*!< 95 - Burma
                                                                   (Myanmar) */
  API_LAS_COUNTRY_ID_IRAN                             = 0x0062, /*!< 98 - Iran */
  API_LAS_COUNTRY_ID_MOROCCO                          = 0x00D4, /*!< 212 - Morocco */
  API_LAS_COUNTRY_ID_ALGERIA                          = 0x00D5, /*!< 213 - Algeria */
  API_LAS_COUNTRY_ID_TUNISIA                          = 0x00D8, /*!< 216 - Tunisia */
  API_LAS_COUNTRY_ID_LIBYA                            = 0x00DA, /*!< 218 - Libya */
  API_LAS_COUNTRY_ID_GAMBIA                           = 0x00DC, /*!< 220 - Gambia */
  API_LAS_COUNTRY_ID_SENEGAL                          = 0x00DD, /*!< 221 - Senegal */
  API_LAS_COUNTRY_ID_MAURITANIA                       = 0x00DE, /*!< 222 - Mauritania */
  API_LAS_COUNTRY_ID_MALI                             = 0x00DF, /*!< 223 - Mali */
  API_LAS_COUNTRY_ID_GUINEA                           = 0x00E0, /*!< 224 - Guinea */
  API_LAS_COUNTRY_ID_IVORY_COAST                      = 0x00E1, /*!< 225 - Ivory Coast */
  API_LAS_COUNTRY_ID_BURKINA_FASO                     = 0x00E2, /*!< 226 - Burkina Faso */
  API_LAS_COUNTRY_ID_NIGER                            = 0x00E3, /*!< 227 - Niger */
  API_LAS_COUNTRY_ID_TOGO                             = 0x00E4, /*!< 228 - Togo */
  API_LAS_COUNTRY_ID_BENIN                            = 0x00E5, /*!< 229 - Benin */
  API_LAS_COUNTRY_ID_MAURITIUS                        = 0x00E6, /*!< 230 - Mauritius */
  API_LAS_COUNTRY_ID_LIBERIA                          = 0x00E7, /*!< 231 - Liberia */
  API_LAS_COUNTRY_ID_SIERRA_LEONE                     = 0x00E8, /*!< 232 - Sierra Leone */
  API_LAS_COUNTRY_ID_GHANA                            = 0x00E9, /*!< 233 - Ghana */
  API_LAS_COUNTRY_ID_NIGERIA                          = 0x00EA, /*!< 234 - Nigeria */
  API_LAS_COUNTRY_ID_CHAD                             = 0x00EB, /*!< 235 - Chad */
  API_LAS_COUNTRY_ID_CENTRAL_AFRICAN_REPUBLIC         = 0x00EC, /*!< 236 - Central
                                                                   African Republic */
  API_LAS_COUNTRY_ID_CAMEROON                         = 0x00ED, /*!< 237 - Cameroon */
  API_LAS_COUNTRY_ID_CAPE_VERDE                       = 0x00EE, /*!< 238 - Cape Verde */
  API_LAS_COUNTRY_ID_SAO_TOME_AND_PRINCIPE            = 0x00EF, /*!< 239 - Sao Tome and
                                                                   Principe */
  API_LAS_COUNTRY_ID_EQUATORIAL_GUINEA                = 0x00F0, /*!< 240 - Equatorial
                                                                   Guinea */
  API_LAS_COUNTRY_ID_GABON                            = 0x00F1, /*!< 241 - Gabon */
  API_LAS_COUNTRY_ID_REPUBLIC_OF_THE_CONGO            = 0x00F2, /*!< 242 - Republic of
                                                                   the Congo */
  API_LAS_COUNTRY_ID_DEMOCRATIC_REPUBLIC_OF_THE_CONGO = 0x00F3, /*!< 243 - Democratic
                                                                   Republic of the Congo */
  API_LAS_COUNTRY_ID_ANGOLA                           = 0x00F4, /*!< 244 - Angola */
  API_LAS_COUNTRY_ID_GUINEA_BISSAU                    = 0x00F5, /*!< 245 - Guinea-Bissau */
  API_LAS_COUNTRY_ID_SEYCHELLES                       = 0x00F8, /*!< 248 - Seychelles */
  API_LAS_COUNTRY_ID_SUDAN                            = 0x00F9, /*!< 249 - Sudan */
  API_LAS_COUNTRY_ID_RWANDA                           = 0x00FA, /*!< 250 - Rwanda */
  API_LAS_COUNTRY_ID_ETHIOPIA                         = 0x00FB, /*!< 251 - Ethiopia */
  API_LAS_COUNTRY_ID_SOMALIA                          = 0x00FC, /*!< 252 - Somalia */
  API_LAS_COUNTRY_ID_DJIBOUTI                         = 0x00FD, /*!< 253 - Djibouti */
  API_LAS_COUNTRY_ID_KENYA                            = 0x00FE, /*!< 254 - Kenya */
  API_LAS_COUNTRY_ID_TANZANIA                         = 0x00FF, /*!< 255 - Tanzania */
  API_LAS_COUNTRY_ID_UGANDA                           = 0x0100, /*!< 256 - Uganda */
  API_LAS_COUNTRY_ID_BURUNDI                          = 0x0101, /*!< 257 - Burundi */
  API_LAS_COUNTRY_ID_MOZAMBIQUE                       = 0x0102, /*!< 258 - Mozambique */
  API_LAS_COUNTRY_ID_ZAMBIA                           = 0x0104, /*!< 260 - Zambia */
  API_LAS_COUNTRY_ID_MADAGASCAR                       = 0x0105, /*!< 261 - Madagascar */
  API_LAS_COUNTRY_ID_MAYOTTE                          = 0x0106, /*!< 262 - Mayotte */
  API_LAS_COUNTRY_ID_ZIMBABWE                         = 0x0107, /*!< 263 - Zimbabwe */
  API_LAS_COUNTRY_ID_NAMIBIA                          = 0x0108, /*!< 264 - Namibia */
  API_LAS_COUNTRY_ID_MALAWI                           = 0x0109, /*!< 265 - Malawi */
  API_LAS_COUNTRY_ID_LESOTHO                          = 0x010A, /*!< 266 - Lesotho */
  API_LAS_COUNTRY_ID_BOTSWANA                         = 0x010B, /*!< 267 - Botswana */
  API_LAS_COUNTRY_ID_SWAZILAND                        = 0x010C, /*!< 268 - Swaziland */
  API_LAS_COUNTRY_ID_COMOROS                          = 0x010D, /*!< 269 - Comoros */
  API_LAS_COUNTRY_ID_SAINT_HELENA                     = 0x0122, /*!< 290 - Saint Helena */
  API_LAS_COUNTRY_ID_ERITREA                          = 0x0123, /*!< 291 - Eritrea */
  API_LAS_COUNTRY_ID_ARUBA                            = 0x0129, /*!< 297 - Aruba */
  API_LAS_COUNTRY_ID_FAROE_ISLANDS                    = 0x012A, /*!< 298 - Faroe Islands */
  API_LAS_COUNTRY_ID_GREENLAND                        = 0x012B, /*!< 299 - Greenland */
  API_LAS_COUNTRY_ID_GIBRALTAR                        = 0x015E, /*!< 350 - Gibraltar */
  API_LAS_COUNTRY_ID_PORTUGAL                         = 0x015F, /*!< 351 - Portugal */
  API_LAS_COUNTRY_ID_LUXEMBOURG                       = 0x0160, /*!< 352 - Luxembourg */
  API_LAS_COUNTRY_ID_IRELAND                          = 0x0161, /*!< 353 - Ireland */
  API_LAS_COUNTRY_ID_ICELAND                          = 0x0162, /*!< 354 - Iceland */
  API_LAS_COUNTRY_ID_ALBANIA                          = 0x0163, /*!< 355 - Albania */
  API_LAS_COUNTRY_ID_MALTA                            = 0x0164, /*!< 356 - Malta */
  API_LAS_COUNTRY_ID_CYPRUS                           = 0x0165, /*!< 357 - Cyprus */
  API_LAS_COUNTRY_ID_FINLAND                          = 0x0166, /*!< 358 - Finland */
  API_LAS_COUNTRY_ID_BULGARIA                         = 0x0167, /*!< 359 - Bulgaria */
  API_LAS_COUNTRY_ID_LITHUANIA                        = 0x0172, /*!< 370 - Lithuania */
  API_LAS_COUNTRY_ID_LATVIA                           = 0x0173, /*!< 371 - Latvia */
  API_LAS_COUNTRY_ID_ESTONIA                          = 0x0174, /*!< 372 - Estonia */
  API_LAS_COUNTRY_ID_MOLDOVA                          = 0x0175, /*!< 373 - Moldova */
  API_LAS_COUNTRY_ID_ARMENIA                          = 0x0176, /*!< 374 - Armenia */
  API_LAS_COUNTRY_ID_BELARUS                          = 0x0177, /*!< 375 - Belarus */
  API_LAS_COUNTRY_ID_ANDORRA                          = 0x0178, /*!< 376 - Andorra */
  API_LAS_COUNTRY_ID_MONACO                           = 0x0179, /*!< 377 - Monaco */
  API_LAS_COUNTRY_ID_SAN_MARINO                       = 0x017A, /*!< 378 - San Marino */
  API_LAS_COUNTRY_ID_UKRAINE                          = 0x017C, /*!< 380 - Ukraine */
  API_LAS_COUNTRY_ID_KOSOVO                           = 0x017D, /*!< 381 - Kosovo */
  API_LAS_COUNTRY_ID_SERBIA                           = 0x017D, /*!< 381 - Serbia */
  API_LAS_COUNTRY_ID_MONTENEGRO                       = 0x017E, /*!< 382 - Montenegro */
  API_LAS_COUNTRY_ID_CROATIA                          = 0x0181, /*!< 385 - Croatia */
  API_LAS_COUNTRY_ID_SLOVENIA                         = 0x0182, /*!< 386 - Slovenia */
  API_LAS_COUNTRY_ID_BOSNIA_AND_HERZEGOVINA           = 0x0183, /*!< 387 - Bosnia and
                                                                   Herzegovina */
  API_LAS_COUNTRY_ID_MACEDONIA                        = 0x0185, /*!< 389 - Macedonia */
  API_LAS_COUNTRY_ID_CZECH_REPUBLIC                   = 0x01A4, /*!< 420 - Czech
                                                                   Republic */
  API_LAS_COUNTRY_ID_SLOVAKIA                         = 0x01A5, /*!< 421 - Slovakia */
  API_LAS_COUNTRY_ID_LIECHTENSTEIN                    = 0x01A7, /*!< 423 - Liechtenstein */
  API_LAS_COUNTRY_ID_FALKLAND_ISLANDS                 = 0x01F4, /*!< 500 - Falkland
                                                                   Islands */
  API_LAS_COUNTRY_ID_BELIZE                           = 0x01F5, /*!< 501 - Belize */
  API_LAS_COUNTRY_ID_GUATEMALA                        = 0x01F6, /*!< 502 - Guatemala */
  API_LAS_COUNTRY_ID_EL_SALVADOR                      = 0x01F7, /*!< 503 - El Salvador */
  API_LAS_COUNTRY_ID_HONDURAS                         = 0x01F8, /*!< 504 - Honduras */
  API_LAS_COUNTRY_ID_NICARAGUA                        = 0x01F9, /*!< 505 - Nicaragua */
  API_LAS_COUNTRY_ID_COSTA_RICA                       = 0x01FA, /*!< 506 - Costa Rica */
  API_LAS_COUNTRY_ID_PANAMA                           = 0x01FB, /*!< 507 - Panama */
  API_LAS_COUNTRY_ID_SAINT_PIERRE_AND_MIQUELON        = 0x01FC, /*!< 508 - Saint Pierre
                                                                   and Miquelon */
  API_LAS_COUNTRY_ID_HAITI                            = 0x01FD, /*!< 509 - Haiti */
  API_LAS_COUNTRY_ID_SAINT_BARTHELEMY                 = 0x024E, /*!< 590 - Saint
                                                                   Barthelemy */
  API_LAS_COUNTRY_ID_BOLIVIA                          = 0x024F, /*!< 591 - Bolivia */
  API_LAS_COUNTRY_ID_GUYANA                           = 0x0250, /*!< 592 - Guyana */
  API_LAS_COUNTRY_ID_ECUADOR                          = 0x0251, /*!< 593 - Ecuador */
  API_LAS_COUNTRY_ID_PARAGUAY                         = 0x0253, /*!< 595 - Paraguay */
  API_LAS_COUNTRY_ID_SURINAME                         = 0x0255, /*!< 597 - Suriname */
  API_LAS_COUNTRY_ID_URUGUAY                          = 0x0256, /*!< 598 - Uruguay */
  API_LAS_COUNTRY_ID_NETHERLANDS_ANTILLES             = 0x0257, /*!< 599 - Netherlands
                                                                   Antilles */
  API_LAS_COUNTRY_ID_TIMOR_LESTE                      = 0x029E, /*!< 670 - Timor-Leste */
  API_LAS_COUNTRY_ID_ANTARCTICA                       = 0x02A0, /*!< 672 - Antarctica */
  API_LAS_COUNTRY_ID_NORFOLK_ISLAND                   = 0x02A0, /*!< 672 - Norfolk
                                                                   Island */
  API_LAS_COUNTRY_ID_BRUNEI                           = 0x02A1, /*!< 673 - Brunei */
  API_LAS_COUNTRY_ID_NAURU                            = 0x02A2, /*!< 674 - Nauru */
  API_LAS_COUNTRY_ID_PAPUA_NEW_GUINEA                 = 0x02A3, /*!< 675 - Papua New
                                                                   Guinea */
  API_LAS_COUNTRY_ID_TONGA                            = 0x02A4, /*!< 676 - Tonga */
  API_LAS_COUNTRY_ID_SOLOMON_ISLANDS                  = 0x02A5, /*!< 677 - Solomon
                                                                   Islands */
  API_LAS_COUNTRY_ID_VANUATU                          = 0x02A6, /*!< 678 - Vanuatu */
  API_LAS_COUNTRY_ID_FIJI                             = 0x02A7, /*!< 679 - Fiji */
  API_LAS_COUNTRY_ID_PALAU                            = 0x02A8, /*!< 680 - Palau */
  API_LAS_COUNTRY_ID_WALLIS_AND_FUTUNA                = 0x02A9, /*!< 681 - Wallis and
                                                                   Futuna */
  API_LAS_COUNTRY_ID_COOK_ISLANDS                     = 0x02AA, /*!< 682 - Cook Islands */
  API_LAS_COUNTRY_ID_NIUE                             = 0x02AB, /*!< 683 - Niue */
  API_LAS_COUNTRY_ID_SAMOA                            = 0x02AD, /*!< 685 - Samoa */
  API_LAS_COUNTRY_ID_KIRIBATI                         = 0x02AE, /*!< 686 - Kiribati */
  API_LAS_COUNTRY_ID_NEW_CALEDONIA                    = 0x02AF, /*!< 687 - New Caledonia */
  API_LAS_COUNTRY_ID_TUVALU                           = 0x02B0, /*!< 688 - Tuvalu */
  API_LAS_COUNTRY_ID_FRENCH_POLYNESIA                 = 0x02B1, /*!< 689 - French
                                                                   Polynesia */
  API_LAS_COUNTRY_ID_TOKELAU                          = 0x02B2, /*!< 690 - Tokelau */
  API_LAS_COUNTRY_ID_MICRONESIA                       = 0x02B3, /*!< 691 - Micronesia */
  API_LAS_COUNTRY_ID_MARSHALL_ISLANDS                 = 0x02B4, /*!< 692 - Marshall
                                                                   Islands */
  API_LAS_COUNTRY_ID_NORTH_KOREA                      = 0x0352, /*!< 850 - North Korea */
  API_LAS_COUNTRY_ID_HONG_KONG                        = 0x0354, /*!< 852 - Hong Kong */
  API_LAS_COUNTRY_ID_MACAU                            = 0x0355, /*!< 853 - Macau */
  API_LAS_COUNTRY_ID_CAMBODIA                         = 0x0357, /*!< 855 - Cambodia */
  API_LAS_COUNTRY_ID_LAOS                             = 0x0358, /*!< 856 - Laos */
  API_LAS_COUNTRY_ID_PITCAIRN_ISLANDS                 = 0x0366, /*!< 870 - Pitcairn
                                                                   Islands */
  API_LAS_COUNTRY_ID_BANGLADESH                       = 0x0370, /*!< 880 - Bangladesh */
  API_LAS_COUNTRY_ID_TAIWAN                           = 0x0376, /*!< 886 - Taiwan */
  API_LAS_COUNTRY_ID_MALDIVES                         = 0x03C0, /*!< 960 - Maldives */
  API_LAS_COUNTRY_ID_LEBANON                          = 0x03C1, /*!< 961 - Lebanon */
  API_LAS_COUNTRY_ID_JORDAN                           = 0x03C2, /*!< 962 - Jordan */
  API_LAS_COUNTRY_ID_SYRIA                            = 0x03C3, /*!< 963 - Syria */
  API_LAS_COUNTRY_ID_IRAQ                             = 0x03C4, /*!< 964 - Iraq */
  API_LAS_COUNTRY_ID_KUWAIT                           = 0x03C5, /*!< 965 - Kuwait */
  API_LAS_COUNTRY_ID_SAUDI_ARABIA                     = 0x03C6, /*!< 966 - Saudi Arabia */
  API_LAS_COUNTRY_ID_YEMEN                            = 0x03C7, /*!< 967 - Yemen */
  API_LAS_COUNTRY_ID_OMAN                             = 0x03C8, /*!< 968 - Oman */
  API_LAS_COUNTRY_ID_GAZA_STRIP                       = 0x03CA, /*!< 970 - Gaza Strip */
  API_LAS_COUNTRY_ID_WEST_BANK                        = 0x03CA, /*!< 970 - West Bank */
  API_LAS_COUNTRY_ID_UNITED_ARAB_EMIRATES             = 0x03CB, /*!< 971 - United Arab
                                                                   Emirates */
  API_LAS_COUNTRY_ID_ISRAEL                           = 0x03CC, /*!< 972 - Israel */
  API_LAS_COUNTRY_ID_BAHRAIN                          = 0x03CD, /*!< 973 - Bahrain */
  API_LAS_COUNTRY_ID_QATAR                            = 0x03CE, /*!< 974 - Qatar */
  API_LAS_COUNTRY_ID_BHUTAN                           = 0x03CF, /*!< 975 - Bhutan */
  API_LAS_COUNTRY_ID_MONGOLIA                         = 0x03D0, /*!< 976 - Mongolia */
  API_LAS_COUNTRY_ID_NEPAL                            = 0x03D1, /*!< 977 - Nepal */
  API_LAS_COUNTRY_ID_TAJIKISTAN                       = 0x03E0, /*!< 992 - Tajikistan */
  API_LAS_COUNTRY_ID_TURKMENISTAN                     = 0x03E1, /*!< 993 - Turkmenistan */
  API_LAS_COUNTRY_ID_AZERBAIJAN                       = 0x03E2, /*!< 994 - Azerbaijan */
  API_LAS_COUNTRY_ID_GEORGIA                          = 0x03E3, /*!< 995 - Georgia */
  API_LAS_COUNTRY_ID_KYRGYZSTAN                       = 0x03E4, /*!< 996 - Kyrgyzstan */
  API_LAS_COUNTRY_ID_UZBEKISTAN                       = 0x03E6, /*!< 998 - Uzbekistan */
  API_LAS_COUNTRY_ID_BAHAMAS                          = 0x04DA, /*!< 1242 - Bahamas */
  API_LAS_COUNTRY_ID_BARBADOS                         = 0x04DE, /*!< 1246 - Barbados */
  API_LAS_COUNTRY_ID_ANGUILLA                         = 0x04F0, /*!< 1264 - Anguilla */
  API_LAS_COUNTRY_ID_ANTIGUA_AND_BARBUDA              = 0x04F4, /*!< 1268 - Antigua and
                                                                   Barbuda */
  API_LAS_COUNTRY_ID_BRITISH_VIRGIN_ISLANDS           = 0x0504, /*!< 1284 - British
                                                                   Virgin Islands */
  API_LAS_COUNTRY_ID_US_VIRGIN_ISLANDS                = 0x053C, /*!< 1340 - US Virgin
                                                                   Islands */
  API_LAS_COUNTRY_ID_CAYMAN_ISLANDS                   = 0x0541, /*!< 1345 - Cayman
                                                                   Islands */
  API_LAS_COUNTRY_ID_BERMUDA                          = 0x05A1, /*!< 1441 - Bermuda */
  API_LAS_COUNTRY_ID_GRENADA                          = 0x05C1, /*!< 1473 - Grenada */
  API_LAS_COUNTRY_ID_SAINT_MARTIN                     = 0x063F, /*!< 1599 - Saint Martin */
  API_LAS_COUNTRY_ID_TURKS_AND_CAICOS_ISLANDS         = 0x0671, /*!< 1649 - Turks and
                                                                   Caicos Islands */
  API_LAS_COUNTRY_ID_MONTSERRAT                       = 0x0680, /*!< 1664 - Montserrat */
  API_LAS_COUNTRY_ID_NORTHERN_MARIANA_ISLANDS         = 0x0686, /*!< 1670 - Northern
                                                                   Mariana Islands */
  API_LAS_COUNTRY_ID_GUAM                             = 0x0687, /*!< 1671 - Guam */
  API_LAS_COUNTRY_ID_AMERICAN_SAMOA                   = 0x0694, /*!< 1684 - American
                                                                   Samoa */
  API_LAS_COUNTRY_ID_SAINT_LUCIA                      = 0x06DE, /*!< 1758 - Saint Lucia */
  API_LAS_COUNTRY_ID_DOMINICA                         = 0x06E7, /*!< 1767 - Dominica */
  API_LAS_COUNTRY_ID_SAINT_VINCENT_AND_THE_GRENADINES = 0x06F8, /*!< 1784 - Saint
                                                                   Vincent and the
                                                                   Grenadines */
  API_LAS_COUNTRY_ID_DOMINICAN_REPUBLIC               = 0x0711, /*!< 1809 - Dominican
                                                                   Republic */
  API_LAS_COUNTRY_ID_TRINIDAD_AND_TOBAGO              = 0x074C, /*!< 1868 - Trinidad and
                                                                   Tobago */
  API_LAS_COUNTRY_ID_SAINT_KITTS_AND_NEVIS            = 0x074D, /*!< 1869 - Saint Kitts
                                                                   and Nevis */
  API_LAS_COUNTRY_ID_JAMAICA                          = 0x0754, /*!< 1876 - Jamaica */
  API_LAS_COUNTRY_ID_UNKNOWN                          = 0xFFFF  /*!<  */
} RSENUM16(ApiLasCountryCodeTypeType);

/*! Unique Id of a session */
typedef rsuint16 ApiLasSessionIdType;   /*!< Identifier that uniquely identifies one
                                           instance of a session to one single list. The
                                           SessionIdentifier is always issued by the FP and
                                           can be obtained by sending an
                                           API_LAS_START_SESSION_REQ. */

/*! Unique Id of a list entry */
typedef rsuint16 ApiLasEntryIdType;     /*!< Identifier that uniquely identifies a
                                           single entry in a list. This identifier is issued
                                           by the FP when saving an entry and will stay the
                                           same until the entry is deleted again. */

/*! The index number on an entry in the a sorted list */
typedef rsuint16 ApiLasEntryIndexType;  /*!< The position of an entry in the current
                                           sorting of the list. */

/*! Number attributes. The value can be combined of one or more of the
   defined values below (ored together). All other values not described below
   are not valid and will be disregarded by the API. */
typedef rsuint8 ApiLasNumberAttributesType;
#define API_LAS_NUMBER_ATTRIB_INTERNAL 0x01 /*!< The 'Internal' property is used to
                                                identify internal phone numbers and shall be
                                                set to 1 in all entries of the internal
                                                names list.
                                                As the call related lists do not include
                                                internal calls, this property is only set
                                                for the 'internal names list'. */
#define API_LAS_NUMBER_ATTRIB_OWN      0x02 /*!< The 'Own' property is used to indicate
                                                its own entry to the PP which consults the
                                                'internal names list'. It shall be sent to 1
                                                for the PP's own entry, and to 0 for all
                                                other entries in that list. It is not used
                                                in other lists (set to 0 in other lists). */

/*! Contact number attributes. The value can be combined of one or more of
   the defined values below (ored together). All other values not described
   below are not valid and will be disregarded by the API. */
typedef rsuint8 ApiLasContactNumberAttributesType;
#define API_LAS_CONTACT_NUMBER_ATTRIB_OWN    0x01 /*!< Own property is used to identify
                                                      in the contact list, contact numbers
                                                      belonging to the user of the system */
#define API_LAS_CONTACT_NUMBER_ATTRIB_FIXED  0x02 /*!< Indicates that the number is a
                                                      'Fixed' number. */
#define API_LAS_CONTACT_NUMBER_ATTRIB_Mobile 0x04 /*!< Indicates that the number is a
                                                      'Mobile' number. */
#define API_LAS_CONTACT_NUMBER_ATTRIB_WORK   0x08 /*!< Indicates that the number is a
                                                      'Work' number. */

/*! Contact number item. */
typedef struct ApiLasContactNumberItemType
{
  ApiLasContactNumberAttributesType Attributes; /*!< Number attributes. */
  rsuint8 LengthOfNumber;               /*!< Length of Number in bytes. */
  rsuint8 Number[1];                    /*!< First digit in array */
} PACKED_STRUCT ApiLasContactNumberItemType;

/*! Blocked number item. */
typedef struct ApiLasBlockedNumberItemType
{
  rsuint8 LengthOfNumber;               /*!< Length of Number in bytes. */
  rsuint8 Number[1];                    /*!< First digit in array */
} PACKED_STRUCT ApiLasBlockedNumberItemType;

/*! Locked Entry item */
typedef struct ApiLasLockedEntryItemType
{
  ApiLasListIdType ListIdentifier;      /*!< List Identifier */
  ApiLasEntryIdType EntryIdentifier;    /*!< Locked Entry Identifier. */
  rsuint16 HandsetId;                    /*!< Id of the handset that currently have
                                           locked the entry. */
} PACKED_STRUCT ApiLasLockedEntryItemType;

/*! This type is used for API_IE_LAS_SORTING_FIELD_IDENTIFIERS infoElement */
typedef struct ApiLasSortingFieldsType
{
  rsuint8  Length;                      /*!< Length of FieldIdentifiers in bytes. */
  ApiIeType  FieldIdentifiers[1];       /*!< Array of field identifiers. Depended on the
                                           list used. See section 4 for available field
                                           identifiers */
}PACKED_STRUCT ApiLasSortingFieldsType;

/*! This type is used for API_IE_LAS_EDITABLE_FIELDS infoElement */
typedef struct ApiLasEditableFieldsType
{
  rsuint8  Length;                      /*!< Length of FieldIdentifiers in bytes. */
  ApiIeType  FieldIdentifiers[1];       /*!< Array of field identifiers. Depended on the
                                           list used. See section 4 for available field
                                           identifiers */
}PACKED_STRUCT ApiLasEditableFieldsType;

/*! This type is used for API_IE_LAS_NON_EDITABLE_FIELDS infoElement */
typedef struct ApiLasNonEditableFieldsType
{
  rsuint8  Length;                      /*!< Length of FieldIdentifiers in bytes. */
  ApiIeType  FieldIdentifiers[1];       /*!< Array of field identifiers. Depended on the
                                           list used. See section 4 for available field
                                           identifiers */
}PACKED_STRUCT ApiLasNonEditableFieldsType;

/*! This type is used for API_IE_LAS_REQUESTED_FIELD_IDENTIFIERS
   infoElement */
typedef struct ApiLasReqFldIdentifiersType
{
  rsuint8  Length;                      /*!< Length of FieldIdentifiers in bytes. */
  ApiIeType  FieldIdentifiers[1];       /*!< Array of field identifiers. Depended on the
                                           list used. See section 4 for available field
                                           identifiers */
}PACKED_STRUCT ApiLasReqFldIdentifiersType;

/*! This type is used for API_IE_LAS_SEARCH_TEXT infoElement */
typedef struct ApiLasSearchTextType
{
  rsuint8  Length;                      /*!< Length of Characters in bytes. */
  rsuint8  Characters[1];               /*!< Array of UTF8 characters coded search text. */
}PACKED_STRUCT ApiLasSearchTextType;

/*! This type is used for API_IE_LAS_LIST_IDENTIFIERS infoElement */
typedef struct ApiLasListIdentifierType
{
  rsuint8  Length;                      /*!< Length of ListIdentifier in bytes. */
  ApiLasListIdType  ListIdentifier[1];  /*!< First list identifier in array */
}PACKED_STRUCT ApiLasListIdentifierType;

/*! This type is used for API_IE_LAS_NUMBER infoElement */
typedef struct ApiLasNumberType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  ApiLasNumberAttributesType  Attributes; /*!< Number attributes. */
  rsuint8  LengthOfNumber;              /*!< Length of Number in bytes. */
  rsuint8  Number[1];                   /*!< First digit in array */
}PACKED_STRUCT ApiLasNumberType;

/*! This type is used for API_IE_LAS_ NAME infoElement */
typedef struct ApiLasNameType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsuint8  Length;                      /*!< Length of  Name in bytes. */
  rsuint8  Name[1];                     /*!< First character in array (UTF8 encoded) */
}PACKED_STRUCT ApiLasNameType;

/*! This type is used for API_IE_LAS_DATE_TIME infoElement */
typedef struct ApiLasDateTimeType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsuint8  Year;                        /*!< Year  (counted since year 2000) */
  rsuint8  Month;                       /*!< Month of year [1-12] */
  rsuint8  Day;                         /*!< Day of month [1-31] */
  rsuint8  Hour;                        /*!< Hour of day [0-23] */
  rsuint8  Min;                         /*!< Minute [0-59] */
  rsuint8  Sec;                         /*!< Second [0-59] */
  rsuint8  TimeZone;                    /*!< The Time Zone indicates the difference,
                                           expressed in quarters of an hour, between the
                                           local time and GMT. In the first of the two
                                           semi-octets, the first bit represents the
                                           algebraic sign of this difference (0: positive;
                                           1: negative).
                                           The Time Zone code enables the receiver to
                                           calculate the equivalent time in GMT from the
                                           other semi-octets in the element, or indicate the
                                           time zone (GMT, GMT+1H, etc.), or perform other
                                           similar calculations as required by the
                                           implementation. */
}PACKED_STRUCT ApiLasDateTimeType;

/*! This type is used for API_IE_LAS_ENTRY_READSTATUS infoElement */
typedef struct ApiLasEntryReadStatusType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  ApiLasReadStatusType  ReadStatus;     /*!< Entry read status. */
}PACKED_STRUCT ApiLasEntryReadStatusType;

/*! This type is used for API_IE_LAS_ LINE_NAME infoElement */
typedef struct ApiLasLineNameType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  rsuint8  Length;                      /*!< Length of  LineName in bytes. */
  rsuint8  LineName[1];                 /*!< First character in array (UTF8 encoded) */
}PACKED_STRUCT ApiLasLineNameType;

/*! This type is used for API_IE_LAS_ LINE_ID infoElement */
typedef struct ApiLasLineIdType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  ApiLineIdentifierSubType  LineIdSubtype; /*!< Line identifier subtype. 
                                              The following rules should be followed:
                                              For all call-related lists, the subtype shall
                                              be set to 'Line identifier for external call'
                                              (call is external).
                                               For the 'Contact list', subtype shall be set
                                               to 'Relating to' or 'All lines', depending on
                                              the contact.
                                               For the 'Line settings' list, and for any
                                              other list, the subtype shall be set to
                                               'Relating to'. */
  rsuint8  Length;                      /*!< Length of  LineId in bytes. */
  rsuint8  LineId[1];                   /*!< First byte in LineId array */
} PACKED_STRUCT ApiLasLineIdType;

/*! This type is used for API_IE_LAS_FIELD_NUMBER_OF_CALLS infoElement */
typedef struct ApiLasNumberOfCallsType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsuint8  Value;                       /*!< First identifier value in array */
}PACKED_STRUCT ApiLasNumberOfCallsType;

/*! This type is used for API_IE_LAS_NUMBER_OF_CALLS infoElement */
typedef struct ApiLasCallType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  ApiLasCallTypeType  CallType;         /*!< Call type */
}PACKED_STRUCT ApiLasCallType;

/*! This type is used for API_IE_LAS_ FIRST_NAME infoElement */
typedef struct ApiLasFirstNameType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsuint8  Length;                      /*!< Length of  FirstName in bytes. */
  rsuint8  FirstName[1];                /*!< First character in array (UTF8 encoded) */
}PACKED_STRUCT ApiLasFirstNameType;

/*! This type is used for API_IE_LAS_CONTACT_NUMBER infoElement */
typedef struct ApiLasContactNumberType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsuint8  NumberOfNumbers;             /*!< This value gives the number of Contact
                                           numbers. */
  rsuint16  LengthOfNumbers;            /*!< Total length of all contact numbers in
                                           bytes. All numbers are specified as
                                           ApiLasContactNumberItemType. */
  rsuint8  Data[1];                     /*!< Array with all contact numbers. */
}PACKED_STRUCT  ApiLasContactNumberType;
 
/*! This type is used for API_IE_LAS_ ASS_MELODY infoElement */
typedef struct ApiLasAssMelodyType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  rsuint8  MelodyId;                    /*!< Melody id */
}PACKED_STRUCT ApiLasAssMelodyType;

/*! This type is used for API_IE_LAS_CALL_INTERCEPTION infoElement */
typedef struct ApiLasCallInterceptionType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  ApiLasCallInterceptionTypeType  CallInterception; /*!< This field is related to the
                                                        'call interception'. When not
                                                        allowed, it is forbidden for other
                                                        PPs to intercept a call initiated by
                                                        this PP. */
}PACKED_STRUCT ApiLasCallInterceptionType;

/*! This type is used for API_IE_LAS_PIN_CODE infoElement */
typedef struct ApiLasPinCodeType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsuint8  PinCode[API_LAS_LENGTH_OF_PINCODE]; /*!< Each decimal digit shall be
                                                   translated into one nibble (4 bits, BCD
                                                   coded). If the entered pin is less than
                                                   API_LAS_LENGTH_OF_PINCODE bytes long the
                                                   leading nibbles should be padded with 0xF */
}PACKED_STRUCT ApiLasPinCodeType;

/*! This type is used for API_IE_LAS_ NEW_PIN_CODE infoElement */
typedef struct ApiLasNewPinCodeType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  rsuint8  PinCode[API_LAS_LENGTH_OF_PINCODE]; /*!< Each decimal digit shall be
                                                   translated into one nibble (4 bits, BCD
                                                   coded). If the entered pin is less than
                                                   API_LAS_LENGTH_OF_PINCODE bytes long the
                                                   leading nibbles should be padded with 0xF */
}PACKED_STRUCT ApiLasNewPinCodeType;

/*! This type is used for API_IE_LAS_ CLOCK_MASTER infoElement */
typedef struct ApiLasClockMasterType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  ApiLasClockMasterTypeType  ClockMaster; /*!< Defines the entity which sets date and
                                              time for the DECT system (PP or FP). */
}PACKED_STRUCT ApiLasClockMasterType;

/*! This type is used for API_IE_LAS_ BASE_RESET infoElement */
typedef struct ApiLasBaseResetType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  ApiLasBaseResetTypeType  Reset;       /*!< The Base reset field respect the following
                                           rules: 
                                           If at least one DECT system setting, or line
                                           setting, has been set to a non default value, the
                                           Base reset field will be equal to False when a PP
                                           performs a read command. 
                                           If a registered PP sets the value to True, all
                                           DECT system and line settings will be reset to
                                           their default value. The setting remains set to
                                           True until any DECT system or line setting is
                                           changed. 
                                           Any attempt from to set this parameter to False
                                           will result in a negative acknowledgement. */
}PACKED_STRUCT ApiLasBaseResetType;

/*! This type is used for API_IE_LAS_IP_ADDRESS_TYPE infoElement */
typedef struct ApiLasIpAdrType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  ApiLasIpAdrTypeType  IpAddressType;   /*!< The IP address of the FP may be assigned
                                           dynamically using DHCP or manually using a static
                                           address entered by the user. */
}PACKED_STRUCT ApiLasIpAdrType;

/*! This type is used for API_IE_LAS_IP_ADDRESS infoElement */
typedef struct ApiLasIpAdrValueType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  ApiLasIpAdrFormatType  IpAddressFormat; /*!< if set to API_LAS_IPADRFORMAT_IPV4, the
                                              format is IPv4 (4 bytes long); if set to
                                              API_LAS_IPADRFORMAT_IPV6, the format is IPv6
                                              (16 bytes long). */
  rsuint8  Digit[1];                    /*!< Digits in address */
}PACKED_STRUCT ApiLasIpAdrValueType;

/*! This type is used for API_IE_LAS_IP_SUBNET_MASK infoElement */
typedef struct ApiLasIpSubnetMaskType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  ApiLasIpAdrFormatType  IpAddressFormat; /*!< if set to API_LAS_IPADRFORMAT_IPV4, the
                                              format is IPv4 (4 bytes long); if set to
                                              API_LAS_IPADRFORMAT_IPV6, the format is IPv6
                                              (16 bytes long). */
  rsuint8  Digit[1];                    /*!< Digits in address */
}PACKED_STRUCT ApiLasIpSubnetMaskType;

/*! This type is used for API_IE_LAS_IP_GATEWAY infoElement */
typedef struct ApiLasIpGatewayType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  ApiLasIpAdrFormatType  IpAddressFormat; /*!< if set to API_LAS_IPADRFORMAT_IPV4, the
                                              format is IPv4 (4 bytes long); if set to
                                              API_LAS_IPADRFORMAT_IPV6, the format is IPv6
                                              (16 bytes long). */
  rsuint8  Digit[1];                    /*!< Digits in address */
}PACKED_STRUCT ApiLasIpGatewayType;

/*! This type is used for API_IE_LAS_IP_DNS infoElement */
typedef struct ApiLasIpDnsType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  ApiLasIpAdrFormatType  IpAddressFormat; /*!< if set to API_LAS_IPADRFORMAT_IPV4, the
                                              format is IPv4 (4 bytes long); if set to
                                              API_LAS_IPADRFORMAT_IPV6, the format is IPv6
                                              (16 bytes long). */
  rsuint8  Digit[1];                    /*!< Digits in address */
}PACKED_STRUCT ApiLasIpDnsType;

/*! This type is used for API_IE_LAS_FIRMWARE_VERSION infoElement */
typedef struct ApiLasVerFirmwareType
{
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  rsuint8  Length;                      /*!< Length of Character in bytes. */
  rsuint8  Character[1];                /*!< First character in array (UTF8 encoded) */
}PACKED_STRUCT ApiLasVerFirmwareType;

/*! This type is used for API_IE_LAS_EEPROM_VERSION infoElement */
typedef struct ApiLasVerEePromType
{
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  rsuint8  Length;                      /*!< Length of Character in bytes. */
  rsuint8  Character[1];                /*!< First character in array (UTF8 encoded) */
}PACKED_STRUCT ApiLasVerEePromType;

/*! This type is used for API_IE_LAS_HARDWARE_VERSION infoElement */
typedef struct ApiLasVerHardwareType
{
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  rsuint8  Length;                      /*!< Length of Character in bytes. */
  rsuint8  Character[1];                /*!< First character in array (UTF8 encoded) */
}PACKED_STRUCT ApiLasVerHardwareType;

/*! This type is used for API_IE_LAS_EMISSION_MODE infoElement */
typedef struct ApiLasEmissionModeType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool PinProtected;                  /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  ApiLasNoEmissionModeType NoEmissionMode; /*!< Setting for activating/deactivating the
                                               'No Emission mode' */
} PACKED_STRUCT ApiLasEmissionModeType;

/*! This type is used for API_IE_LAS_ ATTACHED_HANDSETS
    infoElement */
typedef struct ApiLasAttachedHandsetsType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  rsuint8  NumberOfAttachedHandsets;    /*!< This value tells how many handsets that are
                                           attached to this line (Number of bits set in the
                                           bitmap field).  
                                           
                                           NB. This value is automatically calculated by
                                           the API and should there for not be added when
                                           sending this InfoElement. */
  rsuint8  Length;                      /*!< Length of Bitmap in bytes. */
  rsuint8  Bitmap[1];                   /*!< The Bitmap is showing whish handsets that
                                           are connected to each line. Each handset is
                                           represented by a bit in this field 
                                           
                                           Bits 8 7 6 5 4 3 2 1  Meaning
                                           x x x x x x x 1  Handset nr 1 is attached
                                           x x x x x x 1 x  Handset nr 2 is attached
                                           x x x x x 1 x x  Handset nr 3 is attached
                                           x x x x 1 x x x  Handset nr 4 is attached
                                           x x x 1 x x x x  Handset nr 5 is attached
                                           x x 1 x x x x x  Handset nr 6 is attached
                                           x 1 x x x x x x  Handset nr 7 is attached
                                           1 x x x x x x x  Handset nr 8 is attached */
}PACKED_STRUCT ApiLasAttachedHandsetsType;

/*! This type is used for API_IE_LAS_ DIALING_PREFIX infoElement. */
typedef struct ApiLasDialingPrefixType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  rsuint8  LengthOfNumber;              /*!< Lengthof dial prefix number in bytes. */
  rsuint8  Number[1];                   /*!< Dial prefix number */
}PACKED_STRUCT  ApiLasDialingPrefixType;

/*! This type is used for API_IE_LAS_ FP_MELODY infoElement */
typedef struct ApiLasFpMelodyType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  rsuint8  Value;                       /*!< Melody id */
}PACKED_STRUCT ApiLasFpMelodyType;

/*! This type is used for API_IE_LAS_ FP_VOLUME infoElement */
typedef struct ApiLasFpVolumeType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  rsuint8  Volume;                      /*!< Volumen value [0-9] */
}PACKED_STRUCT ApiLasFpVolumeType;

/*! This type is used for API_IE_LAS_ BLOCKED_NUMBERS infoElement */
typedef struct ApiLasBlockedNumberType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  rsuint8  NumberOfNumbers;             /*!< This value gives the number of Contact
                                           numbers. */
  rsuint16  LengthOfNumbers;            /*!< Total length of all contact numbers in
                                           bytes. All numbers are specified as
                                           ApiLasBlockedNumberItemType. */
  rsuint8  Data[1];                     /*!< Array with all contact numbers. */
}PACKED_STRUCT  ApiLasBlockedNumberType;

/*! This type is used for API_IE_LAS_ MULTIPLE_CALL infoElement */
typedef struct ApiLasMultipleCallType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  ApiLasMultipleCallModeType  MultipleCallMode; /*!< This field allows to configure a
                                                    multiple call line in single call mode.
                                                    For non-multiple call lines, the value
                                                    Single call mode shall always be used.
                                                     */
}PACKED_STRUCT ApiLasMultipleCallType;

/*! This type is used for API_IE_LAS_ INTRUSION_CALL infoElement */
typedef struct ApiLasIntrusionCallType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  ApiLasIntrusionCallModeType  IntrusionCallMode; /*!< Intrusion call mode */
}PACKED_STRUCT ApiLasIntrusionCallType;

/*! This type is used for API_IE_LAS_ PERMANENT_CLIR infoElement */
typedef struct ApiLasPermanentClirType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  ApiLasPermanentClirTypeType  ClirMode; /*!< CLIR mode */
  rsuint8  LengthOfActivationCode;      /*!< Length in bytes of the CLIR activation code */
  rsuint8  LengthOfDeactivationCode;    /*!< Length in bytes of the CLIR deactivation
                                           code */
  rsuint8  ClirCodes[1];                /*!< Each digit shall be out of interval
                                           30H..39H, and values 23H, 2AH, 05H and 15H. 
                                           The CLIR activation code should be placed first
                                           and the deactivation code second. */
}PACKED_STRUCT ApiLasPermanentClirType;

/*! This type is used for API_IE_LAS _CALL_FORWARDING_CFU infoElement */
typedef struct ApiLasCallForwardingCfuType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  ApiLasCallForwardStateType  State;    /*!< Call forward state. */
  rsuint8  LengthOfActivationCode;      /*!< Length in bytes of the activation code */
  rsuint8  LengthOfDeactivationCode;    /*!< Length in bytes of the deactivation code */
  rsuint8  LengthOfCfNumber;            /*!< Length in bytes of the call forward number */
  rsuint8  Data[1];                     /*!< Each digit shall be out of interval
                                           30H..39H, and values 23H, 2AH, 05H and 15H. 
                                           The Data should be arranged the following way:
                                           1) Activation code 
                                           2) Deactivation code
                                           3) CfNumber */
}PACKED_STRUCT ApiLasCallForwardingCfuType;

/*! This type is used for API_IE_LAS _CALL_FORWARDING_CFNA infoElement */
typedef struct ApiLasCallForwardingCfnaType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  ApiLasCallForwardStateType  State;    /*!< Call forward state. */
  rsuint8  DelayTime;                   /*!< Number of seconds before call is forwarded.
                                           Allowable values are 0 to 64. A value of zero
                                           indicates that the choice of the 
                                           number of seconds is left to the FP (use of a
                                           default or preferred value configured in the FP). */
  rsuint8  LengthOfActivationCode;      /*!< Length in bytes of the activation code */
  rsuint8  LengthOfDeactivationCode;    /*!< Length in bytes of the deactivation code */
  rsuint8  LengthOfCfNumber;            /*!< Length in bytes of the call forward number */
  rsuint8  Data[1];                     /*!< Each digit shall be out of interval
                                           30H..39H, and values 23H, 2AH, 05H and 15H. 
                                           The Data should be arranged the following way:
                                           1) Activation code 
                                           2) Deactivation code
                                           3) CfNumber */
}PACKED_STRUCT ApiLasCallForwardingCfnaType;

/*! This type is used for API_IE_LAS _CALL_FORWARDING_CFB infoElement */
typedef struct ApiLasCallForwardingCfbType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  ApiLasCallForwardStateType  State;    /*!< Call forward state. */
  rsuint8  LengthOfActivationCode;      /*!< Length in bytes of the activation code */
  rsuint8  LengthOfDeactivationCode;    /*!< Length in bytes of the deactivation code */
  rsuint8  LengthOfCfNumber;            /*!< Length in bytes of the call forward number */
  rsuint8  Data[1];                     /*!< Each digit shall be out of interval
                                           30H..39H, and values 23H, 2AH, 05H and 15H. 
                                           The Data should be arranged the following way:
                                           1) Activation code 
                                           2) Deactivation code
                                           3) CfNumber */
} ApiLasCallForwardingCfbType;

/*! This type is used for API_IE_LAS_COUNTRY_CODE infoElement */
typedef struct ApiLasCountryCodeType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  ApiLasCountryCodeTypeType  CountryCode; /*!< System country code */
}PACKED_STRUCT  ApiLasCountryCodeType;

/*! This type is used for API_IE_LAS_IPMAC infoElement */
typedef struct ApiLasIpMacType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  rsuint16  LengthOfIpMac;              /*!< Length of IP MAC address in bytes. */
  rsuint8  IpMac[1];                    /*!< FP IP MAC address. */
}PACKED_STRUCT  ApiLasIpMacType;

/*! This type is used for API_IE_LAS_DECT_MODE infoElement */
typedef struct ApiLasDectModeType
{
  rsbool  Editable;                     /*!< Read only or editable. Please refer to
                                           section 2 for further information on this
                                           setting. */
  rsbool  PinProtected;                 /*!< Indicates if the InfoElement is PIN code
                                           protected. Please refer to section 2.5 for
                                           further information on this setting. */
  ApiDectTypeType  DectMode;            /*!< FP Dect mode. */
} PACKED_STRUCT ApiLasDectModeType;

/*! This type is used for API_IE_LAS_PIN_PROTECTED_FIELDS infoElement */
typedef struct ApiLasPinProtectedFieldsType
{
  rsuint8 Length;                       /*!< Length of FieldIdentifiers in bytes. */
  ApiIeType FieldIdentifiers[1];        /*!< Array of field identifiers. Depended on the
                                           list used. See section 4 for available field
                                           identifiers */
} PACKED_STRUCT ApiLasPinProtectedFieldsType;

/*! This type is used for API_IE_LAS_DISABLED_FIELDS infoElement */
typedef struct ApiLasDisabledFieldsType
{
  rsuint8 Length;                       /*!< Length of FieldIdentifiers in bytes. */
  ApiIeType FieldIdentifiers[1];        /*!< Array of field identifiers. Depended on the
                                           list used. See section 4 for available field
                                           identifiers */
} PACKED_STRUCT ApiLasDisabledFieldsType;

/*! This type is used for API_IE_LOCKED_ENTRIES_LIST infoElement */
typedef struct ApiLasLockedEntriesListType
{
  rsuint8 Length;                       /*!< Total length of the LockedEntriesList in
                                           bytes. All LockedEntries items are specified as
                                           ApiLasLockedEntryItemType. */
  rsuint8 LockedEntriesList[1];         /*!< Array of LockedEntry items. */
} PACKED_STRUCT ApiLasLockedEntriesListType;


/*! Mail without parameters. */
typedef struct ApilasEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
}PACKED_STRUCT ApilasEmptySignalType;

/*! This mail is used by the MMI to start up a list handling session with a
   specified list in FP. */
typedef struct ApiLasStartSessionReqType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_START_SESSION_REQ = 0x5500 */
  ApiLasListIdType ListIdentifier;      /*!< Id of list to start session with */
  rsuint8 InfoElementLength;            /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElement can hold a number Info
                                           Elements placed in the format (ApiInfoElementType):
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Valid Info elements for this command:
                                           API_IE_LAS_SORTING_FIELD_IDENTIFIERS */
}PACKED_STRUCT ApiLasStartSessionReqType;

/*! This mail is used by the API to inform the MMI that a session has been
   started with or without success.
    
    Error cases:
    If a start settion request is sendt with an unsupported ListIdentifier,
   API_LAS_REJECT_LIST_NOT_SUPPORTED will be returned as reject reason. 
    
    If a start settion request is sendt before LAS has finished initializing,
   API_LAS_REJECT_NOT_ENOUGH_RESOURCES will be returned as reject reason. 
     */
typedef struct ApiLasStartSessionCfmType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_START_SESSION_CFM = 0x5501 */
  ApiLasListIdType ListIdentifier;      /*!< Id of list to start session with */
  ApiLasSessionIdType SessionIdentifier; /*!< Allocated session id reserved for the
                                             started session. Will be 0 in case of
                                             rejection. */
  rsuint16 NoOfEntries;                 /*!< Number of entries in list related to
                                           session. */
  ApiLasDiscriminatorType DiscriminatorType; /*!< API_LIST_DISCRIMINATOR_UNDEFINED or
                                                 API_LIST_DISCRIMINATOR_EMC. If
                                                 API_LIST_DISCRIMINATOR_UNDEFINED the
                                                 following parameter is not used */
  rsuint16 Discriminator;               /*!< Not used of DiscriminatorType is 0 */
  ApiLasRejectReasonType RejectReason;  /*!< Reject reason in case of reject */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElement can hold a number Info
                                           Elements placed in the format (ApiInfoElementType):
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Valid Info elements for this command:
                                           API_IE_LAS_SORTING_FIELD_IDENTIFIERS */
}PACKED_STRUCT ApiLasStartSessionCfmType;

/*! This mail is used by the MMI to end a list handling session with a
   specified list in FP. Remaining locked entries will be unlocked.
    
    If SessionIdentifier is wrong command is ignored. */
typedef struct ApiLasEndSessionReqType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_END_SESSION_REQ = 0x5502 */
  ApiLasSessionIdType SessionIdentifier; /*!< Id of session. */
}PACKED_STRUCT ApiLasEndSessionReqType;

/*! This mail is used by the API to inform the MMI that the session has
   ended. */
typedef struct ApiLasEndSessionCfmType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_END_SESSION_CFM = 0x5503 */
  ApiLasSessionIdType SessionIdentifier; /*!< Id of session. */
}PACKED_STRUCT ApiLasEndSessionCfmType;

/*! This mail is used by the MMI to query FP about which fields are
   supported in the entries of a specific list.
    
    If session id is wrong FP will answer back with negative acknowledgement
   (API_LAS_INVALID_SESSION_NO ) else confirm will be received. */
typedef struct ApiLasQuerySupportedEntryFieldsReqType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_QUERY_SUPPORTED_ENTRY_FIELDS_REQ = 0x5504 */
  ApiLasSessionIdType SessionIdentifier; /*!< Id of session. */
}PACKED_STRUCT ApiLasQuerySupportedEntryFieldsReqType;

/*! This mail is used to confirm the API_LAS_END_REQ command. */
typedef struct ApiLasQuerySupportedEntryFieldsCfmType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_QUERY_SUPPORTED_ENTRY_FIELDS_CFM = 0x5505 */
  ApiLasSessionIdType SessionIdentifier; /*!< Id of session. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElement can hold a number Info
                                           Elements placed in the format (ApiInfoElementType):
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Valid Info elements for this command:
                                           API_IE_LAS_EDITABLE_FIELDS
                                           API_IE_LAS_NON_EDITABLE_FIELDS */
}PACKED_STRUCT ApiLasQuerySupportedEntryFieldsCfmType;

/*! This mail is used by the MMI to request one or more list entries in FP.
   The received list corresponds to the sorting and setup done by the start
   session command. 
    
    If StartIndex  + NumberOfEntries is larget than the number of entries
   stored, FP will return the existing elements in the range in the confirm command.
    
    If an unknown list entry field is requested the FP will ignore this field
   and continue with the next field.
    
    If no errors:
    API will return API_LAS_READ_ENTRIES_CFM
    
    If error:
    API will return API_LAS_NEGATIVE_ACKNOWLEDGE_IND with the following RejectReason:
    [API_LAS_INVALID_SESSION_NO] If SessionIdentifier is wrong.
    [API_LAS_INVALID_START_INDEX] If StartIndex is wrong.
    [API_LAS_INVALID_RANGE] If NumberOfEntries is larger than 0x7F.
     */
typedef struct ApiLasReadEntriesReqType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_READ_ENTRIES_REQ = 0x5506 */
  ApiLasSessionIdType SessionIdentifier; /*!< Id of session. */
  ApiLasEntryIndexType StartIndex;      /*!< Start number [0-0x3FFF] where:
                                           0: Last entry in list
                                           0x1 - 0x3FFF: Entry number in list */
  rsuint8 NumberOfEntries;              /*!< Number of requested entries [0x1-0x7F] */
  ApiLasReadDirectionType ReadDirection; /*!< This enum defines the direction of
                                             received list entries. */
  ApiLasReadStatusType ReadStatus;      /*!< Flag for requesting setting/resetting of
                                           the 'Read status' field for all read entrie. This
                                           field only applies to a list having a 'Read
                                           status' field, and is otherwise ignored. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElement can hold a number Info
                                           Elements placed in the format (ApiInfoElementType):
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Valid Info elements for this command:
                                           API_IE_LAS_REQUESTED_FIELD_IDENTIFIERS */
}PACKED_STRUCT ApiLasReadEntriesReqType;

/*! This mail is used by the API to tell the MMI about the received list
   entries. Content of list entry is transmitted in data packets.
    Content of list entry is transmitted in data packets. */
typedef struct ApiLasReadEntriesCfmType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_READ_ENTRIES_CFM = 0x5507 */
  ApiLasSessionIdType SessionIdentifier; /*!< Id of session. */
  ApiLasEntryIndexType StartIndex;      /*!< Smallest index value of list response [0x1
                                           - 0x3FFF] */
  rsuint8 NumberOfEntries;              /*!< Number of delivered entries [0-0xFF] */
}PACKED_STRUCT ApiLasReadEntriesCfmType;

/*! This mail is used by the MMI to edit and lock one entry. FP prevent
   other PP's from changing the requested list entry until PP has sent the
   save entry command or the session is terminated. 
    If session id is wrong FP will answer back with negative acknowledgement
   (API_LAS_INVALID_SESSION_NO ) else confirm will be received.
    
    If an unknown entry identifier is requested FP will answer back with
   negative acknowledgement (API_LAS_ENTRY_NOT_AVAILABLE) else confirm will be received.
    
    If an unknown list field identifier is requested FP will ignore this filed
   and continue. */
typedef struct ApiLasEditEntryReqType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_EDIT_ENTRY_REQ = 0x5508 */
  ApiLasSessionIdType SessionIdentifier; /*!< Id of session. */
  ApiLasEntryIdType EntryIdentifier;    /*!< Id of entry. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElemen can hold a number Info
                                           Elements placed in the format (ApiInfoElementType):
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Valid Info elements for this command:
                                           API_IE_LAS_REQUESTED_FIELD_IDENTIFIERS */
}PACKED_STRUCT ApiLasEditEntryReqType;

/*! This mail is used by the API to tell the MMI that the entry has been
   locked and are ready for edit. 
    Content of list entry is transmitted in data packets. */
typedef struct ApiLasEditEntryCfmType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_EDIT_ENTRY_CFM = 0x5509 */
  ApiLasSessionIdType SessionIdentifier; /*!< Id of session. */
}PACKED_STRUCT ApiLasEditEntryCfmType;

/*! This mail is used by the MMI to request to save a new or existing list
   entry identified by the entry identifier. Corresponding entry is sent in
   data packets.
    
    If the previously started edit procedure has to be terminated without
   changing the entry, PP shall perform the the save entry procedure with only
   one empty last data packet following after the save entry.
    
    Fields which shall be deleted shall be sent back to FP with length 0.
    
    List entries which are updated must have been locked using the edit
   command (except for new entries).
    
    If session id is wrong FP will answer back with negative acknowledgement
   (API_LAS_INVALID_SESSION_NO ) else confirm will be received.
    
    If entry identifier id is unknown FP will answer back with negative
   acknowledgement (API_LAS_ENTRY_NOT_AVAILABLE) else confirm will be received.
    
    If a field content cannot be accepted FP will answer back with negative
   acknowledgement (API_LAS_CONTENT_NOT_ACCEPTED) else confirm will be received.
    
    If an entry cannot be added to a list which cannot accept an additional
   entry, FP will answer back with negative acknowledgement (API_LAS_FULL)
   else confirm will be received.
     */
typedef struct ApiLasSaveEntryReqType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_SAVE_ENTRY_REQ = 0x550A */
  ApiLasSessionIdType SessionIdentifier; /*!< Id of session. */
  ApiLasEntryIdType EntryIdentifier;    /*!< Id of entry. If 0 entry is new and no
                                           identifier has been assigned yet. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElemen can hold a number Info
                                           Elements placed in the format (ApiInfoElementType):
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Valid Info elements:
                                           See section 4 for available info elements. */
}PACKED_STRUCT ApiLasSaveEntryReqType;

/*! This mail is used by the API to tell the MMI that an entry has been
   saved. */
typedef struct ApiLasSaveEntryCfmType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_SAVE_ENTRY_CFM = 0x550B */
  ApiLasSessionIdType SessionIdentifier; /*!< Id of session. */
  ApiLasEntryIdType EntryIdentifier;    /*!< Id of entry. */
  ApiLasEntryIndexType PositionNumber;  /*!< Indicates the (possible new) index number
                                           of the entry in the list. */
  rsuint16 NoOfEntries;                 /*!< Total number of available entries in the
                                           list. */
}PACKED_STRUCT ApiLasSaveEntryCfmType;

/*! This mail is used by the MMI to request to delete one existing list entry.
    
    If session id is wrong FP will answer back with negative acknowledgement
   (API_LAS_INVALID_SESSION_NO ) else confirm will be received.
    
    If entry identifier id is unknown FP will answer back with negative
   acknowledgement (API_LAS_ENTRY_NOT_AVAILABLE) else confirm will be received.
    
    It is not allowed to delete entries in List of supported lists and DECT
   system settings list. When doing this FP will answer back with negative
   acknowledgement (API_LAS_PROCEDURE_NOT_ALLOWED) else confirm will be received..
     */
typedef struct ApiLasDeleteEntryReqType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DELETE_ENTRY_REQ = 0x550C */
  ApiLasSessionIdType SessionIdentifier; /*!< Id of session. */
  ApiLasEntryIdType EntryIdentifier;    /*!< Id of entry.[0x1 - 0x3FFF] */
}PACKED_STRUCT ApiLasDeleteEntryReqType;

/*! This mail is used by the API to tell the MMI that an entry has been
   deleted. */
typedef struct ApiLasDeleteEntryCfmType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DELETE_ENTRY_CFM = 0x550D */
  ApiLasSessionIdType SessionIdentifier; /*!< Id of session. */
  rsuint16 NumberOfEntriesLeft;         /*!< Number of entries left in the list after
                                           deletion */
}PACKED_STRUCT ApiLasDeleteEntryCfmType;

/*! This mail is used by the MMI to request a deletion of all entries in a
   list. The list itself will still remain.
    
    If session id is wrong FP will answer back with negative acknowledgement
   (API_LAS_INVALID_SESSION_NO) else confirm will be received.
    
    If an unknown list identifier is requested FP will answer back with
   negative acknowledgement (API_LAS_PROCEDURE_NOT_ALLOWED) else confirm will
   be received.
    
    If FP reject the delete list command it will answer back with negative
   acknowledgement (API_LAS_PROCEDURE_NOT_ALLOWED) else confirm will be received.
    
    It is not allowed to delete List of supported lists, Line settings List
   and DECT system settings list. When doing this FP will answer back with
   negative acknowledgement (API_LAS_PROCEDURE_NOT_ALLOWED) else confirm will
   be received.
     */
typedef struct ApiLasDeleteListReqType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DELETE_LIST_REQ = 0x550E */
  ApiLasSessionIdType SessionIdentifier; /*!< Id of session. */
}PACKED_STRUCT ApiLasDeleteListReqType;

/*! This mail is used by the API to tell the MMI that all entries in a list
   have been deleted. */
typedef struct ApiLasDeleteListCfmType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DELETE_LIST_CFM = 0x550F */
  ApiLasSessionIdType SessionIdentifier; /*!< Id of session. */
}PACKED_STRUCT ApiLasDeleteListCfmType;

/*! This mail is used by the MMI to request a range of entries in the list
   which satisfy the search criteria. The search is performed on the primary
   sorting field (returned as the first fieldidentifier in the
   API_LAS_START_SESSION_CFM message)
    
    If session id is wrong FP will answer back with negative acknowledgement
   (API_LAS_INVALID_SESSION_NO) else confirm will be received.
    
    If an unknown list entry filed identifier is requested FP will ignore
   field and continue. */
typedef struct ApiLasSearchEntriesReqType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_SEARCH_ENTRIES_REQ = 0x5510 */
  ApiLasSessionIdType SessionIdentifier; /*!< Id of session. */
  ApiLasSearchOptionType SearchOption;  /*!< Option that should be used in search */
  ApiLasSearchCaseOptionType SearchCaseOption; /*!< Case option that should be used in
                                                   search */
  rsuint8 NumberOfEntries;              /*!< Number of requested entries [0x1 ? 0x7F] */
  ApiLasReadDirectionType ReadDirection; /*!< This enum defines the direction of
                                             received list entries. */
  ApiLasReadStatusType ReadStatus;      /*!< Flag for requesting setting/resetting of
                                           the 'Read status' field for all read entrie. This
                                           field only applies to a list having a 'Read
                                           status' field, and is otherwise ignored. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElement can hold a number Info
                                           Elements placed in the format (ApiInfoElementType):
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Valid Info elements for this command:
                                           API_IE_LAS_SEARCH_TEXT
                                           API_IE_LAS_REQUESTED_FIELD_IDENTIFIERS */
}PACKED_STRUCT ApiLasSearchEntriesReqType;

/*! This mail is used by the API to tell MMI about the found entries in the search.
    
    Content of list/entries is transmitted in data packets, except if no
   entries found. */
typedef struct ApiLasSearchEntriesCfmType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_SEARCH_ENTRIES_CFM = 0x5511 */
  ApiLasSessionIdType SessionIdentifier; /*!< Id of session. */
  ApiLasEntryIndexType StartIndex;      /*!< Index number of first returned list entry. */
  rsuint8 NumberOfEntries;              /*!< Number of returned entries. */
}PACKED_STRUCT ApiLasSearchEntriesCfmType;

/*! This mail is used by the API to tell MMI that the previous command was
   rejected. 
    
    If the reject reason was an invalid session number the SessionIdentifier
   will contain the invalid number. */
typedef struct ApiLasNegativeAcknowledgeIndType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_NEGATIVE_ACKNOWLEDGE_IND = 0x5512 */
  ApiLasSessionIdType SessionIdentifier; /*!< Id of session. */
  ApiLasNegativeAcknowledgeReasonType RejectReason; /*!< Reject reason */
}PACKED_STRUCT ApiLasNegativeAcknowledgeIndType;

/*! This mail is used by the API to send data to the MMI.
    The data content is distributed over several data packet messages. One
   entry field might be distributed over more than one data packet. */
typedef struct ApiLasDataPacketIndType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DATA_PACKET_IND = 0x5513 */
  ApiLasSessionIdType SessionIdentifier; /*!< Id of session. */
  ApiLasEntryIdType EntryIdentifier;    /*!< Id of entry. */
  rsbool Last;                          /*!< Indicate if packet is the last one. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElement can hold a number Info
                                           Elements placed in the format (ApiInfoElementType):
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Valid Info elements for this command:
                                           See section 4 for available info elements. */
}PACKED_STRUCT ApiLasDataPacketIndType;

/*! This mail is used by the API to tell MMI that a BaseReset have been
   requested. 
     */
typedef struct ApiLasBaseResetIndType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_BASE_RESET_IND = 0x5580 */
  ApiLasSessionIdType SessionIdentifier; /*!< Id of session. */
} PACKED_STRUCT ApiLasBaseResetIndType;

/*! This mail is used by the API to tell MMI that an internal error has
   occurred in the API. */
typedef struct ApiLasStatusIndType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_STATUS_IND = 0x5581 */
  ApiLasSessionIdType SessionIdentifier; /*!< Id of session. */
  ApiLasStatusType Status;              /*!< Status. */
} PACKED_STRUCT ApiLasStatusIndType;

/*! This mail is used by the MMI to query FP about the protection of fields
   for a list (disabled, read-only, writeable or writeable with PIN
   protection). */
typedef struct ApiLasGetFieldProtectionReqType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_GET_FIELD_PROTECTION_REQ = 0x5582 */
  ApiLasListIdType ListIdentifier;      /*!< Id of list. */
} PACKED_STRUCT ApiLasGetFieldProtectionReqType;

/*! Field protection information. */
typedef struct ApiLasGetFieldProtectionCfmType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_GET_FIELD_PROTECTION_CFM = 0x5583 */
  ApiLasListIdType ListIdentifier;      /*!< Id of list. */
  RsStatusType Status;                  /*!< Command status, either RSS_SUCCESS or
                                           RSS_NOT_SUPPORTED. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElement can hold a number Info
                                           Elements placed in the format (ApiInfoElementType):
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Valid Info elements for this command:
                                           API_IE_LAS_DISABLED_FIELDS
                                           API_IE_LAS_EDITABLE_FIELDS
                                           API_IE_LAS_NON_EDITABLE_FIELDS
                                           API_IE_LAS_PIN_PROTECTED_FIELDS */
} PACKED_STRUCT ApiLasGetFieldProtectionCfmType;

/*! This mail is used by the MMI to modify the protection of fields for a
   list (disabled, read-only, writeable or writeable with PIN protection). */
typedef struct ApiLasSetFieldProtectionReqType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_SET_FIELD_PROTECTION_REQ = 0x5584 */
  ApiLasListIdType ListIdentifier;      /*!< Id of list. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElement can hold a number Info
                                           Elements placed in the format (ApiInfoElementType):
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Valid Info elements for this command:
                                           API_IE_LAS_DISABLED_FIELDS
                                           API_IE_LAS_EDITABLE_FIELDS
                                           API_IE_LAS_NON_EDITABLE_FIELDS
                                           API_IE_LAS_PIN_PROTECTED_FIELDS */
} PACKED_STRUCT ApiLasSetFieldProtectionReqType;

/*! Field protection information. */
typedef struct ApiLasSetFieldProtectionCfmType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_SET_FIELD_PROTECTION_CFM = 0x5585 */
  ApiLasListIdType ListIdentifier;      /*!< Id of list. */
  RsStatusType Status;                  /*!< Command status, either RSS_SUCCESS or
                                           RSS_NOT_SUPPORTED. */
} PACKED_STRUCT ApiLasSetFieldProtectionCfmType;

/*! This mail is used by the MMI to query FP about the editing status of
   specific lists. */
typedef ApilasEmptySignalType ApiLasGetLockedEntriesListReqType;

/*! Field protection information. */
typedef struct ApiLasGetLockedEntriesListCfmType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_GET_LOCKED_ENTRIES_LIST_CFM = 0x5587 */
  RsStatusType Status;                  /*!< Command status, either RSS_SUCCESS or
                                           RSS_NOT_SUPPORTED. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElement can hold a number Info
                                           Elements placed in the format (ApiInfoElementType):
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Valid Info elements for this command:
                                           API_IE_LAS_LOCK_ENTRIES_LIST */
} PACKED_STRUCT ApiLasGetLockedEntriesListCfmType;

/*! This mail is used by the MMI to clear a specified list in FP. 
    This command can only be used with a Phoenix based FPs which support LAS
   and should only be used for debug/test purpose and not for application use. */
typedef struct ApiLasDbClearReqType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_CLEAR_REQ = 0x55C0 */
  ApiLasSessionIdType SessionIdentifier; /*!< Id of session. */
  ApiLasListIdType ListIdentifier;      /*!< Id of list to clear. Any list can be
                                           cleared from any session.  
                                           If API_LAS_SUPPORTED_LISTS is selected all lists
                                           are cleared */
}PACKED_STRUCT ApiLasDbClearReqType;

/*! This mail is used by the API to inform the MMI that the list has been cleared.
    This command can only be used with a Phoenix based FPs which support LAS
   and should only be used for debug/test purpose and not for application use. */
typedef struct ApiLasDbClearCfmType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_CLEAR_CFM = 0x55C1 */
  ApiLasSessionIdType SessionIdentifier; /*!< Id of session. */
}PACKED_STRUCT ApiLasDbClearCfmType;


#ifdef __cplusplus
extern "C"
{
#endif
/** \cond internal */

/****************************************************************************
*     Function prototypes for mail packaging and sending(MPS) functions
****************************************************************************/

/****************************************************************************
* FUNCTION:      SendApiLasStartSessionReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_START_SESSION_REQ = 0x5500
****************************************************************************/
void SendApiLasStartSessionReq ( RosTaskIdType Src,
                                 ApiLasListIdType ListIdentifier,
                                                             /*!< Id of list to start
                                                                session with */
                                 rsuint8 InfoElementLength,  /*!< The length of the Data
                                                                Information Element */
                                 rsuint8 InfoElement[1]);    /*!< The InfoElement can
                                                                hold a number Info Elements
                                                                placed in the format (ApiInfoElementType):
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Valid Info elements for
                                                                this command:
                                                                API_IE_LAS_SORTING_FIELD_IDE
                                                                NTIFIERS */

/****************************************************************************
* FUNCTION:      SendApiLasEndSessionReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_END_SESSION_REQ = 0x5502
****************************************************************************/
void SendApiLasEndSessionReq ( RosTaskIdType Src,
                               ApiLasSessionIdType SessionIdentifier);
                                                             /*!< Id of session. */

/****************************************************************************
* FUNCTION:      SendApiLasQuerySupportedEntryFieldsReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_QUERY_SUPPORTED_ENTRY_FIELDS_REQ = 0x5504
****************************************************************************/
void SendApiLasQuerySupportedEntryFieldsReq ( RosTaskIdType Src,
                                              ApiLasSessionIdType SessionIdentifier);
                                                             /*!< Id of session. */

/****************************************************************************
* FUNCTION:      SendApiLasReadEntriesReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_READ_ENTRIES_REQ = 0x5506
****************************************************************************/
void SendApiLasReadEntriesReq ( RosTaskIdType Src,
                                ApiLasSessionIdType SessionIdentifier,
                                                             /*!< Id of session. */
                                ApiLasEntryIndexType StartIndex,
                                                             /*!< Start number
                                                                [0-0x3FFF] where:
                                                                0: Last entry in list
                                                                0x1 - 0x3FFF: Entry number
                                                                in list */
                                rsuint8 NumberOfEntries,     /*!< Number of requested
                                                                entries [0x1-0x7F] */
                                ApiLasReadDirectionType ReadDirection,
                                                             /*!< This enum defines the
                                                                direction of received list
                                                                entries. */
                                ApiLasReadStatusType ReadStatus,
                                                             /*!< Flag for requesting
                                                                setting/resetting of the
                                                                'Read status' field for all
                                                                read entrie. This field only
                                                                applies to a list having a
                                                                'Read status' field, and is
                                                                otherwise ignored. */
                                rsuint16 InfoElementLength,  /*!< The length of the Data
                                                                Information Element */
                                rsuint8 InfoElement[1]);     /*!< The InfoElement can
                                                                hold a number Info Elements
                                                                placed in the format (ApiInfoElementType):
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Valid Info elements for
                                                                this command:
                                                                API_IE_LAS_REQUESTED_FIELD_I
                                                                DENTIFIERS */

/****************************************************************************
* FUNCTION:      SendApiLasEditEntryReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_EDIT_ENTRY_REQ = 0x5508
****************************************************************************/
void SendApiLasEditEntryReq ( RosTaskIdType Src,
                              ApiLasSessionIdType SessionIdentifier,
                                                             /*!< Id of session. */
                              ApiLasEntryIdType EntryIdentifier,
                                                             /*!< Id of entry. */
                              rsuint16 InfoElementLength,    /*!< The length of the Data
                                                                Information Element */
                              rsuint8 InfoElement[1]);       /*!< The InfoElemen can
                                                                hold a number Info Elements
                                                                placed in the format (ApiInfoElementType):
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Valid Info elements for
                                                                this command:
                                                                API_IE_LAS_REQUESTED_FIELD_I
                                                                DENTIFIERS */

/****************************************************************************
* FUNCTION:      SendApiLasSaveEntryReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_SAVE_ENTRY_REQ = 0x550A
****************************************************************************/
void SendApiLasSaveEntryReq ( RosTaskIdType Src,
                              ApiLasSessionIdType SessionIdentifier,
                                                             /*!< Id of session. */
                              ApiLasEntryIdType EntryIdentifier,
                                                             /*!< Id of entry. If 0
                                                                entry is new and no
                                                                identifier has been assigned
                                                                yet. */
                              rsuint16 InfoElementLength,    /*!< The length of the Data
                                                                Information Element */
                              rsuint8 InfoElement[1]);       /*!< The InfoElemen can
                                                                hold a number Info Elements
                                                                placed in the format (ApiInfoElementType):
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Valid Info elements:
                                                                See section 4 for available
                                                                info elements. */

/****************************************************************************
* FUNCTION:      SendApiLasDeleteEntryReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DELETE_ENTRY_REQ = 0x550C
****************************************************************************/
void SendApiLasDeleteEntryReq ( RosTaskIdType Src,
                                ApiLasSessionIdType SessionIdentifier,
                                                             /*!< Id of session. */
                                ApiLasEntryIdType EntryIdentifier);
                                                             /*!< Id of entry.[0x1 -
                                                                0x3FFF] */

/****************************************************************************
* FUNCTION:      SendApiLasDeleteListReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DELETE_LIST_REQ = 0x550E
****************************************************************************/
void SendApiLasDeleteListReq ( RosTaskIdType Src,
                               ApiLasSessionIdType SessionIdentifier);
                                                             /*!< Id of session. */

/****************************************************************************
* FUNCTION:      SendApiLasSearchEntriesReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_SEARCH_ENTRIES_REQ = 0x5510
****************************************************************************/
void SendApiLasSearchEntriesReq ( RosTaskIdType Src,
                                  ApiLasSessionIdType SessionIdentifier,
                                                             /*!< Id of session. */
                                  ApiLasSearchOptionType SearchOption,
                                                             /*!< Option that should be
                                                                used in search */
                                  ApiLasSearchCaseOptionType SearchCaseOption,
                                                             /*!< Case option that
                                                                should be used in search */
                                  rsuint8 NumberOfEntries,   /*!< Number of requested
                                                                entries [0x1 - 0x7F] */
                                  ApiLasReadDirectionType ReadDirection,
                                                             /*!< This enum defines the
                                                                direction of received list
                                                                entries. */
                                  ApiLasReadStatusType ReadStatus,
                                                             /*!< Flag for requesting
                                                                setting/resetting of the
                                                                'Read status' field for all
                                                                read entrie. This field only
                                                                applies to a list having a
                                                                'Read status' field, and is
                                                                otherwise ignored. */
                                  rsuint16 InfoElementLength,
                                                             /*!< The length of the Data
                                                                Information Element */
                                  rsuint8 InfoElement[1]);   /*!< The InfoElement can
                                                                hold a number Info Elements
                                                                placed in the format (ApiInfoElementType):
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Valid Info elements for
                                                                this command:
                                                                API_IE_LAS_SEARCH_TEXT
                                                                API_IE_LAS_REQUESTED_FIELD_I
                                                                DENTIFIERS */

/****************************************************************************
* FUNCTION:      SendApiLasGetFieldProtectionReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_GET_FIELD_PROTECTION_REQ = 0x5582
****************************************************************************/
void SendApiLasGetFieldProtectionReq ( RosTaskIdType Src,
                                       ApiLasListIdType ListIdentifier);
                                                             /*!< Id of list. */

/****************************************************************************
* FUNCTION:      SendApiLasSetFieldProtectionReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_SET_FIELD_PROTECTION_REQ = 0x5584
****************************************************************************/
void SendApiLasSetFieldProtectionReq ( RosTaskIdType Src,
                                       ApiLasListIdType ListIdentifier,
                                                             /*!< Id of list. */
                                       rsuint16 InfoElementLength,
                                                             /*!< The length of the Data
                                                                Information Element */
                                       rsuint8 InfoElement[1]);
                                                             /*!< The InfoElement can
                                                                hold a number Info Elements
                                                                placed in the format (ApiInfoElementType):
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Valid Info elements for
                                                                this command:
                                                                API_IE_LAS_DISABLED_FIELDS
                                                                API_IE_LAS_EDITABLE_FIELDS
                                                                API_IE_LAS_NON_EDITABLE_FIELDS
                                                                API_IE_LAS_PIN_PROTECTED_FIE
                                                                LDS */

/****************************************************************************
* FUNCTION:      SendApiLasGetLockedEntriesListReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_GET_LOCKED_ENTRIES_LIST_REQ = 0x5586
****************************************************************************/
void SendApiLasGetLockedEntriesListReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiLasDbClearReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_CLEAR_REQ = 0x55C0
****************************************************************************/
void SendApiLasDbClearReq ( RosTaskIdType Src,
                            ApiLasSessionIdType SessionIdentifier,
                                                             /*!< Id of session. */
                            ApiLasListIdType ListIdentifier);
                                                             /*!< Id of list to clear.
                                                                Any list can be cleared from
                                                                any session.  
                                                                If API_LAS_SUPPORTED_LISTS
                                                                is selected all lists are
                                                                cleared */

/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APILAS_H */


