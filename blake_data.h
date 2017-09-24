#ifndef BLAKE_DATA_H
#define BLAKE_DATA_H

#include <stdint.h>

#define ROTATE_LEFT(x, y) (((x) << (y)) | ((x) >> (32 -(y))))
#define ROTATE_RIGHT(x, y) (((x) >> (y)) | ((x) << (32 -(y))))

/* Takes a pointer to uin8_t array and converts it to an 32bits big endian*/
#define UINT8_TO_32_BIG_ENDIAN(p) \
 ( ( ( uint32_t )( ( p )[0] ) << 24 ) | \
   ( ( uint32_t )( ( p )[1] ) << 16 ) | \
   ( ( uint32_t )( ( p )[2] ) <<  8 ) | \
   ( ( uint32_t )( ( p )[3] ) <<  0 ) )

/* Takes a 32bits value and assign to uint8_t array changing endiannes*/
#define INT32_TO_UINT8_BIG_ENDIAN(p, v) \
  (p)[0] = ( uint8_t )((v) >> 24); \
  (p)[1] = ( uint8_t )((v) >> 16); \
  (p)[2] = ( uint8_t )((v) >>  8); \
  (p)[3] = ( uint8_t )((v) >>  0);

#define G_FACTOR1(round, index, ctx, blake_constants, sigma) \
  ctx->message_block[ sigma[ round ][ 2 * index ] ] ^ blake_constants[ sigma[ round ][ ( 2 * index ) + 1 ] ]

#define G_FACTOR2(round, index, ctx, blake_constants, sigma) \
  ctx->message_block[ sigma[ round ][ ( 2 * index ) + 1 ] ] ^ blake_constants[ sigma[ round ][ 2 * index ] ]

#define G_FACTORS(round, index, ctx, blake_constants, sigma) \
  G_FACTOR1(round, index, ctx, blake_constants, sigma), G_FACTOR2(round, index, ctx, blake_constants, sigma)

#define G(a, b, c, d, factor1, factor2) \
  a += b + factor1;                     \
  d = ROTATE_RIGHT( ( d ^ a ), 16 );    \
  c += d;                               \
  b = ROTATE_RIGHT( ( b ^ c ), 12 );    \
  a += b + factor2;                     \
  d = ROTATE_RIGHT( ( d ^ a ), 8 );     \
  c += d;                               \
  b = ROTATE_RIGHT( ( b ^ c ), 7 );     

#define BLOCK_SIZE 512
#define BLOCK_SIZE_BYTES (BLOCK_SIZE >> 3)

#define SWAP_ENDIANESS_64(val) \
     (((val & 0xff00000000000000ull) >> 56) | \
      ((val & 0x00ff000000000000ull) >> 40) | \
      ((val & 0x0000ff0000000000ull) >> 24) | \
      ((val & 0x000000ff00000000ull) >>  8) | \
      ((val & 0x00000000ff000000ull) <<  8) | \
      ((val & 0x0000000000ff0000ull) << 24) | \
      ((val & 0x000000000000ff00ull) << 40) | \
      ((val & 0x00000000000000ffull) << 56))


#endif /*BLAKE_DATA_H*/
