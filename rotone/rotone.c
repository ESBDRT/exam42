#include <unistd.h>

int main(int argc, const char **argv)
{
    int i;
    char c;
    const char *str = argv[1];

    if (argc != 2)
        return (write(1, "\n", 1), 0);
    
    i = 0;
    while (str[i])
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            if (str[i] == 'z')
                c = 'a';
            else
                c = str[i] + 1;
            write(1, &c , 1);
        }
        else if (str[i] >= 'A' && str[i <= 'Z'])
        {
            if (str[i] == 'Z')
                c = 'A';
            else
                c = str[i] + 1;
            write(1, &c, 1);
        }
        else
            write(1, &str[i], 1);
        i++;
    }
    write(1, "\n", 1);
    return (0);
}