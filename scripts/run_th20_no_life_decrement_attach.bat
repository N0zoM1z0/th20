@echo off
setlocal
rem Copy this launcher, runtime-no-life-decrement.py and repo-python.cmd beside th20.exe.
set "GAME_DIR=%~dp0"
if defined TH20_GAME_DIR set "GAME_DIR=%TH20_GAME_DIR%"
cd /d "%GAME_DIR%" || exit /b 1
call "%~dp0repo-python.cmd" "%~dp0runtime-no-life-decrement.py" --game-dir "%GAME_DIR%." --launch --timeout 20
if errorlevel 1 echo Runtime patch failed. See runtime_patch_log.txt.
pause
