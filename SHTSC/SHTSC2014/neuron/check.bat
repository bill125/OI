@echo off
:loop
neuron_data.exe
neuron_2.exe
neuron.exe
fc neuron.out neuron2.out
if not errorlevel 1  goto loop
