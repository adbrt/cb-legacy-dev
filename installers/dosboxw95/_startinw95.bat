@echo off

if exist "%~1" (
echo Startup directory: %~dp1
echo Executable name: %~nx1
echo Adding launchit.cfg to startup directory...
echo %~nx1 > "%~dp1\launchit.cfg"

if not [%2]==[] (
if "%2"=="NOSHUTDOWN" echo Adding NOSHUTDOWN flag
if "%2"=="NOSHUTDOWN" echo NOSHUTDOWN >> "%~dp1\launchit.cfg"
)

echo Executing in DOSBox-X Win95...
cd "%~dp0"
start dosbox-x.exe -c "MOUNT D: '%~dp1' -ide 2s " -c "BOOT C: "
REM timeout /t 5
REM del /Q "%~dp1\launchit.cfg"
)

if not exist "%~1" (
echo This scripts will run given executable in Windows 95 inside DOSBox-X.
echo.
echo Usage: 
echo _startinwin95.bat "PathToExecutable.exe"
echo.
echo Note: a file "launchit.cfg" will be created in executable directory at launch time, it can be safely removed at any time.
echo Emulated machine also needs to have "alaucnhr.exe" installed in autostart directory.
)
