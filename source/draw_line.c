#include "../include/fdf.h"

void	draw_y_line(t_env *env)
{
	int		tmp_x_point = 0;
	int		tmp_y_point = 0;
	int		tmp_gap = env->gap;
	char	r = 100, g = 0, b = 100;
	int		x1 = 1, x2 = 1, y1 = 1, y2 = 1;

	while (tmp_y_point < env->y_point)
	{
		tmp_x_point = 0;
		while (tmp_x_point < env->x_point - 1)
		{
			x2 = x1 + env->gap;
			sf2d_draw_line(x1, y1, x2, y2, 2, RGBA8(r, g, b, 255)); // draw all line.
			sf2d_draw_rectangle(x1, y1, 1, 1, RGBA8(255, 0, 0, 255)); // draw all point.
			x1 += env->gap;
			tmp_x_point++;
		}
		x1 = 1;
		x2 = 1;
		y1 += env->gap;
		y2 += env->gap;
		tmp_y_point++;
	}
}

void	draw_x_line(t_env *env)
{
	int		tmp_x_point = 0;
	int		tmp_y_point = 0;
	int		tmp_gap = env->gap;
	char	r = 100, g = 0, b = 100;
	int		x1 = 1, x2 = 1, y1 = 1, y2 = 1;

	while (tmp_x_point < env->x_point)
	{
		tmp_y_point = 0;
		while (tmp_y_point < env->y_point - 1)
		{
			y2 = y1 + env->gap;
			sf2d_draw_line(x1, y1, x2, y2, 2, RGBA8(r, g, b, 255)); // draw all line.
			sf2d_draw_rectangle(x1, y1, 1, 1, RGBA8(255, 0, 0, 255)); // draw all point.
			y1 += env->gap;
			tmp_y_point++;
		}
		y1 = 1;
		y2 = 1;
		x1 += env->gap;
		x2 += env->gap;
		tmp_x_point++;
	}
}
