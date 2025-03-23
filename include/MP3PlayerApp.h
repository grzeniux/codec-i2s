#ifndef MP3_PLAYER_APP_H
#define MP3_PLAYER_APP_H

#include "Buttons.h"
#include "OLEDDisplay.h"
#include "SDCard.h"
#include "PlayerController.h"
#include "UIController.h"

class MP3PlayerApp {
public:
    MP3PlayerApp(ButtonManager& buttons, OLEDDisplayManager& display, SDCardManager& sd, PlayerController& player, UIController& ui);
    void setup();
    void loop();

private:
    ButtonManager& buttons;
    OLEDDisplayManager& displayManager;
    SDCardManager& sdManager;
    PlayerController& player;
    UIController& ui;

    unsigned long lastUpdate = 0;
    const unsigned long LOOP_DELAY = 20;
};

#endif
