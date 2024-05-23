void playing_menu (SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_Texture* menu = loadTexture ("asset//playing_menu.png", renderer);
    SDL_Rect menu_rect = SetRect (590, 400, 105, 100);
    SDL_RenderCopy(renderer, menu, NULL, &menu_rect);
    SDL_RenderPresent (renderer);

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
                if (if_clicked (mouse_x, mouse_y, 276, 48, 157, 161)) new_game ();
                if (if_clicked (mouse_x, mouse_y, 276, 48, 157, 214)) restart ();
                if (if_clicked (mouse_x, mouse_y, 276, 48, 157, 268)) choosing = false;
            }

        }
    }
}
