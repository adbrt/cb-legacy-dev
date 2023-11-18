@echo off
mkdir C:\WINDOWS\TEMP
echo REGEDIT4 > C:\WINDOWS\TEMP\nostsnd.reg
echo. >> C:\WINDOWS\TEMP\nostsnd.reg
echo [HKEY_CURRENT_USER\AppEvents\Schemes\Apps\.Default\SystemStart\.Current] >> C:\WINDOWS\TEMP\nostsnd.reg
echo @="" >> C:\WINDOWS\TEMP\nostsnd.reg

C:\WINDOWS\REGEDIT.EXE /L:C:\WINDOWS\SYSTEM.DAT /R:C:\WINDOWS\USER.DAT C:\WINDOWS\TEMP\nostsnd.reg

echo REGEDIT4 > C:\WINDOWS\TEMP\nostsnd.reg
echo. >> C:\WINDOWS\TEMP\nostsnd.reg
echo [HKEY_CURRENT_USER\AppEvents\Schemes\Apps\.Default\SystemExit\.Current] >> C:\WINDOWS\TEMP\nostsnd.reg
echo @="" >> C:\WINDOWS\TEMP\nostsnd.reg

C:\WINDOWS\REGEDIT.EXE /L:C:\WINDOWS\SYSTEM.DAT /R:C:\WINDOWS\USER.DAT C:\WINDOWS\TEMP\nostsnd.reg

del C:\WINDOWS\TEMP\nostsnd.reg