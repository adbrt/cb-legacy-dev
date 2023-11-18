@echo off

REM === CUSTOM SETTINGS ====================


REM Select virtual hard drive size.
REM Valid choices: 504MB, 2GB, 4GB, 8GB.
SET HDSIZE=504MB

REM Select resolution here. May be changed later.
REM Valid choices: 640x480x16bpp, 800x600x16bpp
SET SCREENRES=800x600x16bpp

REM SET PRODUCTKEY=ask
SET PRODUCTKEY=na

REM this disables startup/shutdown sounds
SET DISABLEONOFFSOUNDS=true


REM === DO NOT EDIT BELOW THIS LINE ========
REM ========================================


echo Dosbox-x + Windows 95 OSR2 ENG autoinstaller
echo.
echo This installed DOES NOT provide Windows 95 files.
echo.
echo You need to place your own installation files in .\installers\WIN95 directory.
echo Only English OSR2 OEM CD version will work with this script.
echo Other files - redistributables, updates and configuration files - will be downloaded automatically.
echo. 
echo If required Windows 95 files are not present, you will be prompted to copy them to appropriate directory.
echo. 
pause


REM default virtual hard drive size
SET HDCHS=512,63,16,1023
SET HDTEMPLATE=hd_520

if "%HDSIZE%"=="2GB" SET HDCHS=512,63,64,1023
if "%HDSIZE%"=="2GB" SET HDTEMPLATE=hd_2gig

if "%HDSIZE%"=="4GB" SET HDCHS=512,63,130,1023
if "%HDSIZE%"=="4GB" SET HDTEMPLATE=hd_4gig

if "%HDSIZE%"=="8GB" SET HDCHS=512,63,255,1023
if "%HDSIZE%"=="8GB" SET HDTEMPLATE=hd_8gig


pushd "%~dp0"
cd ..
cd ..
cd installers
SET DBOXIN=%CD%
cd 7-zip
SET ZPATH=%CD%
pushd "%~dp0"


if not exist "%~dp0\installers\" (
mkdir "%~dp0\installers"
)

if not exist "%~dp0\installers\WIN95\WIN95_02.cab" (
mkdir "%~dp0\installers\WIN95"
echo "" > "%~dp0\installers\WIN95\_PLACE_WIN95_FILES_HERE_"
echo.
echo Windows 95 files not found. Please copy them from CD-ROM .\WIN95 directory.
timeout /t 1 > nul
cd "%~dp0\installers\WIN95\"
start.
cd "%~dp0"
echo.
pause

)

if exist "%~dp0\installers\WIN95\_PLACE_WIN95_FILES_HERE_" (
del "%~dp0\installers\WIN95\_PLACE_WIN95_FILES_HERE_"
)


if not exist "%~dp0\installers\WIN95\WIN95_02.cab" (
echo Windows 95 installation files still not found.
echo Restart the script after copying installation files.
pause
exit
)

if not exist "%ZPATH%\7za.exe" (
mkdir .\installers\7-zip
echo Downloading 7-zip
powershell wget https://www.7-zip.org/a/7zr.exe -UseBasicParsing -OutFile "%~dp0\installers\7-zip\7zr.exe"
powershell wget https://www.7-zip.org/a/7z2201-extra.7z -UseBasicParsing -OutFile "%~dp0\installers\7-zip\7z2201-extra.7z"
"%~dp0\installers\7-zip\7zr.exe" x "%~dp0\installers\7-zip\7z2201-extra.7z" -o"%~dp0\installers\7-zip"
)

if not exist "%ZPATH%\7za.exe" (
"%~dp0\installers\7-zip\7zr.exe" x "%~dp0\installers\7-zip\7z2201-extra.7z" -o"%ZPATH%"
)


REM =============================
REM WIN95 FILES EXTRACTION
REM =============================
echo.
echo Extracting Windows 95 installation files
echo.

