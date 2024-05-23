void printFinalScore (SDL_Window* window, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    SDL_Texture* background = loadTexture ("asset//sky.png",renderer);
    SDL_Texture* finalScoreText = renderText(("Your Final Score: " + to_string(score)).c_str(), font, color, renderer);
    SDL_Texture* ask_play_again = renderText ("Do you want to play again?", font, color, renderer);
    SDL_Texture* if_want_to [2] = {renderText ("NO", font, color, renderer) , renderText ("YES", font, color, renderer)};

    /*initMusic();
    Mix_Chunk* end_game_sound = Mix_LoadWAV("asset//pop.wav");*/

    bool choosing = true;
    while (choosing)
    {
        SDL_RenderCopy (renderer, background, NULL, NULL);
        renderTexture(finalScoreText, 220, 26, renderer);
        renderTexture(ask_play_again, 190, 200, renderer);
        renderTexture (if_want_to[continue_playing], 370, 270, renderer);
        SDL_RenderPresent (renderer);
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                quit = true;
                choosing = false;
            }
            if (event.type == SDL_KEYDOWN) {
              if (event.key.keysym.sym == SDLK_RETURN) choosing = false;

              if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT) {
                    continue_playing = 1-continue_playing;
                    SDL_RenderClear (renderer);
              }
            }
        }
    }

}
