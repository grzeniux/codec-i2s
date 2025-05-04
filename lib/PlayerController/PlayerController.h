#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include <Arduino.h>
#include <AudioOutputI2S.h>

#include "Buttons.h"
#include "SDCard.h"

class PlayerController {
public:
    PlayerController(SDCardManager& sd);

    void handleInput(ButtonManager& buttons);
    void update();
    void updateTrackInfo();

    // Ustawienia
    void setPlay(bool play);
    void clearVolumeChangedFlag();

    // Zapytania o stan
    bool isPlaying() const;
    bool wasVolumeChanged() const;
    bool isPlayClicked() const;
    bool isNextClicked() const;
    bool isPrevClicked() const;

    // Dane do UI
    int getCurrentTime() const;
    int getTotalTime() const;
    int getVolume() const;
    String getCurrentSongTitle() const;

private:
    SDCardManager& sdManager;

    // Stan odtwarzania
    bool playing = true;
    bool volumeChanged = false;
    int volumeLevel = 4;
    int currentTime = 0;
    int totalTime = 0;

    // Kliknięcia i animacje
    bool playClicked = false;
    bool nextClicked = false;
    bool prevClicked = false;
    unsigned long playClickTime = 0;
    unsigned long nextClickTime = 0;
    unsigned long prevClickTime = 0;
    static constexpr unsigned long CLICK_ANIM_DURATION = 200;

    // Pomiar czasu
    unsigned long lastSecondUpdate = 0;
    static constexpr unsigned long SECOND_INTERVAL = 1000;

    int getMP3DurationSeconds(const String& fullPath);
    String normalizePath(const String& raw);
};

#endif // PLAYER_CONTROLLER_H
