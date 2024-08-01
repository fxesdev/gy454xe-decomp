@echo off
if not exist build md build
call C:\LAPIS\LEXIDE\BuildTools\Ver.20231124\setVer20231124.bat
ccu8 /SD /TML610CASESplus /Om /Orp /Zc /Fabuild\main.asm /Lv /ML src\main.c
cd build
xcopy ..\src\*.asm /y
for %%a in (..\src\*.asm) do (
xcopy %%a .
rasu8 %%~nxa /G /SD
)
rlu8 /G /CC /SD rom startup main;
ohu8 main.abs;
..\assets\hex2bin main.hex
cd..
