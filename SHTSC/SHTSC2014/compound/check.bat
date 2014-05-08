@echo off
:loop
compound_data.exe
compound_2.exe
compound.exe
fc compound.out compound2.out
if not errorlevel 1  goto loop
