#ifndef MP3_INFO_EXTRACTOR_H
#define MP3_INFO_EXTRACTOR_H

#include <Arduino.h>
#include <AudioGeneratorMP3.h>

class MP3RateReader : public AudioGeneratorMP3 {
public:
    using AudioGeneratorMP3::lastRate; // udostępniamy protected jako public
};

class MP3InfoExtractor {
public:
    static int getMP3DurationSeconds(const char* path);
};

#endif
