@echo off

set BUILD_TYPE=Ninja
set BUILD_SUFFIX=ninja

chcp 65001

set BUILD_FOLDER=build_%BUILD_SUFFIX%
set SOURCE_FOLDER=Source

if not exist %BUILD_FOLDER% mkdir %BUILD_FOLDER%

cd %BUILD_FOLDER%

cmake -G %BUILD_TYPE% ..\%SOURCE_FOLDER%
cmake --build .

set arr[0].file=run_bubble_sort.bat
set arr[1].file=run_bubble_sort_mf.bat
set arr[2].file=run_obuchaika.bat

set arr[0].folder=bubble_sort
set arr[1].folder=bubble_sort_mf
set arr[2].folder=obuchaika

for /L %%i in (0,1,2) do (
	copy ..\%SOURCE_FOLDER%\!arr[%%i].folder!\!arr[%%i].file! .\!arr[%%i].folder!
)

copy ..\run_tests.bat .