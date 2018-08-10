//
// Created by vbrau on 6/30/2018.
//

#include <cassert>
#include <allegro5/allegro.h>
#include <iostream>
#include "BitmapManager.h"
#include "yaml-cpp/yaml.h"

BitmapManager::~BitmapManager() {
    for (auto &&item : bitmaps) {
        al_destroy_bitmap(item.second);
        item.second = nullptr;
    }
}

ALLEGRO_BITMAP *BitmapManager::get(const char *key) {
    return bitmaps[key];
}

BitmapManager::BitmapManager(const char *yamlfile) {
    YAML::Node base = YAML::LoadFile(yamlfile);

    assert(base.IsMap());

    for (auto &&item : base) {
        ALLEGRO_BITMAP* bitmap = al_load_bitmap(item.second["file"].as<std::string>().c_str());
        if (bitmap == nullptr)
        {
//std::cout << item.first.as<std::string>() << " didn't load!" << std::endl;
        } else {
            bitmaps[item.first.as<std::string>()] = bitmap;
        }
    }
}
