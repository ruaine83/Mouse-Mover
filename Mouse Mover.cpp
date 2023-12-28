// Mouse Mover.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <ctime>

// #define DEBUG


#define MAX_IDLE_TIME_SECONDS 300
#define MOVEMENT_CHECK_PERIOD_MS 1000U


// Personal Libraries
#include "Windows_Utils.hpp"

using namespace std;

int main()
{
    POINT curr_point, prev_point, new_point;

    std::time_t current_idle_time;
    std::time_t last_move_time, curr_time;

    DWORD check_movement_period_ms = MOVEMENT_CHECK_PERIOD_MS;

    const unsigned int max_idle = MAX_IDLE_TIME_SECONDS;

    last_move_time = std::time(NULL);

    // Get starting position
    GetCursorPos(&prev_point);

    while (true)
    {
        GetCursorPos(&curr_point);

        // Check cursor position against current position
        if ((curr_point.x != prev_point.x) && (curr_point.y != prev_point.y))
        {
#ifdef DEBUG
            printf("Cursor has moved!\n");
#endif
            // Cursor has moved
            // Reset Timer
            last_move_time = std::time(NULL);
            prev_point = curr_point;
        }
        else {
#ifdef DEBUG
            printf("Cursor has not moved!\n");
#endif
            curr_time = std::time(NULL);
            // Cursor has NOT moved
            // Check if max idle time has elapsed
            current_idle_time = curr_time - last_move_time;
            
#ifdef DEBUG
            printf("Curent delay has been %u of max period %u\n", (unsigned int)current_idle_time, (unsigned int)max_idle);
#endif
            if (current_idle_time > max_idle) {
                // Time has elapsed, move cursor
                
                new_point = Utils::MoveCursorSmallRandom(curr_point);
#ifdef DEBUG
                printf("Time elapsed, moving cursor to %d,%d\n", new_point.x, new_point.y);
#endif
                SetCursorPos(new_point.x, new_point.y);
            }
        }

        Sleep(check_movement_period_ms);
    }
    
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
