# Architecture support

uDevkit-SDK supports for a large range of MCU families.

Each sub directory contains a family or a subfamily that can include a parent family.

Compiler specific, compilation flags or core dependent definition are contained in these support.

## Microchip

[microchip](microchip/README.md)

### 16 bits

835 devices on May 2025.

|Family name|Parent family|Device count|
|-----------|-------------|-----------:|
|[PIC16b](pic16b/README.md)|[microchip](microchip/README.md)|835|
|[dsPIC33AK](../dspic33ak/README.md)|[pic16b](pic16b/README.md)| 48|
|[PIC32AK](../pic32ak/README.md)    |[pic16b](pic16b/README.md)|  9|
|[PIC32MK](../pic32mk/README.md)    |[pic16b](pic16b/README.md)| 31|
|[PIC32MM](../pic32mm/README.md)    |[pic16b](pic16b/README.md)| 21|
|[PIC32MX](../pic32mx/README.md)    |[pic16b](pic16b/README.md)|120|
|[PIC32MZDA](../pic32mzda/README.md)|[pic16b](pic16b/README.md)| 72|
|[PIC32MZEC](../pic32mzec/README.md)|[pic16b](pic16b/README.md)| 24|
|[PIC32MZEF](../pic32mzef/README.md)|[pic16b](pic16b/README.md)| 48|

### 32 bits

373 devices on May 2025.

|Family name|Parent family|Device count|
|-----------|-------------|-----------:|
|[PIC32](pic32/README.md)|[microchip](microchip/README.md)|373|
|[dsPIC33AK](../dspic33ak/README.md)|[pic32](pic32/README.md)| 48|
|[PIC32AK](../pic32ak/README.md)    |[pic32](pic32/README.md)|  9|
|[PIC32MK](../pic32mk/README.md)    |[pic32](pic32/README.md)| 31|
|[PIC32MM](../pic32mm/README.md)    |[pic32](pic32/README.md)| 21|
|[PIC32MX](../pic32mx/README.md)    |[pic32](pic32/README.md)|120|
|[PIC32MZDA](../pic32mzda/README.md)|[pic32](pic32/README.md)| 72|
|[PIC32MZEC](../pic32mzec/README.md)|[pic32](pic32/README.md)| 24|
|[PIC32MZEF](../pic32mzef/README.md)|[pic32](pic32/README.md)| 48|

## Simulator

|Family name|Parent family|
|-----------|-------------|
|[simulator](simulator/README.md)| - |
