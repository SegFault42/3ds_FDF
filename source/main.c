#include "../include/fdf.h"

static void	init_t_fdf_struct(t_env *env)
{
	env->tab = NULL;
	env->size_tab = 0;
	env->iter_tab = 0;
	env->left_or_right = 0;
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
	printf("%s\r", env->tab[env->iter_tab]);
	printf("\niter_tab = %d\r", env->iter_tab);
}

void	parse_map(t_env *env)
{
	int		fd;
	char	*map = NULL;

	//==========================get_map_name===================================
	// Alloc size for name path (./Maps/) and map name.
	map = (char *)malloc(sizeof(char) * (strlen(env->tab[env->iter_tab]) + 7));
	strcpy(map, "./Maps/");
	strcat(map, env->tab[env->iter_tab]);
	//=========================================================================
	if ((fd = open(map, O_RDONLY)) < 0)
	{
		printf("Opening map error !\n");
		return ;
	}
	printf("fd = %d\n", fd);
}

int main()
{
	PrintConsole	bot_screen;
	t_env			env;
	u32				k_held;
	u32				k_down;

	init_t_fdf_struct(&env);
	sf2d_init();
	sf2d_set_3D(0);
	sf2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));
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
		{
			parse_map(&env);
		}
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
			sf2d_draw_line(0, 0, 100, 100, 1, RGBA8(0x00, 0xFF, 0x00, 100));
		sf2d_end_frame();

		sf2d_swapbuffers();
		/*sf2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));*/
	}
	sf2d_fini();
	return 0;
}
