#include <stdio.h>
#include <stdlib.h>

int is_wide(char c)
{
    if ((c >= 9 && c <= 13) || (c == 32))
        return (1);
    return (0);
}

int count_words(char *str)
{
    int i;
    int words;

    i = 0;
    words = 0;

    while (str[i])
    {
        while (str[i] && is_wide(str[i]))
            i++;
        if (str[i])
            words++;
        while (str[i] && !is_wide(str[i]))
            i++;
    }
    return (words);
}

char  *ft_strdup(char *str, int start, int end)
{
    char *dup;
    int i;

    dup = malloc(end - start + 1);
    if (!dup)
        return (NULL);
    i = 0;
    while (i < end - start)
    {
        dup[i] = str[start + i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

char **ft_split(char *str)
{
    char **arr;
    int start;
    int pos;
    int i;

    arr = malloc((count_words(str) + 1) * sizeof(char *));
    if (!arr)
        return (NULL);

    pos = 0;
    i = 0;
    while (str[i])
    {
        while (str[i] && is_wide(str[i]))
            i++;
        start = i;
        while (str[i] && !is_wide(str[i]))
            i++;
        if (start < i)
            arr[pos++] = ft_strdup(str, start, i);
    }
    arr[pos] = NULL;
    return (arr);

}
