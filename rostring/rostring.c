#include <unistd.h>
#include <stdio.h>

int is_wide(const char c)
{
    if ((c >= 9 && c <= 13) || (c == 32))
        return (1);
    return (0);
}

void first_word(const char *str, int start, int end)
{
    while (start < end)
        write(1, &str[start++], 1);
    write(1, "\n", 1);
    return ;
}

int finish(const char *str, int start)
{
    while (str[start] && is_wide(str[start]))
        start++;
    if (str[start] == '\0')
        return (1);
    return (0);
}

int main(int argc, const char **argv)
{
    int i;
    int start;
    int end;

    if (argc < 2)
        return (write(1, "\n", 1), 0);
    
    i = 0;
    while (argv[1][i] && is_wide(argv[1][i]))
        i++;
    start = i;
    while (argv[1][i] && !is_wide(argv[1][i]))
        i++;
    end = i;
    if (finish(argv[1], end))
        return (first_word(argv[1], start, end), 0);    
    while (argv[1][i])
    {
        while (argv[1][i] && is_wide(argv[1][i]))
            i++;
        while (argv[1][i] && !is_wide(argv[1][i]))
            write(1, &argv[1][i++], 1);
        if (!finish(argv[1], i))
            write(1, " ", 1);
    }
    write(1, " ", 1);
    first_word(argv[1], start, end);
    return (0);
}