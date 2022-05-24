@echo off
REM run this bat file in a visual studio command prompt

rmdir /s /q bin
rmdir /s /q obj
mkdir bin
mkdir obj
mkdir inc

cl /MD /O2 /c /DLUA_BUILD_AS_DLL /Fo"obj\\" src\*.c
ren obj\lua.obj lua.o
ren obj\luac.obj luac.o
link /DLL /IMPLIB:bin\lua.lib /OUT:bin\lua.dll obj\*.obj 
link /OUT:bin\lua.exe obj\lua.o bin\lua.lib 
lib /OUT:bin\lua-static.lib obj\*.obj
link /OUT:bin\luac.exe obj\luac.o bin\lua-static.lib

xcopy src\*.h inc\