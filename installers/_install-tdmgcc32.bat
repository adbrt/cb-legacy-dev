@echo off
REM TDM-GCC 4.7.1 32-bit installation
REM =================================


pushd "%~dp0"
mkdir CodeBlocks
if not exist "%~dp0\installers\tdm-gcc-4.7.1-2.exe" (
mkdir installers
echo Downloading TDM-GCC 4.7.1 32-bit compiler

REM powershell "$client = New-Object System.Net.WebClient; $client.DownloadFile('https://downloads.sourceforge.net/project/tdm-gcc/TDM-GCC Installer/Previous/1.1006.0/tdm-gcc-4.7.1-2.exe','%~dp0\installers\tdm-gcc-4.7.1-2.exe')"

powershell Invoke-WebRequest 'https://master.dl.sourceforge.net/project/tdm-gcc/TDM-GCC Installer/Previous/1.1006.0/tdm-gcc-4.7.1-2.exe?viasf=1' -UserAgent "Wget" -OutFile '%~dp0\installers\tdm-gcc-4.7.1-2.exe'

REM powershell "wget 'https://master.dl.sourceforge.net/project/tdm-gcc/TDM-GCC Installer/Previous/1.1006.0/tdm-gcc-4.7.1-2.exe?viasf=1' -UseBasicParsing -OutFile "%~dp0\installers\tdm-gcc-4.7.1-2.exe"
)

echo Unpacking TDM-GCC installer
"%ZPATH%\7z.exe" x "%~dp0\installers\tdm-gcc-4.7.1-2.exe" -o"%~dp0\installers\tdm-gcc-4.7.1-2"

cd "%~dp0\installers\tdm-gcc-4.7.1-2\$PLUGINSDIR"

"%ZPATH%\7z.exe" x "*.lzma" -o".\tdmgcc32"
"%ZPATH%\7z.exe" x "*.gz" -o".\tdmgcc32"

cd tdmgcc32

"%ZPATH%\7z.exe" x "*.tar" -o"%~dp0\CodeBlocks\tdmgcc32" -aos
del /Q *.tar

pushd "%~dp0"

cd installers
rmdir /S /Q "tdm-gcc-4.7.1-2"

pushd "%~dp0"

if not exist "%~dp0\installers\libunicows-1.1.1-mingw32.zip" (
echo Downloading libunicows-1.1.1-mingw32.zip
powershell wget https://master.dl.sourceforge.net/project/libunicows/libunicows/1.1.1/libunicows-1.1.1-mingw32.zip?viasf=1 -UseBasicParsing -OutFile '%~dp0\installers\libunicows-1.1.1-mingw32.zip'
)

if not exist "%~dp0\installers\libunicows-1.1.1-mingw32\libunicows.a" (
echo Extracting libunicows-1.1.1-mingw32
"%ZPATH%\7z.exe" x "%~dp0\installers\libunicows-1.1.1-mingw32.zip" -o"%~dp0\installers"
)

copy "%~dp0\installers\libunicows-1.1.1-mingw32\libunicows.a" "%~dp0\CodeBlocks\tdmgcc32\lib\libunicows.a"
copy "%~dp0\installers\libunicows-1.1.1-mingw32\liblibunicows.a" "%~dp0\CodeBlocks\tdmgcc32\lib\liblibunicows.a"


pushd "%~dp0"
if not exist "%~dp0\installers\unicows.exe" (
echo Downloading unicows redistributable
powershell wget http://web.archive.org/web/20051029063254if_/http://download.microsoft.com/download/b/7/5/b75eace3-00e2-4aa0-9a6f-0b6882c71642/unicows.exe -UseBasicParsing -OutFile '%~dp0\installers\unicows.exe'
)

if not exist "%~dp0\CodeBlocks\redist\unicows\unicows.dll" (
echo Extracting unicows.dll
mkdir "%~dp0\CodeBlocks\redist\unicows"
"%ZPATH%\7z.exe" x "%~dp0\installers\unicows.exe" -o"%~dp0\CodeBlocks\redist\unicows"
)
