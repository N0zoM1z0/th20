@echo off
setlocal
rem Windows companion to scripts/repo-python; supports game-directory copies.
if defined TH20_PYTHON (
    "%TH20_PYTHON%" %*
    exit /b
)
if exist "%~dp0..\.venv\Scripts\python.exe" (
    "%~dp0..\.venv\Scripts\python.exe" %*
    exit /b
)
if exist "D:\Sec-Tools\Reverse\IDA Pro 9.3\python311\python.exe" (
    "D:\Sec-Tools\Reverse\IDA Pro 9.3\python311\python.exe" %*
    exit /b
)
where py >nul 2>nul
if not errorlevel 1 (
    py -3 %*
    exit /b
)
python %*
exit /b
