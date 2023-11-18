@echo off
pushd "%~dp0"
cd ..

echo Checking DPI and setting correct scaling for 640x480
echo.
echo System DPI:
powershell "$dpi = try { (Get-ItemPropertyValue -Path 'HKCU:\Control Panel\Desktop' -Name 'LogPixels') } catch { try { powershell (Get-ItemPropertyValue -Path 'HKCU:\Control Panel\Desktop\WindowMetrics' -Name 'AppliedDPI') } catch { 96 }  }; echo $dpi "
echo.

set "tempfile=tmpresfil.tmp"
>"%tempfile%" powershell "$dpi = try { (Get-ItemPropertyValue -Path 'HKCU:\Control Panel\Desktop' -Name 'LogPixels') } catch { try { powershell (Get-ItemPropertyValue -Path 'HKCU:\Control Panel\Desktop\WindowMetrics' -Name 'AppliedDPI') } catch { 96 }  } ; if ($dpi -In -999..113) { echo 640x480 } ; if ($dpi -In 114..134) { echo 800x600 } ; if ($dpi -In 135..164) { echo 960x720 } ; if ($dpi -In 165..182) { echo 1120x840 } ; if ($dpi -In 183..999) { echo 1280x960 } "

set /p RESOLUTIONSTRING=<"%tempfile%"
del /q "%tempfile%"

echo Scaling 640x480 to:
echo %RESOLUTIONSTRING%

powershell "Get-Content 'dosbox-x.conf' | Foreach-Object {$_ -replace '^windowresolution.+$','windowresolution = %RESOLUTIONSTRING%'} | Set-Content 'dosbox-x.new'"

if exist "dosbox-x.new" (
del /Q dosbox-x.conf.bak
rename dosbox-x.conf dosbox-x.conf.bak
rename dosbox-x.new dosbox-x.conf
)

REM del /Q ".\guest_tools\runonce\runonce.bat"
echo. >> ".\guest_tools\runonce\runonce.bat"
type ".\guest_tools\guest-scripts\640_16bpp.bat" >> ".\guest_tools\runonce\runonce.bat"