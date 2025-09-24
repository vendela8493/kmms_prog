@echo off
chcp 1251 > log
del log

set MAIN="main.cpp"
set EXE=example
set CHARSET="-finput-charset=utf-8 -fexec-charset=windows-1251"

g++ "%CHARSET%" "%MAIN%" -o %EXE%

example.exe