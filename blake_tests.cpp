#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "blake.h"
#include <string.h>
#include <stdio.h>

// https://stackoverflow.com/questions/17261798/converting-a-hex-string-to-a-byte-array
std::vector< unsigned char > ConvertHexToBytes( const std::string& hexString )
{
   std::vector< unsigned char > bytes;

   for( size_t i = 0; i < hexString.size(); i += 2 )
   {
      auto byteString = hexString.substr( i, 2 );
      auto byte = static_cast< char >( strtol( byteString.c_str(), NULL, 16 ) );
      bytes.push_back( byte );
   }

   return bytes;
}



TEST_CASE( "[empty]", "[blake]" )
{
  unsigned char expected_output[] = {
    0x71, 0x6f, 0x6e, 0x86, 0x3f, 0x74, 0x4b, 0x9a, 0xc2, 0x2c, 0x97, 0xec, 0x7b, 0x76, 0xea, 0x5f, 
    0x59, 0x08, 0xbc, 0x5b, 0x2f, 0x67, 0xc6, 0x15, 0x10, 0xbf, 0xc4, 0x75, 0x13, 0x84, 0xea, 0x7a };

  const char message[] = "";
  const auto message_size = sizeof(message) - 1;
  uint8_t output[32] = { 0 };

  blake_hash( message, message_size, ( char* ) output );

  REQUIRE( !memcmp( expected_output, output, sizeof(output) - 1 ) );

}

TEST_CASE( "[abc]", "[blake]" )
{
  unsigned char expected_output[] = { 0x18, 0x33, 0xa9, 0xfa, 0x7c, 0xf4, 0x08, 0x6b, 0xd5, 0xfd, 0xa7, 0x3d, 0xa3, 0x2e, 
                                      0x5a, 0x1d, 0x75, 0xb4, 0xc3, 0xf8, 0x9d, 0x5c, 0x43, 0x63, 0x69, 0xf9, 0xd7, 0x8b, 0xb2, 0xda, 0x5c, 0x28 };


  const char message[] = "abc";
  const auto message_size = sizeof(message) - 1;
  char output[32] = { 0 };

  blake_hash( message, message_size, output );

  REQUIRE( !memcmp( expected_output, output, sizeof(output) - 1 ) );

}

TEST_CASE( "[loremIpsum]", "[blake]" )
{
   unsigned char expected_output[] = {
      0x8a, 0xa7, 0xa8, 0x70, 0xdb, 0x62, 0x0d, 0x53, 0xcf, 0x5f, 0x05, 0xfd, 0xd0, 0xeb, 0x02, 0xb0, 
      0x09, 0x20, 0xfe, 0x93, 0xfc, 0xa8, 0x57, 0x87, 0xde, 0xb8, 0xf0, 0x6d, 0xb1, 0x31, 0xab, 0xfc };


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

TEST_CASE( "[QUICKFOX]", "[blake]" )
{
   auto expected_output = ConvertHexToBytes( "7576698ee9cad30173080678e5965916adbb11cb5245d386bf1ffda1cb26c9d7" );
   const char message[] = "The quick brown fox jumps over the lazy dog";

   const auto message_size = sizeof( message ) - 1;
   char output[ 32 ] = { 0 };

   blake_hash( message, message_size, output );

   REQUIRE( !memcmp( expected_output.data(), output, sizeof( output ) - 1 ) );
}
