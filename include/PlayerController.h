#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include <Arduino.h>
#include "Buttons.h"
#include "SDCard.h"

class PlayerController {
public:
    PlayerController(SDCardManager& sd);
    void handleInput(ButtonManager& buttons);
    void update();
    void clearVolumeChangedFlag();
    void setPlay(bool play);
    void updateTrackInfo();

    int getCurrentTime() const;
    int getTotalTime() const;
    int getVolume() const;

    bool isPlayClicked();
    bool isNextClicked();
    bool isPrevClicked();
    bool wasVolumeChanged();
    bool isPlaying() const;

    String getCurrentSongTitle() const;

private:
    SDCardManager& sdManager;
    int volumeLevel = 5;
    int currentTime = 0;
    int totalTime = 0;

    unsigned long lastSecondUpdate = 0;
    const unsigned long SECOND_INTERVAL = 1000;
    
    bool playing = true;
    bool volumeChanged = false;
    bool playClicked = false;
    bool nextClicked = false;
    bool prevClicked = false;

    unsigned long playClickTime = 0;
    unsigned long nextClickTime = 0;
    unsigned long prevClickTime = 0;
    const unsigned long CLICK_ANIM_DURATION = 200;

};

#endif
