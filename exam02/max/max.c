#include <limits.h>

int max(int *tab, unsigned int len)
{
    int i;
    int max;

    i = 0;
    max = INT_MIN;
    while (i < len)
    {
        if (tab[i] > max)
            max = tab[i];
        i++;
    }
    return (max);
}