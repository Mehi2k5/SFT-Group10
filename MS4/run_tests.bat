@echo off
set SRC_DIR=src
set TEST_DIR=tests
set BUILD_DIR=build

if exist %BUILD_DIR% (rmdir /S /Q %BUILD_DIR%)
mkdir %BUILD_DIR%
cd %BUILD_DIR%

:: Compile the project
echo Compiling the project...
cmake ..\%SRC_DIR%
if errorlevel 1 (
    echo Compilation failed. Exiting.
    exit /b 1
)
msbuild project.sln /p:Configuration=Release

:: Run blackbox tests
echo Running blackbox tests...
blackbox_tests.exe > blackbox_results.log

:: Run whitebox tests
echo Running whitebox tests...
whitebox_tests.exe > whitebox_results.log

echo Blackbox Test Results:
type blackbox_results.log

echo Whitebox Test Results:
type whitebox_results.log

echo Tests completed successfully.
