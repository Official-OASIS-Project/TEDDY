# TEDDY - Transducer Electronic Datasheet Decryption Yielder

## Current capabilities in Version 0.4

### Supported TEDS rom device types

* DS2430A (0x14)
* DS2431 (0x2D)

### Supported TEDS versions & templates

* v.0.9 Legacy
  * Accelerometer (Template ID 0)

### Tested devices
| Manufacturer | Model number | ROM device type | TEDS version | Template ID | Read serial number | Read sensor direction | Read sensitivity | Read transducer type | Read Manufacturer | Read calibration date |
|--------------|--------------|-----------------|--------------|-------------|--------------------|-----------------------|------------------|----------------------|-------------------|-----------------------|
| **KISTLER** | 8688A50T | DS2430A (0x14) | v.0.9 | 0 | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| **KISTLER** | 8688A50T | DS2431 (0x2D)  | v.0.9 | 0 | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| **KISTLER** | 8762A10T | DS2430A (0x14) | v.0.9 | 0 | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |

## Links

Convert calibration date: https://www.topster.net/calendar/tagerechner.php?styp=datum&smonat=1&stag=1&sjahr=1998&emonat=&etag=&ejahr=&typ=dazu&subDazu=%2B&dazu=0

IEEE Manufacturer IDs: https://regauth.standards.ieee.org/standards-ra-web/pub/view.html#registries
