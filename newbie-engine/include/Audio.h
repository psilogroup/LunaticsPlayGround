#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL.h>
#include "SDL_mixer.h"
#include <string>

#define NUM_SOUNDS 2






static void InitAudio()
{
    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = 2;
    int audio_buffers = 4096;

    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
        fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
        exit(1);

    }
}

class Audio
{
    public:

        Audio (std::string src);
        void play();

        virtual ~Audio();
    protected:
       Mix_Chunk *sound;

    private:
};

#endif // AUDIO_H
