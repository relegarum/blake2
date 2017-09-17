#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "blake.h"
#include <string.h>



TEST_CASE( "[empty]", "[blake]" )
{
  unsigned char expected_output[] = {
    0x71, 0x6f, 0x6e, 0x86, 0x3f, 0x74, 0x4b, 0x9a, 0xc2, 0x2c, 0x97, 0xec, 0x7b, 0x76, 0xea, 0x5f, 
    0x59, 0x08, 0xbc, 0x5b, 0x2f, 0x67, 0xc6, 0x15, 0x10, 0xbf, 0xc4, 0x75, 0x13, 0x84, 0xea, 0x7a };

  const char message[] = "";
  const auto message_size = sizeof(message) - 1;
  char output[32] = { 0 };

  blake_hash( message, message_size, output );

  REQUIRE( !memcmp( expected_output, output, sizeof(output) - 1 ) );

}

TEST_CASE( "[abc]", "[blake]" )
{
  unsigned char expected_output[] = {
    0xf7, 0x55, 0xe0, 0x5e, 0x91, 0x59, 0x08, 0x10, 0x06, 0xc7, 0xaf, 0x24, 0xaa, 0x01, 0x47, 0xfc,
    0x45, 0x1c, 0x95, 0xcc, 0x8b, 0x80, 0x22, 0x2b, 0xd2, 0x02, 0x35, 0x80, 0xf5, 0x4b, 0x32, 0x67 };


  const char message[] = "abc";
  const auto message_size = sizeof(message) - 1;
  char output[32] = { 0 };

  blake_hash( message, message_size, output );

  REQUIRE( !memcmp( expected_output, output, sizeof(output) - 1 ) );

}

TEST_CASE( "[loremIpsum]", "[blake]" )
{
   unsigned char expected_output[] = {
     0xf9, 0xbc, 0xf1, 0xf7, 0xef, 0xeb, 0xcd, 0x79, 0x54, 0x64, 0x7b, 0xb4, 0x93, 0x04, 0x16, 0x8f,
     0x53, 0x35, 0x63, 0x8a, 0xa9, 0x91, 0x55, 0x23, 0x0a, 0x61, 0x9a, 0x61, 0x27, 0x04, 0x61, 0x4f};


  const char message[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus a lacus ac metus sollicitudin porttitor."
                         " Donec vestibulum elit eget neque tincidunt, in mollis ipsum iaculis. Integer scelerisque congue dolor et"
                         " finibus. Vestibulum vitae ipsum et eros ullamcorper luctus at id velit. Aenean orci orci, dictum a viverra"
                         " sollicitudin, vulputate in dolor. Proin mollis ac nunc nec pulvinar. Donec at tempus ligula. Donec varius"
                         " turpis vel ex vulputate tempor. Nulla id bibendum erat. Duis vel consequat tortor. Pellentesque habitant"
                         " morbi tristique senectus et netus et malesuada fames ac turpis egestas. Nulla facilisi. Vestibulum ante"
                         " ipsum primis in faucibus orci luctus et ultrices posuere cras amet.";

  const auto message_size = sizeof(message) - 1;
  char output[32] = { 0 };

  blake_hash( message, message_size, output );

  REQUIRE( !memcmp( expected_output, output, sizeof(output) - 1 ) ); 
}
