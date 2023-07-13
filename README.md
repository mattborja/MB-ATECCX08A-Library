# MB-ATECCX08A-Library
Status: **Development**

![01 Platform](https://github.com/mattborja/MB-ATECCX08A-Library/assets/3855027/b25a6b15-98f6-4a2e-85b1-e71559ede970)

Arduino C development library and program interface for ATECCX08A by [Matt Borja](https://mattborja.dev/) (PGP: `F30F F4FC 9365 8457 4EE3 2518 3368 8C2E DC08 CD38`).

## Purpose
To canonicalize a subset of ongoing research and development in cryptographic applications and hardware-based implementations. The attached libraries are provided with their respective program interfaces for testing and are intended for academic use only (see LICENSE).

## ATECCX08A
### Program Interface (Serial)
![02 IDE](https://github.com/mattborja/MB-ATECCX08A-Library/assets/3855027/900fdd58-c6db-4e54-99f3-648aca6d28e5)

Program accepts fully parameterized command string as a sequence of hexadecimal characters over serial input, as shown in the 2-part SHA-256 demo below:

![03 Full SHA Demo Readout](https://github.com/mattborja/MB-ATECCX08A-Library/assets/3855027/b44db93b-28c9-4aed-81ca-7c0e910e2a43)

For additional examples, see [TestVectors.csv](/TestVectors.csv).

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
