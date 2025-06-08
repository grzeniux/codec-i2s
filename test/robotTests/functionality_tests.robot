*** Settings ***
Library         ../lib/read_serial.py
Library         ../lib/TabulateLibrary.py
Library         String

Resource        ../robotTests/keywords.resource


Suite Setup   Set default gpio

Test Tags    i2s

*** Variables ***
${ESP32_PORT_UART}   COM13
${ESP32_BAUD}   115200
${TIMEOUT}      2



*** Test Cases ***
VERIFY_AUTO_NEXT
    [Documentation]  Czeka na skończenie piosenki i sprawdza, czy pojawił się AUTO_NEXT
    [Setup]    Hardware Reboot
    Ensure music is playing
    Open Serial Port    ${ESP32_PORT_UART}   ${ESP32_BAUD}   ${TIMEOUT}
    Sleep    157
    ${lines}=    Read From Serial    5
    Verify Log Contains Action    ${lines}    AUTO_NEXT
    [Teardown]    Close Serial Port

VERIFY_NEXT_AND_PREV_BUTTONS
    [Documentation]  Weryfikuje działanie przycisków NEXT i PREV przez analizę logów z seriala
    Hardware reboot
    Ensure music is playing

    # --- NEXT ---
    Open Serial Port  ${ESP32_PORT_UART}    ${ESP32_BAUD}    ${TIMEOUT}
    Set Gpio State    ${NEXT}    0
    Sleep    0.5
    Set Gpio State    ${NEXT}    1
    Sleep    1
    ${lines_next}=    Read From Serial    3
    Close Serial Port
    Verify Log Contains Action    ${lines_next}    NEXT

    # --- PREV ---
    Open Serial Port  ${ESP32_PORT_UART}    ${ESP32_BAUD}    ${TIMEOUT}
    Set Gpio State    ${PREV}    0
    Sleep    0.5
    Set Gpio State    ${PREV}    1
    Sleep    1
    ${lines_prev}=    Read From Serial    3
    Close Serial Port
    Verify Log Contains Action    ${lines_prev}    PREV

VERIFY_PLAY_PAUSE_TOGGLE
    [Documentation]  Sprawdza poprawne przełączanie Play/Pause i analizuje czy piosenka gra
    [Tags]    i2s
    [Setup]    Hardware Reboot
    Open Serial Port    ${ESP32_PORT_UART}    ${ESP32_BAUD}    ${TIMEOUT}
    Play Stop
    Sleep    1
    ${logs_after_pause}=    Read From Serial    5
    Verify Log Contains Action    ${logs_after_pause}    PAUSE

    Play Stop
    Sleep    1
    ${logs_after_play}=    Read From Serial    5
    Verify Log Contains Action    ${logs_after_play}    PLAY
    [Teardown]    Close Serial Port

MEASURE_BOOT_TIMES_OVER_10_RUNS
    [Documentation]    Mierzy czasy startu urządzenia przez 10 restartów i wypisuje je w ms i sekundach.
    ${boot_times}=    Create List

    FOR    ${index}    IN RANGE    10
        Log    Iteracja: ${index + 1}
        Open Serial Port    ${ESP32_PORT_UART}    ${ESP32_BAUD}    ${TIMEOUT}
        Hardware Reboot
        ${lines}=    Read From Serial    4
        Close Serial Port
        ${boot}=    Extract Boot Millis From Lines    ${lines}
        Append To List    ${boot_times}    ${boot}
    END

    Log    Czasy uruchomienia (ms): ${boot_times}

VERIFY_VOLUME_CONTROL
    [Documentation]  Zwiększa i zmniejsza głośność, potem sprawdza, czy zmiana została zarejestrowana
    [Tags]    i2s
    [Setup]    Hardware Reboot
    Open Serial Port    ${ESP32_PORT_UART}    ${ESP32_BAUD}    ${TIMEOUT}
    Sleep  1s

    Volume Device Up
    ${logs_after_up}=    Read From Serial    4
    Verify Log Field Contains    ${logs_after_up}    volume    5    5
    Verify Log Field Contains    ${logs_after_up}    volume    5    6
    Verify Log Field Contains    ${logs_after_up}    volume    5    7
    Verify Log Field Contains    ${logs_after_up}    volume    5    9
    Verify Log Field Contains    ${logs_after_up}    volume    5    9
    Verify Log Field Contains    ${logs_after_up}    volume    5    10
    Close Serial Port

    Open Serial Port    ${ESP32_PORT_UART}    ${ESP32_BAUD}    ${TIMEOUT}
    Volume Device Down
    ${logs_after_down}=    Read From Serial    4
    Verify Log Field Contains    ${logs_after_down}    volume    5    9
    Verify Log Field Contains    ${logs_after_down}    volume    5    8
    Verify Log Field Contains    ${logs_after_down}    volume    5    7
    Verify Log Field Contains    ${logs_after_down}    volume    5    6
    Verify Log Field Contains    ${logs_after_down}    volume    5    5
    Verify Log Field Contains    ${logs_after_down}    volume    5    4
    Verify Log Field Contains    ${logs_after_down}    volume    5    3
    Verify Log Field Contains    ${logs_after_down}    volume    5    2
    Verify Log Field Contains    ${logs_after_down}    volume    5    1
    [Teardown]    Close Serial Port