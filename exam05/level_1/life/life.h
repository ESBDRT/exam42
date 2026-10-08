#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct s_game {
    
    char **map;
    char alive;
    char dead;

    int  width;
    int  height;
    int  iterations;

    bool draw;
    bool err;

    int i;
    int j;
}              t_game;