@echo off
:loop
blaster_data.exe
blaster.exe
blaster_2.exe
fc blaster.out blaster2.out
if not errorlevel 1 goto loop
pause