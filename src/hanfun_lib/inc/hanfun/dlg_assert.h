#ifndef HF_DLG_EXTRA_H
#define HF_DLG_EXTRA_H

/* Custom assert. Report assert error without stopping execution.
 * Fall-back to original assert functionality if DLG_HF_NO_ASSERT not defined
 */
#ifdef DLG_HF_NO_ASSERT

void _dlg_assert (const char*, const char*, int);
#undef assert
#define assert(e)       ((e) ? (void)0 : _dlg_assert(#e, __FILE__, __LINE__))

#else
#include <assert.h>
#endif

#endif /* HF_DLG_EXTRA_H */
