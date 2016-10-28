#include "../include/fdf.h"

/*       draw_y_line
 *  --------------------
 *  --------------------
 *  --------------------
*/

void	draw_y_line(t_env *env)
{
	int		x = 0;
	int		y = 0;
	char	r = 0, g = 204, b = 0;
	int		iso = 2;
	int		tmp_x1 = env->x1, tmp_x2 = env->x2, tmp_y1 = env->y1, tmp_y2 = env->y2;

	while (y < env->y_point)
	{
		tmp_x1 = (x * env->gap) - (y * env->gap) + 200;
		if ((y + 1) < env->y_point)
			tmp_y1 = ((x * env->gap) + (y * env->gap) / iso + 0 + env->gap / iso) - (env->map[y][x] * env->level);
		else
			tmp_y1 = ((x * env->gap) + (y * env->gap) / iso + 0 + env->gap / iso);
		while (x <= env->x_point - 1)
		{
			tmp_x2 = (x * env->gap) - (y * env->gap) + 200;
			tmp_y2 = ((x * env->gap) + (y * env->gap) / iso + 0 + env->gap / iso) - (env->map[y][x] * env->level);
			sf2d_draw_line(tmp_x1, tmp_y1, tmp_x2, tmp_y2, 2, RGBA8(r, g, b, 255)); // draw all line.
			sf2d_draw_rectangle(tmp_x1, tmp_y1, 1, 1, RGBA8(255, 0, 0, 255)); // draw all point.
			tmp_x1 = tmp_x2;
			tmp_y1 = tmp_y2;
			x++;
		}
		y++;
		x = 0;
	}
}

/*     draw_x_line
 * |||||||||||||||||||
 * |||||||||||||||||||
 * |||||||||||||||||||
*/
void	draw_x_line(t_env *env)
{
	int		x = 0;
	int		y = 0;
	char	r = 0, g = 204, b = 0;
	int		iso = 2;
	int		tmp_x1 = env->x1, tmp_x2 = env->x2, tmp_y1 = env->y1, tmp_y2 = env->y2;

	while (x < env->x_point)
	{
		tmp_x1 = (x * env->gap) - (y * env->gap) + 200;
		if ((y + 1) < env->y_point)
			tmp_y1 = ((x * env->gap) + (y * env->gap) / iso + 0 + env->gap / iso) - (env->map[y][x] * env->level);
		else
			tmp_y1 = ((x * env->gap) + (y * env->gap) / iso + 0 + env->gap / iso);
		while (y <= env->y_point - 1)
		{
			tmp_x2 = (x * env->gap) - (y * env->gap) + 200;
			tmp_y2 = ((x * env->gap) + (y * env->gap) / iso + 0 + env->gap / iso) - (env->map[y][x] * env->level);
			sf2d_draw_line(tmp_x1, tmp_y1, tmp_x2, tmp_y2, 2, RGBA8(r, g, b, 255)); // draw all line.
			sf2d_draw_rectangle(tmp_x1, tmp_y1, 1, 1, RGBA8(255, 0, 0, 255)); // draw all point.
			tmp_x1 = tmp_x2;
			tmp_y1 = tmp_y2;
			y++;
		}
		x++;
		y = 0;
	}
}
