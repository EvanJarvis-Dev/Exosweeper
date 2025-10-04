#include "raylib.h"

#include "game/settings.h"
#include "game/grid.h"
#include "game/audio.h"

#include "input/input_menu.h"
#include "input/input_game.h"

#include "draw/menu/menu.h"
#include "draw/game/draw_game.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
    Command to build: /opt/pop/bin/build-wasm.sh $(find src -type f -name "*.c")
    Command to run: /opt/pop/bin/run-wasm.sh 
*/

void CleanUp(GlobalSettings *p_settings, GridInstance *p_gridInstance, Audio *p_audio, Images *p_images)
{
    UnloadAudio(p_audio);
    UnloadTextures(p_images);
    UnloadFont(p_settings -> font);
    UnloadFont(p_settings -> numberFont);
    FreeGrid(p_gridInstance);
    free(p_gridInstance);
    
    CloseAudioDevice();
}

int main(void) 
{
    GlobalSettings globalSettings = CreateGlobalSettings();
    
    // GridInstance *p_gridInstance = malloc(sizeof(GridInstance));
    GridInstance *p_gridInstance = calloc(1, sizeof(GridInstance));

    Menu menu = InitialiseMenus(&globalSettings);
    
    srand(time(0));

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(globalSettings.SCREEN_WIDTH, globalSettings.SCREEN_HEIGHT, "Exosweep");
    SetTargetFPS(60);
    
    Audio audio = LoadAudio();
    Images images = InitialiseImages();
    globalSettings.font = LoadFontEx("./resources/fonts/ExosweeperFont.ttf", 256, NULL, 0);
    globalSettings.numberFont = LoadFontEx("./resources/fonts/ExosweeperNumberFont.ttf", 256, NULL, 0);
    SetTextureFilter(globalSettings.font.texture, TEXTURE_FILTER_TRILINEAR);
    SetTextureFilter(globalSettings.numberFont.texture, TEXTURE_FILTER_TRILINEAR);

    GameState currentState = MENU_STATE;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        switch (currentState)
        {
            case MENU_STATE:
                ManageMenuInput(&globalSettings, &currentState, &images, &audio, menu, p_gridInstance);
                DrawMainMenu(&globalSettings, &images, menu);
                break;

            case PLAY_STATE:
                UpdateFinishTime(p_gridInstance -> timer);
                ManageGameInput(*p_gridInstance, &currentState, &audio);
                DrawGame(*p_gridInstance, &globalSettings, &images, false);
                break;

            case SUCCESS_STATE:
            case FAIL_STATE:
                DrawFinishedGame(*p_gridInstance, &globalSettings, &images, currentState, menu.mainMenuButton);
                ManageFinishedInput(&currentState, &audio, menu);
                break;
        }

        UpdateAudioStreams(&audio);

        EndDrawing();
    }

    CleanUp(&globalSettings, p_gridInstance, &audio, &images);

    CloseWindow();
    return 0;
}