#include <unistd.h>

int is_wide(const char c)
{
    if ((c >= 9 && c <= 13) || (c == 32))
        return (1);
    return (0);

}

int main(int argc, const char **argv)
{
    int i;

    if (argc != 2)
        return (write(1, "\n", 1), 0);
    
    if (argv[1][0] == '\0')
        return (write(1, "\n", 1), 0);

    i = 0;
    while (argv[1][i] && is_wide(argv[1][i]))
        i++;
    
    while (argv[1][i] && !is_wide(argv[1][i]))
        write(1, &argv[1][i++], 1);
    
    write(1, "\n", 1);
    return (0);
}