#include "../include/fdf.h"

/*
** mode = 0 : zoom
** mode = 1 : Red color
** mode = 2 : Green color
** mode = 3 : Blue color
** mode = 4 : iso
*/

static void	init_t_fdf_struct(t_env *env)
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
	int		fd;
	char	*map_name = NULL;
	char	*line = NULL;
	int		i = 0;
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
		split_line = ft_strsplit(line, ' ');
		while (split_line[i])
			++i;
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
		++env->y_point;
		i = 0;
		free(line);
		ft_tab_free(split_line);
	}
	close(fd);
	free(map_name);
	return (EXIT_SUCCESS);
}

int	get_z_point(t_env *env)
{
	int		fd, i = 0, j = 0;
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
	t_env			env;
	u32				k_held;
	u32				k_down;

	init_t_fdf_struct(&env);
	sf2d_init_advanced(SF2D_GPUCMD_DEFAULT_SIZE, SF2D_TEMPPOOL_DEFAULT_SIZE);
	sf2d_set_3D(0);
	sf2d_set_clear_color(RGBA8(64, 64, 64, 255));
	consoleInit(GFX_BOTTOM, &bot_screen); //Init bottom screen

	get_maps(&env);

	while (aptMainLoop())
	{
	//=====================================Button==============================
		hidScanInput();
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
		printf("fps = %2.f\r", sf2d_get_fps()); // print frame per second
	}
	sf2d_fini();
	return 0;
}
