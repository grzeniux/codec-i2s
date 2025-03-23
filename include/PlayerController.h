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
    bool wasVolumeChanged();
    void clearVolumeChangedFlag();
    
    bool isPlaying() const;
    int getCurrentTime() const;
    int getTotalTime() const;
    int getVolume() const;
    String getCurrentSongTitle() const;

    void setPlay(bool play);
    bool isPlayClicked();
    bool isNextClicked();
    bool isPrevClicked();
    
private:
    SDCardManager& sdManager;

    bool playing = true;
    int volumeLevel = 5;
    int currentTime = 0;
    const int totalTime = 210;
    bool volumeChanged = false;

    unsigned long lastSecondUpdate = 0;
    const unsigned long SECOND_INTERVAL = 1000;
    
    
    bool playClicked = false;
    bool nextClicked = false;
    bool prevClicked = false;

    unsigned long playClickTime = 0;
    unsigned long nextClickTime = 0;
    unsigned long prevClickTime = 0;
    const unsigned long CLICK_ANIM_DURATION = 200;

};

#endif
