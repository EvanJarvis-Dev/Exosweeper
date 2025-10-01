#ifndef IMAGE_H
#define IMAGE_H

#include "raylib.h"

typedef struct
{
    Texture2D mainMenuBackground;
    Texture2D gameBackgroundOff;
    Texture2D gameBackgroundOn;
    Texture2D button;
    
    Texture2D grass[7];
    int grassCount;
    Texture2D ore[15];
    int oreCount;
    Texture2D ice[3];
    int iceCount;

    Texture2D magma;
    Texture2D marker;
} Images;

Texture2D LoadTextureSafe(const char *p_filePath);
Images InitialiseImages();
void UnloadTextures(Images *p_images);

#endif