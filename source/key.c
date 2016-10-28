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
	if (*k_down & KEY_A)
	{
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
		printf("Zoom\r");
	else if (env->mode == 1)
		printf("Red color\r");
	else if (env->mode == 2)
		printf("Green color\r");
	else if (env->mode == 3)
		printf("Blue color\r");
	else if (env->mode == 4)
		printf("iso\r");
}

void	key_up(t_env *env, u32 *k_down)
{
	if (*k_down & KEY_ZR)
		env->level++;
	if (*k_down & KEY_ZL)
		env->level--;
	if (*k_down & KEY_R)
	{
		consoleClear();
		printf("%d\n", env->speed);
		env->speed++;
		if (env->speed <= 0)
			env->speed = 1;
	}
	if (*k_down & KEY_L)
	{
		consoleClear();
		printf("%d\n", env->speed);
		env->speed--;
		if (env->speed <= 0)
			env->speed = 1;
	}
}
