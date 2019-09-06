#include "../inc/lem_in.h"

void    free_all(t_all *all)
{
    t_room  *tmp;

	while (all->room)
	{
		ft_strdel(&(all->room->name));
		tmp = all->room->next;
		free(all->room);
		all->room = tmp;
	}
}
