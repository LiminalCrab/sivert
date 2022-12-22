@echo off
mkdir D:\Projects\sivert\build
@echo "Building Sivert... "
pushd D:\Projects\sivert\build

cl -Zi D:\Projects\sivert\win32_sivert.cpp user32.lib gdi32.lib

popd 
