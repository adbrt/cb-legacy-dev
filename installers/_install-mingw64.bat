@echo off
REM MinGW-W64 installation
REM =================================


pushd "%~dp0"
mkdir CodeBlocks
if not exist "%~dp0\installers\x86_64-8.1.0-release-posix-seh-rt_v6-rev0.7z" (
mkdir installers
echo Downloading MinGW-W64 8.1.0 compiler

powershell Invoke-WebRequest 'https://altushost-swe.dl.sourceforge.net/project/mingw-w64/Toolchains targetting Win64/Personal Builds/mingw-builds/8.1.0/threads-posix/seh/x86_64-8.1.0-release-posix-seh-rt_v6-rev0.7z' -UserAgent "Wget" -OutFile "%~dp0\installers\x86_64-8.1.0-release-posix-seh-rt_v6-rev0.7z"
)

echo Unpacking MinGW-W64 8.1.0
"%ZPATH%\7z.exe" x "%~dp0\installers\x86_64-8.1.0-release-posix-seh-rt_v6-rev0.7z" -o"%~dp0\CodeBlocks"
