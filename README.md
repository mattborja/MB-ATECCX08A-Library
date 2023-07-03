# MB-ATECCX08A-Library
Status: **Development**

Arduino C development library and program interface for ATECCX08A by [Matt Borja](https://mattborja.dev/) (PGP: `F30F F4FC 9365 8457 4EE3 2518 3368 8C2E DC08 CD38`).

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
Opcode: `0x1B` (Table 9-4, p. 57, [DS20005927A](https://ww1.microchip.com/downloads/aemDocuments/documents/OTH/ProductDocuments/DataSheets/20005928A.pdf))

Generate a random number.
```bash
ateccx08_cmd@0x50> 501b0000002000
CONNECT_OK

_raw:		501B 0000 0020 00 ...
send:	opcode=0x1B, param1=0x0, param2=0x0, outlen=0x20, datalen=0x0, data=  
result:		status=OK, res=FFFF 0000 FFFF 0000 FFFF 0000 FFFF 0000 FFFF 0000 FFFF 0000 FFFF 0000 FFFF 0000 ...
```

### Test Vectors
See [TestVectors.csv](/TestVectors.csv).

### Application Notes
- "The ATECC608A has an error in the I2C circuitry, where the device may respond incorrectly under certain conditions" (p.3, [DS40002237A](https://www.mouser.com/pdfDocs/Migrating-from-the-ATECC608A-to-the-ATECC608B-DS40002237A.pdf), Microchip). The issue is resolved in its replacement part, **ATECC608B**.
- "Prior to the configuration zone being locked, the RNG produces a value of `0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00` to facilitate testing." (p. 81, DS20005927A)

## License
See [LICENSE](/LICENSE) within this repository.

## Legal Notice
See [LEGAL.md](/LEGAL.md) within this repository.

## Contact
- Open a [new issue](https://github.com/mattborja/MB-ATECCX08A-Library/issues)
- Send an email to: [mb-ateccx08a-library.area473@passmail.com](mailto:mb-ateccx08a-library.area473@passmail.com)
