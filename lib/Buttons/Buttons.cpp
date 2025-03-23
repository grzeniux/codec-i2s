#include "Buttons.h"

ButtonManager::ButtonManager(uint8_t playPausePin, uint8_t prevTrackPin, uint8_t nextTrackPin, uint8_t volUpPin, uint8_t volDownPin)
    : pinPlayPause(playPausePin), pinPrevTrack(prevTrackPin), pinNextTrack(nextTrackPin), pinVolUp(volUpPin), pinVolDown(volDownPin),
      lastPlayPauseState(HIGH), lastPrevTrackState(HIGH), lastNextTrackState(HIGH), lastVolUpState(HIGH), lastVolDownState(HIGH),
      playPausePressed(false), prevTrackPressed(false), nextTrackPressed(false), volUpPressed(false), volDownPressed(false) {
    pinMode(pinPlayPause, INPUT_PULLUP);
    pinMode(pinPrevTrack, INPUT_PULLUP);
    pinMode(pinNextTrack, INPUT_PULLUP);
    pinMode(pinVolUp, INPUT_PULLUP);
    pinMode(pinVolDown, INPUT_PULLUP);
}

void ButtonManager::update() {
    bool currentPlayPause = digitalRead(pinPlayPause);
    bool currentPrevTrack = digitalRead(pinPrevTrack);
    bool currentNextTrack = digitalRead(pinNextTrack);
    bool currentVolUp = digitalRead(pinVolUp);
    bool currentVolDown = digitalRead(pinVolDown);

    playPausePressed = (currentPlayPause == LOW && lastPlayPauseState == HIGH);
    prevTrackPressed = (currentPrevTrack == LOW && lastPrevTrackState == HIGH);
    nextTrackPressed = (currentNextTrack == LOW && lastNextTrackState == HIGH);
    volUpPressed = (currentVolUp == LOW && lastVolUpState == HIGH);
    volDownPressed = (currentVolDown == LOW && lastVolDownState == HIGH);

    lastPlayPauseState = currentPlayPause;
    lastPrevTrackState = currentPrevTrack;
    lastNextTrackState = currentNextTrack;
    lastVolUpState = currentVolUp;
    lastVolDownState = currentVolDown;
}

bool ButtonManager::wasPlayPausePressed() { return playPausePressed; }
bool ButtonManager::wasPrevTrackPressed() { return prevTrackPressed; }
bool ButtonManager::wasNextTrackPressed() { return nextTrackPressed; }
bool ButtonManager::wasVolUpPressed()     { return volUpPressed; }
bool ButtonManager::wasVolDownPressed()   { return volDownPressed; }
