#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct s_game {
    char **map;
    int  width;
    int  height;
    int  iterations;
    char alive;
    char dead;
}              t_game;