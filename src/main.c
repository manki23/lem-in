/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:09:18 by manki             #+#    #+#             */
/*   Updated: 2019/09/18 15:42:26 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static void		ft_error_bis(t_all *all, char str[], char fd, t_list **list)
{
	free_all(all);
	if (list && list[0])
		ft_lstdel_2(list);
	ft_error(str, fd);
}

static void		ft_init_all_struct(t_all *all)
{
	all->room = NULL;
	all->command_stack = NULL;
	all->ants = -1;
}

static void		ft_analyse_input(char **input, t_all *all, char *end_input, t_list **list)
{
	if (!ft_check_map(*input, ft_check_line(*input), all))
	{
		if (ft_map_enough_to_launch(all))
			end_input[0] = 1;
		else
		{
			ft_strdel(input);
			ft_error_bis(all, "ERROR", 2, list);
		}
	}
}

int				main(void)
{
	char		*input;
	t_list		*input_list;
	t_all		all;
	char		end_input;
	t_queue		*solution;

	ft_init_all_struct(&all);
	end_input = 0;
	solution = NULL;
	input_list = NULL;
	while (!end_input && get_next_line(0, &input) == 1)
	{
		ft_analyse_input(&input, &all, &end_input, &input_list);
		if (!input_list && !end_input)
			input_list = ft_lstnew(input, ft_strlen(input));
		else
			ft_lsadd(&input_list, input, ft_strlen(input));
		ft_strdel(&input);
	}
	if (ft_map_enough_to_launch(&all))
	{
		if (!(solution = ft_breadth_first_search(&all)))
			ft_error_bis(&all, "ERROR", 2, &input_list);
	}
	else
		ft_error_bis(&all, "ERROR", 2, &input_list);
	if (solution)
		display(solution, all.ants);
	/*if (solution)
	{
		ft_lstprint(input_list, '\n');
		write(1, "\n", 1);
		ft_free_queue(&solution);
	}*/
	ft_lstdel_2(&input_list);
	free_all(&all);
	return (0);
}
