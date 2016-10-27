#include "../include/fdf.h"

void	c_stick(t_env *env, u32 *k_held)
{
	if (*k_held & KEY_CSTICK_UP)
	{
		env->gap++;
		env->level++;
		if (env->gap <= 0)
		{
			env->gap = 1;
			env->level == env->gap - 8;
		}
		if (env->level <= 1)
			env->level = 1;
	}
	if (*k_held & KEY_CSTICK_DOWN)
	{
		env->gap--;
		env->level--;
		if (env->gap <= 0)
		{
			env->gap = 1;
			env->level == env->gap - 8;
		}
		if (env->level <= 1)
			env->level = 1;
	}
}

void	c_pad(t_env *env, u32 *k_held)
{
	if (*k_held & KEY_CPAD_LEFT)
	{
		env->x1 -= env->speed;
		env->x2 -= env->speed;
	}
	if (*k_held & KEY_CPAD_RIGHT)
	{
		env->x1 += env->speed;
		env->x2 += env->speed;
	}
	if (*k_held & KEY_CPAD_UP)
	{
		env->y1 -= env->speed;
		env->y2 -= env->speed;
	}
	if (*k_held & KEY_CPAD_DOWN)
	{
		env->y1 += env->speed;
		env->y2 += env->speed;
	}
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

int		button(t_env *env, u32 *k_down)
{
	if (*k_down & KEY_A)
	{
		env->draw = parse_map(&env);
		get_z_point(&env);
	}
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
