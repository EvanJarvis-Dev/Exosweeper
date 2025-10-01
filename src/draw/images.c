#include "raylib.h"
#include "draw/images.h"
#include <stdlib.h>
#include <stdio.h>

Texture2D LoadTextureSafe(const char *p_filePath) 
{
    Image image = LoadImage(p_filePath);
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);
    return texture;
}

Images InitialiseImages()
{
    Images images = {0};

    images.mainMenuBackground = LoadTextureSafe("resources/backgrounds/title-screen.png");
    images.gameBackgroundOn = LoadTextureSafe("resources/backgrounds/game-screen-on.png");
    images.gameBackgroundOff = LoadTextureSafe("resources/backgrounds/game-screen-off.png");
    images.button = LoadTextureSafe("resources/sprites/button.png");

    images.grassCount = 7;
    for (int i = 0; i < images.grassCount; i++)
    {
        char path[50];
        sprintf(path, "resources/sprites/grass/grass%d.png", i + 1);
        images.grass[i] = LoadTextureSafe(path);
    }

    images.oreCount = 15;
    for (int i = 0; i < images.oreCount; i++)
    {
        char path[50];
        sprintf(path, "resources/sprites/ore/ore%d.png", i + 1);
        images.ore[i] = LoadTextureSafe(path);
    }

    images.iceCount = 3;
    for (int i = 0; i < images.iceCount; i++)
    {
        char path[50];
        sprintf(path, "resources/sprites/ice/ice%d.png", i + 1);
        images.ice[i] = LoadTextureSafe(path);
    }

    images.magma = LoadTextureSafe("resources/sprites/magma.png");
    images.marker = LoadTextureSafe("resources/sprites/marker.png");

    return images;
}

void UnloadTextures(Images *p_images)
{
    UnloadTexture(p_images->mainMenuBackground);
    UnloadTexture(p_images->gameBackgroundOn);
    UnloadTexture(p_images->gameBackgroundOff);
    UnloadTexture(p_images->button);

    for (int i = 0; i < p_images -> grassCount; i++)
    {
        UnloadTexture(p_images->grass[i]);
    }

    for (int i = 0; i < p_images -> oreCount; i++)
    {
        UnloadTexture(p_images->ore[i]);
    }

    for (int i = 0; i < p_images -> iceCount; i++)
    {
        UnloadTexture(p_images->ice[i]);
    }

    UnloadTexture(p_images->magma);
    UnloadTexture(p_images->marker);
}