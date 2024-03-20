@echo off
setlocal

pushd "%~dp0"

if not exist build mkdir build

pushd build

cl /Zi ..\src\main.c /Feapp.exe /Od /nologo /I..\src 

popd
