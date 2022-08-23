@echo off
xcopy .\Game\res\* .\bin\windows-Debug-x86_64\res\* /S /Y
cd bin\windows-Debug-x86_64\
.\Game.exe
cd ..\..
@echo on