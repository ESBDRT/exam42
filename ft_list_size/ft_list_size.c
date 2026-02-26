#include "ft_list_size.h"

int ft_list_size(t_list *begin)
{
    int size = 0;
    while (begin)
    {
        size++;
        begin = begin->next;
    }
    return (size);
}