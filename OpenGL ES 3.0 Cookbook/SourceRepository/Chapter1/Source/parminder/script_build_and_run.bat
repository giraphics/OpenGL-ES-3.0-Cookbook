@echo off
REM =============================================================================
REM script_build_and_run.bat – Desktop build and run for GLPIFrameworkIntro-Modern
REM
REM Prerequisites:
REM   - CMake 3.15+  in PATH
REM   - Visual Studio 2022 (or adjust the generator below)
REM   - Internet access (CMake downloads GLFW + GLEW via FetchContent)
REM
REM Run from the project root (same folder as CMakeLists.txt).
REM =============================================================================

cmake --version >nul 2>&1
IF %ERRORLEVEL% NEQ 0 (
    echo ERROR: CMake not found in PATH.
    pause
    exit /b 1
)

echo [1/3] Configuring ...
IF EXIST build_desktop RMDIR /S /Q build_desktop
MKDIR build_desktop
cmake -S . -B build_desktop -G "Visual Studio 17 2022" -A x64
IF %ERRORLEVEL% NEQ 0 ( echo Configuration failed. & pause & exit /b 1 )

echo [2/3] Building ...
cmake --build build_desktop --config Debug
IF %ERRORLEVEL% NEQ 0 ( echo Build failed. & pause & exit /b 1 )

echo [3/3] Running ...
echo.
echo Watch the triangle rotate. Press ESC to quit.
echo.
pushd build_desktop\Debug
GLPIFrameworkIntro.exe
popd

pause
