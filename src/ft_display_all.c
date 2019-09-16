/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:35:59 by manki             #+#    #+#             */
/*   Updated: 2019/09/09 13:59:55 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	display(SDL_Renderer *renderer, t_all *all)
{
	SDL_Rect rec;

	SDL_SetRenderDrawColor(renderer, 255,
                                255, 255, 255);
	while (all->room != NULL)
	{
		rec.h = 100;
		rec.w = 100;
		rec.x = all->room->x * 100;
		rec.y = all->room->y * 100;
		SDL_RenderFillRect(renderer, &rec);
		//SDL_RenderDrawLine(renderer, p_hor / 2, 0, p_hor / 2, p_ver);
		all->room = all->room->next;
	}
	SDL_RenderPresent(renderer);
}

void	display_window(t_all *all)
{
	SDL_Window		*window;
	SDL_Event		event;
	SDL_Renderer	*renderer;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        ft_printf("Échec de l'initialisation de la SDL (%s)\n", SDL_GetError());
	   	return ;
    }
	window = SDL_CreateWindow("LEM IN",
                        SDL_WINDOWPOS_UNDEFINED,
                        SDL_WINDOWPOS_UNDEFINED,
                        1920,
                        1080,
                        SDL_WINDOW_MAXIMIZED);
	renderer = SDL_CreateRenderer(window, -1, 0);
	display(renderer, all);
	if (window)
	{
		while (1)
		{
			SDL_PollEvent(&event);
			 if (event.type == SDL_QUIT
                        || event.key.keysym.sym == SDLK_ESCAPE)
                exit(0);
		}
	}
}

void	ft_display_all(t_all *map)
{
	int		i;
	t_room	*room_tmp;

	ft_putendl("---------------------------------");
	ft_printf("Ants number: %d\n", map->ants);
	ft_printf("Rooms: (%d)\n", ft_room_lstlen(map->room));
	room_tmp = map->room;
	while (room_tmp)
	{
		if (room_tmp->command == CMD_START)
			ft_putstr(" (start) ");
		else if (room_tmp->command == CMD_END)
			ft_putstr(" (end) ");
		ft_printf("{%s} has %d connections :\n", room_tmp->name,
				ft_tab_len(room_tmp));
		i = -1;
		while (room_tmp->tab && room_tmp->tab[++i])
			ft_printf("| %s |\n", room_tmp->tab[i]->name);
		ft_putendl("");
		room_tmp = room_tmp->next;
	}
}
