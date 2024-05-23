void playing (SDL_Window * window, SDL_Texture* texture, SDL_Texture* background, TTF_Font* font,
             SDL_Color color, SDL_Renderer* renderer, bool& if_restart, bool& if_new_game)
{
    SDL_Texture* sky = loadTexture ("asset//sky.png", renderer);
    SDL_Texture* cloud = loadTexture ("asset//cloud.png", renderer);
    SDL_Texture* grass = loadTexture ("asset//grass.png", renderer);
    SDL_Texture* pause_button = loadTexture ("asset//pause.png", renderer);
    SDL_Texture* levelText = renderText(("Level: " + to_string(difficulty)).c_str(), font, color, renderer);
    SDL_Texture* pf_strikes = renderText(("Perfect! x"+to_string(perfect_strikes)).c_str(), font, color, renderer);
    SDL_Texture* bonus_score = renderText(("+" + to_string(perfect_strikes*5) + "%").c_str(), font, color, renderer);

    initMusic();
    Mix_Music* bgmusic = loadMusic("asset//bgmusic_easy.mp3");;
    Mix_Chunk* pop_sound = Mix_LoadWAV("asset//pop.wav");
    Mix_Chunk* game_over = Mix_LoadWAV("asset//gameover.mp3");
    Mix_Chunk* perfect_sound = Mix_LoadWAV("asset//perfect.mp3");
    Mix_Chunk* selected = Mix_LoadWAV("asset//selected.mp3");
    Mix_PlayMusic(bgmusic, -1);

    vector <SDL_Rect> rect; // mảng các hình chữ nhật
    int len;

    // hình chữ nhật dưới đáy
    SDL_Rect rectangle0;
    rectangle0.w = init_rect_width; // Width of the rectangle
    rectangle0.h = rect_height; // Height of the rectangle
    rectangle0.x = (SCREEN_WIDTH - rectangle0.w)/2; // Initial x-position (leftmost edge)
    rectangle0.y = SCREEN_HEIGHT - rectangle0.h; // Y-position (fixed)
    rect.push_back (rectangle0);

    SDL_Rect fillcloud;
        fillcloud.w = SCREEN_WIDTH;
        fillcloud.h = 400;
        fillcloud.x = 0;
        fillcloud.y = 50;
    SDL_Rect fillcloud2;
        fillcloud2.w = SCREEN_WIDTH;
        fillcloud2.h = 400;
        fillcloud2.x = 0;
        fillcloud2.y = fillcloud.y-450;
    SDL_Rect fillgrass;
        bool atground = 1;
        fillgrass.w = SCREEN_WIDTH;
        fillgrass.h = 189;
        fillgrass.x = 0;
        fillgrass.y = SCREEN_HEIGHT - fillgrass.h;
    SDL_Rect fillpause = SetRect (50, 50, 10, 10);

    while (latest_width > 0)
    {
        pf_strikes = renderText(("Perfect! x"+to_string(perfect_strikes)).c_str(), font, color, renderer);
        bonus_score = renderText(("+" + to_string(perfect_strikes*5) + "%").c_str(), font, color, renderer);
        Uint32 startTime = SDL_GetTicks();
        Uint32 duration = 3000;

        SDL_Rect rectangle; //current cake
        rectangle.x = 0; // Initial x-position (leftmost edge)
        rectangle.y = rect[num_of_cakes_in_tower].y - rect_height; // Y-position (fixed)
        rectangle.w = latest_width; // Width of the rectangle
        rectangle.h = rect_height; // Height of the rectangle

        // Movement variables
        int x_direction = 1; // Direction of movement (1 = right, -1 = left)
        int x_max = SCREEN_WIDTH - rectangle.w; // Maximum x-position (rightmost edge)

        bool if_menu_selected = false;

        bool running = true;
        while (running) {
            SDL_RenderCopy (renderer, sky, NULL, NULL);
            if (atground) SDL_RenderCopy(renderer, grass, NULL, &fillgrass);
            SDL_RenderCopy(renderer, cloud, NULL, &fillcloud);
            SDL_RenderCopy(renderer, cloud, NULL, &fillcloud2);
            SDL_RenderCopy (renderer, pause_button, NULL, &fillpause);

            // level text
            renderTexture(levelText, 200, 26, renderer);

            // Score text
            SDL_Texture* scoreText = renderText(("Score: " + to_string(score)).c_str(), font, color, renderer);
            renderTexture(scoreText, 450, 26, renderer);
            SDL_DestroyTexture(scoreText);

            // Perfect strikes text
            if (perfect_strikes>0 && SDL_GetTicks() - startTime <= duration)
            {
                renderTexture(pf_strikes, 200, 70, renderer);
                renderTexture(bonus_score, 550, 70, renderer);
            }

            // Draw the rectangle
            SDL_RenderCopy(renderer, texture, NULL, &rectangle);

            // Update rectangle position
            rectangle.x += x_direction * velocity;

            // Reverse direction if it reaches the edges
            if (rectangle.x >= x_max || rectangle.x <= 0) {
                x_direction *= -1;
            }

            // Update the screen
            len = rect.size();
            for (int i = 0; i < len; i++) SDL_RenderCopy(renderer, texture, NULL, &rect[i]);
            SDL_RenderPresent(renderer);

            // Handle events
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    SDL_Quit();
                    quit = true;
                    running = false;
                    latest_width = 0;
                }
                if ((event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_RETURN))) {
                    Mix_PlayChannel(-1, pop_sound, 0);
                    running = false;
                }
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                    Mix_PlayChannel(-1, selected, 0);
                    playing_menu (window, renderer, if_restart, if_new_game, if_menu_selected);
                }
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    int mouse_x = event.button.x;
                    int mouse_y = event.button.y;
                    if (if_clicked (mouse_x, mouse_y, 50, 50, 10, 10)) {
                        Mix_PlayChannel(-1, selected, 0);
                        playing_menu (window, renderer, if_restart, if_new_game, if_menu_selected);
                    } else {
                        Mix_PlayChannel(-1, pop_sound, 0);
                        running = false;
                    }
                }
            }

            if (quit) break; // when quited
            if (!running) {
                SDL_RenderClear(renderer);
                SDL_RenderCopy (renderer, sky, NULL, NULL);
                if (atground) SDL_RenderCopy(renderer, grass, NULL, &fillgrass);
                SDL_RenderCopy(renderer, cloud, NULL, &fillcloud);
                SDL_RenderCopy(renderer, cloud, NULL, &fillcloud2);
                SDL_RenderCopy (renderer, pause_button, NULL, &fillpause);

                // level text
                renderTexture(levelText, 200, 26, renderer);

                // Score text
                SDL_Texture* scoreText = renderText(("Score: " + to_string(score)).c_str(), font, color, renderer);
                renderTexture(scoreText, 450, 26, renderer);

                // Perfect strikes text
                if (perfect_strikes > 0 && SDL_GetTicks() - startTime <= duration)
                {
                    renderTexture(pf_strikes, 200, 70, renderer);
                    renderTexture(bonus_score, 550, 70, renderer);
                }

                len = rect.size();
                for (int i = 0; i < len; i++) SDL_RenderCopy(renderer, texture, NULL, &rect[i]);
                SDL_RenderCopy(renderer, texture, NULL, &rectangle);
                SDL_RenderPresent(renderer);

                // Free the text textures
                SDL_DestroyTexture(scoreText);
            }

            if (if_menu_selected) running = false;
        }

        if (if_menu_selected) break;

        // cắt bánh
        if (rectangle.x < rect[num_of_cakes_in_tower].x) {
            rectangle.w -= (rect[num_of_cakes_in_tower].x - rectangle.x);
            rectangle.x = rect[num_of_cakes_in_tower].x;
        } else if (rectangle.x - rect[num_of_cakes_in_tower].x < rect[num_of_cakes_in_tower].w) {
            rectangle.w = rect[num_of_cakes_in_tower].w - (rectangle.x - rect[num_of_cakes_in_tower].x);
        } else {
            rectangle.w = 0;
            break;
        }
        // if perfect then play this sound
        if (rectangle.w == latest_width) {
                Mix_PlayChannel(-1, perfect_sound, 0);
                perfect_strikes++;
        }
        else perfect_strikes = 0;

        if (len > 4 && rectangle.w > 0) {
            drop_cake(rectangle, rect, fillgrass, fillcloud, fillcloud2, atground, window, texture, background, font, color, renderer);
        }

        latest_width = rectangle.w; // cập nhật bề rộng mới nhất
        if (latest_width > 0) num_of_cakes_in_tower++; // đã thêm 1 bánh

        if (latest_width > 0) score += velocity * sqrt(latest_width); // điểm được cộng thêm
        if (perfect_strikes > 0) score += (score * perfect_strikes * 5)/100;// bonus points if perfect

        // thêm bánh vừa cắt vào mảng
        rect.push_back(rectangle);

        // nếu chồng quá cao thì bỏ bớt bánh dưới đáy đi
        if (len > 4) {
            rect.erase(rect.begin());
            num_of_cakes_in_tower--;
            // change positions of cakes, cloud and grass
            for (int i = 0; i <= num_of_cakes_in_tower; i++) rect[i].y = rect[i].y + rect_height;
            fillcloud.y = (fillcloud.y + 400 + 100) % 1000 - 400;
            fillcloud2.y = (fillcloud2.y + 400 + 100) % 1000 - 400;
            atground = 0;
        }
    }

    // Free the loaded textures
    SDL_DestroyTexture(sky);
    SDL_DestroyTexture(cloud);
    SDL_DestroyTexture(grass);
    SDL_DestroyTexture(pause_button);
    SDL_DestroyTexture(levelText);
    SDL_DestroyTexture(pf_strikes);
    SDL_DestroyTexture(bonus_score);

    Mix_FreeMusic(bgmusic);
    Mix_FreeChunk(pop_sound);
    Mix_FreeChunk(perfect_sound);
    Mix_FreeChunk(selected);

    if (!if_new_game && !if_restart)
    {
        Mix_PlayChannel(-1, game_over, 0);
        SDL_Delay(2500);
    }

    Mix_FreeChunk(game_over);
}
