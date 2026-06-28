@echo off

rem lupdate.exe所在的绝对路径
@set upt=D:\Qt\Qt6.11\6.11.1\msvc2022_64\bin\lupdate.exe
@set srcdir=%~dp0..\

%upt% %srcdir% -ts zh_CN.ts zh_TW.ts en.ts ru.ts