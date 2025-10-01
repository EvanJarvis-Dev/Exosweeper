#include "game/audio.h"
#include <stdlib.h>

Audio LoadAudio()
{
    Audio newAudio = {0};

    InitAudioDevice();

    newAudio.menuTheme = LoadMusicStream("./resources/audio/menu_theme.mp3");
    newAudio.gameTheme = LoadMusicStream("./resources/audio/game_theme.mp3");

    newAudio.button = LoadSound("./resources/audio/button.wav");

    newAudio.dig[0] = LoadSound("./resources/audio/dig1.wav");
    newAudio.dig[1] = LoadSound("./resources/audio/dig2.wav");
    newAudio.dig[2] = LoadSound("./resources/audio/dig3.wav");

    newAudio.marker = LoadSound("./resources/audio/marker.wav");

    SetMusicVolume(newAudio.menuTheme, 0.2f);
    SetMusicVolume(newAudio.gameTheme, 0.2f);

    newAudio.menuTheme.looping = true;
    newAudio.gameTheme.looping = true;

    SetSoundVolume(newAudio.button, 0.6f);
    SetSoundVolume(newAudio.dig[0], 0.5f);
    SetSoundVolume(newAudio.dig[1], 0.5f);
    SetSoundVolume(newAudio.dig[2], 0.5f);
    SetSoundVolume(newAudio.marker, 0.7f);

    return newAudio;
}

void PlayMusic(Audio *p_audio, bool isMainMenu)
{
    if (isMainMenu)
    {
        StopMusicStream(p_audio -> gameTheme);
        PlayMusicStream(p_audio -> menuTheme);
    }
    else
    {
        StopMusicStream(p_audio -> menuTheme);
        PlayMusicStream(p_audio -> gameTheme);
    }
}

void UpdateAudioStreams(Audio *p_audio)
{
    UpdateMusicStream(p_audio -> menuTheme);
    UpdateMusicStream(p_audio -> gameTheme);
}

void PlayRandomDigSound(Audio *p_audio)
{
    int randomIndex = rand() % 3;
    PlaySound(p_audio -> dig[randomIndex]); 
}

void UnloadAudio(Audio *p_audio)
{
    UnloadMusicStream(p_audio -> menuTheme);
    UnloadMusicStream(p_audio -> gameTheme);

    UnloadSound(p_audio -> button);
    UnloadSound(p_audio -> dig[0]);
    UnloadSound(p_audio -> dig[1]);
    UnloadSound(p_audio -> dig[2]);
    UnloadSound(p_audio -> marker);
}