/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:01:13 by manki             #+#    #+#             */
/*   Updated: 2019/09/11 10:53:03 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"
# include "limits.h"

enum	{ ERROR, NUMBER, COMMAND, ROOM, TUBE, COMMENT };

enum	{ NO_CMD, CMD_START, CMD_END};

int					ft_check_line(char *in);

typedef struct		s_coord
{
	int				x;
	int				y;
}					t_coord;

typedef struct		s_room
{
	char			*name;
	char			command;
	char			visit;
	int				x;
	int				y;
	struct s_room	**tab;
	struct s_room	*next;
	struct s_room	*parent;
	struct s_room	*child;
	struct s_room	*old_parent;
	struct s_room	*old_child;
}					t_room;

typedef struct		s_all
{
	int				ants;
	char			*command_stack;
	t_room			*room;

}					t_all;

typedef struct		s_queue
{
	t_room			*room;
	struct s_queue	*next;
}					t_queue;

char				ft_stock_room(char *input, t_room **list, char **cmd_stack);
void				free_all(t_all *all);

char				ft_cmp(char str1[], char str2[], char ref1[], char ref2[]);
char				ft_stock_tube(char *input, t_all **map);
char				ft_check_map(char *input, char line_id, t_all *map);
char				ft_map_enough_to_launch(t_all *map);

void				ft_display_all(t_all *map);

t_room				*ft_room_lstnew(char *name, t_coord c, char cmd);
void				ft_room_lstadd(t_room **l, char *name, t_coord c, char cmd);
int					ft_room_lstlen(t_room *list);
t_room				*ft_get_room(t_room **list, int position);
int					ft_get_room_pos_by_cmd(t_room *list, char cmd);

int					ft_tab_len(t_room *r);
char				ft_add_tube(t_room **list, char *room_a, char *room_b);

t_queue				*ft_create_queue(t_room **room);
void				ft_enqueue(t_queue **list, t_room **room);
t_queue				*ft_dequeue(t_queue **list);
void				ft_free_queue(t_queue **list);
void				ft_print_queue(t_queue *list);

void				ft_breadth_first_search(t_all *map);

#endif
