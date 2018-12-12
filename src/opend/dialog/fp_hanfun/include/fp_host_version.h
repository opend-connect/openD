#ifndef FP_HOST_VERSION_H
#define FP_HOST_VERSION_H

#include "fp_git_version.h"

#define ver_xstr(s) ver_str(s)
#define ver_str(s) #s

#ifndef IPBS_452_BUILD
#define BUILD_VERSION ver_xstr(FP_HOST_VERSION_MAJOR) "." \
						ver_xstr(FP_HOST_VERSION_MINOR) "." \
						ver_xstr(FP_HOST_VERSION_INC_BUILD)

#define BUILD_DATE __DATE__ " " __TIME__
#endif


#endif /* FP_HOST_VERSION_H */
