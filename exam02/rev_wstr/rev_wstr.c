#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int is_wide(const char c)
{
    if (c == '\t' || c == ' ')
        return (1);
    return (0);
}

int main(int argc, const char **argv)
{
    int i;
    int start;
    const char *str;

    if (argc != 2)
        return (write(1, "\n", 1), 0);

    str = argv[1];
    i = 0;
    while (str[i])
        i++;
    i--;

    while (str[i])
    {
        while (str[i] && is_wide(str[i]))
            i--;
        while (str[i] && !is_wide(str[i]))
            i--;
        start = i + 1;
        while (str[start] && !is_wide(str[start]))
            write(1, &str[start++], 1);
        if (i != -1)
            write(1, " ", 1);        
    }
    write(1, "\n", 1);  
    return (0);
}