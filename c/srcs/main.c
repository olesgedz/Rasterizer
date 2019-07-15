/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olesgedz <olesgedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:34:45 by sdurgan           #+#    #+#             */
/*   Updated: 2019/07/15 12:33:51 by olesgedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rst.h"
#include <time.h>
#include "libsdl.h"

t_game game;
float xa, ya, za;


int		ft_input_keys(void *sdl, SDL_Event *ev)
{
	switch (ev->type)
		{
			case SDL_QUIT: ft_exit(NULL);
		}
	return (1);
}

void 	ft_render(t_game* game)
{
	int		i;
	int		j;
	int width = game->sdl->surface->width;
	int height = game->sdl->surface->height;
	j = -1;
	//ft_run_gpu(game->gpu);
	ft_line(game->sdl->surface, &(t_point){0,400}, &(t_point){250,250}, 0xff0000);
	ft_line(game->sdl->surface, &(t_point){250,250}, &(t_point){500,500}, 0xff0000);
}


/*
*	Fucntion: Main loop
*		1. Clear the screen
*		2. Handle input
*		3. Render
*	!	4. surface_combine is redrawing only part of the screen, not used yet
*		5. Put surface to texture and then to on Screen
*			? don't use surfaces and use just textures for speed
*	Parameters: game, sdl
*	Return: none
*/

void ft_update(t_game *game)
{
	t_rectangle r = (t_rectangle){(t_point){0,0},(t_size){WIN_W, WIN_H}};
	clock_t current_ticks, delta_ticks;
	clock_t fps = 0;
	while(TRUE)
	{
		current_ticks = clock();
		ft_surface_clear(game->sdl->surface);
		ft_input(game->sdl, &ft_input_keys);
		ft_render(game);
		ft_surface_present(game->sdl, game->sdl->surface);
	#ifdef FPS
				 delta_ticks = clock() - current_ticks; //the time, in ms, that took to render the scene
    if(delta_ticks > 0)
        fps = CLOCKS_PER_SEC / delta_ticks;
		
			printf("fps :%lu\n", fps);
	#endif
	SDL_Delay(200);
	 }

}

int	main(int argc, char **argv)
{
	game.sdl = malloc(sizeof(t_sdl));
	game.image = ft_surface_create(WIN_W, WIN_H);

	ft_init_window(game.sdl, WIN_W, WIN_H);
	ft_update(&game);
	ft_exit(NULL);
}