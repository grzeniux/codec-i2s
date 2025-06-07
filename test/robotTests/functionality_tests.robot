*** Settings ***
Library         ../lib/read_serial.py
Library         ../lib/TabulateLibrary.py
Library         String

Resource        ../robotTests/keywords.resource


Suite Setup   Set default gpio
#Test Setup    Ensure music is stopped

Test Tags    i2s

*** Variables ***
@{EXPECTED_TITLES}
...                    Connor Kauffman - Bleed
...                    Eminem - Lose Yourself
...                    Felix Jaehn & Shouse - Walk With Me
...                    Fly Away
...                    Gibbs - Zawsze chciałem
...                    Lordofon - Cheesy
...                    Paramore - Hard Times
...                    zawsze tam gdzie ja
...                    Pitbull Lil Jon - JUMPIN
...                    Confetti - Right Now

${ESP32_PORT_UART}   COM13
${ESP32_BAUD}   115200
${TIMEOUT}      2
${SERIAL_READ_TIME}    20



*** Test Cases ***
#VERIFY_QUE_SONG
#    [Documentation]  Po reboocie (z Confetti - Right Now) weryfikuje kolejność 10 utworów
#    [Tags]    i2s
#    Hardware Reboot
#    Sleep  2s
#
#    Open Serial Port    ${ESP32_PORT_UART}   ${ESP32_BAUD}   ${TIMEOUT}
#    ${lines}=    Read Next Tracks    11
#    Close Serial Port
#
#    ${log_lines}=       Extract Relevant Logs    @{lines}
#    ${actual_titles}=   Extract Titles From Logs Robust    @{log_lines}
#
#    Print Song Table    ${EXPECTED_TITLES}    ${actual_titles}
#    Lists Should Be Equal    ${EXPECTED_TITLES}    ${actual_titles}

VERIFY_PLAY_PAUSE_TOGGLE
    [Documentation]  Sprawdza poprawne przełączanie Play/Pause i analizuje czy piosenka gra
    [Tags]    i2s
    [Setup]    Hardware Reboot

    Open Serial Port    ${ESP32_PORT_UART}    ${ESP32_BAUD}    ${TIMEOUT}
    Play Stop
    Sleep    1
    ${logs_after_play}=    Read From Serial    5
    Verify Log Contains Action    ${logs_after_play}    PLAY

    Play Stop
    Sleep    1
    ${logs_after_pause}=    Read From Serial    5
    Verify Log Contains Action    ${logs_after_pause}    PAUSE
    [Teardown]    Close Serial Port
#
#MEASURE_BOOT_TIMES_OVER_10_RUNS
#    [Documentation]    Mierzy czasy startu urządzenia przez 10 restartów i wypisuje je w ms i sekundach.
#    ${boot_times}=    Create List
#    ${boot_times_sec}=    Create List
#
#    FOR    ${index}    IN RANGE    10
#        Log    Iteracja: ${index + 1}
#        Hardware Reboot
#        Sleep    1s
#        Open Serial Port    ${ESP32_PORT_UART}    ${ESP32_BAUD}    ${TIMEOUT}
#        Sleep    1s
#        ${lines}=    Read From Serial    10
#        Close Serial Port
#        ${boot}=    Extract Boot Millis From Lines    ${lines}
#        Append To List    ${boot_times}    ${boot}
#        ${seconds}=    Evaluate    round(${boot} / 1000, 2)
#        Append To List    ${boot_times_sec}    ${seconds}
#    END
#
#    Log    Czasy uruchomienia (ms): ${boot_times}
#    Log    Czasy uruchomienia (s): ${boot_times_sec}
#
#
#VERIFY_VOLUME_CONTROL
#    [Documentation]  Zwiększa i zmniejsza głośność, potem sprawdza, czy zmiana została zarejestrowana
#    [Tags]    i2s
#    [Setup]    Hardware Reboot
#    Open Serial Port    ${ESP32_PORT_UART}    ${ESP32_BAUD}    ${TIMEOUT}
#
#    Volume Device Up
#    Sleep    2
#    ${logs_after_up}=    Read From Serial    6
#    Verify Log Field Contains    ${logs_after_up}    volume    5    5
#    Verify Log Field Contains    ${logs_after_up}    volume    5    6
#    Verify Log Field Contains    ${logs_after_up}    volume    5    7
#    Verify Log Field Contains    ${logs_after_up}    volume    5    9
#    Verify Log Field Contains    ${logs_after_up}    volume    5    9
#    Verify Log Field Contains    ${logs_after_up}    volume    5    10
#    Close Serial Port
#
#    Open Serial Port    ${ESP32_PORT_UART}    ${ESP32_BAUD}    ${TIMEOUT}
#    Volume Device Down
#    Sleep    2
#    ${logs_after_down}=    Read From Serial    6
#    Verify Log Field Contains    ${logs_after_down}    volume    5    9
#    Verify Log Field Contains    ${logs_after_down}    volume    5    8
#    Verify Log Field Contains    ${logs_after_down}    volume    5    7
#    Verify Log Field Contains    ${logs_after_down}    volume    5    6
#    Verify Log Field Contains    ${logs_after_down}    volume    5    5
#    Verify Log Field Contains    ${logs_after_down}    volume    5    4
#    Verify Log Field Contains    ${logs_after_down}    volume    5    3
#    Verify Log Field Contains    ${logs_after_down}    volume    5    2
#    Verify Log Field Contains    ${logs_after_down}    volume    5    1
#
#    [Teardown]    Close Serial Port
#
#
#
#VERIFY_TRACK_LOOPING
#    [Documentation]  Przechodzi przez wszystkie utwory i sprawdza, czy po ostatnim wraca pierwszy
#    [Setup]    Run Keywords    Hardware reboot   Ensure music is stopped
#
#    Open Serial Port    ${ESP32_PORT_UART}   ${ESP32_BAUD}   ${TIMEOUT}
#    ${titles}=    Create List
#    FOR    ${i}    IN RANGE    10
#        Next
#        Sleep    0.5
#        ${chunk}=    Read From Serial    2
#        FOR    ${item}    IN    @{chunk}
#            ${contains}=    Evaluate    'NEXT' in '''${item}'''
#            Run Keyword If    ${contains}    Append To List    ${titles}    ${item}
#        END
#    END
#    Close Serial Port
#
#    ${parsed}=    Create List
#    FOR    ${log}    IN    @{titles}
#        ${parts}=    Split String    ${log}    ,
#        ${title}=    Get From List    ${parts}    1
#        Append To List    ${parsed}    ${title}
#    END
#    Log Many    ${parsed}
#    Should Contain    ${parsed}    Confetti - Right Now
#
#
#VERIFY_AUTO_NEXT
#    [Documentation]  Czeka na skończenie piosenki i sprawdza, czy pojawił się AUTO_NEXT
#    [Setup]    Hardware Reboot
#    Open Serial Port    ${ESP32_PORT_UART}   ${ESP32_BAUD}   ${TIMEOUT}
#    Play Stop
#    Sleep    155
#    ${lines}=    Read From Serial    10
#    Verify Log Contains Action    ${lines}    AUTO_NEXT
#    Close Serial Port
#