if not exist "%~dp0\installers\WIN95\MINI\KRNL386.EXE" (
"%ZPATH%\7za.exe" x "%~dp0\installers\WIN95\MINI.CAB" -o"%~dp0\installers\WIN95\MINI"
)
if not exist "%~dp0\installers\WIN95\WIN95_02\VMM32.VXD" (
"%ZPATH%\7za.exe" x "%~dp0\installers\WIN95\WIN95_02.CAB" -o"%~dp0\installers\WIN95\WIN95_02"
)
if not exist "%~dp0\installers\WIN95\PRECOPY1\COMMAND.COM" (
"%ZPATH%\7za.exe" x "%~dp0\installers\WIN95\PRECOPY1.CAB" -o"%~dp0\installers\WIN95\PRECOPY1"
)
if not exist "%~dp0\installers\WIN95\SWINST4\REGSVR32.EXE" (
"%ZPATH%\7za.exe" x "%~dp0\installers\WIN95\SWINST4.EXE" -o"%~dp0\installers\WIN95\SWINST4"
)
if not exist "%~dp0\installers\WIN95\WIN95_02\SETUPSLT\REGSVR32.EXE" (
"%ZPATH%\7za.exe" x "%~dp0\installers\WIN95\WIN95_02\SETUPSLT.EXE" -o"%~dp0\installers\WIN95\WIN95_02\SETUPSLT"
)
if not exist "%~dp0\installers\WIN95\WIN95_02\SETUP32" (
"%ZPATH%\7za.exe" x "%~dp0\installers\WIN95\WIN95_02\SETUP32.EXE" -o"%~dp0\installers\WIN95\WIN95_02\SETUP32"
)
if not exist "%~dp0\installers\WIN95\WIN95_02\SETUP25i" (
"%ZPATH%\7za.exe" x "%~dp0\installers\WIN95\WIN95_02\SETUP25i.EXE" -o"%~dp0\installers\WIN95\WIN95_02\SETUP25i"
)
REM =============================










REM =============================
REM WIN95 UPDATES DOWNLOAD
REM =============================
if not exist "%~dp0\installers\DX7Aeng.exe" (
echo Downloading DirectX 7.0A  DX7Aeng.exe
powershell wget http://web.archive.org/web/20020607231943if_/http://download.microsoft.com/download/win98SE/Update/7.0a/W9X/EN-US/DX7Aeng.exe -UseBasicParsing -OutFile "%~dp0\installers\DX7Aeng.exe"
)

if not exist "%~dp0\installers\dcom95.exe" (
echo Downloading DCOM95 dcom95.exe
powershell wget http://web.archive.org/web/20020223193556if_/http://msdl.microsoft.com/msdownload/dcom/95/x86/en/dcom95.exe -UseBasicParsing -OutFile "%~dp0\installers\dcom95.exe"
)

if not exist "%~dp0\installers\w95y2k.exe" (
echo Downloading Year 2000 patch w95y2k.exe
powershell wget http://web.archive.org/web/20010607121741if_/http://msdownload.microsoft.com/msdownload/w95/y2kupdate/x86/en/w95y2k.exe -UseBasicParsing -OutFile "%~dp0\installers\w95y2k.exe"
)

if not exist "%~dp0\installers\mpfull.exe" (
echo Downloading Windows Media Player 6.4 mpfull.exe
powershell wget http://web.archive.org/web/20040612122847if_/http://download.microsoft.com/download/winmediaplayer/update/6.4/w9xnt4/en-us/mpfull.exe -UseBasicParsing -OutFile "%~dp0\installers\mpfull.exe"
)

if not exist "%~dp0\installers\W95WS2setup.exe" (
echo Downloading Winsock 2 Update W95WS2setup.exe
powershell wget http://web.archive.org/web/20010418081915if_/http://microsoft.com/windows/downloads/bin/W95WS2setup.exe -UseBasicParsing -OutFile "%~dp0\installers\W95WS2setup.exe"
)

if not exist "%~dp0\installers\vg-w9x-q3.exe" (
echo Downloading 3Dfx Voodoo Graphics driver vg-w9x-q3.exe
powershell wget http://web.archive.org/web/20031111193444if_/https://www.3dfxzone.it/voodoo1/3dfx/vg-w9x-q3.exe -UseBasicParsing -OutFile "%~dp0\installers\vg-w9x-q3.exe"
)

