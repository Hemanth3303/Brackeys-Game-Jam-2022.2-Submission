@echo off
xcopy .\Game\res\* .\bin\windows-Release-x86_64\res\* /S /Y
cd bin\windows-Release-x86_64\
.\Light-Robo.exe
cd ..\..
@echo on