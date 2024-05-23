void playing_menu (SDL_Window* window, SDL_Renderer* renderer,
                  bool& if_restart, bool& if_new_game, bool& if_menu_selected)
{
    SDL_Texture* menu = loadTexture ("asset//playing_menu.png", renderer);
    SDL_Rect menu_rect = SetRect (590, 400, 105, 100);
    SDL_RenderCopy(renderer, menu, NULL, &menu_rect);

    initText();
    TTF_Font* font = loadFont("asset//font.otf", 30);
    SDL_Color color = {0, 0, 0, 0};

    High_score high;
    high.loadOld();
    SDL_Texture* currentScoreText;
    if (high.hs >= score) currentScoreText = renderText(("Latest Highscore: " + to_string(high.hs)).c_str(), font, color, renderer);
    else currentScoreText = renderText(("Latest Highscore: " + to_string(score)).c_str(), font, color, renderer);
    renderTexture(currentScoreText, mid_x(currentScoreText), 200, renderer);
    SDL_RenderPresent (renderer);

    Mix_PauseMusic();

    bool choosing = true;
    while (choosing)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                choosing = false;
                quit = true;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouse_x = event.button.x;
                int mouse_y = event.button.y;
                if (if_clicked (mouse_x, mouse_y, 276, 48, 157+menu_rect.x, 161+menu_rect.y))//new_game
                {
                    choosing = false;
                    if_new_game = true;
                    if_menu_selected = true;
                    break;
                }
                if (if_clicked (mouse_x, mouse_y, 276, 48, 157+menu_rect.x, 214+menu_rect.y)) //restart
                {
                    choosing = false;
                    if_restart = true;
                    if_menu_selected = true;
                    break;
                }
                if (if_clicked (mouse_x, mouse_y, 276, 48, 157+menu_rect.x, 268+menu_rect.y))//resume
                {
                    SDL_RenderClear (renderer);
                    choosing = false;
                    break;
                }
            }

        }
    }
    initMusic();
    Mix_Chunk* selected = Mix_LoadWAV("asset//selected.mp3");
    Mix_PlayChannel(-1, selected, 0);
    SDL_Delay(300);
    Mix_FreeChunk(selected);
    SDL_DestroyTexture(menu);
    SDL_DestroyTexture(currentScoreText);
    TTF_CloseFont(font);
    Mix_ResumeMusic();
}

