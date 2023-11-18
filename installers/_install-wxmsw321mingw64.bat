@echo off
REM WXWIDGETS 3.2.1 INSTALLATION
REM =============================

pushd "%~dp0"
if not exist "%~dp0\installers\wxWidgets-3.2.1.7z" (
echo Downloading wxWidgets-3.2.1.7z
powershell wget https://github.com/wxWidgets/wxWidgets/releases/download/v3.2.1/wxWidgets-3.2.1.7z -UseBasicParsing -OutFile '%~dp0\installers\wxWidgets-3.2.1.7z'
)

if not exist "%~dp0\CodeBlocks\wxWidgets-3.2.1\" (
echo.
mkdir "%~dp0\CodeBlocks"
echo Extracting wxWidgets-3.2.1
"%ZPATH%\7z.exe" x "%~dp0\installers\wxWidgets-3.2.1.7z" -o"%~dp0\CodeBlocks\wxWidgets-3.2.1"
)


SET BUILDTYPE=release
SET UNICODE=1
call :BUILDWX

SET BUILDTYPE=debug
SET UNICODE=1
call :BUILDWX

GOTO END

:BUILDWX
pushd "%~dp0"
cd ".\CodeBlocks\mingw64"
SET MINGWPATH=%CD%
pushd "%~dp0"

cd ".\CodeBlocks\mingw64\bin"
SET PATH = %WINDIR%;%WINDIR%\System32;%CD%

pushd "%~dp0"
cd ".\CodeBlocks\mingw64\libexec\gcc\x86_64-w64-mingw32\8.1.0"
SET PATH = %WINDIR%;%WINDIR%\System32;%CD%

pushd "%~dp0"

echo Cleaning up
cd ".\CodeBlocks\wxWidgets-3.2.1\build\msw"
SET WXBUILDPATH=%CD%

SET DEBUGFLAG=0
if "%BUILDTYPE%"=="debug" SET DEBUGFLAG=1

@echo on
mingw32-make SHELL=CMD.exe -f makefile.gcc SHARED=0 DEBUG_FLAG=%DEBUGFLAG% MONOLITHIC=1 UNICODE=%UNICODE% BUILD=%BUILDTYPE% CXXFLAGS="-march=x86-64" LDFLAGS="-m64" clean 

@echo off
echo Building
mingw32-make SHELL=CMD.exe -f makefile.gcc SHARED=0 DEBUG_FLAG=%DEBUGFLAG% MONOLITHIC=1 UNICODE=%UNICODE% BUILD=%BUILDTYPE% CXXFLAGS="-march=x86-64" LDFLAGS="-m64"

@echo off 

echo Building done

echo Prepending __WXMSW__ to setup.h because it might make code completion work better
pushd "%~dp0"

if "%BUILDTYPE%"=="release" (
if "%UNICODE%"=="0" cd CodeBlocks\wxWidgets-3.2.1\lib\gcc_lib\msw\wx
if "%UNICODE%"=="1" cd CodeBlocks\wxWidgets-3.2.1\lib\gcc_lib\mswu\wx
)
if "%BUILDTYPE%"=="debug" (
if "%UNICODE%"=="0" cd CodeBlocks\wxWidgets-3.2.1\lib\gcc_lib\mswd\wx
if "%UNICODE%"=="1" cd CodeBlocks\wxWidgets-3.2.1\lib\gcc_lib\mswud\wx
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