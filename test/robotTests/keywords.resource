*** Settings ***
Library      ../lib/pico.py       %{PICO_PORT}
Library      ../lib/read_serial.py
Library      OperatingSystem
Library      Collections
Resource     keywords.resource

*** Variables ***
${PWR_RELAY}       7
${VOL_UP}          11
${VOL_DOWN}        12
${NEXT}            10
${PLAY_STOP}       6
${PREV}            8

*** Keywords ***
Set default gpio
    Set Gpio As Output    ${PWR_RELAY}     0
    Set Gpio As Output    ${VOL_UP}        1
    Set Gpio As Output    ${VOL_DOWN}      1
    Set Gpio As Output    ${NEXT}          1
    Set Gpio As Output    ${PLAY_STOP}     1
    Set Gpio As Output    ${PREV}          1

Cut off power from device
    Set Gpio State    ${PWR_RELAY}    1

Power up device
    Set Gpio State    ${PWR_RELAY}    0

Prev
    Set Gpio State    ${PREV}    1
    Sleep             0.3
    Set Gpio State    ${PREV}    0

Next
    Set gpio state    ${NEXT}      1
    Sleep             0.3
    Set gpio state    ${NEXT}      0
    Sleep             0.3

Play Stop
    Set gpio state    ${PLAY_STOP}      1
    Sleep             0.5
    Set gpio state    ${PLAY_STOP}      0

Volume UP
    Set gpio state    ${VOL_UP}      1
    Sleep             0.5
    Set gpio state    ${VOL_UP}      0
    Sleep             0.5

Volume DOWN
    Set gpio state    ${VOL_DOWN}    1
    Sleep             0.5
    Set gpio state    ${VOL_DOWN}    0
    Sleep             0.5

Volume device up
    FOR    ${TOGGLE_COUNTER}    IN RANGE    0    10
        Volume UP
    END

Volume device down
    FOR    ${TOGGLE_COUNTER}    IN RANGE    0    10
        Volume DOWN
    END

Ensure Music Is Stopped
    [Documentation]  Zatrzymuje muzykę jeśli nadal gra
    Open Serial Port    ${ESP32_PORT_UART}    ${ESP32_BAUD}    ${TIMEOUT}
    Play Stop
    Sleep    1
    ${lines}=    Read From Serial    5
    Close Serial Port

    Run Keyword Unless    ${lines}    Log    "Brak danych z seriala – pomijam analizę stanu muzyki"    WARN
    ${last_line}=    Run Keyword If    ${lines}    Get From List    ${lines}    -1
    ${is_music_playing}=    Run Keyword If    ${lines}    Evaluate    '${last_line}'.split(',')[4].strip() == '1'
    Run Keyword If    '${is_music_playing}' == 'True'    Play Stop


Hardware reboot
    Cut off power from device
    Sleep    3s
    Power up device
    Sleep    2s
