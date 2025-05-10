#include "raylib.h"
#include "Game.h"

int main(int argc, const char **argv)
{
    Game game;

    while (!WindowShouldClose())
    {
        game.Update();
    }

    return 0;
}