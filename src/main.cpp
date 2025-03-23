#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <AudioOutputI2S.h>

#include "bitmaps.h"
#include "Buttons.h"
#include "OLEDDisplay.h"
#include "SDCard.h"
#include "MP3PlayerApp.h"
#include "PlayerController.h"
#include "UIController.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

AudioOutputI2S* out = new AudioOutputI2S();
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
OLEDDisplayManager oledManager(display);
ButtonManager buttons(36, 39, 34, 35, 2);
SDCardManager& sdManager = SDCardManager::getInstance();
PlayerController player(sdManager);
UIController ui(oledManager);
MP3PlayerApp app(buttons, oledManager, sdManager, player, ui);


void setup() {
    out->SetPinout(26, 25, 27);  // BCLK = 26, WS = 25, SDOUT = 27
    out->SetGain(0.0);           // cisza (nie odtwarzamy dźwięku) bo nie ma czym :(
    app.setup();
}

void loop() {
    app.loop();
}
