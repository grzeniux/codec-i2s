@echo off
setlocal

:: Konfiguracja zmiennych
set VENV_PATH=run_tests_venv\.venv\Scripts\activate.bat
set OUTPUT_DIR=robotTestsOutput
set OUTPUT_FILE=output.xml
set LOG_FILE=log.html
set REPORT_FILE=report.html
set TAG=i2s

:: Tworzenie katalogu na wyniki, jeśli nie istnieje
if not exist %OUTPUT_DIR% (
    mkdir %OUTPUT_DIR%
)

echo Aktywowanie środowiska wirtualnego...
call %VENV_PATH%

echo Uruchamianie testów z tagiem "%TAG%"...
robot -i %TAG% -d %OUTPUT_DIR% -o %OUTPUT_FILE% -r %REPORT_FILE% -l %LOG_FILE% --console verbose --loglevel TRACE .

exit /b %ERRORLEVEL%
