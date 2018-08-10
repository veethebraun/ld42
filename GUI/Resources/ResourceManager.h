//
// Created by vbrau on 6/30/2018.
//

#ifndef LD42_VBRAUN_RESOURCEMANAGER_H
#define LD42_VBRAUN_RESOURCEMANAGER_H


#include "FontManager.h"
#include "BitmapManager.h"
#include "AudioSampleManager.h"

class ResourceManager {
public:
    ResourceManager(const char *fontYaml, const char *bitmapYaml, const char *audioYaml);
    virtual ~ResourceManager();

    ALLEGRO_FONT* get_font(const char* key) {
        return fontManager->get(key);
    }


    ALLEGRO_BITMAP* get_bitmap(const char* key) {
        return bitmapManager->get(key);
    }

    ALLEGRO_SAMPLE* get_audio_sample(const char* key) {
        return audioManager->get(key);
    }

private:
    FontManager* fontManager;
    BitmapManager* bitmapManager;
    AudioSampleManager* audioManager;
};


#endif //LD42_VBRAUN_RESOURCEMANAGER_H
