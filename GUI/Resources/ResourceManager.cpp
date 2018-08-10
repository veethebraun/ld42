//
// Created by vbrau on 6/30/2018.
//

#include "ResourceManager.h"

ResourceManager::ResourceManager(const char *fontYaml, const char *bitmapYaml, const char *audioYaml) {
    fontManager = new FontManager(fontYaml);
    bitmapManager = new BitmapManager(bitmapYaml);
    audioManager = new AudioSampleManager(audioYaml);
}

ResourceManager::~ResourceManager() {
    delete fontManager;
    delete bitmapManager;
    delete audioManager;
}
