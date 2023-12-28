#ifndef WIN_UTILS_HPP
#define WIN_UTILS_HPP

// Need this so that rand_s() works
#define _CRT_RAND_S
#define random_pct(x) (x / UINT_MAX)

#include <wtypes.h>
#include <WinUser.h>
#include <random>
#include <cstdlib>

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

    POINT MoveCursorSmallRandom(POINT current_pos, float max_diff_pct = 0.3) {
        int screen_x, screen_y, sign;

        unsigned int base, pos_neg;

        POINT new_pos;

        GetDesktopResolution(screen_y, screen_x);

        
        if(!rand_s(&base))
        {
            printf_s("The rand_s function failed for getting base!\n");            
        }

            double movement_pct = min(max_diff_pct, random_pct(base));

            // Get new x position
            if (!rand_s(&pos_neg))
            {
                printf_s("The rand_s function failed for pos/neg!\n");                
            }
            sign = (random_pct(pos_neg) >= 0.5) ? -1 : 1; // Determines positive or negative motion
            new_pos.x = sign * (current_pos.x * movement_pct);

            // Get new y position 
            if (!rand_s(&pos_neg))
            {
                printf_s("The rand_s function failed for pos/neg!\n");                
            }
            sign = (random_pct(pos_neg) >= 0.5) ? -1 : 1;  // Determines positive or negative motion
            new_pos.y = sign * (current_pos.y * movement_pct);
    }
}

#endif