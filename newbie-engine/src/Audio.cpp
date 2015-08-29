#include "Audio.h"



Audio::Audio(std::string src)
{
    sound = Mix_LoadWAV(src.c_str());

}

void Audio::play()
{

    Mix_PlayChannel(-1,sound,0);
}

Audio::~Audio()
{
    Mix_FreeChunk(sound);
    //dtor
}
