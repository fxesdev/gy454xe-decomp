This is a **very WIP** decompilation of the Casio fx-570/991ES PLUS (`GY454X VerE`, `SUM 8929`) real calculator ROM.

## Why this ROM?
Casio fx-570/991ES PLUS VerE real ROM was chosen because it has been very well documented.
After this ROM is fully decompiled, the codebase may be expanded to include features in other GY models that are not in the fx-570/991ES PLUS (e.g. `VERIF` mode), and potentially expand the code to other Casio model families.

## General information
The fx-570/991ES PLUS uses the nX-U8/100 architecture by ROHM Co., Ltd.
The code is a mix of hand-written U8 assembly code, ANSI-C code compiled to U8 assembly with the **CCU8** compiler from the U8/U16 Development Tools, U8 implementations for some C library functions and the MCU's entry/startup code.

## About the code
In order to create an accurate decompilation, the code will need to be separated into 4 categories:
1. **Code written by Casio in ANSI-C** (`main`, diagnostic, reset_all, etc): will be decompiled into **ANSI-C** code that can be compiled with CCU8 to produce matching assembly.
2. **Code written by Casio in ASM**: will be disassembled, reverse engineered and made to work with RASU8.
3. **Code from the SDK .lib files** (memset, etc): will not need to be decompiled. SDK code can be linked using the `/CC` option of RLU8.
4. **Code from the SDK MCU-specific files** (startup code, etc): will have to be recreated using existing files for other U8 MCUs, as the files for the specific MCU Casio used is not in the development tools.

The code was compiled with the LARGE memory model and NEAR data model options.

## Building
Run `build.bat` in the root directory. Note that a successful build is NOT guaranteed.

Also included is a compiled version of [Hex2bin](https://sourceforge.net/projects/hex2bin/) by Jacques Pelletier, version v1.0.1.
