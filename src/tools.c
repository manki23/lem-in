#include "../inc/lem_in.h"

int         number_ants(int ants, t_room *room, t_room *worst)
{
    int res;

    res = 1;
    if (ft_compare(room->name, worst->name) == 0)
        return (res);
    res = res + (room->nodes - worst->nodes);
    return (res);
}