#include <stdlib.h>

size_t	ft_strcspn(const char *s, const char *reject)
{
    size_t len = 0;
    int i;
    
    while (s[len])
    {
        i = 0;
        while (reject[i])
        {
            if (s[len] == reject[i])
                return (len);
            i++;
        }   
        len++;
    }
    return (len);
}