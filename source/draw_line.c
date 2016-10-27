#include "../include/fdf.h"

/*       draw_y_line
 *  --------------------
 *  --------------------
 *  --------------------
*/

void	draw_y_line(t_env *env)
{
	int		tmp_x_point = 0;
	int		tmp_y_point = 0;
	int		tmp_gap = env->gap;
	char	r = 100, g = 0, b = 100;
	int		x1 = 0;
	int		x2 = 0;
	int		y1 = 0;
	int		y2 = 0;
	int		iso = 2;

	while (tmp_y_point < env->y_point)
	{
		x1 = (tmp_x_point * env->gap) - (tmp_y_point * env->gap) + 100 ;
		y1 = (tmp_x_point * env->gap) + (tmp_y_point * env->gap) / iso + 100;
		while (tmp_x_point <= env->x_point - 1)
		{
			x2 = (tmp_x_point * env->gap) - (tmp_y_point * env->gap) + 100;
			y2 = (tmp_x_point * env->gap) + (tmp_y_point * env->gap) / iso + 100;
			sf2d_draw_line(x1, y1, x2, y2, 1, RGBA8(r, g, b, 255)); // draw all line.
			sf2d_draw_rectangle(x1, y1, 1, 1, RGBA8(255, 0, 0, 255)); // draw all point.
			x1 = x2;
			y1 = y2;
			tmp_x_point++;
		}
		tmp_y_point++;
		tmp_x_point = 0;
	}
}

/*     draw_x_line
 * |||||||||||||||||||
 * |||||||||||||||||||
 * |||||||||||||||||||
*/
void	draw_x_line(t_env *env)
{
	int		tmp_x_point = 0;
	int		tmp_y_point = 0;
	int		tmp_gap = env->gap;
	char	r = 100, g = 0, b = 100;
	int		x1 = 0;
	int		x2 = 0;
	int		y1 = 0;
	int		y2 = 0;
	int		iso = 2;

	while (tmp_x_point < env->x_point)
	{
		x1 = (tmp_x_point * env->gap) - (tmp_y_point * env->gap) + 100;
		y1 = (tmp_x_point * env->gap) + (tmp_y_point * env->gap) / iso + 100;
		while (tmp_y_point <= env->y_point - 1)
		{
			x2 = (tmp_x_point * env->gap) - (tmp_y_point * env->gap) + 100;
			y2 = (tmp_x_point * env->gap) + (tmp_y_point * env->gap) / iso + 100;
			sf2d_draw_line(x1, y1, x2, y2, 1, RGBA8(r, g, b, 255)); // draw all line.
			sf2d_draw_rectangle(x1, y1, 1, 1, RGBA8(255, 0, 0, 255)); // draw all point.
			x1 = x2;
			y1 = y2;
			tmp_y_point++;
		}
		tmp_x_point++;
		tmp_y_point = 0;
	}
}
