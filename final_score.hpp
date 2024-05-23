void end_game (SDL_Window* window, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    SDL_Texture* background = loadTexture ("asset//sky.png",renderer);
    SDL_Texture* menu = loadTexture ("asset//end_game_menu.png", renderer);
    SDL_Texture* confirm = loadTexture ("asset//ok.png", renderer);
    SDL_Rect menu_rect = SetRect (590, 400, 105, 40);
    SDL_Texture* left = loadTexture ("asset//left.png", renderer);
    SDL_Texture* right = loadTexture ("asset//right.png", renderer);
    SDL_Texture* if_want_to [2] = {renderText ("NO", font, color, renderer) , renderText ("YES", font, color, renderer)};

    High_score high;
    high.loadOld();
    SDL_Texture* finalScoreText;
    if (high.hs >= score) finalScoreText = renderText(("Your Final Score: " + to_string(score)).c_str(), font, color, renderer);
    else {
        finalScoreText = renderText(("New Highscore: " + to_string(score)).c_str(), font, color, renderer);
        high.getNew(score);
    }

    bool choosing = true;
    while (choosing)
    {
        SDL_RenderCopy (renderer, background, NULL, NULL);
        SDL_RenderCopy(renderer, menu, NULL, &menu_rect);
        renderTexture(finalScoreText, mid_x(finalScoreText), 135, renderer);
        renderTexture (if_want_to[continue_playing], mid_x(if_want_to[continue_playing]), 300, renderer);
        renderTexture (left, 230, 293, renderer);
        renderTexture (right, 520, 293, renderer);
        renderTexture (confirm, 275, 460, renderer);
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
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouse_x = event.button.x;
                int mouse_y = event.button.y;
                if (if_clicked(mouse_x, mouse_y, 50, 50, 230, 293)||if_clicked(mouse_x, mouse_y, 50, 50, 520, 293))
                {
                    continue_playing = 1-continue_playing;
                    SDL_RenderClear (renderer);
                }
                if (if_clicked (mouse_x, mouse_y, 250, 67, 275, 460)) choosing = false;
            }
        }
    }
    initMusic();
    Mix_Chunk* selected = Mix_LoadWAV("asset//selected.mp3");
    Mix_PlayChannel(-1, selected, 0);
    SDL_Delay(300);
    Mix_FreeChunk(selected);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(menu);
    SDL_DestroyTexture(confirm);
    SDL_DestroyTexture(left);
    SDL_DestroyTexture(right);
    SDL_DestroyTexture(finalScoreText);
    for (int i=0; i<2; i++) SDL_DestroyTexture(if_want_to[i]);
}
