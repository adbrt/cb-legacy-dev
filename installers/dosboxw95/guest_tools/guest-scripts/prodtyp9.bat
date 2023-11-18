@echo off
mkdir C:\WINDOWS\TEMP
echo REGEDIT4 > C:\WINDOWS\TEMP\prodtyp.reg
echo. >> C:\WINDOWS\TEMP\prodtyp.reg
echo [HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion] >> C:\WINDOWS\TEMP\prodtyp.reg
echo "ProductType"="9" >> C:\WINDOWS\TEMP\prodtyp.reg

C:\WINDOWS\REGEDIT.EXE /L:C:\WINDOWS\SYSTEM.DAT /R:C:\WINDOWS\USER.DAT C:\WINDOWS\TEMP\prodtyp.reg
del C:\WINDOWS\TEMP\prodtyp.reg