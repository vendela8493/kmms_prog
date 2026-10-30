@echo off
chcp 1251 > log
del log 

set EXE=mario.exe
set CHARSET="-finput-charset=utf-8 -fexec-charset=windows-1251"

if exist %EXE% del %EXE%

g++ "%CHARSET%" main.cpp game_object.cpp moving_object.cpp map.cpp level.cpp player.cpp enemy.cpp -o %EXE%

if exist %EXE% (
	%EXE%
)