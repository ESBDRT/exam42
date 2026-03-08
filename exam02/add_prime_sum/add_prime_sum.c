#include <unistd.h>

int widespace(const char c)
{
    if ((c >= 9 && c <= 13) || (c == 32))
        return (1);
    return (0);
}

int ft_atoi(const char *str)
{
    int sign = 1;
    int res = 0;
    int i = 0;

    while (widespace(str[i]))
        i++;
    if (str[i] == '-')
    {
        sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return (res * sign);
}

int isprime(int nb)
{
    int i = 2;

    while (i <= nb / 2)
    {
        if (!(nb % i))
            return (0);
        i++;
    }
    return (1);
}

void ft_putnbr(int nb)
{
    char c;

    if (nb > 9)
        ft_putnbr(nb / 10);
    c = nb % 10 + '0';
    write(1, &c, 1);
    return ;
}
int main(int argc, const char **argv)
{
    int nb;
    int sum;
    int i;

    if (argc != 2)
        return (write(1, "0\n", 2), 0);
    
    nb = ft_atoi(argv[1]);
    if (nb < 0)
        return (write(1, "0\n", 2), 0);
    
    if (nb == 2)
        return (write(1, "2\n", 2), 0);
    i = 2;
    sum = 0;
    while (i <= nb)
    {
        if (isprime(i))
            sum += i;
        i++; 
    }
    ft_putnbr(sum);
    write(1, "\n", 1);    
    return (0);
}