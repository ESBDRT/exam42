#include "life.h"

void print_map(t_game *game)
{
    for (int i = 0; i < game->height; i++)
    {
        for (int j = 0; j < game->width; j++)
            putchar(game->map[i][j]);
        putchar('\n');
    }
}

char **get_base_map(t_game *game)
{
    char **map = malloc((game->height + 1) * sizeof(char *));
    if (!map)
        return (NULL);
    
    for (int i = 0; i < game->height; i++)
    {
        map[i] = malloc((game->width + 1) * sizeof(char));
        if (!map[i])
            return (NULL);

        for (int j = 0; j < game->width; j++)
            map[i][j] = game->dead;

        map[i][game->width] = '\0';        
    }
    map[game->height] = NULL;
    return (map);
}

void try_draw(t_game *game)
{
    if (game->draw)
        game->map[game->i][game->j] = game->alive;
}

int read_input(t_game *game)
{
    char buf;

    while (read(STDIN_FILENO, &buf, 1) == 1)
    {
        switch (buf)
        {
            case 'w':
                if (game->i > 0){
                    game->i--;
                    try_draw(game);
                }
                break;

            case 'a':
                if (game->j > 0){
                    game->j--;
                    try_draw(game);
                }
                break;

            case 's':
                if (game->i < game->height - 1){
                    game->i++;
                    try_draw(game);
                }
                break;

            case 'd':
                if (game->j < game->width - 1){
                    game->j++;
                    try_draw(game);
                }
                break;

            case 'x':
                if (!game->draw){
                    game->draw = true;
                    try_draw(game);
                }
                else
                    game->draw = false;
                break;

            case '\n':
                break;

            default:
                game->err = true;
                break;
            
        }

        if (game->err)
            return (1);
    }
    
    return (0);
}

int init_game(t_game *game, const char **argv)
{
    game->alive = 'O';
    game->dead = ' ';
    game->draw = false;
    game->err = false;
    game->i = 0;
    game->j = 0;

    game->width = atoi(argv[1]);
    game->height = atoi(argv[2]);
    game->iterations = atoi(argv[3]);
    game->map = get_base_map(game);
    if (game->width < 0 || game->height < 0 || game->iterations < 0 || read_input(game))
        return (1);

    return (0);
}


int count_neighbors(t_game *game, int row, int col)
{
    int count = 0;

    for (int row_off = -1; row_off <= 1; row_off++)
    {
        for (int col_off = -1; col_off <= 1; col_off++)
        {
            if (row_off == 0 && col_off == 0)
                continue;

            int nrow = row + row_off;
            int ncol = col + col_off;

            if (nrow >= 0 && nrow < game->height && ncol >= 0 && ncol < game->width && game->map[nrow][ncol] == game->alive)
                count++;
        }
    }
    return (count);
}


int play(t_game *game)
{
    char **newmap = get_base_map(game);
    if (!newmap)
        return (1);

    int neighbors;

    for (int i = 0; i < game->height; i++)
    {
        for (int j = 0; j < game->width; j++)
        {
            neighbors = count_neighbors(game, i, j);
            if (game->map[i][j] == game->alive)
            {
                if (neighbors == 2 || neighbors == 3)
                    newmap[i][j] = game->alive;
                else
                    newmap[i][j] = game->dead;
            }
            else
                if (neighbors == 3)
                    newmap[i][j] = game->alive;
        }
    }

    game->map = newmap;
    return (0);
}

int main(int argc, const char **argv)
{
    t_game game;

    if (argc != 4 || init_game(&game, argv))
        return (1);
    
    for (int i = 0; i < game.iterations; i++)
        if (play(&game))
            return (1);

    print_map(&game);
    return (0);
}