void introduction (SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_Texture* background = loadTexture ("asset//sky.png",renderer);

    SDL_Texture* logo = loadTexture ("asset//logo.png", renderer);
    SDL_Rect filllogo = SetRect (316, 300, 242, 100);

    initText();
    TTF_Font* font = loadFont("asset//font.otf", 40);
    SDL_Color color = {0, 0, 0, 0};
    SDL_Texture* instruc = renderText("Press Enter To Continue", font, color, renderer);

    initMusic();
    Mix_Chunk* selected = Mix_LoadWAV("asset//selected.mp3");

    SDL_RenderCopy (renderer, background, NULL, NULL);
    renderTexture (instruc, 200, 450, renderer);
    SDL_RenderCopy (renderer, logo, NULL, &filllogo);
    SDL_RenderPresent (renderer);
    SDL_Event event;
    while (true) {
            SDL_PollEvent(&event);
            if (event.type == SDL_QUIT) {
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                continue_playing = 0;
                quit = true;
                break;
            }
            if (event.type == SDL_KEYDOWN) {
              if (event.key.keysym.sym == SDLK_RETURN) {
                    Mix_PlayChannel(-1, selected, 0);
                    SDL_Delay(400);
                    break;
              }
            }
    }
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(logo);
    SDL_DestroyTexture(instruc);
    TTF_CloseFont(font);
    Mix_FreeChunk(selected);
    SDL_RenderClear(renderer);
}

