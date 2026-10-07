#include "life.h"

char **get_base_map(t_game *game)
{
    char **map = malloc((game->height + 1) * sizeof(char *));
    if (!map)
        return (NULL);

    for (int i = 0; i < game->height; i++)
    {
        map[i] = malloc(game->width * sizeof(char *) + 1);
        if (!map[i])
            return (NULL);

        for (int j = 0; j < game->width; j++)
            map[i][j] = game->dead;

        map[i][game->width] = '\0';
    }

    map[game->height] = NULL;
    return (map);
}

void print_map(t_game *game)
{
    for (int i = 0; i < game->height; i++){
        for (int j = 0; j < game->width; j++)
            putchar(game->map[i][j]);
        putchar('\n');
    }
}

int init_game(t_game *game, const char **argv)
{
    game->width = atoi(argv[1]);
    game->height = atoi(argv[2]);
    game->iterations = atoi(argv[3]);
    game->map = get_base_map(game);
    game->alive = 'O';
    game->dead = ' ';

    return (game->width < 0 || game->height < 0 || game->iterations < 0 || !game->map ? 1 : 0);
}

int main(int argc, const char **argv)
{
    t_game game;

    if (argc != 4 || init_game(&game, argv))
        return (1);

    
    

    print_map(&game);
    
}