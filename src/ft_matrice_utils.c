/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrice_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 13:19:49 by manki             #+#    #+#             */
/*   Updated: 2019/09/07 14:05:25 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int		**ft_alloc_matrice(int **mat, int len)
{
	int		i;
	int		j;

	if (!(mat = (int **)malloc(sizeof(int *) * len)))
		return (NULL);
	i = len;
	while (--i >= 0)
	{
		if (!(mat[i] = (int *)malloc(sizeof(int) * len)))
			return (NULL);
		j = -1;
		while (++j < len)
			mat[i][j] = 0;
	}
	return (mat);
}

void	ft_free_matrice(int **mat, int len)
{
	while (--len >= 0)
	{
		free(mat[len]);
		mat[len] = NULL;
	}
	free(mat);
	mat = NULL;
}

void	ft_display_matrice(char str[], int **mat, int len)
{
	int		i;
	int		j;

	ft_putendl("---------------------------");
	ft_putendl(str);
	i = -1;
	while (++i < len)
	{
		j = -1;
		while (++j < len)
		{
			ft_printf("%d   ", mat[i][j]);
		}
		ft_putendl("");
	}
	ft_putendl("");
}
