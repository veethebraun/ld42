//
// Created by vbrau on 6/30/2018.
//

#include <iostream>
#include "FontManager.h"
#include "yaml-cpp/yaml.h"
#include <cassert>
#include <direct.h>
#include <stdio.h>

FontManager::FontManager(const char *filename) {
    YAML::Node base = YAML::LoadFile(filename);
    if (base.size() == 0)
        return;

    char path[FILENAME_MAX];
    _getcwd(path, sizeof(path));

    assert(base.IsMap());
    for (auto &&item : base) {

        auto file = item.second["file"].as<std::string>();
        auto size = item.second["size"].as<int>();

        fonts[item.first.as<std::string>()] = al_load_font(file.c_str(), size, 0);
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
