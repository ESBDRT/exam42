#include <unistd.h>

int main(int argc, const char **argv)
{
    int i = 0;
    char c;

    if (argc != 2)
        return (write(1, "\n", 1), 0);

    while (argv[1][i])
    {
        if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
        {
            c = 'A' + 'Z' - argv[1][i];
            write(1, &c, 1);
        }
        else if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
        {
            c = 'a' + 'z' - argv[1][i];
            write(1, &c, 1); 
        }
        else
            write(1, &argv[1][i], 1);
        i++;
    }
    write(1, "\n", 1);
    return (0);
}