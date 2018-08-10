//
// Created by vbrau on 8/5/2018.
//

#ifndef LD42_VBRAUN_AUDIOSTUFF_H
#define LD42_VBRAUN_AUDIOSTUFF_H

#include "allegro5/allegro_audio.h"
#include <queue>

#define MAXSAMPLES 10

class AudioStuff {
public:
    void init();

    void play_music(ALLEGRO_SAMPLE* sample);
    bool isMusicPlaying();

    void play_audio_fx(ALLEGRO_SAMPLE* sample);
private:
    ALLEGRO_VOICE* voice = nullptr;
    ALLEGRO_MIXER* mainMixer = nullptr;
    ALLEGRO_MIXER* musicMixer = nullptr;
    ALLEGRO_MIXER* fxMixer = nullptr;

    ALLEGRO_SAMPLE_INSTANCE* currentMusic = nullptr;

    std::queue<ALLEGRO_SAMPLE_INSTANCE*> samplesPlaying;
    void cleanupSamples();
};


#endif //LD42_VBRAUN_AUDIOSTUFF_H
