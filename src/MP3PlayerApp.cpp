#include "MP3PlayerApp.h"

MP3PlayerApp::MP3PlayerApp(ButtonManager& buttons, OLEDDisplayManager& display, SDCardManager& sd, PlayerController& player, UIController& ui)
    : buttons(buttons), displayManager(display), sdManager(sd), player(player), ui(ui) {}

void MP3PlayerApp::setup() {
    Serial.begin(115200);
    if (!displayManager.getDisplay().begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("Błąd inicjalizacji OLED");
        while (1);
    }
    displayManager.getDisplay().clearDisplay();

    if (sdManager.begin(5)) {
        Serial.println("Piosenki załadowane z karty SD.");
        player.updateTrackInfo();
    }
}

void MP3PlayerApp::loop() {
    if (millis() - lastUpdate < LOOP_DELAY) return;
    lastUpdate = millis();

    buttons.update();
    player.handleInput(buttons);
    player.update();
    ui.update(player);
}
