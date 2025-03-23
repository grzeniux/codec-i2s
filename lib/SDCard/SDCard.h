#ifndef SDCARD_H
#define SDCARD_H

#include <Arduino.h>
#include <SD.h>
#include <vector>

class SDCardManager {
public:
    static SDCardManager& getInstance();
    bool begin(uint8_t csPin);
    std::vector<String> getMp3Files();
    String getCurrentTrack();
    void nextTrack();
    void prevTrack();

private:
    SDCardManager() {};
    std::vector<String> mp3Files;
    int currentTrackIndex = 0;
};

#endif
