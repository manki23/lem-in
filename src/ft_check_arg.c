/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 14:53:36 by manki             #+#    #+#             */
/*   Updated: 2019/09/29 16:04:07 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static void		ft_print_usage(t_all **all)
{
	ft_putendl("Usage:\t./lem-in [-vc] <map>\n");
	ft_putendl("\t-v, --visu-hex\t\tto use visu-hex.py visualizer");
	ft_putendl("\t-c, --color\t\t\tto see output with colors");
	free_all(all[0]);
	exit(-2);
}

static char		ft_check_one(char arg[], t_all **all)
{
		ft_putendl("X");
		ft_putendl(arg);
	if (!all[0]->args[0] && (!ft_strcmp(arg, "-v")
				|| !ft_strcmp(arg, "--visu-hex")))
		all[0]->args[0] = 1;
	else if (!all[0]->args[1] && (!ft_strcmp(arg, "-c")
				|| !ft_strcmp(arg, "--color")))
		all[0]->args[1] = 1;
	else if (!all[0]->args[1] && !all[0]->args[0]  && (!ft_strcmp(arg, "-vc")
				|| !ft_strcmp(arg, "-cv")))
	{
		all[0]->args[0] = 1;
		all[0]->args[1] = 1;
	}
	else
	{
		ft_print_usage(all);
		return (0);
	}
	return (1);
}


void			ft_check_arg(int ac, char *av[], t_all *all)
{
	int		i;

	ac++;
	av--;
	if (ac > 2)
	{
		i = -1;
		while (++i < ac - 2)
			ft_check_one(av[i], &all);
	}
}
