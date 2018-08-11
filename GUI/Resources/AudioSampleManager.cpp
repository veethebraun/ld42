//
// Created by vbrau on 8/4/2018.
//

#include "AudioSampleManager.h"
#include "yaml-cpp/yaml.h"

AudioSampleManager::AudioSampleManager(const std::string &filename) {
    YAML::Node base = YAML::LoadFile(filename);
    if (base.size() == 0)
        return;

    assert(base.IsMap());
    for (auto &&item : base) {

        const char* file = item.second["file"].as<std::string>().c_str();

        samples[item.first.as<std::string>()] = al_load_sample(file);
    }
}

ALLEGRO_SAMPLE *AudioSampleManager::get(const char *key) {
    return samples[key];
}

AudioSampleManager::~AudioSampleManager() {
    for (const auto &item : samples) {
        al_destroy_sample(item.second);
    }
}
