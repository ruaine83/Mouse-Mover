#ifndef WIN_UTILS_HPP
#define WIN_UTILS_HPP

// Need this so that rand_s() works
#define _CRT_RAND_S

#define random_pct(x) (x / UINT_MAX)

#include <cstdlib>
#include <random>
#include <windows.h>
#include <wtypes.h>
#include <time.h>

using namespace std;

namespace Utils {
    // Get the horizontal and vertical screen sizes in pixel
    void GetDesktopResolution(int& horizontal, int& vertical)
    {
        RECT desktop;
        // Get a handle to the desktop window
        const HWND hDesktop = GetDesktopWindow();
        // Get the size of screen to the variable desktop
        GetWindowRect(hDesktop, &desktop);
        // The top left corner will have coordinates (0,0)
        // and the bottom right corner will have coordinates
        // (horizontal, vertical)
        horizontal = desktop.right;
        vertical = desktop.bottom;
    }

    POINT MoveCursorSmallRandom(POINT current_pos) {
        int screen_x, screen_y;
        POINT new_pos;

        GetDesktopResolution(screen_y, screen_x);
        std::srand((unsigned int)time(NULL));


        new_pos.x = (LONG)((double)(std::rand() % 1000) / 1000.0) * screen_x;
        new_pos.y = (LONG)((double)(std::rand() % 1000) / 1000.0) * screen_y;

        return new_pos;
    }

    
}

#endif