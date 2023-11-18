@echo off
pushd "%~dp0"
cd ..

echo Checking DPI and setting correct scaling for 800x600
echo.
echo System DPI:
powershell "$dpi = try { (Get-ItemPropertyValue -Path 'HKCU:\Control Panel\Desktop' -Name 'LogPixels') } catch { try { powershell (Get-ItemPropertyValue -Path 'HKCU:\Control Panel\Desktop\WindowMetrics' -Name 'AppliedDPI') } catch { 96 }  }; echo $dpi "

IF ERRORLEVEL 1 powershell "$dpi = 96 ; $echo scaling not detected, setting default $dpi DPI "
echo.

set "tempfile=tmpresfil.tmp"
>"%tempfile%" powershell "$dpi = try { (Get-ItemPropertyValue -Path 'HKCU:\Control Panel\Desktop' -Name 'LogPixels') } catch { try { powershell (Get-ItemPropertyValue -Path 'HKCU:\Control Panel\Desktop\WindowMetrics' -Name 'AppliedDPI') } catch { 96 }  } ; if ($dpi -In -999..113) { echo 800x600 } ; if ($dpi -In 114..134) { echo 1000x750 } ; if ($dpi -In 135..164) { echo 1200x900 } ; if ($dpi -In 165..182) { echo 1400x1050 } ; if ($dpi -In 183..999) { echo 1600x1200 } "

set /p RESOLUTIONSTRING=<"%tempfile%"
del /q "%tempfile%"

echo Scaling 800x600 to:
echo %RESOLUTIONSTRING%

powershell "Get-Content 'dosbox-x.conf' | Foreach-Object {$_ -replace '^windowresolution.+$','windowresolution = %RESOLUTIONSTRING%'} | Set-Content 'dosbox-x.new'"

if exist "dosbox-x.new" (
del /Q dosbox-x.conf.bak
rename dosbox-x.conf dosbox-x.conf.bak
rename dosbox-x.new dosbox-x.conf
)

REM del /Q ".\guest_tools\runonce\runonce.bat"
echo. >> ".\guest_tools\runonce\runonce.bat"
type ".\guest_tools\guest-scripts\800_16bpp.bat" >> ".\guest_tools\runonce\runonce.bat"