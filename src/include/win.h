
#ifndef H_TEACHESS_WINDOW
#define H_TEACHESS_WINDOW

// Window information, centered and 1080x540

#define WIN_TITLE "TeaChess"
#define WIN_X     SDL_WINDOWPOS_CENTERED
#define WIN_Y     SDL_WINDOWPOS_CENTERED
#define WIN_H     540
#define WIN_W     1080
#define WIN_FLAGS SDL_WINDOW_SHOWN

int  winInit();

void winRender();
void winQuit();

#endif

