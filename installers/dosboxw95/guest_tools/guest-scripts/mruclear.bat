@echo off
mkdir C:\WINDOWS\TEMP
echo REGEDIT4 > C:\WINDOWS\TEMP\mruclear.reg
echo. >> C:\WINDOWS\TEMP\mruclear.reg
echo [HKEY_CURRENT_USER\InstallLocationsMRU] >> C:\WINDOWS\TEMP\mruclear.reg
echo "a"="C:\\WIN95" >> C:\WINDOWS\TEMP\mruclear.reg
echo "MRUList"="abc" >> C:\WINDOWS\TEMP\mruclear.reg
echo "b"="C:\\DRIVERS" >> C:\WINDOWS\TEMP\mruclear.reg
echo "c"="A:\\" >> C:\WINDOWS\TEMP\mruclear.reg

C:\WINDOWS\REGEDIT.EXE /L:C:\WINDOWS\SYSTEM.DAT /R:C:\WINDOWS\USER.DAT C:\WINDOWS\TEMP\mruclear.reg
del C:\WINDOWS\TEMP\mruclear.reg