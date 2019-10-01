/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:09:18 by manki             #+#    #+#             */
/*   Updated: 2019/09/29 16:18:26 by manki            ###   ########.fr       */
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
	all->args = ft_memalloc(ARGS_NUMBER);
	all->command_stack = NULL;
	all->ants = -1;
}

static char		ft_analyse_input(char **input, t_all *all, t_list **list)
{
	char		end_input;

	end_input = 0;
	if (!ft_check_map(*input, ft_check_line(*input), all))
	{
		if (ft_map_enough_to_launch(all))
			end_input = 1;
		else
		{
			ft_strdel(input);
			ft_error_bis(all, "ERROR", 2, list);
		}
	}
	if (!list && !list[0] && !end_input)
		list[0] = ft_lstnew(input[0], ft_strlen(input[0]));
	else if (!end_input)
		ft_lsadd(list, input[0], ft_strlen(input[0]));
	ft_strdel(input);
	return (end_input);
}

static void		ft_get_and_display_solution(t_queue **so, t_list **in, t_all *a)
{
	if (so && so[0])
	{
		ft_lstprint(*in, '\n');
		write(1, "\n", 1);
		display(so, a->ants);
		if (a->args[2] == 1)
			ft_printf("Nombre de tours == %d\n", so[0]->c_t);
		ft_free_queue(so);
	}
	ft_lstdel_2(in);
	free_all(a);
}

int				main(int ac, char **av)
{
	char		*input;
	t_list		*input_list;
	t_all		all;
	char		end_input;
	t_queue		*solution;

	ft_init_all_struct(&all);
	ft_check_arg(ac, av, &all);
	end_input = 0;
	solution = NULL;
	input_list = NULL;
	while (!end_input && get_next_line(0, &input) == 1)
		end_input = ft_analyse_input(&input, &all, &input_list);
	if (ft_map_enough_to_launch(&all))
	{
		if (!(solution = ft_breadth_first_search(&all)))
			ft_error_bis(&all, "ERROR", 2, &input_list);
	}
	else
		ft_error_bis(&all, "ERROR", 2, &input_list);
	ft_get_and_display_solution(&solution, &input_list, &all);
	return (0);
}
