#include "game/settings.h"
#include "draw/images.h"

GlobalSettings CreateGlobalSettings()
{
    Color backgroundColour = { 0x19, 0x0A, 0x43, 0xFF };
    Color fontColour = { 0x14, 0x5d, 0x87, 0xFF };
    UIStyle uiStyle = {
        .BACKGROUND_COLOUR = backgroundColour,
        .FONT_COLOUR = fontColour,
        .FONT_SIZE = 40.0f,
        .SPACING = 2.0f,
    };

    GameStyle gameStyle = {
        .mineTextColours = {
            { 0x00, 0x09, 0x24, 0xFF },
            { 0x04, 0x1B, 0x38, 0xFF },
            { 0x09, 0x36, 0x59, 0xFF },
            { 0x46, 0xCF, 0xB3, 0xFF },
            { 0x73, 0xF0, 0xC9, 0xFF },
            { 0xAB, 0xFF, 0xD1, 0xFF },
            { 0xD9, 0xFF, 0xE2, 0xFF },
            { 0xD9, 0xFF, 0xE2, 0xFF },
        },
        
        .GRID_LINE_COLOUR = BLACK,
        .HIGHLIGHTED_GRID_LINE_COLOUR = { 0xD9, 0xFF, 0xE2, 0xFF },
        .FONT_COLOUR = BLACK,
    
        .MINE_FONT_SIZE = 55.0f,
    };

    GlobalSettings globalSettings = {
        .SCREEN_WIDTH = 1280,
        .SCREEN_HEIGHT = 720, 
        
        .gameStyle = gameStyle,
        .uiStyle = uiStyle,
    };

    return globalSettings;
}