*** Keywords ***
Skip To Song Title
    [Arguments]    ${title}
    ${found}=    Set Variable    False
    ${attempts}=    Set Variable    0
    ${max_attempts}=    Set Variable    20

    WHILE    ${found} == False
        Run Keyword If    ${attempts} >= ${max_attempts}    Fail    Song "${title}" not found within ${max_attempts} skips.
        Next
        ${chunk}=    Read From Serial    3
        FOR    ${line}    IN    @{chunk}
            ${found}=    Run Keyword If    "'${title}'" in '''${line}'''    Set Variable    True
        END
        ${attempts}=    Evaluate    ${attempts} + 1
    END


Read Next Tracks
    [Arguments]    ${count}
    ${lines}=    Create List
    FOR    ${i}    IN RANGE    ${count}
        Next
        ${chunk}=    Read From Serial    12
        FOR    ${line}    IN    @{chunk}
            ${contains}=    Evaluate    'NEXT' in '''${line}'''
            Run Keyword If    ${contains}    Append To List    ${lines}    ${line}
        END
    END
    RETURN    ${lines}

Extract Relevant Logs
    [Arguments]    @{lines}
    ${log_lines}=    Create List
    FOR    ${line}    IN    @{lines}
        ${contains}=    Evaluate    'NEXT' in '''${line}'''
        Run Keyword If    ${contains}    Append To List    ${log_lines}    ${line}
    END
    RETURN    @{log_lines}


Extract Titles From Logs
    [Arguments]    @{log_lines}
    ${actual_titles}=    Create List
    FOR    ${log}    IN    @{log_lines}
        ${parts}=    Split String    ${log}    ,
        ${title}=    Strip String    ${parts[1]}
        Append To List    ${actual_titles}    ${title}
    END
    RETURN    ${actual_titles}

Extract Titles From Logs Robust
    [Arguments]    @{log_lines}
    ${actual_titles}=    Create List
    FOR    ${log}    IN    @{log_lines}
        ${log_string}=    Convert To String    ${log}
        ${log_clean}=     Strip String         ${log_string}
        ${has_log}=       Evaluate    ',' in '''${log_clean}''' and 'LOG' in '''${log_clean}'''
        IF    ${has_log}
            ${parts}=    Split String    ${log_clean}    ,
            ${title}=    Get From List    ${parts}    1
            Append To List    ${actual_titles}    ${title}
        ELSE
            Append To List    ${actual_titles}    ${log_clean}
        END
    END
    RETURN    ${actual_titles}

Set Volume To Level
    [Arguments]    ${target}
    Open Serial Port    ${ESP32_PORT_UART}    ${ESP32_BAUD}    ${TIMEOUT}

    FOR    ${i}    IN RANGE    ${target}
        Volume device up
        Sleep    0.5
    END
    Close Serial Port