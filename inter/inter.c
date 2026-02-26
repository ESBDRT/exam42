#include <unistd.h>

int main(int argc, const char **argv)
{
    int i;
    int j;
    int seen[256] = {0};

    if (argc != 3)
        return (write(1, "\n", 1), 0);

    i = 0;
    while (argv[1][i])
    {
        j = 0;
        while (argv[2][j])
        {
            if (argv[1][i] == argv[2][j])
            {
                if (!seen[(int)argv[1][i]])
                {
                    seen[(int)argv[1][i]] = 1;
                    write(1, &argv[1][i], 1);
                }
            }
            j++;
        }
        i++;
    }

    write(1, "\n", 1);
    return (0);
}