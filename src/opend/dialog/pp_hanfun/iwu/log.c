
#include "log.h"

#include <unistd.h>
#include <alloca.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*!
 * Print a string.
 */
void LogString(const char* fmt, ...)
{
  va_list argptr;
  va_start(argptr, fmt);
  vprintf(fmt, argptr);
  va_end(argptr);
}
