This is a **very WIP** decompilation of the Casio fx-570/991ES PLUS (`GY454X VerE`, `SUM 8928`) real calculator ROM.

## Why this ROM?
Casio fx-570/991ES PLUS VerE real ROM was chosen because it has been very well documented.
After this ROM is fully decompiled, the codebase may be expanded to include features in other GY models that are not in the fx-570/991ES PLUS (e.g. `VERIF` mode), and potentially expand the code to other Casio model families.

## General information
The fx-570/991ES PLUS uses the nX-U8/100 architecture by Lapis Technology.
The code is a mix of hand-written U8 assembly code, ANSI-C code compiled to U8 assembly with the **CCU8** compiler from the Lapis U8/U16 Development Tools, U8 implementations for some C library functions and the MCU's entry/startup code.

## About the code
In order to create an accurate decompilation, the code will need to be separated into 4 categories:
1. **Code written by Casio in ANSI-C** (`main`, diagnostic, reset_all, etc): will be decompiled by hand into **ANSI-C** code that can be compiled with CCU8 to produce matching assembly.
2. **Code written by Casio in ASM**: will be disassembled and reverse engineered.
3. **Code from the SDK .lib files written by Lapis** (memset, etc): will most likely not need to be decompiled.
4. **Code from the SDK MCU-specific files written by Lapis** (startup code, etc): will have to be recreated using existing files for other U8 MCUs, as the files for the specific MCU Casio used is not in the development tools.

The code was compiled with the LARGE memory model and NEAR data model options.

## Building
At this time, there is no provided way to build this code, however you can (try to) build it yourself with CCU8 and the MACU8 Assembler Package in the development tools.
The code is not guaranteed to build successfully and will not work yet.
