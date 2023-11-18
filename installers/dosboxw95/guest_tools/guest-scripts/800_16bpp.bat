@echo off
mkdir C:\WINDOWS\TEMP
echo REGEDIT4 > C:\WINDOWS\TEMP\set800.reg
echo. >> C:\WINDOWS\TEMP\set800.reg
echo [HKEY_LOCAL_MACHINE\Config\0001\Display\Settings\] >> C:\WINDOWS\TEMP\set800.reg
echo "fonts.fon"="vgasys.fon" >> C:\WINDOWS\TEMP\set800.reg
echo "fixedfon.fon"="vgafix.fon" >> C:\WINDOWS\TEMP\set800.reg
echo "oemfonts.fon"="vgaoem.fon" >> C:\WINDOWS\TEMP\set800.reg
echo "DPILogicalX"="96" >> C:\WINDOWS\TEMP\set800.reg
echo "DPILogicalY"="96" >> C:\WINDOWS\TEMP\set800.reg
echo "DPIPhysicalX"="96" >> C:\WINDOWS\TEMP\set800.reg
echo "DPIPhysicalY"="96" >> C:\WINDOWS\TEMP\set800.reg
echo "BitsPerPixel"="16" >> C:\WINDOWS\TEMP\set800.reg
echo "Resolution"="800,600" >> C:\WINDOWS\TEMP\set800.reg
echo "DisplayFlags"="0" >> C:\WINDOWS\TEMP\set800.reg

C:\WINDOWS\REGEDIT.EXE /L:C:\WINDOWS\SYSTEM.DAT /R:C:\WINDOWS\USER.DAT C:\WINDOWS\TEMP\set800.reg
del C:\WINDOWS\TEMP\set800.reg