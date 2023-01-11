# Changelog for TEDDY

## Changes in Version 0.4
- Decrypts the transducer manufacturer
- Decrypts the transducer calibration date

## Changes in Version 0.3
- Decrypts the transducer type (model number + model version + model version number)
- Memory optimization

## Changes in Version 0.2
- Decrypts the sensitivity of acceleration sensors with legacy TEDS version 0.9 and template Id 0
- Refactoring to not only include acceleration sensors

## Changes in Version 0.1
- Reads TEDS from devices 0x2D and 0x14 implementing legacy version 0.9 with template Id 0
- Decrypts the serial number of connected sensors