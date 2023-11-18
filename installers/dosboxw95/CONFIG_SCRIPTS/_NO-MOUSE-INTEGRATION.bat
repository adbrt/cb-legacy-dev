@echo off
pushd "%~dp0"
cd ..

echo Disabling mouse integration

powershell "Get-Content 'dosbox-x.conf' | Foreach-Object {$_ -replace '^integration device.+$','integration device = false'} | Set-Content 'dosbox-x.new'"

if exist "dosbox-x.new" (
del /Q dosbox-x.conf.bak
rename dosbox-x.conf dosbox-x.conf.bak
rename dosbox-x.new dosbox-x.conf
)

 
REM del /Q ".\guest_tools\runonce\runonce.bat"
echo @echo off >> ".\guest_tools\runonce\runonce.bat"
echo O:\setmdrv.exe ps2 >> ".\guest_tools\runonce\runonce.bat"

if not exist ".\guest_tools\runonce\setmdrv.exe" (
copy ".\guest_tools\setmdrv\setmdrv.exe" ".\guest_tools\runonce\setmdrv.exe"
)