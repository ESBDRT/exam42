#include "life.h"

void draw_check(t_game *game)
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
                draw_check(game);
            }
            break;
        
        case 'a':
            if (game->j > 0){
                game->j--;
                draw_check(game);
            }
            break;

        case 's':
            if (game->i < game->height - 1){
                game->i++;
                draw_check(game);
            }
            break;
        
        case 'd':
            if (game->j < game->width - 1){
                game->j++;
                draw_check(game);
            }
            break;

        case 'x':
            if (!game->draw)
                game->draw = true;
            else
                game->draw = false;
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

char **get_base_map(t_game *game)
{
    char **map = malloc((game->height + 1) * sizeof(char *));
    if (!map)
        return (NULL);

    for (int i = 0; i < game->height; i++)
    {
        map[i] = malloc(game->width * sizeof(char ) + 1);
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
    game->alive = 'O';
    game->dead = 32;
    game->width = atoi(argv[1]);
    game->height = atoi(argv[2]);
    game->iterations = atoi(argv[3]);
    game->map = get_base_map(game);
    game->i = 0;
    game->j = 0;
    game->err = false;
    game->draw = false;
    
    return (read_input(game), game->width < 0 || game->height < 0 || game->iterations < 0 || !game->map ? 1 : 0);
}

int main(int argc, const char **argv)
{
    t_game game;

    if (argc != 4 || init_game(&game, argv))
        return (1);

    print_map(&game);
    
}