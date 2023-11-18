@echo off
REM WXWIDGETS 2.8.12 INSTALLATION
REM =============================

pushd "%~dp0"

if not exist "%~dp0\installers\wxMSW-2.8.12.zip" (
echo Downloading wxWidgets 2.8.12
powershell wget https://github.com/wxWidgets/wxWidgets/releases/download/v2.8.12/wxMSW-2.8.12.zip -UseBasicParsing -OutFile '%~dp0\installers\wxMSW-2.8.12.zip'
)

if not exist "%~dp0\CodeBlocks\wxMSW-2.8.12\" (
echo.
mkdir "%~dp0\CodeBlocks"
echo Extracting wxWidgets 2.8.12
REM powershell "Expand-Archive '%~dp0\installers\wxMSW-2.8.12.zip' '%~dp0\CodeBlocks'"
"%ZPATH%\7z.exe" x "%~dp0\installers\wxMSW-2.8.12.zip" -o"%~dp0\CodeBlocks"
)

echo Applying patches for Win32s/Win3.11 compatibility
xcopy /Y /E "%~dp0\installers\patch_wx28_win32s\*.*" "%~dp0\CodeBlocks\wxMSW-2.8.12"

SET BUILDTYPE=release
SET UNICODE=0
call :BUILDWX

SET BUILDTYPE=debug
SET UNICODE=0
call :BUILDWX

GOTO END

:BUILDWX
echo.
echo Building wxWidgets 2.8.12 with BCC5.5 compiler
cd /D %~dp0
cd CodeBlocks
cd BCC55
cd Bin
echo Updating environmental variables
set PATH=%WINDIR%;%WINDIR%\System32;%CD%
pushd "%~dp0"
cd CodeBlocks

echo.
echo wxWidgets 2.8.12 %BUILDTYPE% UNICODE=%UNICODE% WINVER=0x0400

echo Cleaning up

cd .\wxMSW-2.8.12\build\msw
make SHELL=CMD.exe -f makefile.bcc -DWINVER=0x0400 SHARED=0 MONOLITHIC=1 UNICODE=%UNICODE% BUILD=%BUILDTYPE% clean

echo Building
make SHELL=CMD.exe -f makefile.bcc -DWINVER=0x0400 SHARED=0 MONOLITHIC=1 UNICODE=%UNICODE% BUILD=%BUILDTYPE%

echo Building done

echo Prepending __WXMSW__ to setup.h to fix not working code completion in wx 2.8.12
pushd "%~dp0"
if "%BUILDTYPE%"=="release" (
if "%UNICODE%"=="0" cd CodeBlocks\wxMSW-2.8.12\lib\bcc_lib\msw\wx
if "%UNICODE%"=="1" cd CodeBlocks\wxMSW-2.8.12\lib\bcc_lib\mswu\wx
)
if "%BUILDTYPE%"=="debug"  (
if "%UNICODE%"=="0" cd CodeBlocks\wxMSW-2.8.12\lib\bcc_lib\mswd\wx
if "%UNICODE%"=="1" cd CodeBlocks\wxMSW-2.8.12\lib\bcc_lib\mswud\wx
)

if exist "setup.h" (
echo // Prepended __WXMSW__ to fix problems with CodeBlocks parser > setup0.tmp
echo #ifndef __WXMSW__ >> setup0.tmp
echo #define __WXMSW__ >> setup0.tmp
echo #endif >> setup0.tmp
type setup.h >> setup0.tmp
del setup.h
ren setup0.tmp setup.h
)
pushd "%~dp0"
goto :eof

:END