@echo off
:loop
charger_data.exe
charger_2.exe
charger_3.exe
fc charger2.out charger.out
if not errorlevel 1 goto loop
pause