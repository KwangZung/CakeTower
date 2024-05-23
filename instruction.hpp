void instruction(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_Texture* frame[32];
    for (int i = 0; i < 32; i++) {
        frame[i] = loadTexture(("asset//hub//frame (" + to_string(i + 1) + ").png").c_str(), renderer);
    }

    initMusic();
    Mix_Chunk* hub_sound = Mix_LoadWAV("asset//hub.mp3");
    Mix_PlayChannel(-1, hub_sound, 0);

    bool running = true;

    // Display frames
    for (int i = 0; i < 32 && running; i++) {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, frame[i], NULL, NULL);
        SDL_RenderPresent(renderer);

        //events when video is playing
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                quit = true;
            } else if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_RETURN)) {
                running = false;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                running = false;
            }
        }

        SDL_Delay(93); // Delay between frames
    }

    // events when video ended
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                quit = true;
            } else if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_RETURN)) {
                running = false;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                running = false;
            }
        }
    }

    // Clean up resources
    for (int i = 0; i < 32; i++) SDL_DestroyTexture(frame[i]);
    Mix_FreeChunk(hub_sound);

    SDL_RenderClear(renderer);
}

