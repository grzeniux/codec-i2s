#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>

class ButtonManager {
public:
    ButtonManager(uint8_t playPausePin,
                  uint8_t prevTrackPin,
                  uint8_t nextTrackPin,
                  uint8_t volUpPin,
                  uint8_t volDownPin);

    // Obsługa cykliczna
    void update();

    // Zapytania o kliknięcia
    bool wasPlayPausePressed();
    bool wasPrevTrackPressed();
    bool wasNextTrackPressed();
    bool wasVolUpPressed();
    bool wasVolDownPressed();

private:
    // Piny
    uint8_t pinPlayPause;
    uint8_t pinPrevTrack;
    uint8_t pinNextTrack;
    uint8_t pinVolUp;
    uint8_t pinVolDown;

    // Poprzednie stany
    bool lastPlayPauseState;
    bool lastPrevTrackState;
    bool lastNextTrackState;
    bool lastVolUpState;
    bool lastVolDownState;

    // Flagi kliknięć
    bool playPausePressed;
    bool prevTrackPressed;
    bool nextTrackPressed;
    bool volUpPressed;
    bool volDownPressed;
};

#endif // BUTTONS_H
