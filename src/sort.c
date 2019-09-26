#include "../inc/lem_in.h"

void			set_next(t_queue **cpy, t_queue **before, t_queue **next)
{
	(*cpy)->next = (*next)->next;
	(*next)->next = *cpy;
	(*before) = *next;
	*next = (*cpy)->next;
}

int				sort(t_queue *cpy, t_queue *before, t_queue *next
							, t_queue **first)
{
	int			i;

	i = 0;
	before = NULL;
	cpy = *first;
	next = cpy->next;
	while (next)
	{
		if (cpy->nodes > cpy->next->nodes)
		{
			i = 1;
			if (before == NULL)
            {
				first[0] = next;
				cpy->next = next->next;
            }
            else
            {   
				before->next = next;
			}
			set_next(&cpy, &before, &next);
		}
		else
		{
			before = cpy;
			cpy = cpy->next;
			next = cpy->next;
		}
	}
	return (i);
}

void	print_queue(t_queue *queue)
{
	t_queue *tmp;

	tmp = queue;
	while (tmp)
	{
		ft_printf("room == %s\n",tmp->room->name);
		tmp = tmp->next;
	}
}
t_queue   *sort_lst(t_queue *display)
{
	t_queue    *cpy;
	t_queue    *before;
	t_queue    *next;
	t_queue    **first;

	first = &display;
	before = NULL;
	cpy = display;
    next = cpy->next;
	print_queue(display);
	//*first = next;
	//cpy->next = next->next;
	//next->next = display;
	//before = next;
	//next = cpy->next;
	while (sort(cpy, before, next, first))
        ;
	print_queue(display);
		ft_printf("display a == %s\n", display->room->name);
    return (*first);
}

int		calc_nodes(t_room *room)
{
	t_room *tmp;
	int c;

	c = 0;
	tmp = room;
	while (tmp)
	{
		tmp = tmp->child;
		c++; 
	}
	return (c);
}

int		total_ants(int *ants, int size)
{
	int res;
	int i;

	i = 0;
	res = 0;
	while (i < size)
	{
		res = res + ants[i];
		i++;
	}
	return (res);
}