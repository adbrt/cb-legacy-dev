@echo off

if exist "%~1" (
echo Startup directory: %~dp1
echo Executable name: %~nx1

echo Executing in DOSBox-X Win3.11...
cd "%~dp0"
dosbox-x.exe -c "MOUNT D: '%~dp1' " -c "C:\WINDOWS\WIN.COM D:\%~nx1 " -c "exit "
REM timeout /t 5
REM del /Q "%~dp1\launchit.cfg"
)

if not exist "%~1" (
echo This scripts will run given executable in Windows 3.11 inside DOSBox-X.
echo.
echo Usage: 
echo w31launcher.bat "PathToExecutable.exe"
echo.
)
