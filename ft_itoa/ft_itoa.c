#include <stdlib.h>
#include <stdio.h>

int getlen(int nb)
{
    int len = 0;

    if (nb == 0)
        return (1);
    if (nb < 0)
    {
        len++;
        nb = -nb;
    }
    while (nb > 0)
    {
        len++;
        nb /= 10;
    }
    return (len);
}

char *ft_itoa(int nbr)
{
    char *str;
    int len;

    len = getlen(nbr);
    str = malloc(len * sizeof(char) + 1);
    if (!str)
        return (NULL);

    if (nbr < 0)
    {
        str[0] = '-';
        nbr = -nbr;
    }
    str[len] = '\0';
    while (len-- > 0)
    {
        if (str[len] == '-')
            break;
        str[len] = nbr % 10 + '0';
        nbr /= 10;
    }
    return (str);
}
