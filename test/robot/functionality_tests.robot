*** Settings ***
Library         ../lib/read_serial.py
Library         ../lib/TabulateLibrary.py
Library         String
Library         Collections

Resource        ../robot/keywords.resource

*** Variables ***
@{EXPECTED_TITLES}     Confetti - Right Now
...                    Connor Kauffman - Bleed    
...                    Eminem - Lose Yourself
...                    Felix Jaehn & Shouse - Walk With Me
...                    Fly Away
...                    Gibbs - Zawsze chciałem
...                    Paramore - Hard Times

${ESP32_PORT}   COM4
${ESP32_BAUD}   115200
${TIMEOUT}      2
${SERIAL_READ_TIME}    8

*** Test Cases ***
Test Manual Next Playback Order
    [Documentation]  Przełącza 7 piosenek przyciskiem NEXT i sprawdza kolejność tytułów z logów
    Open Serial Port    ${ESP32_PORT}   ${ESP32_BAUD}   ${TIMEOUT}
    ${lines}=    Create List
    FOR    ${i}    IN RANGE    7
        Next
        ${chunk}=    Read From Serial    2
        FOR    ${item}    IN    @{chunk}
            Append To List    ${lines}    ${item}
        END
    END
    Close Serial Port

    ${log_lines}=    Create List
    FOR    ${line}    IN    @{lines}
        ${contains_next}=    Evaluate    'NEXT' in '''${line}'''
        Run Keyword If    ${contains_next}    Append To List    ${log_lines}    ${line}
    END
    Log Many    ${log_lines}

    ${actual_titles}=    Create List
    FOR    ${log}    IN    @{log_lines}
        ${parts}=    Split String    ${log}    ,
        ${title}=    Get From List    ${parts}    1
        Append To List    ${actual_titles}    ${title}
    END

    Print Song Table    ${EXPECTED_TITLES}    ${actual_titles}
    Lists Should Be Equal    ${EXPECTED_TITLES}    ${actual_titles}
