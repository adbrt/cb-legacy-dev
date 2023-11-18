@echo off

REM this allows to use this launcher in place of GDB debugger (just to launch DOSBox-X instead of GDB)

if not [%3]==[] (
if "%3"=="-args" GOTO EXECUTE
GOTO END
)

:EXECUTE

if exist "%~4" (
echo Startup directory: %~dp4
echo Executable name: %~nx4
echo Adding launchit.cfg to startup directory...
echo %~nx4 > "%~dp4\launchit.cfg"

if not [%5]==[] (
if "%5"=="NOSHUTDOWN" echo Adding NOSHUTDOWN flag
if "%5"=="NOSHUTDOWN" echo NOSHUTDOWN >> "%~dp4\launchit.cfg"
)

echo Executing in DOSBox-X Win95...
cd "%~dp0"
dosbox-x.exe -c "MOUNT D: '%~dp4' -ide 2s " -c "BOOT C: "
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

:END