#include "raylib.h"
#include "stdio.h"

#include "../include/game.h"

// Specific include for build_web
#if defined(WEB_BUILD)
#include <emscripten/emscripten.h>
#endif

const int screenWidth = 800;
const int screenHeight = 600;

void GameLoop(void);

Game game;

int main(void)
{

    InitWindow(screenWidth, screenHeight, "Raylib StarterKit GPPI");

    // Initialise Game
    game.init();

    // For web builds, do not use WindowShouldClose
    // see https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5)#41-avoid-raylib-whilewindowshouldclose-loop

#if defined(WEB_BUILD)
    emscripten_set_main_loop(GameLoop, 0, 1);
#else
    SetTargetFPS(60);
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Call GameLoop
        GameLoop();
    }
#endif


    CloseWindow();

    return 0;
}

void GameLoop(void)
{
    game.update();

    BeginDrawing();

    ClearBackground(WHITE);

    // Draw the Game Objects
    game.draw();

    EndDrawing();
}
