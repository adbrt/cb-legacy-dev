@echo off
REM DJGPP INSTALLATION
REM =========================

set PATH=%PATH%;%SYSTEMROOT%\System32\WindowsPowerShell\v1.0\

pushd "%~dp0"
if not exist "%~dp0\installers\djgpp-mingw-gcc930-standalone.zip" (
echo Downloading DJGPP
powershell wget https://github.com/andrewwutw/build-djgpp/releases/download/v3.0/djgpp-mingw-gcc930-standalone.zip -UseBasicParsing -OutFile '%~dp0\installers\djgpp-mingw-gcc930-standalone.zip'
)

if not exist .\CodeBlocks\djgpp (
echo.
mkdir "%~dp0\CodeBlocks"
echo Extracting DJGPP
REM powershell "Expand-Archive '%~dp0\installers\djgpp-mingw-gcc930-standalone.zip' '%~dp0\CodeBlocks'"
"%ZPATH%\7z.exe" x "%~dp0\installers\djgpp-mingw-gcc930-standalone.zip" -o"%~dp0\CodeBlocks"
)

REM hardcode some defs to fix not working code completion
REM this is probably not a great thing to do, but is important from user experience perspective
cd "%~dp0\CodeBlocks\djgpp\lib\gcc\i586-pc-msdosdjgpp\9.3.0\include\c++\"


if exist "cstdio" (
echo // Prepended hardcoded __STDC_VERSION__ to fix problems with CodeBlocks parser > cstdio.tmp
echo #ifndef __STDC_VERSION__ >> cstdio.tmp
echo #define __STDC_VERSION__ 199901L >> cstdio.tmp
echo #endif >> cstdio.tmp
type cstdio >> cstdio.tmp
del cstdio
ren cstdio.tmp cstdio
)
pushd "%~dp0"
