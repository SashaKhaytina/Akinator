#ifndef GAME_OPTIONS
#define GAME_OPTIONS

#include "akinator_h.h"

#define PRINTF_RED(string, ...)     printf("\x1b[31m" string "\x1b[0m", ##__VA_ARGS__)   
#define PRINTF_GREEN(string, ...)   printf("\x1b[32m" string "\x1b[0m", ##__VA_ARGS__)   
#define PRINTF_YELLOW(string, ...)  printf("\x1b[33m" string "\x1b[0m", ##__VA_ARGS__) 
#define PRINTF_BLUE(string, ...)    printf("\x1b[34m" string "\x1b[0m", ##__VA_ARGS__)
#define PRINTF_MAGENTA(string, ...) printf("\x1b[35m" string "\x1b[0m", ##__VA_ARGS__)
#define PRINTF_CYAN(string, ...)    printf("\x1b[36m" string "\x1b[0m", ##__VA_ARGS__)

const char* const CRITERIA_RIGHT   = "YES";
const char* const CRITERIA_LEFT    = "NO";
const size_t      MAX_SIZE_COMMAND = 30;



enum StatusEndPlay
{
    LOSE,
    WIN
};

void start_game();


#endif