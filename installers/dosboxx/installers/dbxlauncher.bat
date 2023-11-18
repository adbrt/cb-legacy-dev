@echo off

if exist "%~1" (
echo Startup directory: %~dp1
echo Executable name: %~nx1
echo Executing in DOSBox-X...
cd "%~dp0"
dosbox-x.exe -c "MOUNT C: '%~dp1' " -c "C: " -c "cls " -c "%~nx1 "
)