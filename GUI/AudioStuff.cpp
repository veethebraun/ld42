//
// Created by vbrau on 8/5/2018.
//

#include <stdexcept>
#include "AudioStuff.h"

void AudioStuff::init() {
    unsigned int freq = 44100;
    voice = al_create_voice(freq, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
    mainMixer = al_create_mixer(freq, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);

    if (!al_attach_mixer_to_voice(mainMixer, voice))
    {
        throw std::runtime_error("couldn't connect voice to mainMixer!");
    }

    musicMixer = al_create_mixer(freq, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
    fxMixer = al_create_mixer(freq, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);

    if (!(al_attach_mixer_to_mixer(musicMixer, mainMixer) && al_attach_mixer_to_mixer(fxMixer, mainMixer)))
    {
        throw std::runtime_error("couldn't connect mixers!");
    }
}

void AudioStuff::play_music(ALLEGRO_SAMPLE *sample) {
    if (currentMusic != nullptr)
    {
        al_stop_sample_instance(currentMusic);
        al_destroy_sample_instance(currentMusic);
    }

    currentMusic = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(currentMusic,ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(currentMusic, musicMixer);
    al_play_sample_instance(currentMusic);
}

void AudioStuff::play_audio_fx(ALLEGRO_SAMPLE *sample) {
    cleanupSamples();

    auto spl = al_create_sample_instance(sample);
    al_attach_sample_instance_to_mixer(spl, fxMixer);
    al_play_sample_instance(spl);
    samplesPlaying.push(spl);
}

bool AudioStuff::isMusicPlaying() {
    return currentMusic != nullptr;
}

void AudioStuff::cleanupSamples() {
    if (samplesPlaying.empty())
        return;
    
    if (samplesPlaying.size() > MAXSAMPLES)
    {
        auto spl = samplesPlaying.front();
        al_destroy_sample_instance(spl);
        samplesPlaying.pop();
    }

    auto spl = samplesPlaying.front();
    while (true)
    {
        if (!al_get_sample_instance_playing(spl))
        {
            samplesPlaying.pop();
            spl = samplesPlaying.front();
        } else {
            break;
        }

        if (samplesPlaying.empty())
        {
            break;
        }
    }
}
