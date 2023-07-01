/*
 * MIT License
 * -----
 * 
 * Copyright (c) 2023 Matt Borja
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * - The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * - THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
 
#include "Helpers.h"

// TODO: Sanitize & release
#include "_Config.h"
#include "_ATECCX08A.h"

void setup()
{
  Serial.begin(SERIAL_BAUD_RATE);
  
  // Required by ATECCX08A.begin(), else board will fail with error: Error Status: 0x80FF013D Code: 317 Module: 255
  Wire.begin();
  Wire.setClock(WIRE_CLOCK_FREQ);
}

/*
 * Executes arbitrary commands against ATECCX08 at I2C address specified
 * input: [addr:1][opcode:1][param1:1][param2:2][outlen:1][datalen:1][data:datalen] (datalen=0-249)
 */
bool ateccx08_cmd(uint8_t input[256], bool debug = false)
{
  Serial.println();

  ATECCX08A atecc;
  uint8_t addr = input[0];

  if (debug)
  {
    Serial.print("ateccx08_cmd@0x");
    Serial.print(addr, HEX);
    Serial.print("> ");
  }

  if (!atecc.begin(addr))
  {
    if (debug)
      Serial.println("CONNECT_FAIL");
    
    return false;
  }

  if (debug)
    Serial.println("CONNECT_OK");

  // ===
  
  uint8_t data[249] = {};
  uint8_t res[128] = {}; // "up to 128 bytes"
  
  uint8_t opcode = input[1];
  uint8_t param1 = input[2];
  uint16_t param2 = ((input[3] << 8) | input[4]);
  size_t outlen = input[5] < 129 ? input[5] : 128;
  size_t datalen = input[6] < 250 ? input[6] : 249;

  memcpy(data, input+7, datalen);

  if (debug)
  {
    Serial.print("_raw:\t\t");
    Helpers::xxd(input, 256);
    
    Serial.print("send:\topcode=0x");
    Serial.print(opcode, HEX);
    Serial.print(", param1=0x");
    Serial.print(param1, HEX);
    Serial.print(", param2=0x");
    Serial.print(param2, HEX);
    Serial.print(", outlen=0x");
    Serial.print(outlen, HEX);
    Serial.print(", datalen=0x");
    Serial.print(datalen, HEX);
    Serial.print(", data=");
    Helpers::xxd(data, datalen);
  }

  // Protocol
  bool status;
  status = atecc.exec(opcode, param1, param2, (datalen > 0 ? data : NULL), datalen, outlen);

  if (status)
    memcpy(res, atecc.res, outlen);

  if (debug)
  {
    Serial.print("result:\t\tstatus=");
    Serial.print(status ? "OK" : "FAIL");
    Serial.print(", res=");
  }

  if (status)
  {
    Helpers::xxd(res, outlen);
    return true;
  }
  
  Serial.println();
  return false;
}

/*
 * Deserializes 512-byte serial input as 256-byte input packet sent directly to ATECCX08 at I2C address specified
 * input: [addr:1][opcode:1][param1:1][param2:2][outlen:1][datalen:1][data:datalen] (datalen:0x00-0xf9)
 *
 * Tested (6/30/23):
 * - 501b0000002000 — Random()
 * - ..........0110000102030405060708090a0b0c0d0e0f - AES-128 key vector (C.1, FIPS-197) (ATECC608A only; NDA, see LEGAL.md)
 * - ..........101000112233445566778899aabbccddeeff - AES-128 encrypt vector (C.1, FIPS-197) (ATECC608A only; NDA, see LEGAL.md)
 * - ..........101069c4e0d86a7b0430d8cdb78070b4c55a - AES-128 decrypt vector (C.1, FIPS-197) (ATECC608A only; NDA, see LEGAL.md)
 *
 * Notes:
 * - "The ATECC608A has an error in the I2C circuitry, where the device may respond incorrectly under certain conditions" (p.3, DS40002237A, Microchip). The issue is resolevd in its replacement part, ATECC608B.
 */
void ateccx08_serial_loop()
{
  while (Serial.available())
  {
    uint8_t line[512] = {};
    uint8_t parsed[256] = {};

    uint8_t count = Serial.readBytes(line, 512);
    Helpers::parse_hex_bytes(parsed, line, 512);

    ateccx08_cmd(parsed, true);
  }
}

void loop() {
  ateccx08_serial_loop();
}
