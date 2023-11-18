@echo off
mkdir C:\WINDOWS\TEMP
echo REGEDIT4 > C:\WINDOWS\TEMP\set1024.reg
echo. >> C:\WINDOWS\TEMP\set1024.reg
echo [HKEY_LOCAL_MACHINE\Config\0001\Display\Settings\] >> C:\WINDOWS\TEMP\set1024.reg
echo "fonts.fon"="vgasys.fon" >> C:\WINDOWS\TEMP\set1024.reg
echo "fixedfon.fon"="vgafix.fon" >> C:\WINDOWS\TEMP\set1024.reg
echo "oemfonts.fon"="vgaoem.fon" >> C:\WINDOWS\TEMP\set1024.reg
echo "DPILogicalX"="96" >> C:\WINDOWS\TEMP\set1024.reg
echo "DPILogicalY"="96" >> C:\WINDOWS\TEMP\set1024.reg
echo "DPIPhysicalX"="96" >> C:\WINDOWS\TEMP\set1024.reg
echo "DPIPhysicalY"="96" >> C:\WINDOWS\TEMP\set1024.reg
echo "BitsPerPixel"="16" >> C:\WINDOWS\TEMP\set1024.reg
echo "Resolution"="1024,768" >> C:\WINDOWS\TEMP\set1024.reg
echo "DisplayFlags"="0" >> C:\WINDOWS\TEMP\set1024.reg

C:\WINDOWS\REGEDIT.EXE /L:C:\WINDOWS\SYSTEM.DAT /R:C:\WINDOWS\USER.DAT C:\WINDOWS\TEMP\set1024.reg
del C:\WINDOWS\TEMP\set1024.reg