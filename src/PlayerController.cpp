#include "PlayerController.h"

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
    
    if (buttons.wasPlayPausePressed()) {
        playing = !playing;
        playClicked = true;
        playClickTime = millis();
    }
    
    if (buttons.wasNextTrackPressed()) {
        sdManager.nextTrack();
        updateTrackInfo();
        nextClicked = true;
        nextClickTime = millis();
    }
    
    if (buttons.wasPrevTrackPressed()) {
        sdManager.prevTrack();
        updateTrackInfo();
        prevClicked = true;
        prevClickTime = millis();
    }
    
}

void PlayerController::update() {
    if (millis() - lastSecondUpdate >= SECOND_INTERVAL) {
        lastSecondUpdate = millis();
        if (playing && currentTime < totalTime) currentTime++;
        else {
            sdManager.nextTrack();
            updateTrackInfo();
        }

    }
}

bool PlayerController::isPlaying() const { return playing; }
int PlayerController::getCurrentTime() const { return currentTime; }
int PlayerController::getTotalTime() const { return totalTime; }
int PlayerController::getVolume() const { return volumeLevel; }
String PlayerController::getCurrentSongTitle() const { return sdManager.getCurrentTrack(); }
void PlayerController::setPlay(bool play) { playing = play; }
bool PlayerController::wasVolumeChanged() { return volumeChanged; }
void PlayerController::clearVolumeChangedFlag() { volumeChanged = false; }
bool PlayerController::isPlayClicked() { return playClicked && millis() - playClickTime < CLICK_ANIM_DURATION; }
bool PlayerController::isNextClicked() { return nextClicked && millis() - nextClickTime < CLICK_ANIM_DURATION; }
bool PlayerController::isPrevClicked() { return prevClicked && millis() - prevClickTime < CLICK_ANIM_DURATION; }
void PlayerController::updateTrackInfo() {
    int duration = sdManager.getCurrentTrackDuration();
    if (duration <= 0) {
        Serial.println("[PlayerController] Uwaga: totalTime = 0, ustawiam na 10s awaryjnie");
        duration = 10;
    }
    totalTime = duration;
    currentTime = 0;
}