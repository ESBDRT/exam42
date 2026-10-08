#include "life.h"

void draw_check(t_game *game)
{
    if (game->draw)
        game->map[game->i][game->j] = game->alive;
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

int count_neighbors(t_game *game, int row, int col)
{
    int row_off;
    int col_off;
    int nrow;
    int ncol;
    int count;

    count = 0;
        
    // Visit the 3 rows around the cell: above, same row, and below.
    for (row_off = -1; row_off <= 1; row_off++)
    {
        // In each row, visit the 3 columns: left, same column, and right.
        for (col_off = -1; col_off <= 1; col_off++)
        {

            // Skip the cell itself; it is not its own neighbor.
            if (row_off == 0 && col_off == 0)
                continue;

            // Turn the offsets into the neighbor's board coordinates
            nrow = row + row_off;
            ncol = col + col_off;
            if (nrow >= 0 && nrow < game->height && ncol >= 0 && ncol < game->width && game->map[nrow][ncol] == game->alive)
                count++;
        }
    }
    return (count);
}

int play(t_game *game)
{
    int neighbors;
    char **map_tmp;

    map_tmp = get_base_map(game);
    if (!map_tmp)
        return (1);

    for (int i = 0; i < game->height; i++)
    {
        for (int j = 0; j < game->width; j++)
        {
            neighbors = count_neighbors(game, i, j);
            if (game->map[i][j] == game->alive)
            {
                if (neighbors == 2 || neighbors == 3)
                    map_tmp[i][j] = game->alive;
                else
                    map_tmp[i][j] = game->dead;
            }
            else
                if (neighbors == 3)
                    map_tmp[i][j] = game->alive;
        }
    }

    game->map = map_tmp;
    return (0);
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
            if (!game->draw){
                game->draw = true;
                draw_check(game);
            }
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

    for (int i = 0; i < game.iterations; i++)
    {
        if (play(&game))
            return (1);
    }
    
    print_map(&game);
    return (0);
}