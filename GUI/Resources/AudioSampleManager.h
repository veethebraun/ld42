//
// Created by vbrau on 8/4/2018.
//

#ifndef LD42_VBRAUN_AUDIOSAMPLEMANAGER_H
#define LD42_VBRAUN_AUDIOSAMPLEMANAGER_H


#include <string>
#include <allegro5/allegro_audio.h>
#include <map>

class AudioSampleManager {
public:
    explicit AudioSampleManager(const std::string& filename);
    ALLEGRO_SAMPLE* get(const char* key);

    virtual ~AudioSampleManager();

private:
    std::map<std::string, ALLEGRO_SAMPLE*> samples;
};


#endif //LD42_VBRAUN_AUDIOSAMPLEMANAGER_H
