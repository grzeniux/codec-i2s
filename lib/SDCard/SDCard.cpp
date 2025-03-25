#include "SDCard.h"

SDCardManager& SDCardManager::getInstance() {
    static SDCardManager instance;
    return instance;
}

bool SDCardManager::begin(uint8_t csPin) {
    if (!SD.begin(csPin)) {
        Serial.println("Błąd inicjalizacji karty SD");
        return false;
    }
    Serial.println("Karta SD zainicjalizowana.");
    mp3Files.clear();

    File root = SD.open("/");
    while (true) {
        File entry = root.openNextFile();
        if (!entry) break;
        String filename = entry.name();
        if (filename.endsWith(".mp3")) {
            mp3Files.push_back(filename);
        }
        entry.close();
    }
    return !mp3Files.empty();
}

std::vector<String> SDCardManager::getMp3Files() {
    return mp3Files;
}

String SDCardManager::getCurrentTrack() {
    if (mp3Files.empty()) return "Brak plików";
    String track = mp3Files[currentTrackIndex];
    if (track.endsWith(".mp3")) {
        track = track.substring(0, track.length() - 4); // Usuwa ".mp3"
    }
    return track;
}


void SDCardManager::nextTrack() {
    if (!mp3Files.empty()) {
        currentTrackIndex = (currentTrackIndex + 1) % mp3Files.size();
        Serial.println("Następna piosenka: " + mp3Files[currentTrackIndex]);
    }
}

void SDCardManager::prevTrack() {
    if (!mp3Files.empty()) {
        currentTrackIndex = (currentTrackIndex - 1 + mp3Files.size()) % mp3Files.size();
        Serial.println("Poprzednia piosenka: " + mp3Files[currentTrackIndex]);
    }
}

int SDCardManager::getCurrentTrackDuration() {
    if (mp3Files.empty()) return 0;

    String fullPath = "/" + mp3Files[currentTrackIndex];
    fullPath.trim();
    
    while (fullPath.indexOf("  ") >= 0) {
        fullPath.replace("  ", " ");
    }

    File f = SD.open(fullPath.c_str());
    if (!f) {
        Serial.println("[DEBUG] SD.open() nie widzi pliku – może coś jeszcze?");
        return 0;
    }
    f.close();

    return MP3InfoExtractor::getMP3DurationSeconds(fullPath.c_str());
}
