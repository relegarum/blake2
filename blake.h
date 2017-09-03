#ifndef BLAKE_H
#define BLAKE_H

#include "blake_data.h"
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

int blake( char* const message, size_t message_size, char* output, size_t output_size );

#ifdef __cplusplus
}
#endif


#endif /*BLAKE_H*/
