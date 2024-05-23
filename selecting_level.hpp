void selecting_level (SDL_Window* window, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer)
{
    int lev = 1;

    SDL_Texture* background = loadTexture("asset//sky.png", renderer);
    SDL_Texture* left = loadTexture("asset//left.png", renderer);
    SDL_Texture* right = loadTexture("asset//right.png", renderer);
    SDL_Texture* confirm = loadTexture("asset//confirm.png", renderer);

    string level[9] = {"asset//level1.png", "asset//level2.png", "asset//level3.png", "asset//level4.png", "asset//level5.png",
        "asset//level6.png", "asset//level7.png", "asset//level8.png", "asset//level9.png"};
    SDL_Texture* select_level[9];
    for (int i = 0; i < 9; i++) {
        select_level[i] = loadTexture(level[i], renderer);
    }

    SDL_Texture* pleaseSelectLevel = renderText("Please Select Level", font, color, renderer);

    initMusic();
    Mix_Chunk* selected = Mix_LoadWAV("asset//selected.mp3");

    bool choosing = true;

    while (choosing)
    {
        SDL_RenderCopy(renderer, background, NULL, NULL);
        renderTexture(pleaseSelectLevel, 225, 26, renderer);
        SDL_Texture* yourLevel = renderText((to_string(lev)).c_str(), font, color, renderer);
        renderTexture(yourLevel, mid_x(yourLevel), 410, renderer);
        renderTexture(select_level[lev - 1], 275, 135, renderer);
        if (lev > 1) renderTexture(left, 310, 400, renderer);
        if (lev < 9) renderTexture(right, 440, 400, renderer);
        renderTexture(confirm, 275, 460, renderer);
        SDL_RenderPresent(renderer);

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                choosing = false;
                quit = true;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RETURN) choosing = false;

                if (event.key.keysym.sym == SDLK_LEFT && lev > 1) {
                    lev--;
                    velocity = v[lev - 1];
                }
                if (event.key.keysym.sym == SDLK_RIGHT && lev < 9) {
                    lev++;
                    velocity = v[lev - 1];
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouse_x = event.button.x;
                int mouse_y = event.button.y;
                if (if_clicked(mouse_x, mouse_y, 50, 50, 310, 400) && lev > 1) // click left
                {
                    lev--;
                    velocity = v[lev - 1];
                }
                if (if_clicked(mouse_x, mouse_y, 50, 50, 440, 400) && lev < 9) // click right
                {
                    lev++;
                    velocity = v[lev - 1];
                }
                if (if_clicked(mouse_x, mouse_y, 250, 67, 275, 460)) choosing = false; // click confirm
            }
        }

        // Clear the current level number texture before rendering the next one
        SDL_DestroyTexture(yourLevel);

        SDL_RenderClear(renderer);
    }

    Mix_PlayChannel(-1, selected, 0);
    SDL_Delay(400);
    // Free the loaded textures
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(left);
    SDL_DestroyTexture(right);
    SDL_DestroyTexture(confirm);
    for (int i = 0; i < 9; i++) SDL_DestroyTexture(select_level[i]);
    SDL_DestroyTexture(pleaseSelectLevel);
    Mix_FreeChunk(selected);

    difficulty = lev;
}

