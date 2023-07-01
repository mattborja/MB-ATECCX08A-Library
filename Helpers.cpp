#include "Helpers.h"

void Helpers::xxd(uint8_t *buf, uint16_t len, uint16_t offset)
{
  for (uint16_t i = offset; i < offset+len; i++)
  {
    if (i > 0 && i % 2 == 0)
      Serial.print(' ');
    
    // Note: sprintf("0.2x", bu[fi]) and Serial.printf() do not work to render leading zeros as of 2/5/23
    if (buf[i] < 0x10)
      Serial.print(F("0"));
    
    Serial.print(buf[i], HEX);
  }

  Serial.print("  ");
  for (uint16_t i = offset; i < offset+len; i++)
    Serial.print(0x20 <= buf[i] && buf[i] <= 0x7e ? (char)buf[i] : '.');
  
  Serial.println();
}

uint8_t Helpers::ascii_hex_byte(uint8_t in)
{
  // 0-9
  if (in >= 0x30 && in <= 0x39)
    return in  - 0x30;
  
  // A-F
  if (in >= 0x41 && in <= 0x46)
    return in - 0x37;
  
  // a-f
  if (in >= 0x61 && in <= 0x66)
    return in - 0x57;
  
  return 0;
}


void Helpers::parse_hex_bytes(uint8_t *out, uint8_t *in, uint16_t inputlen)
{
  uint8_t x = 0;
  for (uint16_t i = 0; i < inputlen; i += 2)
    out[x++] = (Helpers::ascii_hex_byte(in[i]) << 4) | Helpers::ascii_hex_byte(in[i+1]); 
}