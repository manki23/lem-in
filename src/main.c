/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:09:18 by manki             #+#    #+#             */
/*   Updated: 2019/09/17 12:07:15 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static void		ft_error_bis(t_all *all, char str[], char fd)
{
	free_all(all);
	ft_error(str, fd);
}

static void		ft_init_all_struct(t_all *all)
{
	all->room = NULL;
	all->command_stack = NULL;
	all->ants = -1;
}

static void		ft_analyse_input(char **input, t_all *all, char *end_input)
{
	if (!ft_check_map(*input, ft_check_line(*input), all))
	{
		if (ft_map_enough_to_launch(all))
			end_input[0] = 1;
		else
		{
			ft_strdel(input);
			ft_error_bis(all, "ERROR", 2);
		}
	}
	ft_strdel(input);
}

int				main(void)
{
	char		*input;
	t_all		all;
	char		end_input;
	t_queue		*solution;

	ft_init_all_struct(&all);
	end_input = 0;
	solution = NULL;
	while (!end_input && get_next_line(0, &input) == 1)
		ft_analyse_input(&input, &all, &end_input);
	if (ft_map_enough_to_launch(&all))
	{
		if (!(solution = ft_breadth_first_search(&all)))
			ft_error_bis(&all, "ERROR", 2);
		ft_putendl("\nThe solutions path begin with the following room(s) :");
		ft_print_queue(solution);
	}
	else
		ft_error_bis(&all, "ERROR", 2);
	if (solution)
		ft_free_queue(&solution);
	free_all(&all);
	return (0);
}
