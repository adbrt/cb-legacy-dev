@echo off
pushd "%~dp0"
cd ..

echo Checking DPI and setting correct scaling for 1024x768
echo.
echo System DPI:
powershell "$dpi = try { (Get-ItemPropertyValue -Path 'HKCU:\Control Panel\Desktop' -Name 'LogPixels') } catch { try { powershell (Get-ItemPropertyValue -Path 'HKCU:\Control Panel\Desktop\WindowMetrics' -Name 'AppliedDPI') } catch { 96 }  }; echo $dpi "
echo.

set "tempfile=tmpresfil.tmp"
>"%tempfile%" powershell "$dpi = try { (Get-ItemPropertyValue -Path 'HKCU:\Control Panel\Desktop' -Name 'LogPixels') } catch { try { powershell (Get-ItemPropertyValue -Path 'HKCU:\Control Panel\Desktop\WindowMetrics' -Name 'AppliedDPI') } catch { 96 }  }; if ($dpi -In -999..113) { echo 1024x768 } ; if ($dpi -In 114..134) { echo 1280x960 } ; if ($dpi -In 135..164) { echo 1536x1152 } ; if ($dpi -In 165..182) { echo 1792x1344 } ; if ($dpi -In 183..999) { echo 2048x1536 } "

set /p RESOLUTIONSTRING=<"%tempfile%"
del /q "%tempfile%"

echo Scaling 1024x768 to:
echo %RESOLUTIONSTRING%

powershell "Get-Content 'dosbox-x.conf' | Foreach-Object {$_ -replace '^windowresolution.+$','windowresolution = %RESOLUTIONSTRING%'} | Set-Content 'dosbox-x.new'"

if exist "dosbox-x.new" (
del /Q dosbox-x.conf.bak
rename dosbox-x.conf dosbox-x.conf.bak
rename dosbox-x.new dosbox-x.conf
)

REM del /Q ".\guest_tools\runonce\runonce.bat"
echo. >> ".\guest_tools\runonce\runonce.bat"
type ".\guest_tools\guest-scripts\1024_16bpp.bat" >> ".\guest_tools\runonce\runonce.bat"