if not exist "%~dp0\installers\w9521103.zip" (
echo Downloading S3 Graphics driver w9521103.zip
powershell wget http://web.archive.org/web/19970625230911if_/http://www.s3.com/bbs/764drv/w9521103.zip -UseBasicParsing -OutFile "%~dp0\installers\w9521103.zip"
)
REM =============================









REM =============================
REM DOWNLOADS CHECKSUM VALIDATION
REM =============================
echo Checking SHA256 of DX7Aeng.exe (564de93dcc50691480332e2ccb5565908760b295faa70f8c68854f69dad87189 expected)
powershell "Get-FileHash '%~dp0\installers\DX7Aeng.exe' -Algorithm SHA256 | %% { if($_.Hash -match '564de93dcc50691480332e2ccb5565908760b295faa70f8c68854f69dad87189') {Echo 'SHA256 OK'} else{exit 1} }"
if errorlevel 1 (
echo.
echo Bad DX7Aeng.exe checksum
echo Download file manually before continuing or press any key to ignore
pause
)

echo Checking SHA256 of dcom95.exe (6706f79435d75682b0ce69b144108b3c344cae9f7aee7490de47aa20b4f311d3 expected)
powershell "Get-FileHash '%~dp0\installers\dcom95.exe' -Algorithm SHA256 | %% { if($_.Hash -match '6706f79435d75682b0ce69b144108b3c344cae9f7aee7490de47aa20b4f311d3') {Echo 'SHA256 OK'} else{exit 1} }"
if errorlevel 1 (
echo.
echo Bad dcom95.exe checksum
echo Download file manually before continuing or press any key to ignore
pause
)

echo Checking SHA256 of w95y2k.exe (d3c063f2b04311ddbffd8461aa47147d6307f26d2163bef2c715cd168657aa3f expected)
powershell "Get-FileHash '%~dp0\installers\w95y2k.exe' -Algorithm SHA256 | %% { if($_.Hash -match 'd3c063f2b04311ddbffd8461aa47147d6307f26d2163bef2c715cd168657aa3f') {Echo 'SHA256 OK'} else{exit 1} }"
if errorlevel 1 (
echo.
echo Bad w95y2k.exe checksum
echo Download file manually before continuing or press any key to ignore
pause
)

echo Checking SHA256 of mpfull.exe (a39b2b9735cedd513fcb78f8634695d35073e9d7e865e536a0da6db38c7225e4 expected)
powershell "Get-FileHash '%~dp0\installers\mpfull.exe' -Algorithm SHA256 | %% { if($_.Hash -match 'a39b2b9735cedd513fcb78f8634695d35073e9d7e865e536a0da6db38c7225e4') {Echo 'SHA256 OK'} else{exit 1} }"
if errorlevel 1 (
echo.
echo Bad mpfull.exe checksum
echo Download file manually before continuing or press any key to ignore
pause
)

echo Checking SHA256 of W95WS2setup.exe (48c82825328ef63bce1d471d505f0e243cae94b5b05c66cf2e51b75c6d4d4922 expected)
powershell "Get-FileHash '%~dp0\installers\W95WS2setup.exe' -Algorithm SHA256 | %% { if($_.Hash -match '48c82825328ef63bce1d471d505f0e243cae94b5b05c66cf2e51b75c6d4d4922') {Echo 'SHA256 OK'} else{exit 1} }"
if errorlevel 1 (
echo.
echo Bad W95WS2setup.exe checksum
echo Download file manually before continuing or press any key to ignore
pause
)

echo Checking SHA256 of vg-w9x-q3.exe (afde9cfc18080ba4bd94972b783867a9c713e6df3643fef84db5da19414ceea8 expected)
powershell "Get-FileHash '%~dp0\installers\vg-w9x-q3.exe' -Algorithm SHA256 | %% { if($_.Hash -match 'afde9cfc18080ba4bd94972b783867a9c713e6df3643fef84db5da19414ceea8') {Echo 'SHA256 OK'} else{exit 1} }"
if errorlevel 1 (
echo.
echo Bad vg-w9x-q3.exe checksum
echo Download file manually before continuing or press any key to ignore
pause
)

