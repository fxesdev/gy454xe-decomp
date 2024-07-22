@echo off
if not exist build md build
call C:\LAPIS\LEXIDE\BuildTools\Ver.20231124\setVer20231124.bat
ccu8 /SD /TML610CASESplus /Om /Orp /Zc /Fabuild\main.asm /Lv /ML src\main.c
cd build
xcopy ..\src\startup.asm /y
rasu8 main.asm /G /SD
rasu8 startup.asm /G /SD
rlu8 /CC /SD main startup;
ohu8 main.abs;
..\assets\hex2bin main.hex
cd..
