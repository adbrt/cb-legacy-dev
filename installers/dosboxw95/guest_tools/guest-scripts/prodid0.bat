@echo off
mkdir C:\WINDOWS\TEMP
echo REGEDIT4 > C:\WINDOWS\TEMP\prodid.reg
echo. >> C:\WINDOWS\TEMP\prodid.reg
echo [HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion] >> C:\WINDOWS\TEMP\prodid.reg
echo "ProductId"=- >> C:\WINDOWS\TEMP\prodid.reg

C:\WINDOWS\REGEDIT.EXE /L:C:\WINDOWS\SYSTEM.DAT /R:C:\WINDOWS\USER.DAT C:\WINDOWS\TEMP\prodid.reg
del C:\WINDOWS\TEMP\prodid.reg