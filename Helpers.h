#ifndef Helpers_h
#define Helpers_h

#include <Arduino.h>

class Helpers
{
  public:
    /*
     * Serial print helper for printing hex dump of byte array
     */
    static void xxd(uint8_t *buffer, uint16_t len, uint16_t offset = 0);

    /*
     * Converts ASCII byte to raw hexadecimal form (valid values: 0-9, A-F)
     */
    static uint8_t ascii_hex_byte(uint8_t in);

    /*
     * Converts ASCII input array to byte array
     */
    static void parse_hex_bytes(uint8_t *out, uint8_t *in, uint16_t inputlen);
};

#endif