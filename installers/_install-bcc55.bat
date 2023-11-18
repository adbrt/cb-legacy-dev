@echo off
REM BCC5.5 INSTALLATION
REM =========================

set PATH=%PATH%;%SYSTEMROOT%\System32\WindowsPowerShell\v1.0\

pushd "%~dp0"
if not exist "%~dp0\CodeBlocks\" mkdir CodeBlocks
cd CodeBlocks
if not exist "%~dp0\installers\freecommandLinetools.exe" (
mkdir installers
echo Downloading BCC5.5 compiler from http://altd.embarcadero.com/download/bcppbuilder/freecommandLinetools.exe
powershell wget http://altd.embarcadero.com/download/bcppbuilder/freecommandLinetools.exe -UseBasicParsing -OutFile "%~dp0\installers\freecommandLinetools.exe"
)


echo Checking SHA256 of freecommandLinetools.exe (433B44741F07F2AD673EB936511D498C5A6B7F260F98C4D9A6DA70C41A56D855 expected)

powershell "Get-FileHash '%~dp0\installers\freecommandLinetools.exe' -Algorithm SHA256 | %% { if($_.Hash -match '433B44741F07F2AD673EB936511D498C5A6B7F260F98C4D9A6DA70C41A56D855') {Echo 'SHA256 OK'} else{exit 1} }"

if errorlevel 1 (
echo.
echo Bad freecommandLinetools.exe checksum
echo Trying to download again from another sourcce
powershell wget http://web.archive.org/web/20220816023824if_/http://altd.embarcadero.com/download/bcppbuilder/freecommandLinetools.exe -UseBasicParsing -OutFile "%~dp0\installers\freecommandLinetools.exe"
)

echo Checking SHA256 of freecommandLinetools.exe (433B44741F07F2AD673EB936511D498C5A6B7F260F98C4D9A6DA70C41A56D855 expected)

powershell "Get-FileHash '%~dp0\installers\freecommandLinetools.exe' -Algorithm SHA256 | %% { if($_.Hash -match '433B44741F07F2AD673EB936511D498C5A6B7F260F98C4D9A6DA70C41A56D855') {Echo 'SHA256 OK'} else{exit 1} }"

if errorlevel 1 (
echo.
echo Bad freecommandLinetools.exe checksum
echo Download the file manually and place freecommandLinetools.exe in directory
echo then press any key to continue, or close the console window and exit
echo.
pause
)

if not exist "%~dp0\CodeBlocks\BCC55\bin\bcc32.exe" (
echo Unpacking BCC55
"%ZPATH%\7z.exe" x "%~dp0\installers\freecommandLinetools.exe" -o"%~dp0\CodeBlocks\BCC55"
)

echo Updating BCC55 default path

cd /D "%~dp0"
cd CodeBlocks\share\CodeBlocks\compilers
powershell "((Get-Content -path compiler_bcc.xml -Raw) -replace 'C:\\Borland\\BCC55','\$(APPPATH)\\BCC55') | Set-Content -Path compiler_bcc.xml"

REM add additional path for resource compiler
powershell "((Get-Content -path compiler_bcc.xml -Raw) -replace ' <Path type=\""include\"">','<Path type=\""resource\""><Add><master/>\include</Add></Path><Path type=\""include\"">') | Set-Content -Path compiler_bcc.xml"

pushd %~dp0