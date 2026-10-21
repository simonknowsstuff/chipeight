#ifndef AUDIO_H
#define AUDIO_H
#include <SDL3/SDL_audio.h>
#define BUFFER_SIZE 512

class Speaker {
private:
    const float FREQUENCY = 440.0f;
    const float SAMPLE_RATE = 48000.0f;
    float _phase = 0.0f;
    int current_sine_sample = 0;
    bool sound_enabled = false;
    SDL_AudioStream *stream = nullptr;
    SDL_AudioSpec spec{};

public:
    Speaker();

    void play();

    void stop();

    void update();
};

#endif //AUDIO_H
