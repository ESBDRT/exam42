#include "life.h"

char **get_base_map(t_game *game)
{
    char **map = malloc(game->height * sizeof(char *) + 1);
    if (!map)
        return (NULL);

    for (int i = 0; i < game->height; i++)
    {
        map[i] = malloc(game->width * sizeof(char *) + 1);
        if (!map[i])
            return (NULL);
        for (int j = 0; j < game->width; j++)
            map[i][j] = '0';
        map[i][game->width] = '\0';
    }
    map[game->height] = NULL;
    return (map);
}

int init_game(t_game *game, const char **argv)
{
    game->width = atoi(argv[1]);
    game->height = atoi(argv[2]);
    game->iterations = atoi(argv[3]);
    game->map = get_base_map(game);

    return (game->width < 0 || game->height < 0 || game->iterations < 0 || !game->map ? 1 : 0);
}

int main(int argc, const char **argv)
{
    t_game game;

    if (argc != 4 || init_game(&game, argv))
        return (1);

    for (int i = 0; i < game.height; i++)
    {
        printf("%s\n", game.map[i]);
    }
    
    
}