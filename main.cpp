#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
using namespace std;

#include "variables.hpp"
#include "SDL_Ultis.hpp"
#include "mouse_event.hpp"
#include "introduction.hpp"
#include "selecting_level.hpp"
#include "instruction.hpp"
#include "drop_cake.hpp"
#include "menu.hpp"
#include "playing.hpp"
#include "final_score.hpp"


int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    SDL_Surface* icon = loadIcon("asset//icon.bmp");
    if (icon) {
        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);
    }

    SDL_Texture* texture = loadTexture("asset//cake.png", renderer);
    SDL_Texture* background = loadTexture ("asset//sky.png",renderer);

    initText();
    TTF_Font* font = loadFont("asset//font.otf", 40);
    SDL_Color color = {0, 0, 0, 0};

    introduction(window, renderer);

    while (continue_playing && !quit) {
        reset_init_value ();
        bool if_restart, if_new_game;

        new_game:
            if_new_game = false;
        if (!quit) selecting_level(window, font, color, renderer);

        if (!quit) instruction (window, renderer);

        restart:
            if_restart = false;
        if (!quit) playing (window, texture, background, font, color, renderer, if_restart, if_new_game);
            if (if_restart) {
                reset_init_value_when_restarting();
                goto restart;
            }
            if (if_new_game)
            {
                reset_init_value();
                goto new_game;
            }


        if (!quit) end_game (window, font, color, renderer);
    }
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(background);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
