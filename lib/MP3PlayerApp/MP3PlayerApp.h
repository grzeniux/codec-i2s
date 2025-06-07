#ifndef MP3_PLAYER_APP_H
#define MP3_PLAYER_APP_H

#include "Buttons.h"
#include "OLEDDisplay.h"
#include "SDCard.h"
#include "PlayerController.h"
#include "UIController.h"
#include "BatteryMonitor.h"
#include <AudioFileSourceSD.h>
#include <AudioGeneratorMP3.h>

class MP3PlayerApp {
public:
    MP3PlayerApp(ButtonManager& buttons,
                 OLEDDisplayManager& display,
                 SDCardManager& sd,
                 PlayerController& player,
                 UIController& ui,
                 BatteryMonitor& battery);

    void setup();
    void loop(float batteryVoltage);

private:
    ButtonManager& buttons;
    OLEDDisplayManager& displayManager;
    SDCardManager& sdManager;
    PlayerController& player;
    UIController& ui;
    BatteryMonitor& battery;

    // Zmienne stanu
    unsigned long lastUpdate = 0;
    unsigned long lastBatteryCheck = 0;
    float lastBatteryVoltage = 0.0;
    bool isPaused = false;

    // Stałe konfiguracyjne
    static constexpr unsigned long LOOP_DELAY = 10;
    static constexpr unsigned long BATTERY_UPDATE_INTERVAL = 10000; // 10 sekund

    // Funkcje pomocnicze
    void startMP3(String trackName);
    void stopMP3();
};

#endif // MP3_PLAYER_APP_H
