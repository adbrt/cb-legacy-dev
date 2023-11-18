@echo off
REM WXWIDGETS 3.0.5 INSTALLATION
REM =============================

set PATH=%PATH%;%SYSTEMROOT%\System32\WindowsPowerShell\v1.0\

pushd "%~dp0"
if not exist "%~dp0\installers\wxWidgets-3.0.5.zip" (
echo Downloading wxWidgets-3.0.5.zip
powershell wget https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.5/wxWidgets-3.0.5.zip -UseBasicParsing -OutFile '%~dp0\installers\wxWidgets-3.0.5.zip'
)

if not exist "%~dp0\CodeBlocks\wxWidgets-3.0.5\" (
echo.
mkdir "%~dp0\CodeBlocks"
echo Extracting wxWidgets-3.0.5
REM powershell "Expand-Archive '%~dp0\installers\wxWidgets-3.0.5.zip' '%~dp0\CodeBlocks\wxWidgets-3.0.5'"
"%ZPATH%\7z.exe" x "%~dp0\installers\wxWidgets-3.0.5.zip" -o"%~dp0\CodeBlocks\wxWidgets-3.0.5"
)

echo Applying patches for Win9x compatibility
xcopy /Y /E "%~dp0\installers\patch_wx305_9x\*.*" "%~dp0\CodeBlocks\wxWidgets-3.0.5"


SET BUILDTYPE=release
SET UNICODE=1
if not exist "%~dp0\CodeBlocks\wxWidgets-3.0.5\lib\gcc_lib\mswu\wx\setup.h" (
mkdir "%~dp0\CodeBlocks\wxWidgets-3.0.5\lib\gcc_lib\mswu\wx"
copy "%~dp0\CodeBlocks\wxWidgets-3.0.5\include\wx\msw\setup.h" "%~dp0\CodeBlocks\wxWidgets-3.0.5\lib\gcc_lib\mswu\wx\setup.h"
)
call :BUILDWX

SET BUILDTYPE=debug
SET UNICODE=1
if not exist "%~dp0\CodeBlocks\wxWidgets-3.0.5\lib\gcc_lib\mswud\wx\setup.h" (
mkdir "%~dp0\CodeBlocks\wxWidgets-3.0.5\lib\gcc_lib\mswud\wx"
copy "%~dp0\CodeBlocks\wxWidgets-3.0.5\include\wx\msw\setup.h" "%~dp0\CodeBlocks\wxWidgets-3.0.5\lib\gcc_lib\mswud\wx\setup.h"
)
call :BUILDWX

SET BUILDTYPE=release
SET UNICODE=0
if not exist "%~dp0\CodeBlocks\wxWidgets-3.0.5\lib\gcc_lib\msw\wx\setup.h" (
mkdir "%~dp0\CodeBlocks\wxWidgets-3.0.5\lib\gcc_lib\msw\wx"
copy "%~dp0\CodeBlocks\wxWidgets-3.0.5\include\wx\msw\setup.h" "%~dp0\CodeBlocks\wxWidgets-3.0.5\lib\gcc_lib\msw\wx\setup.h"
)
call :BUILDWX

SET BUILDTYPE=debug
SET UNICODE=0
if not exist "%~dp0\CodeBlocks\wxWidgets-3.0.5\lib\gcc_lib\mswd\wx\setup.h" (
mkdir "%~dp0\CodeBlocks\wxWidgets-3.0.5\lib\gcc_lib\mswd\wx"
copy "%~dp0\CodeBlocks\wxWidgets-3.0.5\include\wx\msw\setup.h" "%~dp0\CodeBlocks\wxWidgets-3.0.5\lib\gcc_lib\mswd\wx\setup.h"
)
call :BUILDWX


GOTO END

:BUILDWX
pushd "%~dp0"
cd ".\CodeBlocks\tdmgcc32"
SET MINGWPATH=%CD%
pushd "%~dp0"

cd ".\CodeBlocks\tdmgcc32\bin"
SET PATH=%PATH%;%WINDIR%;%WINDIR%\System32;%CD%

pushd "%~dp0"
cd ".\CodeBlocks\tdmgcc32\libexec\gcc\mingw32\4.7.1"
SET PATH=%PATH%;%WINDIR%;%WINDIR%\System32;%CD%

pushd "%~dp0"

echo Cleaning up
cd ".\CodeBlocks\wxWidgets-3.0.5\build\msw"
SET WXBUILDPATH=%CD%

SET DEBUGFLAG=0
if "%BUILDTYPE%"=="debug" SET DEBUGFLAG=1

@echo on
"%MINGWPATH%\bin\mingw32-make.exe" SHELL=CMD.exe -f makefile.gcc SHARED=0 DEBUG_FLAG=%DEBUGFLAG% MONOLITHIC=1 MSLU=%UNICODE% UNICODE=%UNICODE% BUILD=%BUILDTYPE% clean CXXFLAGS="-DWINVER=0x0400"

@echo off
echo Building
"%MINGWPATH%\bin\mingw32-make.exe" SHELL=CMD.exe -f makefile.gcc SHARED=0 DEBUG_FLAG=%DEBUGFLAG% MONOLITHIC=1 MSLU=%UNICODE% UNICODE=%UNICODE% BUILD=%BUILDTYPE% CXXFLAGS="-DWINVER=0x0400" -j4

@echo off 

echo Building done

echo Prepending __WXMSW__ to setup.h to fix not working code completion in wxWidgets-3.0.5
pushd "%~dp0"

if "%BUILDTYPE%"=="release" (
if "%UNICODE%"=="0" cd CodeBlocks\wxWidgets-3.0.5\lib\gcc_lib\msw\wx
if "%UNICODE%"=="1" cd CodeBlocks\wxWidgets-3.0.5\lib\gcc_lib\mswu\wx
)
if "%BUILDTYPE%"=="debug" (
if "%UNICODE%"=="0" cd CodeBlocks\wxWidgets-3.0.5\lib\gcc_lib\mswd\wx
if "%UNICODE%"=="1" cd CodeBlocks\wxWidgets-3.0.5\lib\gcc_lib\mswud\wx
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
goto :eof


:END

pushd "%~dp0"