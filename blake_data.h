#ifndef BLAKE_DATA_H
#define BLAKE_DATA_H

#include <stdint.h>

#define ROTATE_LEFT(x, y) (((x) << (y)) | ((x) >> (32 -(y))))
#define ROTATE_RIGHT(x, y) (((x) >> (y)) | ((x) << (32 -(y))))

/* Takes a pointer to uin8_t array and converts it to an 32bits big endian*/
#define UINT8_TO_32_BIG_ENDIAN(p) \
  ( ( uint32_t )( ( p )[0] ) << 24 ) | \
  ( ( uint32_t )( ( p )[1] ) << 16 ) | \
  ( ( uint32_t )( ( p )[2] ) <<  8 ) | \
  ( ( uint32_t )( ( p )[3] ) <<  0 ) )

/* Takes a 32bits value and assign to uint8_t array changing endiannes*/
#define INT32_TO_UINT8_BIG_ENDIAN(p, v) \
  (p)[0] = ( uint8_t )((v) >> 24); \
  (p)[1] = ( uint8_t )((v) >> 16); \
  (p)[2] = ( uint8_t )((v) >>  8); \
  (p)[3] = ( uint8_t )((v) >>  0);


#endif /*BLAKE_DATA_H*/
