
#ifndef H_TEACHESS_WINDOW
#define H_TEACHESS_WINDOW

/* Window information, centered and 1280x720 */

#define WIN_TITLE "TeaChess"
#define WIN_X     SDL_WINDOWPOS_CENTERED
#define WIN_Y     SDL_WINDOWPOS_CENTERED
#define WIN_H     720
#define WIN_W     1280
#define WIN_FLAGS SDL_WINDOW_SHOWN

/* Render the TCHS array contents onto the screen */

int boardLoad();

/* Initialize the SDL window and necessary components */

int winInit();

/* Format the TCHS title into TITLE_DISP_SIZE characters which are displayed */

void tchsTitleEdit(int localOffset);

/* Render the visual elements onto the window */

void winRender();

/* Quit the window and clean any memory allocations and calls */

void winQuit();

#endif

