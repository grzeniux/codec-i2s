#include "UIController.h"

UIController::UIController(OLEDDisplayManager& display) : displayManager(display) {}

void UIController::update(PlayerController& player) {
    String songTitle = player.getCurrentSongTitle();
    int textWidth = songTitle.length() * 6;

    if (player.wasVolumeChanged()) {
        showVolumeScreen = true;
        volumeScreenTimer = millis();
        player.clearVolumeChangedFlag();
    }

    if (showVolumeScreen && millis() - volumeScreenTimer > VOLUME_SCREEN_TIMEOUT) {
        showVolumeScreen = false;
    }

    bool scrolling = textWidth > (128 - 8);
    if (scrolling && millis() - lastScrollTime >= SCROLL_INTERVAL) {
        lastScrollTime = millis();
        scrollPixelOffset++;
        if ((8 + textWidth - scrollPixelOffset) < 110) scrollPixelOffset = 0;
    } else if (!scrolling) {
        scrollPixelOffset = 0;
    }

    if (showVolumeScreen) {
        displayManager.drawVolumeScreen(player.getVolume());
    } else {
        displayManager.getDisplay().clearDisplay();
        displayManager.drawIcons();
        displayManager.drawTime(player.getCurrentTime(), player.getTotalTime());
        displayManager.drawNote();
        displayManager.drawProgressBar(player.getCurrentTime(), player.getTotalTime());
        displayManager.drawPlayPauseIcon(player.isPlaying(), player.isPlayClicked());
        displayManager.drawNextPrevIcons(player.isNextClicked(), player.isPrevClicked());        
        displayManager.getDisplay().setTextSize(1);
        displayManager.getDisplay().setTextColor(WHITE);
        displayManager.getDisplay().setCursor(8 - scrollPixelOffset, 56);
        displayManager.getDisplay().print(songTitle);
        displayManager.getDisplay().display();
    }
}