*** Settings ***
Library      ../lib/pico.py       %{PICO_PORT}
Library      OperatingSystem
Resource     keywords.resource

*** Variables ***
${PWR_RELAY}       7
${VOL_UP}          11
${VOL_DOWN}        12
${NEXT}            10
${PLAY_STOP}       6
${PREV}            8

*** Keywords ***
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
