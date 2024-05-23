void drop_cake (SDL_Rect rectangle, vector <SDL_Rect> rect,
               SDL_Rect fillgrass, SDL_Rect fillcloud, SDL_Rect fillcloud2,
               bool atground,
               SDL_Window * window, SDL_Texture* texture, SDL_Texture* background,
               TTF_Font* font, SDL_Color color, SDL_Renderer* renderer)
{
    SDL_Texture* sky = loadTexture ("asset//sky.png", renderer);
    SDL_Texture* cloud = loadTexture ("asset//cloud.png", renderer);
    SDL_Texture* grass = loadTexture ("asset//grass.png", renderer);
    SDL_Texture* pause_button = loadTexture ("asset//pause.png", renderer);
    SDL_Texture* levelText = renderText(("Level: " + to_string(difficulty)).c_str(), font, color, renderer);
    SDL_Texture* scoreText = renderText(("Score: " + to_string(score)).c_str(), font, color, renderer);
    SDL_Texture* pf_strikes = renderText(("Perfect! x"+to_string(perfect_strikes)).c_str(), font, color, renderer);
    SDL_Texture* bonus_score = renderText(("+" + to_string(perfect_strikes*5) + "%").c_str(), font, color, renderer);
    SDL_Rect fillpause = SetRect (50, 50, 10, 10);


    int drop_v = 5;
    for (int i=1; i<=16; i+=1){
        int len = rect.size();
        for (int j=0; j<len; j++) rect[j].y += drop_v;
        rectangle.y += drop_v;
        fillgrass.y += drop_v*2;
        fillcloud2.y += (drop_v+1);
        fillcloud.y += (drop_v+1);


        SDL_RenderClear(renderer);
        SDL_RenderCopy (renderer, sky, NULL, NULL);
        bool lifting = 1;
        if (atground && lifting) {
            SDL_RenderCopy(renderer, grass, NULL, &fillgrass);
            lifting = 0;
        }
        SDL_RenderCopy(renderer, cloud, NULL, &fillcloud);
        SDL_RenderCopy(renderer, cloud, NULL, &fillcloud2);

        SDL_RenderCopy (renderer, pause_button, NULL, &fillpause);


        //level text
        renderTexture(levelText, 200, 26, renderer);

        //Score text
        renderTexture(scoreText, 450, 26, renderer);

        if (perfect_strikes > 0) {
            renderTexture(pf_strikes, 200, 70, renderer);
            renderTexture(bonus_score, 550, 70, renderer);
        }

        // Draw the rectangle
        SDL_RenderCopy(renderer, texture, NULL, &rectangle);

        for (int i=0; i< len; i++) SDL_RenderCopy(renderer, texture, NULL, &rect[i]);
        SDL_RenderPresent(renderer);
        SDL_Delay(30);
    }
    SDL_DestroyTexture(sky);
    SDL_DestroyTexture(cloud);
    SDL_DestroyTexture(grass);
    SDL_DestroyTexture(levelText);
    SDL_DestroyTexture(scoreText);
    SDL_DestroyTexture(pause_button);
    SDL_DestroyTexture(pf_strikes);
    SDL_DestroyTexture(bonus_score);
}
