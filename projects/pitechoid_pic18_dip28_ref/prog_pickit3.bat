echo OFF
set hex_file="\dist\default\production\pitechoid_pic18_dip28_ref.production.hex"
echo ON

"C:\Programs\Microchip\MPLABX\v5.35\mplab_platform\mplab_ipe\pk3cmd.exe" -E -OL -F"%hex_file%" -L -M -P18F252

@if exist MPLABXLog* erase MPLABXLog* /f /q /s > nul 2>&1
@if exist log*       erase log*       /f /q /s > nul 2>&1

pause