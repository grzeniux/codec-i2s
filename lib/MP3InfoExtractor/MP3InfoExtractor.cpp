#include "MP3InfoExtractor.h"
#include <AudioFileSourceSD.h>
#include <AudioOutputI2S.h>

#define DEFAULT_BITRATE 192000
#define FALLBACK_DURATION 10

extern AudioOutputI2S* out;
int MP3InfoExtractor::getMP3DurationSeconds(const char* path) {
    File realFile = SD.open(path);
    int fileSize = 0;

    if (realFile) {
        fileSize = realFile.size();
        realFile.close();
    } else {
        Serial.printf("[MP3] NIE udało się otworzyć pliku %s dla size()\n", path);
    }

    AudioFileSourceSD file(path);
    MP3RateReader mp3gen;

    if (!file.isOpen()) {
        Serial.println("[MP3InfoExtractor] Nie można otworzyć pliku.");
        return FALLBACK_DURATION;
    }

    if (!mp3gen.begin(&file, out)) {
        Serial.println("[MP3InfoExtractor] Nie można rozpocząć dekodera MP3.");
        return FALLBACK_DURATION;
    }

    int bitrate = 0;
    int loops = 0;
    while (mp3gen.isRunning() && loops < 12) {
        if (!mp3gen.loop()) break;
        loops++;
        if (mp3gen.lastRate > 0 && bitrate == 0) {
            bitrate = mp3gen.lastRate;
        }
    }
    
    mp3gen.stop();
    file.close();

    if (bitrate < 64000 || bitrate > 320000) {
        Serial.printf("[MP3InfoExtractor] podejrzany bitrate: %d, używam fallback %d\n", bitrate, DEFAULT_BITRATE);
        bitrate = DEFAULT_BITRATE;
    }
    

    int duration = (fileSize * 8) / bitrate;
    Serial.printf("[MP3] bitrate=%d, size=%dB, duration=%ds\n", bitrate, fileSize, duration);
    return duration;
}
