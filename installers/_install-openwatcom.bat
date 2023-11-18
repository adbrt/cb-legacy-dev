@echo off
REM OPENWATCOM INSTALLATION
REM =========================

pushd "%~dp0"
if not exist "%~dp0\installers\open-watcom-c-win32-1.9.exe" (
echo Downloading OpenWatcom 1.9
powershell wget https://github.com/open-watcom/open-watcom-1.9/releases/download/ow1.9/open-watcom-c-win32-1.9.exe -UseBasicParsing -OutFile '%~dp0\installers\open-watcom-c-win32-1.9.exe'
)

if not exist .\CodeBlocks\watcom (
echo.
echo Extracting OpenWatcom
"%ZPATH%\7z.exe" x "%~dp0\installers\open-watcom-c-win32-1.9.exe" -o"%~dp0\CodeBlocks\watcom"
)