#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char **argv)
{
    int nb1;
    int nb2;
    int mod;
    int max;
    
    if (argc != 3)
        return (printf("\n"), 0);

    nb1 = atoi(argv[1]);
    nb2 = atoi(argv[2]);
    max = 2;
    mod = 2;
    while (mod < nb1 && mod < nb2)
    {
        if (!(nb1 % mod) && !(nb2 % mod))
            max = mod;
        mod++;
    }
    printf("%d\n", max);
    return (0);
}