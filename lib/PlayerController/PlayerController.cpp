#include "PlayerController.h"

extern AudioOutputI2S* out;

PlayerController::PlayerController(SDCardManager& sd) : sdManager(sd) {
    updateTrackInfo();
}

void PlayerController::handleInput(ButtonManager& buttons) {
    if (buttons.wasVolUpPressed() && volumeLevel < 10) {
        volumeLevel++;
        volumeChanged = true;
    }
    if (buttons.wasVolDownPressed() && volumeLevel > 0) {
        volumeLevel--;
        volumeChanged = true;
    }

    unsigned long now = millis();

    if (buttons.wasPlayPausePressed()) {
        playing = !playing;
        playClicked = true;
        playClickTime = now;
    }
    if (buttons.wasNextTrackPressed()) {
        sdManager.nextTrack();
        updateTrackInfo();
        nextClicked = true;
        nextClickTime = now;
    }
    if (buttons.wasPrevTrackPressed()) {
        sdManager.prevTrack();
        updateTrackInfo();
        prevClicked = true;
        prevClickTime = now;
    }
}

void PlayerController::update() {
    unsigned long now = millis();

    if (now - lastSecondUpdate >= SECOND_INTERVAL) {
        lastSecondUpdate = now;

        if (playing && currentTime < totalTime) {
            currentTime++;
        } else if (playing && currentTime >= totalTime) {
            sdManager.nextTrack();
            updateTrackInfo();
        }

        float gain = volumeLevel / 10.0f;
        out->SetGain(gain);
    }
}

bool PlayerController::isPlaying() const { return playing; }
int PlayerController::getCurrentTime() const { return currentTime; }
int PlayerController::getTotalTime() const { return totalTime; }
int PlayerController::getVolume() const { return volumeLevel; }
String PlayerController::getCurrentSongTitle() const { return sdManager.getCurrentTrack(); }
void PlayerController::setPlay(bool play) { playing = play; }
bool PlayerController::wasVolumeChanged() const { return volumeChanged; }
void PlayerController::clearVolumeChangedFlag() { volumeChanged = false; }

bool PlayerController::isPlayClicked() const {
    return playClicked && millis() - playClickTime < CLICK_ANIM_DURATION;
}

bool PlayerController::isNextClicked() const {
    return nextClicked && millis() - nextClickTime < CLICK_ANIM_DURATION;
}

bool PlayerController::isPrevClicked() const {
    return prevClicked && millis() - prevClickTime < CLICK_ANIM_DURATION;
}

void PlayerController::updateTrackInfo() {
    String fullPath = normalizePath(sdManager.getCurrentTrack());
    int duration = getMP3DurationSeconds(fullPath);
    if (duration <= 0) {
        Serial.println("[PlayerController] Uwaga: totalTime = 0, ustawiam na 10s awaryjnie");
        duration = 10;
    }
    totalTime = duration;
    currentTime = 0;
}

String PlayerController::normalizePath(const String& raw) {
    String path = "/" + raw;
    if (!path.endsWith(".mp3")) path += ".mp3";
    path.trim();
    while (path.indexOf("  ") >= 0) {
        path.replace("  ", " ");
    }
    return path;
}

int PlayerController::getMP3DurationSeconds(const String& fullPath) {
    static constexpr int DEFAULT_BITRATE = 192000;
    File file = SD.open(fullPath.c_str());
    if (!file) {
        Serial.printf("[MP3] NIE udało się otworzyć pliku %s\n", fullPath.c_str());
        return 10;
    }
    int fileSize = file.size();
    file.close();
    int duration = (fileSize * 8) / DEFAULT_BITRATE;
    Serial.printf("[MP3] size=%dB → duration=%ds (szacowane @192kbps)\n", fileSize, duration);
    return duration > 0 ? duration : 10;
}