echo Checking SHA256 of w9521103.zip (fb691c872cd7dcc00d7b9445af6d82777586e356e165d5db56f213fa81e96881 expected)
powershell "Get-FileHash '%~dp0\installers\w9521103.zip' -Algorithm SHA256 | %% { if($_.Hash -match 'fb691c872cd7dcc00d7b9445af6d82777586e356e165d5db56f213fa81e96881') {Echo 'SHA256 OK'} else{exit 1} }"
if errorlevel 1 (
echo.
echo Bad w9521103.zip checksum
echo Download file manually before continuing or press any key to ignore
pause
)
REM =============================





REM =============================
REM UPDATES EXTRACTION
REM =============================
echo.
echo Extracting Windows 95 installation files
echo.

mkdir "%~dp0\installers\expanded" 

if not exist "%~dp0\installers\expanded\dcom95\dllhost.exe" (
"%ZPATH%\7za.exe" x "%~dp0\installers\dcom95.exe" -o"%~dp0\installers\expanded\dcom95"
)
if not exist "%~dp0\installers\expanded\DX7Aeng\ddraw.dll" (
"%ZPATH%\7za.exe" x "%~dp0\installers\DX7Aeng.exe" -o"%~dp0\installers\expanded\DX7Aeng"
)
if not exist "%~dp0\installers\expanded\mpfull\mplayer2.exe" (
"%ZPATH%\7za.exe" x "%~dp0\installers\mpfull.exe" -o"%~dp0\installers\expanded\mpfull"
)
if not exist "%~dp0\installers\expanded\mpfull\dxmini\ddhelp.exe" (
"%ZPATH%\7za.exe" x "%~dp0\installers\mpfull\dxmini.exe" -o"%~dp0\installers\expanded\mpfull\dxmini"
)
if not exist "%~dp0\installers\expanded\vg-w9x-q3\voodoo.inf" (
"%ZPATH%\7za.exe" x "%~dp0\installers\vg-w9x-q3.exe" -o"%~dp0\installers\expanded\vg-w9x-q3"
)
if not exist "%~dp0\installers\expanded\w9521103\S3.INF" (
"%ZPATH%\7za.exe" x "%~dp0\installers\w9521103.zip" -o"%~dp0\installers\expanded\w9521103"
)
if not exist "%~dp0\installers\expanded\w95y2k\WINFILE.EXE" (
"%ZPATH%\7za.exe" x "%~dp0\installers\w95y2k.exe" -o"%~dp0\installers\expanded\w95y2k"
)
if not exist "%~dp0\installers\expanded\W95WS2setup\ping.exe" (
"%ZPATH%\7za.exe" x "%~dp0\installers\W95WS2setup.exe" -o"%~dp0\installers\expanded\W95WS2setup"
)
REM =============================



echo.
echo Extracting config files and utilities
"%ZPATH%\7za.exe" x "%~dp0\installers\w95-inst-utils-cfgfiles.7z" -o"%~dp0\installers"

echo.
echo Creating Windows 95 directory structure
echo.
pushd "%~dp0\installers"
call makewin95dir.bat

echo.
echo Applying patches
cd "%~dp0\installers\xdelta"
call "%~dp0\installers\xdelta\undelta.bat"
cd "%~dp0\installers"
call "%~dp0\installers\copypatched.bat"

if not exist "%~dp0\dosbox-x.exe" (


if not exist "%DBOXIN%\dosbox-x-mingw*.<zip" (
echo Downloading DOSbox-X
powershell wget https://github.com/joncampbell123/dosbox-x/releases/download/dosbox-x-v0.84.3/dosbox-x-mingw-win64-20220901233004.zip -UseBasicParsing -OutFile "%DBOXIN%\dosbox-x-mingw-win64-20220901233004.zip"
)

echo Extracting DOSbox-X
"%ZPATH%\7za.exe" x "%DBOXIN%\dosbox-x-*" -o"%~dp0" mingw-build\mingw\*

pushd "%~dp0\mingw-build\mingw"
for %%i in (*) do move "%%i" "%~dp0"
for /d %%i in (*) do move "%%i" "%~dp0"
pushd "%~dp0"
rmdir "%~dp0\mingw-build\mingw"
rmdir "%~dp0\mingw-build"

)

