#ifndef MP3_PLAYER_APP_H
#define MP3_PLAYER_APP_H

#include "Buttons.h"
#include "OLEDDisplay.h"
#include "SDCard.h"
#include "PlayerController.h"
#include "UIController.h"
#include <AudioFileSourceSD.h>
#include <AudioGeneratorMP3.h>
#include "MP3InfoExtractor.h"
#include "BatteryMonitor.h"

class MP3PlayerApp {
public:
    MP3PlayerApp(ButtonManager& buttons, OLEDDisplayManager& display, SDCardManager& sd, PlayerController& player, UIController& ui, BatteryMonitor& battery);
    void setup();
    void loop(float batteryVoltage);

private:
    ButtonManager& buttons;
    OLEDDisplayManager& displayManager;
    SDCardManager& sdManager;
    PlayerController& player;
    UIController& ui;

    unsigned long lastUpdate = 0;
    const unsigned long LOOP_DELAY = 20;
    bool isPaused = false;

    BatteryMonitor& battery;
    float lastBatteryVoltage = 0.0;
    unsigned long lastBatteryCheck = 0;
    static constexpr unsigned long BATTERY_UPDATE_INTERVAL = 10000; // 10s
    void startMP3(String trackName);
    void stopMP3();
};

#endif
