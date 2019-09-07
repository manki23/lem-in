/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:01:13 by manki             #+#    #+#             */
/*   Updated: 2019/09/07 17:20:15 by manki            ###   ########.fr       */
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
	char			*command_stack;
	t_tube			*tube;
	t_room			*room;

}					t_all;

char				ft_stock_room(char *input, t_room **list, char **cmd_stack);
void				ft_print_room_name(t_room *begin);
void				free_all(t_all *all);

char				ft_cmp(char str1[], char str2[], char ref1[], char ref2[]);
char				ft_stock_tube(char *input, t_all **map);
char				ft_check_map(char *input, char line_id, t_all *map);
char				ft_map_enough_to_launch(t_all *map);

void				ft_display_all(t_all *map);

t_room				*ft_room_lstnew(char *name, t_coord c, char cmd);
void				ft_room_lstadd(t_room **l, char *name, t_coord c, char cmd);
int					ft_room_lstlen(t_room *list);
char				*ft_get_room_name(t_room *list, int position);
int					ft_get_room_pos_by_cmd(t_room *list, char cmd);

t_tube				*ft_tube_lstnew(char *room_a, char *room_b);
void				ft_tube_lstadd(t_tube **list, char *room_a, char *room_b);
int					ft_tube_lstlen(t_tube *list);
char				ft_tube_exist(t_tube *list, char room_a[], char room_b[]);

#endif
