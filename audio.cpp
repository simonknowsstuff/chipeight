#include <SDL3/SDL_audio.h>
#include "headers/audio.h"
#include <iostream>

Speaker::Speaker() {
    // Set up the audio spec
    spec.channels = 1;
    spec.format = SDL_AUDIO_F32;
    spec.freq = 8000;

    stream = SDL_OpenAudioDeviceStream( // Create stream to default device
        SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,
        &spec,
        nullptr,
        nullptr
    );
    if (!stream) { // Handle stream creation errors
        std::cerr << "Failed to create Audio Stream " << SDL_GetError() << std::endl;
        throw std::runtime_error("Unable to create Audio Stream");
    }
    SDL_ResumeAudioStreamDevice(stream); // Stream device is paused by default
}

void Speaker::play() {
    sound_enabled = true;
}

void Speaker::stop() {
    sound_enabled = false;
    SDL_ClearAudioStream(stream);
}

void Speaker::update() {
    constexpr int MINIMUM_QUEUED_BYTES = BUFFER_SIZE * sizeof(float);
    static float samples[BUFFER_SIZE];

    if (SDL_GetAudioStreamQueued(stream) < MINIMUM_QUEUED_BYTES) {
        for (float& sample: samples) {
            if (sound_enabled) {
                sample = SDL_sinf(sample);
            } else {
                sample = 0.0f;
            }

            _phase += 2.0f * SDL_PI_F * FREQUENCY / SAMPLE_RATE;
        }

        SDL_PutAudioStreamData(stream, samples, sizeof(samples));
    }
}
