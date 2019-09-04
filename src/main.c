/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:09:18 by manki             #+#    #+#             */
/*   Updated: 2019/09/04 12:37:27 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

/*
static void		ft_stock_input(void)
{
	fuction to stock the input in our structure
}
*/
int		main(void)
{
	char	*input;
	int		result;

	while (get_next_line(0, &input) == 1)
	{
//		result = ft_check_line(input);
//		ft_printf("result = %d\n", result);
		if (!ft_check_line(input))
			ft_error("ERROR", 2);
//		ft_stock_input();
		ft_strdel(&input);
	}
	return (0);
}
