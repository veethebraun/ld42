//
// Created by vbrau on 6/30/2018.
//

#include <iostream>
#include "FontManager.h"
#include "yaml-cpp/yaml.h"
#include <cassert>

FontManager::FontManager(std::string filename) {
    YAML::Node base = YAML::LoadFile(filename);
    if (base.size() == 0)
        return;

    assert(base.IsMap());
    for (auto &&item : base) {

        const char* file = item.second["file"].as<std::string>().c_str();
        auto size = item.second["size"].as<int>();

        fonts[item.first.as<std::string>()] = al_load_font(file, size, 0);
    }
}

ALLEGRO_FONT *FontManager::get(const char *key) {
    return fonts[key];
}

FontManager::~FontManager() {
    for (auto &&item : fonts) {
        al_destroy_font(item.second);
        item.second = nullptr;
    }
}
