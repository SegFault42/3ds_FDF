#include "../include/fdf.h"

/*
** mode = 0 : zoom
** mode = 1 : Red color
** mode = 2 : Green color
** mode = 3 : Blue color
** mode = 4 : iso
*/

void	re_init_t_fdf_struct(t_env *env)
{
	env->map = NULL;
	/*env->iter_tab = 0;*/
	env->left_or_right = 0;
	env->y_point = 0;
	env->x_point = 0;
	env->x1 = 1;
	env->x2 = 1;
	env->y1 = 1;
	env->y2 = 1;
	env->gap = 1;
	env->speed = 1;
	env->level = 1;
	env->origin_x = ORIGIN_X;
	env->origin_y = ORIGIN_Y;
	env->draw = EXIT_FAILURE;
	env->mode = 0;
	env->r = 255;
	env->g = 0;
	env->b = 0;
	env->iso = 2;
}

void	init_t_fdf_struct(t_env *env)
{
	env->tab = NULL;
	env->map = NULL;
	env->size_tab = 0;
	env->iter_tab = 0;
	env->left_or_right = 0;
	env->y_point = 0;
	env->x_point = 0;
	env->x1 = 1;
	env->x2 = 1;
	env->y1 = 1;
	env->y2 = 1;
	env->gap = 1;
	env->speed = 1;
	env->level = 1;
	env->origin_x = ORIGIN_X;
	env->origin_y = ORIGIN_Y;
	env->draw = EXIT_FAILURE;
	env->mode = 0;
	env->r = 255;
	env->g = 0;
	env->b = 0;
	env->iso = 2;
}

int		parse_map(t_env *env)
{
	u8		fd;
	char	*map_name = NULL;
	char	*line = NULL;
	u8		i = 0;
	char	**split_line = NULL;

	//==========================get_map_name===================================
	// Alloc size for name path (./Maps/) and map name.
	map_name = (char *)malloc(sizeof(char) * (strlen(env->tab[env->iter_tab]) + 7));
	strcpy(map_name, "./Maps/");
	strcat(map_name, env->tab[env->iter_tab]);
	//=========================================================================
	if ((fd = open(map_name, O_RDONLY)) < 0)
	{
		printf("Opening map error !\n");
		free(map_name);
		return (EXIT_FAILURE);
	}
	while (get_next_line(fd, &line) > 0)
	{
		++env->y_point;
		split_line = ft_strsplit(line, ' ');
		free(line);
		while (split_line[i] != NULL)
			++i;
		ft_tab_free(split_line);
		if (env->x_point > 0 && env->x_point != i)
		{
			printf("Map size error\n");
			close(fd);
			ft_tab_free(split_line);
			free(map_name);
			return (EXIT_FAILURE);
		}
		else
			env->x_point = i;
		i = 0;
	}
	close(fd);
	free(map_name);
	return (EXIT_SUCCESS);
}

int	get_z_point(t_env *env)
{
	u8	fd, i = 0, j = 0;
	char	*line = NULL;
	char	*map_name = NULL;
	char	**split_line = NULL;

	map_name = (char *)malloc(sizeof(char) * (strlen(env->tab[env->iter_tab]) + 7));
	strcpy(map_name, "./Maps/");
	strcat(map_name, env->tab[env->iter_tab]);
	if ((fd = open(map_name, O_RDONLY)) < 0)
	{
		printf("Opening map error !\n");
		free(map_name);
		return (EXIT_FAILURE);
	}
	env->map = (int **)malloc(sizeof(int *) * env->y_point);
	while (get_next_line(fd, &line) > 0)
	{
		split_line = ft_strsplit(line, ' ');
		env->map[i] = (int *)malloc(sizeof(int) * env->x_point);
		while (j < env->x_point)
		{
			env->map[i][j] = atoi(split_line[j]);
			j++;
		}
		j = 0;
		++i;
		free(line);
		ft_tab_free(split_line);
	}
	free(map_name);
	return (EXIT_SUCCESS);
}

int main()
{
	PrintConsole	bot_screen;
	touchPosition	touch;
	t_env			env;
	u32				k_held;
	u32				k_down;
	u32				touch_x;
	u32				touch_y;

	init_t_fdf_struct(&env);
	sf2d_init_advanced(SF2D_GPUCMD_DEFAULT_SIZE * 2, SF2D_TEMPPOOL_DEFAULT_SIZE * 2);
	sf2d_set_3D(0);
	sf2d_set_clear_color(RGBA8(64, 64, 64, 255));
	consoleInit(GFX_BOTTOM, &bot_screen); //Init bottom screen

	get_maps(&env);

	printf("\x1b[0;15H");
	printf("\x1b[35;1m%s\n\x1b[0m", env.tab[0]);
	while (aptMainLoop())
	{
		printf("\x1b[0;0H");
		printf("\x1b[29;0Hx = %03d; y = %03d", env.origin_x, env.origin_y);
	//=====================================Button==============================
		hidScanInput();
		hidTouchRead(&touch);
		if (k_held & KEY_TOUCH)
		{
			touch_screen(&env, &touch, &k_held);
		}
		k_held = hidKeysHeld();
		k_down = hidKeysDown();
		c_stick(&env, &k_held);
		c_pad(&env, &k_held);
		d_pad(&env, &k_down);
		button(&env, &k_down);
		key_up(&env, &k_down);
		if (k_held & KEY_START)
			break;
	//=========================================================================
	//=====================================Draw================================
		if (env.draw == EXIT_SUCCESS)
		{
			sf2d_start_frame(GFX_TOP, GFX_LEFT);
				draw_y_line(&env);
				draw_x_line(&env);
			sf2d_end_frame();
		}
		sf2d_swapbuffers();
		sf2d_set_clear_color(RGBA8(64, 64, 64, 255));
	//=========================================================================
		printf("\x1b[3;0H");
		printf("fps = %2.f\n", sf2d_get_fps()); // print frame per second
	}
	/*ft_tab_free_int(env.map, env.y_point);*/
	/*ft_tab_free(env.tab);*/
	sf2d_fini();
	return 0;
}
