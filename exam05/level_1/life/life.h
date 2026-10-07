#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct s_game {
    char **map;
    int  width;
    int  height;
    int  iterations;
    char alive;
    char dead;
}              t_game;