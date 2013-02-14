#ifndef STDDEF_H
#define STDDEF_H

#ifndef NULL
#define NULL 0L
#endif

#ifndef offsetof
#define offsetof(type, field)  ((size_t) &(((type *) 0)->field) * 16)
#endif

#ifndef _PTRDIFF_T
#define _PTRDIFF_T
typedef long ptrdiff_t;
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long size_t;
#endif
#endif // STDDEF_H
