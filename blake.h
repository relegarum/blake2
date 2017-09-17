#ifndef BLAKE_H
#define BLAKE_H

#include "blake_data.h"
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int blake_hash( const char* const message, const size_t message_size, char output[32] );

#ifdef __cplusplus
}
#endif


#endif /*BLAKE_H*/
