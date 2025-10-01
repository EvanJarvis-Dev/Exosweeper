#ifndef AUDIO_H
#define AUDIO_H

#include "raylib.h"

typedef struct
{
    Music menuTheme;
    Music gameTheme;

    Sound button;
    Sound marker;
    Sound dig[3];

    bool *p_isMusicMuted;
    bool *p_isSoundMuted;
} Audio;

Audio LoadAudio();
void PlayMusic(Audio *p_audio, bool isMainMenu);
void UpdateAudioStreams(Audio *p_audio);
void PlayRandomDigSound(Audio *p_audio);
void UnloadAudio(Audio *audio);

#endif