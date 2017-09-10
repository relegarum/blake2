#include "blake.h"
#include <stdlib.h>
#include <string.h>


const int32_t initial_state[] =
{
  0x6A09E667,
  0xBB67AE85,
  0x3C6EF372,
  0xA54FF53A,
  0x510E527F,
  0x9B05688C,
  0x1F83D9AB,
  0x5BE0CD19
};

const int32_t blake_constants[] =
{
  0x243f6a88,
  0x85a308d3,
  0x13198a2e,
  0x03707344,
  0xa4093822,
  0x299f31d0,
  0x082efa98,
  0xec4e6c89,
  0x452821e6,
  0x38d01377,
  0xbe5466cf,
  0x34e90c6c,
  0xc0ac29b7,
  0xc97c50dd,
  0x3f84d5b5,
  0xb5470917
};

const uint8_t sigma[][16] = 
{
  {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15},
  { 14, 10,  4,  8,  9, 15, 13,  6,  1, 12,  0,  2, 11,  7,  5,  3},
  { 11,  8, 12,  0,  5,  2, 15, 13, 10, 14,  3,  6,  7,  1,  9,  4},
  {  7,  9,  3,  1, 13, 12, 11, 14,  2,  6,  5, 10,  4,  0, 15,  8},
  {  9,  0,  5,  7,  2,  4, 10, 15, 14,  1, 11, 12,  6,  8,  3, 13},
  {  2, 12,  6, 10,  0, 11,  8,  3,  4, 13,  7,  5, 15, 14,  1,  9},
  { 12,  5,  1, 15, 14, 13,  4, 10,  0,  7,  6,  3,  9,  2,  8, 11},
  { 13, 11,  7, 14, 12,  1,  3,  9,  5,  0, 15,  4,  8,  6,  2, 10},
  {  6, 15, 14,  9, 11,  3,  0,  8, 12,  2, 13,  7,  1,  4, 10,  5},
  { 10,  2,  8,  4,  7,  6,  1,  5, 15, 11,  9, 14,  3, 12, 13,  0},
  {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15},
  { 14, 10,  4,  8,  9, 15, 13,  6,  1, 12,  0,  2, 11,  7,  5,  3},
  { 11,  8, 12,  0,  5,  2, 15, 13, 10, 14,  3,  6,  7,  1,  9,  4},
  {  7,  9,  3,  1, 13, 12, 11, 14,  2,  6,  5, 10,  4,  0, 15,  8}
};


typedef struct blake_struct
{
  uint32_t hash_state[8];
  uint32_t message_block[16];
  uint32_t initial_values[16];
  uint32_t salt[4];
  uint32_t count[2];
  uint32_t states[16];
} blake_ctx;

static inline void blake_g(uint32_t *a,
                           uint32_t *b,
                           uint32_t *c,
                           uint32_t *d,
                           uint32_t const factor1,
                           uint32_t const factor2 )
{
  /**a += *b + ( memory_block1 ^ constant2 );*/
  *a += *b + factor1;
  *d = ROTATE_RIGHT( ( *d ^ *a ), 16 );
  *c += *d;
  *b = ROTATE_RIGHT( ( *b ^ *c ), 12 );
  /**a += *b + ( memory_block2  ^ constant2 );*/
  *a += *b + factor2;
  *d = ROTATE_RIGHT( ( *d ^ *a ), 8 );
  *c += *d;
  *b = ROTATE_RIGHT( ( *b ^ *c ), 7 );
}


static void blake_prepare( blake_ctx* ctx, const uint8_t *block )
{
  ctx->states[ 0] = ctx->hash_state[0];
  ctx->states[ 1] = ctx->hash_state[1];
  ctx->states[ 2] = ctx->hash_state[2];
  ctx->states[ 3] = ctx->hash_state[3];
  ctx->states[ 4] = ctx->hash_state[4];
  ctx->states[ 5] = ctx->hash_state[5];
  ctx->states[ 6] = ctx->hash_state[6];
  ctx->states[ 7] = ctx->hash_state[7];
  ctx->states[ 8] = ctx->salt[0] ^ blake_constants[0];
  ctx->states[ 9] = ctx->salt[1] ^ blake_constants[1];
  ctx->states[10] = ctx->salt[2] ^ blake_constants[2];
  ctx->states[11] = ctx->salt[3] ^ blake_constants[3];
  ctx->states[12] = ctx->count[0] ^ blake_constants[4];
  ctx->states[13] = ctx->count[0] ^ blake_constants[5];
  ctx->states[14] = ctx->count[1] ^ blake_constants[6];
  ctx->states[15] = ctx->count[1] ^ blake_constants[7];

  for( int i = 0; i < 16; ++i )
    ctx->message_block[i] = UINT8_TO_32_BIG_ENDIAN( (block + ( i * 4 )) );
}

