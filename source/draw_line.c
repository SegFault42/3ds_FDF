#include "../include/fdf.h"

void	draw_y_line(t_env *env)
{
	int	tmp_x_point = 0;
	int	tmp_y_point = 0;
	char	r = 100, g = 0, b = 100;
	int	tmp_x1 = env->x1;
	int	tmp_x2 = env->x2;
	int	tmp_y1 = env->y1;
	int	tmp_y2 = env->y2;
	int	tmp_gap = env->gap;

	while (tmp_y_point < env->y_point)
	{
		tmp_x_point = 0;
		while (tmp_x_point < env->x_point - 1)
		{
			tmp_x2 = tmp_x1 + env->gap;
			sf2d_draw_line(tmp_x1, tmp_y1, tmp_x2, tmp_y2, 2, RGBA8(r, g, b, 255)); // draw all line.
			sf2d_draw_rectangle(tmp_x1, tmp_y1, 1, 1, RGBA8(255, 0, 0, 255)); // draw all point.
			tmp_x1 += env->gap;
			tmp_x_point++;
		}
		tmp_x1 = env->x1;
		tmp_y1 += env->gap;
		tmp_y2 += env->gap;
		tmp_y_point++;
	}
}

void	draw_x_line(t_env *env)
{
	int	tmp_x_point = 0;
	int	tmp_y_point = 0;
	char	r = 100, g = 0, b = 100;
	int	tmp_x1 = env->x1;
	int	tmp_x2 = env->x2;
	int	tmp_y1 = env->y1;
	int	tmp_y2 = env->y2;
	int	tmp_gap = env->gap;

	while (tmp_x_point < env->x_point)
	{
		tmp_y_point = 0;
		while (tmp_y_point < env->y_point - 1)
		{
			tmp_y2 = tmp_y1 + env->gap;
			sf2d_draw_line(tmp_x1, tmp_y1, tmp_x2, tmp_y2, 2, RGBA8(r, g, b, 255)); // draw all line.
			sf2d_draw_rectangle(tmp_x1, tmp_y1, 1, 1, RGBA8(255, 0, 0, 255)); // draw all point.
			tmp_y1 += env->gap;
			tmp_y_point++;
		}
		tmp_y1 = env->y1;
		tmp_x1 += env->gap;
		tmp_x2 += env->gap;
		tmp_x_point++;
	}
}
