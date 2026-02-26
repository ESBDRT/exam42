int is_wide(const char c)
{
    if ((c >= 9 && c <= 13) || (c == 32))
        return (1);
    return (0);
}

int ft_atoi(const char *str)
{
    int res;
    int sign;
    int i;

    sign = 1;
    i = 0;
    res = 0;

    while (is_wide(str[i]))
        i++;
    
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }

    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + str[i] - 48;
        i++;
    }
    return (res * sign);
}
