/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:01:13 by manki             #+#    #+#             */
/*   Updated: 2019/09/06 16:26:47 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"
# include "limits.h"

enum	{ ERROR, NUMBER, COMMAND, ROOM, TUBE, COMMENT };

int					ft_check_line(char *in);

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	struct s_room	*next;
}					t_room;

typedef struct		s_tube
{
	char			*room_a;
	char			*room_b;
	struct s_tube	*next;
}					t_tube;

typedef struct		s_all
{
	int				ants;
	t_tube			*tube;
	t_room			*room;

}					t_all;

char				ft_stock_room(char *input, t_room **begin);
void				ft_print_room_name(t_room *begin);
void				free_all(t_all *all);

char				ft_stock_tube(char *input, t_all **map);
char				ft_check_map(char *input, char line_id, t_all *map);

void				ft_display_all(t_all *map);

t_room				*ft_room_lstnew(char *name, int x, int y);
void				ft_room_lstadd(t_room **list, char *name, int x, int y);
int					ft_room_lstlen(t_room *list);

t_tube				*ft_tube_lstnew(char *room_a, char *room_b);
void				ft_tube_lstadd(t_tube **list, char *room_a, char *room_b);
int					ft_tube_lstlen(t_tube *list);

#endif
