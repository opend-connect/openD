/**
* @code
*  ___ _____ _   ___ _  _____ ___  ___  ___ ___
* / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
* \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
* |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
* embedded.connectivity.solutions.==============
* @endcode
*
* @file
* @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
*/


#include "CmndLib_UserImpl_StringUtil.h"
#include <string.h>
#include <stdio.h>

int p_CmndLib_UserImpl_strnlen( const char* str, size_t maxlen )
{
	ARGUSED( maxlen );
	return strlen( str );
}

void p_CmndLib_UserImpl_strncat( char* dst, size_t maxlen, const char* src, size_t count )
{
    strcat( dst, src );
}

int p_CmndLib_UserImpl_snprintf( char* dst, size_t maxlen, const char* format, ... )
{
	int RetCode;
	va_list args;
	va_start(args, format);

	RetCode = vsnprintf( dst, maxlen, format, args );

	va_end(args);
	return RetCode;
}
