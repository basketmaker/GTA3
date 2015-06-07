#include "main.h"
#include "editor/editor.h" 

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    Activite *generale = NULL;
    generale = new Editor();
    generale->run_activity();
    delete generale;

    SDL_Quit();
    return EXIT_SUCCESS;
}
