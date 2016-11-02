#include "../include/fdf.h"

void	c_stick(t_env *env, u32 *k_held)
{
	if (*k_held & KEY_CSTICK_UP)
	{
		if (env->mode == 0)
		{
			env->gap++;
			env->level++;
			if (env->gap <= 0)
				env->gap = 1;
			if (env->level <= 1)
				env->level = 1;
		}
		else if (env->mode == 1)
			++env->r;
		else if (env->mode == 2)
			++env->g;
		else if (env->mode == 3)
			++env->b;
		else if (env->mode == 4)
			++env->iso;
	}
	if (*k_held & KEY_CSTICK_DOWN)
	{
		if (env->mode == 0)
		{
			env->gap--;
			env->level--;
			if (env->gap <= 0)
				env->gap = 1;
			if (env->level <= 1)
				env->level = 1;
		}
		else if (env->mode == 1)
			--env->r;
		else if (env->mode == 2)
			--env->g;
		else if (env->mode == 3)
			--env->b;
		else if (env->mode == 4 && env->iso >= 2)
			--env->iso;
	}
}

void	c_pad(t_env *env, u32 *k_held)
{
	if (*k_held & KEY_CPAD_LEFT)
		env->origin_x -= env->speed;
	if (*k_held & KEY_CPAD_RIGHT)
		env->origin_x += env->speed;
	if (*k_held & KEY_CPAD_UP)
		env->origin_y -= env->speed;
	if (*k_held & KEY_CPAD_DOWN)
		env->origin_y += env->speed;
}

void	d_pad(t_env *env, u32 *k_down)
{
	if (*k_down & KEY_DRIGHT)
	{
		consoleClear();
		env->left_or_right = 1;
		select_map(env);
	}
	if (*k_down & KEY_DLEFT)
	{
		consoleClear();
		env->left_or_right = 0;
		select_map(env);
	}
}

void	button(t_env *env, u32 *k_down)
{
	printf("\x1b[1;0H");
	if (*k_down & KEY_A)
	{
		if (env->map != NULL)
		{
			ft_tab_free_int(env->map, env->y_point);
			/*ft_tab_free(env->tab);*/
			re_init_t_fdf_struct(env);
		}
		env->draw = parse_map(env);
		get_z_point(env);
	}
	if (*k_down & KEY_X)
	{
		++env->mode;
		if (env->mode >= 5)
			env->mode = 0;
	}
	if (env->mode == 0)
		printf("\x1b[37mZoom\x1b[0m                    \n");
	else if (env->mode == 1)
		printf("\x1b[31;1mRed color\x1b[0m                 \n");
	else if (env->mode == 2)
		printf("\x1b[32;1mGreen color\x1b[0m                 \n");
	else if (env->mode == 3)
		printf("\x1b[34mBlue color\x1b[0m                  \n");
	else if (env->mode == 4)
		printf("\x1b[37miso\x1b[0m                         \n");
}

void	key_up(t_env *env, u32 *k_down)
{
	printf("\x1b[4;0H");
	if (*k_down & KEY_ZR)
		env->level++;
	if (*k_down & KEY_ZL)
		env->level--;
	if (*k_down & KEY_R)
	{
		printf("%d\n", env->speed);
		env->speed++;
		if (env->speed <= 0)
			env->speed = 1;
	}
	if (*k_down & KEY_L)
	{
		printf("%d\n", env->speed);
		env->speed--;
		if (env->speed <= 0)
			env->speed = 1;
	}
	printf("Speed : %d                        \n", env->speed);
}

void	touch_screen(t_env *env, touchPosition *touch, u32 *k_held)
{
	u32	touch_x;
	u32	touch_y;

	touch_x = touch->px;
	touch_y = touch->py;
	if (touch_x != 0 && touch_y != 0)
	{
		env->origin_x = touch_x;
		env->origin_y = touch_y;
	}
	printf("\x1b[36mx = %03d; y = %03d\x1b[0m", touch_x, touch_y);
}
