# MB-ATECCX08A-Library
Arduino C development library and program interface for ATECCX08A by [Matt Borja](https://mattborja.dev/).

## Purpose
To canonicalize a subset of ongoing research and development in cryptographic applications and hardware-based implementations. The attached libraries are provided with their respective program interfaces for testing and are intended for academic use only (see LICENSE).

## ATECCX08A
### Program Interface (Serial)
Program accepts fully parameterized command string as a sequence of hexadecimal characters over serial input, deserializing as follows:
```c
/*
 * Executes arbitrary commands against ATECCX08 at I2C address specified
 * input: [addr:1][opcode:1][param1:1][param2:2][outlen:1][datalen:1][data:datalen] (datalen=0-249)
 */
bool ateccx08_cmd(uint8_t input[256], ...) { ... }
```

#### Examples
##### `Random()`
Opcode: `0x1B` (Table 9-4, p. 57, DS20005927A)

Generate a random number.
```bash
ateccx08_cmd@0x50> 501b0000002000
CONNECT_OK

_raw:		501B 0000 0020 00 ...
send:	opcode=0x1B, param1=0x0, param2=0x0, outlen=0x20, datalen=0x0, data=  
result:		status=OK, res=FFFF 0000 FFFF 0000 FFFF 0000 FFFF 0000 FFFF 0000 FFFF 0000 FFFF 0000 FFFF 0000 ...
```

### Test Vectors
| Input                                            | Result                                                                                           | Description                                                                | Last tested |
|--------------------------------------------------|--------------------------------------------------------------------------------------------------|----------------------------------------------------------------------------|-------------|
| `501b0000002000`                                 | `status=OK, res=FFFF 0000 FFFF 0000 FFFF 0000 FFFF 0000 FFFF 0000 FFFF 0000 FFFF 0000 FFFF 0000` | `Random()`                                                                 | 7/1/2023    |
| `..........0110000102030405060708090a0b0c0d0e0f` | `status=OK, res=0001 0203 0405 0607 0809 0a0b 0c0d 0e0f`                                         | AES-128 key vector (C.1, FIPS-197) (ATECC608A only; NDA, see LEGAL.md)     | 7/1/2023    |
| `..........101000112233445566778899aabbccddeeff` | `status=OK, res=69c4 e0d8 6a7b 0430 d8cd b780 70b4 c55a`                                         | AES-128 encrypt vector (C.1, FIPS-197) (ATECC608A only; NDA, see LEGAL.md) | 7/1/2023    |
| `..........101069c4e0d86a7b0430d8cdb78070b4c55a` | `status=OK, res=0011 2233 4455 6677 8899 aabb ccdd eeff`                                         | AES-128 decrypt vector (C.1, FIPS-197) (ATECC608A only; NDA, see LEGAL.md) | 7/1/2023    |

### Application Notes
- "The ATECC608A has an error in the I2C circuitry, where the device may respond incorrectly under certain conditions" (p.3, DS40002237A, Microchip). The issue is resolved in its replacement part, **ATECC608B**.
- "Prior to the configuration zone being locked, the RNG produces a value of `0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00` to facilitate testing." (p. 81, DS20005927A)

## License
See [LICENSE](/LICENSE) within this repository.

## Legal Notice
See [LEGAL.md](/LEGAL.md) within this repository.

## Contact
- Open a [new issue](https://github.com/mattborja/MB-ATECCX08A-Library/issues)
- Send an email to: [mb-ateccx08a-library.area473@passmail.com](mailto:mb-ateccx08a-library.area473@passmail.com)
