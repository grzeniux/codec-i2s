#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class OLEDDisplayManager {
public:
    OLEDDisplayManager(Adafruit_SSD1306& disp);
    Adafruit_SSD1306& getDisplay();

    void drawMainScreen(const char* songTitle, int currentTime, int totalTime, bool isPlaying);
    void drawVolumeScreen(int volumeLevel);
    void drawIcons();
    void drawNote();
    void drawTime(int currentTime, int totalTime);
    void drawProgressBar(int currentTime, int totalTime);

    void drawPlayPauseIcon(bool isPlaying, bool clicked);
    void drawNextPrevIcons(bool nextClicked, bool prevClicked);


private:
    Adafruit_SSD1306& display;
};

#endif
