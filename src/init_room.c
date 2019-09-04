#include "../inc/lem_in.h"

void	print_room_name(t_room *begin)
{
	while (begin)
	{
		begin = begin->next;
	}
}

void		ft_add_room(t_room **begin, t_room *new)
{
	t_room	*tmp;

	if (new)
	{
		tmp = *begin;
		if (tmp == NULL)
			tmp = new;
		else
		{
			while (tmp)
				tmp = tmp->next;
			tmp = new;
		}
	}
}

void		stock_room(char *input, t_room *begin)
{
	char **s;
	int i;
	t_room *room;

	i = 0;
	if (!(room = (t_room*)malloc(sizeof(t_room))))
		return ;
	if (!(s = ft_strsplit(input,' ')))
		return ;
	if (!(room->name = ft_strdup(s[0])))
		return ;
	room->x = ft_atoi(s[1]);
	room->y = ft_atoi(s[2]);
	room->next = NULL;
	ft_add_room(&begin, room);
	ft_strrdel(s);
}