static void blake_init( blake_ctx* ctx )
{
  memset( ctx, 0, sizeof( *ctx ) );
  ctx->hash_state[0] = initial_state[0];
  ctx->hash_state[1] = initial_state[1];
  ctx->hash_state[2] = initial_state[2];
  ctx->hash_state[3] = initial_state[3];
  ctx->hash_state[4] = initial_state[4];
  ctx->hash_state[5] = initial_state[5];
  ctx->hash_state[6] = initial_state[6];
  ctx->hash_state[7] = initial_state[7];
}

static inline void blake_round( blake_ctx* const ctx, const uint32_t round )
{
  blake_g(&ctx->states[0], &ctx->states[4], &ctx->states[ 8], &ctx->states[12], G_FACTORS( round, 0, ctx, blake_constants, sigma));
  blake_g(&ctx->states[1], &ctx->states[5], &ctx->states[ 9], &ctx->states[13], G_FACTORS( round, 1, ctx, blake_constants, sigma));
  blake_g(&ctx->states[2], &ctx->states[6], &ctx->states[10], &ctx->states[14], G_FACTORS( round, 2, ctx, blake_constants, sigma));
  blake_g(&ctx->states[3], &ctx->states[7], &ctx->states[11], &ctx->states[15], G_FACTORS( round, 3, ctx, blake_constants, sigma));


  blake_g(&ctx->states[0], &ctx->states[5], &ctx->states[10], &ctx->states[15], G_FACTORS( round, 4, ctx, blake_constants, sigma));
  blake_g(&ctx->states[1], &ctx->states[6], &ctx->states[11], &ctx->states[12], G_FACTORS( round, 5, ctx, blake_constants, sigma));
  blake_g(&ctx->states[2], &ctx->states[7], &ctx->states[ 8], &ctx->states[13], G_FACTORS( round, 6, ctx, blake_constants, sigma));
  blake_g(&ctx->states[3], &ctx->states[4], &ctx->states[ 9], &ctx->states[14], G_FACTORS( round, 7, ctx, blake_constants, sigma));
}

static void blake_compress( blake_ctx* const ctx, const uint8_t* block)
{
  blake_prepare( ctx, block );
  for( int round = 0; round < 14; ++round )
  {
    blake_round( ctx, round );
  }
}

static void blake_end( blake_ctx* const ctx )
{

  /*Very last*/
  ctx->hash_state[0] = ctx->hash_state[0] ^ ctx->salt[0] ^ ctx->states[0] ^ ctx->states[ 8];
  ctx->hash_state[1] = ctx->hash_state[1] ^ ctx->salt[1] ^ ctx->states[1] ^ ctx->states[ 9];
  ctx->hash_state[2] = ctx->hash_state[2] ^ ctx->salt[2] ^ ctx->states[2] ^ ctx->states[10];
  ctx->hash_state[3] = ctx->hash_state[3] ^ ctx->salt[3] ^ ctx->states[3] ^ ctx->states[11];
  ctx->hash_state[4] = ctx->hash_state[4] ^ ctx->salt[0] ^ ctx->states[4] ^ ctx->states[12];
  ctx->hash_state[5] = ctx->hash_state[5] ^ ctx->salt[1] ^ ctx->states[5] ^ ctx->states[13];
  ctx->hash_state[6] = ctx->hash_state[6] ^ ctx->salt[2] ^ ctx->states[6] ^ ctx->states[14];
  ctx->hash_state[7] = ctx->hash_state[7] ^ ctx->salt[3] ^ ctx->states[7] ^ ctx->states[15];
}

int blake_hash(const char* const message,
               const size_t message_size,
               char* output )
{
  blake_ctx ctx[1];
  blake_init( ctx );
  blake_compress( ctx );
  blake_end( ctx );


}
