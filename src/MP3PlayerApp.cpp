#include "MP3PlayerApp.h"

AudioGeneratorMP3* mp3 = nullptr;
AudioFileSourceSD* file = nullptr;
extern AudioOutputI2S* out;
static bool uiEnabled = true;



MP3PlayerApp::MP3PlayerApp(ButtonManager& buttons, OLEDDisplayManager& display, SDCardManager& sd, PlayerController& player, UIController& ui)
    : buttons(buttons), displayManager(display), sdManager(sd), player(player), ui(ui) {}

void MP3PlayerApp::setup() {
    Serial.begin(115200);
    if (!displayManager.getDisplay().begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("OLED init failed");
        while (1);
    }
    displayManager.getDisplay().clearDisplay();

    if (!sdManager.begin(5)) {
        Serial.println("SD init failed");
        return;
    }

    player.updateTrackInfo();
    String filename = sdManager.getCurrentTrack();
    String path = "/" + filename;
    if (!path.endsWith(".mp3")) path += ".mp3";

    file = new AudioFileSourceSD(path.c_str());
    if (!file->isOpen()) {
        Serial.println("Cannot open MP3 file");
        return;
    }

    mp3 = new AudioGeneratorMP3();
    if (!mp3->begin(file, out)) {
        Serial.println("MP3 begin failed");
        delete file;
        delete mp3;
        file = nullptr;
        mp3 = nullptr;
    }
}



void MP3PlayerApp::loop() {
    // Jeśli MP3 aktywny i gra – wywołuj loop()
    if (mp3 && mp3->isRunning()) {
        if (player.isPlaying() && !isPaused) {
            if (!mp3->loop()) {
                // Auto-next
                mp3->stop();
                delete mp3; mp3 = nullptr;
                delete file; file = nullptr;

                sdManager.nextTrack();
                player.updateTrackInfo();
                ui.update(player, true);

                ui.setUiEnabled(false);
                String filename = sdManager.getCurrentTrack();
                String path = "/" + filename;
                if (!path.endsWith(".mp3")) path += ".mp3";

                file = new AudioFileSourceSD(path.c_str());
                mp3 = new AudioGeneratorMP3();

                if (!file->isOpen() || !mp3->begin(file, out)) {
                    delete file; file = nullptr;
                    delete mp3; mp3 = nullptr;
                }
                ui.setUiEnabled(true);
            }
        }
    }

    // Pauzowanie / wznawianie
    if (mp3 && mp3->isRunning()) {
        if (!player.isPlaying() && !isPaused) {
            isPaused = true;
        } else if (player.isPlaying() && isPaused) {
            isPaused = false;
        }
    }

    // Jeśli nie ma aktywnego MP3, ale play naciśnięte → start
    if (!mp3 && player.isPlaying()) {
        ui.setUiEnabled(false);
        ui.update(player, true);

        String filename = sdManager.getCurrentTrack();
        String path = "/" + filename;
        if (!path.endsWith(".mp3")) path += ".mp3";

        file = new AudioFileSourceSD(path.c_str());
        mp3 = new AudioGeneratorMP3();

        if (!file->isOpen() || !mp3->begin(file, out)) {
            delete file;
            delete mp3;
            file = nullptr;
            mp3 = nullptr;
        }
        ui.setUiEnabled(true);
    }

    // UI, przyciski itp.
    if (millis() - lastUpdate < LOOP_DELAY) return;
    lastUpdate = millis();

    buttons.update();
    player.handleInput(buttons);

    static String lastTrack = "";
    String current = sdManager.getCurrentTrack();
    if (current != lastTrack) {
        if (mp3) { mp3->stop(); delete mp3; mp3 = nullptr; }
        if (file) { delete file; file = nullptr; }
        lastTrack = current;
    }

    player.update();
    ui.update(player);
}


void UIController::setUiEnabled(bool enabled) {
    uiEnabled = enabled;
}
