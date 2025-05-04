#ifndef UI_CONTROLLER_H
#define UI_CONTROLLER_H

#include "OLEDDisplay.h"
#include "PlayerController.h"

class UIController {
public:
    UIController(OLEDDisplayManager& display);

    // Aktualizacja interfejsu
    void update(PlayerController& player, bool force, float batteryVoltage);

    // Włączanie/wyłączanie UI
    void setUiEnabled(bool enabled);

private:
    OLEDDisplayManager& displayManager;

    // Stan UI
    bool uiEnabled = true;
    bool showVolumeScreen = false;
    unsigned long volumeScreenTimer = 0;

    // Przewijanie tytułu
    int scrollPixelOffset = 0;
    unsigned long lastScrollTime = 0;

    // Stałe konfiguracyjne
    static constexpr unsigned long VOLUME_SCREEN_TIMEOUT = 1000;
    static constexpr unsigned long SCROLL_INTERVAL = 20;
};

#endif // UI_CONTROLLER_H
