#include <SDL3/SDL.h>
#include "headers/audio.h"
#include <iostream>

Speaker::Speaker() {
    // Set up the audio spec
    spec.channels = 1;
    spec.format = SDL_AUDIO_F32;
    spec.freq = static_cast<int>(SAMPLE_RATE);

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

Speaker::~Speaker() {
    if (stream) {
        SDL_DestroyAudioStream(stream);
    }
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

    // Only queue audio if it's less than the minimum required bytes
    if (SDL_GetAudioStreamQueued(stream) < MINIMUM_QUEUED_BYTES) {
        for (float& sample: samples) {
            if (sound_enabled) { // Controlled by CPU
                sample = SDL_sinf(_phase); // Pass phase to the sample
            } else {
                sample = 0.0f;
            }

            _phase += 2.0f * SDL_PI_F * FREQUENCY / SAMPLE_RATE;
            if (_phase >= 2.0f * SDL_PI_F) { // Reset phase if it crosses 2 * PI
                _phase -= 2.0f * SDL_PI_F;
            }
        }

        // Finally set all data to the stream
        SDL_PutAudioStreamData(stream, samples, sizeof(samples));
    }
}
