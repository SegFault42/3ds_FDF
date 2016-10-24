#include "../include/fdf.h"

static void	init_t_fdf_struct(t_env *env)
{
	env->tab = NULL;
	env->size_tab = 0;
	env->iter_tab = 0;
	env->left_or_right = 0;
	env->y_point = 0;
	env->x_point = 0;
	return ;
}

static void	print_tab(t_env *env)
{
	int	i = 0;

	while (i < env->size_tab)
	{
		printf("%s\n", env->tab[i]);
		++i;
	}
}

void	select_map(t_env *env)
{
	if (env->left_or_right == 1)
		++env->iter_tab;
	else if (env->left_or_right == 0)
		--env->iter_tab;
	if (env->iter_tab == 0)
		env->iter_tab = env->size_tab -1;
	else if (env->iter_tab >= env->size_tab)
		env->iter_tab = 0;
	printf("                           \r");
	printf(BRED"%s\r"END, env->tab[env->iter_tab]);
}

int		parse_map(t_env *env)
{
	int		fd;
	char	*map_name = NULL;
	char	*line = NULL;
	int		i = 0;
	char	**split_line;

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
			free(map_name);
			return (EXIT_FAILURE);
		}
		else
			env->x_point = i;
		++env->y_point;
		i = 0;
	}
	close(fd);
	free(map_name);
	return (EXIT_SUCCESS);
}

void	draw_grille(t_env *env)
{
	int	tmp_x_point = env->x_point;
	int	tmp_y_point = env->y_point;
	int	x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	int	gap = 10;
	int	size_grille_x = 300;
	int	size_grille_y = gap * env->y_point;

	while (tmp_y_point > 0)
	{
		tmp_x_point = env->x_point;
		while (tmp_x_point > 0)
		{
			sf2d_draw_rectangle(x1, y1, 1, 1, RGBA8(255, 255, 0, 255));
			x1 += gap;
			tmp_x_point--;
			printf("debug\n");
		}
		x1 = 0;
		y1 += gap;
		tmp_y_point--;
	}
}

int main()
{
	PrintConsole	bot_screen;
	t_env			env;
	u32				k_held;
	u32				k_down;
	int				draw = EXIT_FAILURE;

	init_t_fdf_struct(&env);
	sf2d_init();
	sf2d_set_3D(0);
	sf2d_set_clear_color(RGBA8(0x0, 0x00, 0x00, 0xFF));
	consoleInit(GFX_BOTTOM, &bot_screen); //Init bottom screen

	get_maps(&env);
	/*print_tab(&env);*/

	while (aptMainLoop())
	{
		hidScanInput();
		k_held = hidKeysHeld();
		k_down = hidKeysDown();

		if (k_held & KEY_START)
			break;
		if (k_down & KEY_DRIGHT)
		{
			env.left_or_right = 1;
			select_map(&env);
		}
		if (k_down & KEY_DLEFT)
		{
			env.left_or_right = 0;
			select_map(&env);
		}
		if (k_down & KEY_A)
			draw = parse_map(&env);
		if (draw == EXIT_SUCCESS)
		{
			sf2d_start_frame(GFX_TOP, GFX_LEFT);
				draw_grille(&env);
			sf2d_end_frame();
		}

		sf2d_swapbuffers();
		/*sf2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));*/
	}
	sf2d_fini();
	return 0;
}
