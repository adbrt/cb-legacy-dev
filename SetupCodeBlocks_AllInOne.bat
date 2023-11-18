@echo off
echo CB4LSD+ : CodeBlocks for Legacy Software Development (+ modern) installer bundle
echo This scripts automatically installs CodeBlocks IDE (https://www.codeblocks.org/) and various compilers
echo. 
echo This package allows building software for Windows 3.11 (Win32s), ANSI Windows 9x,
echo Windows 9x with Unicode (MSLU/Unicows), modern 64-bit Windows, MS-DOS
echo. 
echo This script will download and prepare for use following software:
echo Code::Blocks 64-bit IDE wxWidgets 2.8.12, wxWidgets 3.0.5, wxWidgets 3.2.1
echo Compilers: Borland BCC5.5 (free version), TDM-GCC 32bit, MinGW-W64, DJGPP, OpenWatcom
echo.
echo DOSBox-X will also be installed to allow executing and testing MS-DOS software.
echo Windows 3.11 and Windows 95 will also be installed and configured
echo to allow automatic execution IF YOU PROVIDE YOUR OWN installation files.
echo Only English Windows 95 OSR2 and English WfW 3.11 are supported now.
echo.
echo.
pause


SET ZPATH=%~dp0\installers\7-zip

if not exist "%ZPATH%\7zr.exe" (
mkdir .\installers\7-zip
echo Downloading 7-zip
powershell wget https://www.7-zip.org/a/7zr.exe -UseBasicParsing -OutFile "%~dp0\installers\7-zip\7zr.exe"
powershell wget https://www.7-zip.org/a/7z2201.exe -UseBasicParsing -OutFile "%~dp0\installers\7-zip\7z2201.exe"
"%~dp0\installers\7-zip\7zr.exe" x "%~dp0\installers\7-zip\7z2201.exe" -o"%~dp0\installers\7-zip"
)

if not exist "%ZPATH%\7z.exe" (
"%~dp0\installers\7-zip\7zr.exe" x "%~dp0\installers\7-zip\7z2201.exe" -o"%~dp0\installers\7-zip"
)


xcopy "%~dp0\installers\_install-*.bat" "%~dp0"



REM CODE::BLOCKS INSTALLATION
REM =========================
pushd "%~dp0"
if not exist "%~dp0\installers\CB_202*.<7z" (
mkdir installers
echo Downloading Code::Blocks 2022.06.19 Win 64-bit
powershell Invoke-WebRequest https://master.dl.sourceforge.net/project/codeblocks/Binaries/Nightlies/2022/CB_20220619_rev12839_win64.7z -UserAgent "Wget" -OutFile '%~dp0\installers\CB_20220619_rev12839_win64.7z'
echo Downloading prerequisites
powershell Invoke-WebRequest https://kumisystems.dl.sourceforge.net/project/codeblocks/Binaries/Nightlies/Prerequisites/wxmsw31u_gcc_cb_wx315_2D_gcc810-mingw64.7z -UserAgent "Wget" -OutFile '%~dp0\installers\wxmsw31u_gcc_cb_wx315_2D_gcc810-mingw64.7z'
powershell Invoke-WebRequest https://altushost-swe.dl.sourceforge.net/project/codeblocks/Binaries/Nightlies/Prerequisites/Mingw64dlls8.1.0.7z -UserAgent "Wget" -OutFile '%~dp0\installers\Mingw64dlls8.1.0.7z'

)

if not exist .\CodeBlocks\ (
echo.
echo Extracting Code::Blocks
REM powershell "Expand-Archive '%~dp0\installers\codeblocks-20.03-nosetup.zip' '%~dp0\CodeBlocks'"
"%ZPATH%\7z.exe" x "%~dp0\installers\CB_202*" -o"%~dp0\CodeBlocks"
"%ZPATH%\7z.exe" x "%~dp0\installers\wxmsw3*" -o"%~dp0\CodeBlocks"
"%ZPATH%\7z.exe" x "%~dp0\installers\mingw64dlls*" -o"%~dp0\CodeBlocks"
)


REM BCC5.5 INSTALLATION
call _install-bcc55.bat

REM TDM-GCC 4.7.1 32-bit installation
call _install-tdmgcc32.bat

REM MinGW-W64 8.1.0 64-bit installation
call _install-mingw64.bat

REM DJGPP INSTALLATION
call _install-djgpp.bat

REM OPENWATCOM INSTALLATION
call _install-openwatcom.bat

REM WXWIDGETS 2.8.12 BUILD
if not exist "%~dp0\installers\wxMSW-2.8.12_prebuild.7z" (
call _install-wxmsw28bcc.bat
call _install-wxmsw28tdm32.bat
)

if exist "%~dp0\installers\wxMSW-2.8.12_prebuild.7z" (
if not exist "%~dp0\CodeBlocks\wxMSW-2.8.12\lib\bcc_lib\wxmsw28.lib" (
echo Unpacking pre-built wxWidgets 2.8.12
"%ZPATH%\7z.exe" x "%~dp0\installers\wxMSW-2.8.12_prebuild.7z" -o"%~dp0\CodeBlocks"
)
)
REM ===============================

REM WXWIDGETS 3.0.5 TDM-GCC32 BUILD
if not exist "%~dp0\installers\wxWidgets-3.0.5_prebuild.7z" (
call _install-wxmsw305tdm32.bat
)

if exist "%~dp0\installers\wxWidgets-3.0.5_prebuild.7z" (
if not exist "%~dp0\CodeBlocks\wxWidgets-3.0.5\lib\gcc_lib\libwxmsw30u.a" (
echo Unpacking pre-built wxWidgets 3.0.5 for TDM-GCC 32bit
"%ZPATH%\7z.exe" x "%~dp0\installers\wxWidgets-3.0.5_prebuild.7z" -o"%~dp0\CodeBlocks"
)
)
REM ===============================

REM WXWIDGETS 3.2.1 MINGW-W64 BUILD
if not exist "%~dp0\installers\wxWidgets-3.2.1_mingw64-810_msw64_prebuild.7z" (
call _install-wxmsw321mingw64.bat
)

if exist "%~dp0\installers\wxWidgets-3.2.1_mingw64-810_msw64_prebuild.7z" (
if not exist "%~dp0\CodeBlocks\wxWidgets-3.2.1\lib\gcc_lib\libwxmsw32u.a" (
echo Unpacking pre-built wxWidgets 3.2.1 for MinGW-W64 8.1.0
"%ZPATH%\7z.exe" x "%~dp0\installers\wxWidgets-3.2.1_mingw64-810_msw64_prebuild.7z" -o"%~dp0\CodeBlocks"
)
)
REM ===============================





pushd "%~dp0"
echo Copying project templates
xcopy /E /Y ".\installers\wizard\*.*" "%~dp0\CodeBlocks\share\CodeBlocks\templates\wizard\*.*"


echo Copying DOSBOX
xcopy /E /Y ".\installers\dosbox\*.*" "%~dp0\CodeBlocks\dosbox\*.*"

echo Copying DOSBOX-X
xcopy /E /Y ".\installers\dosboxx\*.*" "%~dp0\CodeBlocks\dosboxx\*.*"

echo Copying DOSBOXW31
xcopy /E /Y ".\installers\dosboxw31\*.*" "%~dp0\CodeBlocks\dosboxw31\*.*"


echo Copying DOSBOXW95
xcopy /E /Y ".\installers\dosboxw95\*.*" "%~dp0\CodeBlocks\dosboxw95\*.*"


echo Copying utils
xcopy /E /Y ".\installers\utils\*.*" "%~dp0\CodeBlocks\utils\*.*"


echo.
echo Generating run script


echo @echo off > runCodeBlocks.bat
echo cd /D ""%%~dp0"" >> runCodeBlocks.bat
echo cd CodeBlocks >> runCodeBlocks.bat
echo cd BCC55 >> runCodeBlocks.bat
echo set PATH=%%PATH%%;%%CD%% >> runCodeBlocks.bat
echo cd.. >> runCodeBlocks.bat
echo cd CodeBlocks >> runCodeBlocks.bat
echo START """" ""CbLauncher.exe"" >> runCodeBlocks.bat

echo.
echo Copying default config file
mkdir "%~dp0\CodeBlocks\AppData\codeblocks\"
copy "%~dp0\installers\default.conf" "%~dp0\CodeBlocks\AppData\codeblocks\default.conf"
echo.
echo.
echo Updating config file with local paths
pushd "%~dp0"
cd CodeBlocks
cd watcom
set WATCOMPATH=%CD%
pushd "%~dp0"
cd CodeBlocks
cd AppData
cd codeblocks
powershell "((Get-Content -path default.conf -Raw) -replace '\$\(APP-PATH\)\\watcom','%WATCOMPATH%') | Set-Content -Path default.conf"
pushd "%~dp0"
echo.
echo Unpacking samples
"%ZPATH%\7z.exe" x "%~dp0\installers\Samples.zip" -o"%~dp0"


pushd "%~dp0"

del /Q _install-*.bat

echo.
echo Installing DOSBOX and DOSBOX-X w/ Win3.11, Win95

pushd "%~dp0\CodeBlocks\dosboxx"
call dosboxx_install.bat

pushd "%~dp0\CodeBlocks\dosboxw31"
call _WFW311AUTOINSTALLER_.bat

pushd "%~dp0\CodeBlocks\dosboxw95"
call SetupW95DosboxX.bat

pushd "%~dp0"


echo All done.
echo.
echo Run runCodeBlocks.bat file to start the IDE.
echo.
pause
ren SetupCodeBlocks_AllInOne.bat SetupCodeBlocks_AllInOne.bak


