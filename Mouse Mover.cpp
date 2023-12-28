// Mouse Mover.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_RAND_S

#include <iostream>
#include <WinUser.h>
#include <windef.h>
#include <chrono>

#define DEBUG

#define MAX_CURSOR_CHANGE_PCT 3.0
#define MAX_IDLE_TIME_SECONDS 300
#define MOVEMENT_CHECK_PERIOD_MS 1000
#define GET_TIME(x) (x = std::chrono::system_clock::now())

// Personal Libraries
#include "Windows_Utils.hpp"

using namespace std;

int main()
{
    POINT curr_point, prev_point, new_point;
    int max_height, max_width;
    unsigned int to_move;

    std::chrono::system_clock::duration max_idle_time, current_idle_time;
    std::chrono::system_clock::time_point last_move_time, curr_time;

    DWORD check_movement_period_ms = MOVEMENT_CHECK_PERIOD_MS;
    float max_move_pct = MAX_CURSOR_CHANGE_PCT;

    max_idle_time = std::chrono::seconds(MAX_IDLE_TIME_SECONDS);

    last_move_time = std::chrono::system_clock::now();

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
            // Cursor has not moved
            // Reset Timer
            GET_TIME(last_move_time);
            prev_point = curr_point;
        }
        else {
#ifdef DEBUG
            printf("Cursor has not moved!\n");
#endif
            GET_TIME(curr_time);
            // Cursor has NOT moved
            // Check if max idle time has elapsed
            current_idle_time = last_move_time - curr_time;
            
#ifdef DEBUG
            printf("Curent delay has been %ld of max period %ld\n", current_idle_time, max_idle_time);
#endif
            if (current_idle_time >= max_idle_time) {
                // Time has elapsed, move cursor
                GET_TIME(last_move_time);
                new_point = Utils::MoveCursorSmallRandom(curr_point, max_move_pct);
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
