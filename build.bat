@echo off

set build_dir=build_windows
mkdir %build_dir%
copy data\settings.dat %build_dir%\settings.dat
cmake.exe -S . -B %build_dir%
