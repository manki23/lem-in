/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:01:13 by manki             #+#    #+#             */
/*   Updated: 2019/09/04 12:11:53 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"

enum		{ ERROR, NUMBER, COMMAND, ROOM, TUBE, COMMENT };

int			ft_check_line(char *in);
void		stock_room(char *input, t_room *begin);
void	print_room_name(t_room *begin);
typedef struct    s_room
{
    char *name;
    int x;
    int y;
    char **connexion;
    struct s_room *next;
}                   t_room;        

typedef struct     s_all
{
    int ants;
    struct s_room *room;

}           t_all;


#endif
