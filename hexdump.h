#ifndef __HEX_DUMP_H__
#define __HEX_DUMP_H__

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void hex_dump (FILE* f, void *addr, int len);
#define HEX_DUMP( ... )		hex_dump(stdout, __VA_ARGS__)


#ifdef __cplusplus
}
#endif

#endif /* __HEX_DUMP_H__ */
