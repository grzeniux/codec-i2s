#ifndef UI_CONTROLLER_H
#define UI_CONTROLLER_H

#include "OLEDDisplay.h"
#include "PlayerController.h"

class UIController {
public:
    UIController(OLEDDisplayManager& display);
    void update(PlayerController& player);

private:
    OLEDDisplayManager& displayManager;

    bool showVolumeScreen = false;
    unsigned long volumeScreenTimer = 0;
    const unsigned long VOLUME_SCREEN_TIMEOUT = 1000;

    int scrollPixelOffset = 0;
    unsigned long lastScrollTime = 0;
    const unsigned long SCROLL_INTERVAL = 20;
};

#endif
