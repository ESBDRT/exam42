#include <unistd.h>

int is_alpha(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1);
    return (0);
}

int is_wide(char c)
{
    if ((c >= 9 && c <= 13) || (c == 32))
        return (1);
    return (0);
}

int main(int argc, char **argv)
{   
    int i;
    int pos;
    char c;

    if (argc == 1)
        return (write(1, "\n", 1), 1);

    pos = 1;
    while (argv[pos])
    {   
        i = 0;
        while (argv[pos][i])
        {
            if (is_alpha(argv[pos][i]))
                if (argv[pos][i] >= 'A' && argv[pos][i] <= 'Z')
                    argv[pos][i] = argv[pos][i] + 32;
            i++;
        }
        pos++;
    }

    pos = 1;
    while (argv[pos])
    {
        i = 0;
        while (argv[pos][i])
        {
            if (is_alpha(argv[pos][i]) && is_wide(argv[pos][i + 1]))
                c = argv[pos][i] - 32;
            else if (is_alpha(argv[pos][i]) && argv[pos][i + 1] == '\0')
                c = argv[pos][i] - 32;
            else
                c = argv[pos][i];
            write(1, &c, 1);
            i++;
        }
        write(1, "\n", 1);
        pos++;
    }

    return (0);
}