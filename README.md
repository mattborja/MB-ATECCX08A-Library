# MB-ATECCX08A-Library
Status: **Development**

![01 Platform](https://github.com/mattborja/MB-ATECCX08A-Library/assets/3855027/b25a6b15-98f6-4a2e-85b1-e71559ede970)

Arduino C development library and program interface for ATECCX08A by [Matt Borja](https://mattborja.dev/).

## Purpose
To canonicalize a subset of ongoing research and development in cryptographic applications and hardware-based implementations. The attached libraries are provided with their respective program interfaces for testing and are intended for academic use only (see LICENSE).

## Platform (ATECCX08A)
### Program Interface (Serial)
![02 IDE](https://github.com/mattborja/MB-ATECCX08A-Library/assets/3855027/900fdd58-c6db-4e54-99f3-648aca6d28e5)

Program accepts fully parameterized command string as a sequence of hexadecimal characters over serial input, as shown in the 2-part SHA-256 demo below:

![03 Full SHA Demo Readout](https://github.com/mattborja/MB-ATECCX08A-Library/assets/3855027/b44db93b-28c9-4aed-81ca-7c0e910e2a43)

For additional examples, see [TestVectors.csv](/TestVectors.csv).

### Write Procedures (Zone: Config)
Note: The following procedures demonstrates modifying factory settings found for SlotConfig<1> (`0x8320`) to specifically allow `WriteAlways` (`0x8300`) for academic and testing purposes only and are reversible so long as the Configuration zone remains unlocked. Please refer to the ATECC508A Complete Datasheet for SlotConfig settings available for your specific application.

1) Determine bytes of Config zone to be updated: `20-21` (SlotConfig<1>)

2) Determine new configuration to set (LSB first as seen on the I2C bus):
   - `0x8320` (factory settings: IsSecret, -EncryptRead, -LimitedUse, -NoMac, ECDH master secret ignored, -ECDH, Internal signatures enabled, External signatures enabled; WriteNever, KeyStoreOK, NoWriteKeyID)
   - `0x8300` (personalized for TESTING ONLY: IsSecret, -EncryptRead, -LimitedUse, -NoMac, ECDH master secret ignored, -ECDH, Internal signatures enabled, External signatures enabled; WriteAlways, KeyStoreNOTOK, NoWriteKeyID)

3) Derive address within Configuration zone: `0x00` (P1: Config zone), `0x0005` (P2: block 0, offset 5)

4) Use the Program Interface to Read existing values and verify zone addressing is correct: `50 02 00 0005 04 00` (dev: 0x50, read: 4 bytes; zone: Config; block 0; offset: 5; out: 4 bytes; in: 0 bytes; result: `8320 8720`)
   - Important: This preliminary Read operation is necessary to derive the original settings to be reverted if needed.

5) Copy zone address and new setting to Write command (CAUTION: remember to copy existing bytes of unwanted SlotConfig comprising other half of 4-byte write): `50 12 00 0005 01 04 83008720` (dev: 0x50, write: 4 bytes in the clear; zone: Config; block 0: offset: 5; out: 1 byte; in: 4 bytes; data: 0x83008720; result: `00`)

6) Read from interface to verify changes: `50 02 00 0005 04 00` (dev: 0x50, read: 4 bytes; zone: Config; block 0; offset: 5; out: 4 bytes; in: 0 bytes; result: `8300 8720`)

Note: Original settings may be reverted by issuing the same Write command (#5) using the values returned in the prelimiary Read operation (#4).

## Application Notes
- "The ATECC608A has an error in the I2C circuitry, where the device may respond incorrectly under certain conditions" (p.3, [DS40002237A](https://www.mouser.com/pdfDocs/Migrating-from-the-ATECC608A-to-the-ATECC608B-DS40002237A.pdf), Microchip). The issue is resolved in its replacement part, **ATECC608B**.
- "Prior to the configuration zone being locked, the RNG produces a value of `0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00` to facilitate testing." (p. 81, DS20005927A)

## License
See [LICENSE](/LICENSE) within this repository.

## Legal Notice
See [LEGAL.md](/LEGAL.md) within this repository.

## Contact
- Open a [new issue](https://github.com/mattborja/MB-ATECCX08A-Library/issues)
- Send an email to: [mb-ateccx08a-library.area473@passmail.com](mailto:mb-ateccx08a-library.area473@passmail.com)
