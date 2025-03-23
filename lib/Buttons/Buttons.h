#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>

class ButtonManager {
public:
    ButtonManager(uint8_t playPausePin, uint8_t prevTrackPin, uint8_t nextTrackPin, uint8_t volUpPin, uint8_t volDownPin);
    void update();

    bool wasPlayPausePressed();
    bool wasPrevTrackPressed();
    bool wasNextTrackPressed();
    bool wasVolUpPressed();
    bool wasVolDownPressed();

private:
    uint8_t pinPlayPause, pinPrevTrack, pinNextTrack, pinVolUp, pinVolDown;
    bool lastPlayPauseState, lastPrevTrackState, lastNextTrackState, lastVolUpState, lastVolDownState;
    bool playPausePressed, prevTrackPressed, nextTrackPressed, volUpPressed, volDownPressed;
};

#endif
