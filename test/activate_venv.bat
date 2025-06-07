@echo off
setlocal

echo [✓] Tworzę/aktywuję środowisko wirtualne...

set VENV_DIR=run_tests_venv\.venv

if exist "%VENV_DIR%\Scripts\activate.bat" (
    echo [✓] Środowisko już istnieje. Aktywuję...
) else (
    echo [✓] Środowisko nie istnieje. Tworzę nowe...
    python -m venv %VENV_DIR%
)

call "%VENV_DIR%\Scripts\activate.bat"

echo [✓] Instaluję zależności z req.txt (jeśli są)...
pip install -r run_tests_venv\req.txt

echo [✓] Gotowe! Środowisko aktywne.
