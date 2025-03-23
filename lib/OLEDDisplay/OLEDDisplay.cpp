#include "OLEDDisplay.h"
#include "bitmaps.h"

OLEDDisplayManager::OLEDDisplayManager(Adafruit_SSD1306& disp) : display(disp) {}

Adafruit_SSD1306& OLEDDisplayManager::getDisplay() {
    return display;
}

void OLEDDisplayManager::drawMainScreen(const char* songTitle, int currentTime, int totalTime, bool isPlaying) {
    display.clearDisplay();
    drawIcons();
    drawTime(currentTime, totalTime);
    drawNote();
    drawProgressBar(currentTime, totalTime);
    drawPlayPauseIcon(isPlaying, false);        // false = brak animacji
    drawNextPrevIcons(false, false);            // false, false = brak animacji

    display.setTextSize(1);
    display.print(songTitle);
    display.display();
}

void OLEDDisplayManager::drawVolumeScreen(int volumeLevel) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(10, 5);
    display.print("Glosnosc");

    display.drawRect(10, 30, 100, 10, WHITE);
    int barWidth = (volumeLevel * 100) / 10;
    display.fillRect(10, 30, barWidth, 10, WHITE);
    display.display();
}

void OLEDDisplayManager::drawIcons() {
    display.drawBitmap(86, 0, bluetoothIcon, 8, 12, WHITE);
    display.drawBitmap(96, 0, batteryIcon, 27, 14, WHITE);
}

void OLEDDisplayManager::drawNote() {
    display.drawBitmap(20, 20, nutka, 30, 30, WHITE);
}

void OLEDDisplayManager::drawTime(int currentTime, int totalTime) {
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(5, 0);
    display.printf("%d:%02d / %d:%02d", currentTime / 60, currentTime % 60, totalTime / 60, totalTime % 60);
}

void OLEDDisplayManager::drawProgressBar(int currentTime, int totalTime) {
    int barWidth = (currentTime * 60) / totalTime;
    display.drawRect(10, 10, 60, 3, WHITE);
    display.fillRect(10, 10, barWidth, 3, WHITE);
}

void OLEDDisplayManager::drawPlayPauseIcon(bool isPlaying, bool clicked) {
    if (clicked) {
        display.drawRect(97, 28, 20, 14, WHITE); // efekt kliknięcia – ramka
    }

    if (isPlaying) {
        display.fillRect(99, 30, 4, 10, WHITE);
        display.fillRect(106, 30, 4, 10, WHITE);
    } else {
        display.fillTriangle(99, 30, 99, 40, 112, 35, WHITE);
    }
}


void OLEDDisplayManager::drawNextPrevIcons(bool nextClicked, bool prevClicked) {
    if (nextClicked) display.drawRect(116, 28, 14, 14, WHITE);
    if (prevClicked) display.drawRect(79, 28, 14, 14, WHITE);

    display.fillTriangle(118, 30, 118, 40, 125, 35, WHITE);
    display.fillRect(126, 30, 2, 10, WHITE);
    display.fillTriangle(90, 30, 90, 40, 83, 35, WHITE);
    display.fillRect(81, 30, 2, 10, WHITE);
}

