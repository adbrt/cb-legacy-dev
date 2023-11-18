@echo off
pushd "%~dp0"


pushd "%~dp0"
cd ..
cd ..
cd installers
SET DBOXIN=%CD%
cd 7-zip
SET ZPATH=%CD%
pushd "%~dp0"

if not exist "%~dp0\dosbox-x.exe" (


if not exist "%DBOXIN%\dosbox-x-mingw*.<zip" (
echo Downloading DOSbox-X
powershell wget https://github.com/joncampbell123/dosbox-x/releases/download/dosbox-x-v0.84.3/dosbox-x-mingw-win64-20220901233004.zip -UseBasicParsing -OutFile "%DBOXIN%\dosbox-x-mingw-win64-20220901233004.zip"
)

echo Extracting DOSbox-X
"%ZPATH%\7z.exe" x "%DBOXIN%\dosbox-x-*" -o"%~dp0" mingw-build\mingw\*

pushd "%~dp0\mingw-build\mingw"
for %%i in (*) do move "%%i" "%~dp0"
for /d %%i in (*) do move "%%i" "%~dp0"
pushd "%~dp0"
rmdir "%~dp0\mingw-build\mingw"
rmdir "%~dp0\mingw-build"

)

copy "%~dp0\installers\dosbox-x.conf" "%~dp0\dosbox-x.conf"
copy "%~dp0\installers\dbxlauncher.bat" "%~dp0\dbxlauncher.bat"

pushd "%~dp0\INSTALLERS"