echo Copying DOSbox-X config files and utilities
xcopy /Y /E "%~dp0\installers\dosbox-utils\*.*" "%~dp0\*.*"

echo.
echo Starting auto-installation procedure in DOSbox-X, please wait and do not interfere...
echo.
timeout /t 2 > nul

mkdir "%~dp0\HDD"

pushd "%~dp0"

dosbox-x.exe -noautoexec -c "config -set turbo=true " -c "IMGMAKE .\HDD\WIN95.IMG -t %HDTEMPLATE% " -c "IMGMOUNT C .\HDD\WIN95.IMG -size %HDCHS% " -c "MOUNT D: .\installers " -c "4dos D:\prephdd.bat"

timeout /t 1 > NUL

echo.
echo Setting pre-selected screen resolution
if "%SCREENRES%"=="800x600x16bpp" call "%~dp0\CONFIG_SCRIPTS\800x600_16bpp_DPI-scaled.bat"
if "%SCREENRES%"=="640x480x16bpp" call "%~dp0\CONFIG_SCRIPTS\640x480_16bpp_DPI-scaled.bat"

REM ask for product key on first boot
if "%PRODUCTKEY%"=="ask" echo. >> "%~dp0\guest_tools\runonce\runonce.bat"
if "%PRODUCTKEY%"=="ask" type "%~dp0\guest_tools\guest-scripts\prodtyp9.bat" >> "%~dp0\guest_tools\runonce\runonce.bat"


REM disable startup/shutdown sounds
if "%DISABLEONOFFSOUNDS%"=="true" echo. >> "%~dp0\guest_tools\runonce\runonce.bat"
if "%DISABLEONOFFSOUNDS%"=="true" type "%~dp0\guest_tools\guest-scripts\nostsnd.bat" >> "%~dp0\guest_tools\runonce\runonce.bat"


timeout /t 1 > NUL


echo Setting HDD size in config file
pushd "%~dp0"
del /Q dosbox-x.new
powershell "Get-Content 'dosbox-x.conf' | Foreach-Object {$_ -replace 'size 512,63,16,1023 -ide 1m','size %HDCHS% -ide 1m'} | Set-Content 'dosbox-x.new'"
del /Q dosbox-x.conf
copy dosbox-x.new dosbox-x.conf

REM that will make the machine turn off after first boot
copy dosbox-x.new dosbox-x.conf
echo SHUTDOWN > .\SHARED_DRIVE\launchit.cfg

echo Trying to boot for first time...
dosbox-x.exe -c "MOUNT D: .\SHARED_DRIVE -ide 2s " -c "BOOT C: "

del /Q .\SHARED_DRIVE\launchit.cfg


echo Enabling turbo on boot time
pushd "%~dp0"
del /Q dosbox-x.new
powershell "Get-Content 'dosbox-x.conf' | Foreach-Object {$_ -replace '#turbo last second','turbo last second'} | Set-Content 'dosbox-x.new'"
del /Q dosbox-x.conf
copy dosbox-x.new dosbox-x.conf
powershell "Get-Content 'dosbox-x.conf' | Foreach-Object {$_ -replace '#stop turbo after second','stop turbo after second'} | Set-Content 'dosbox-x.new'"
del /Q dosbox-x.conf
copy dosbox-x.new dosbox-x.conf
powershell "Get-Content 'dosbox-x.conf' | Foreach-Object {$_ -replace '#stop turbo on key','stop turbo on key'} | Set-Content 'dosbox-x.new'"
del /Q dosbox-x.conf
copy dosbox-x.new dosbox-x.conf


echo.
echo Done! Start dosbox-x.exe to launch Windows 95.
echo.

pause

