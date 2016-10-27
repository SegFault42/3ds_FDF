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
	int		x1 = 0;
	int		x2 = 0;
	int		y1 = 0;
	int		y2 = 0;
	int		iso = 2;

	while (y < env->y_point)
	{
		x1 = (x * env->gap) - (y * env->gap) + 200;
		if ((y + 1) < env->y_point)
			y1 = ((x * env->gap) + (y * env->gap) / iso + 0 + env->gap / iso) - (env->map[y][x] * env->level);
		else
			y1 = ((x * env->gap) + (y * env->gap) / iso + 0 + env->gap / iso);
		while (x <= env->x_point - 1)
		{
			x2 = (x * env->gap) - (y * env->gap) + 200;
			y2 = ((x * env->gap) + (y * env->gap) / iso + 0 + env->gap / iso) - (env->map[y][x] * env->level);
			sf2d_draw_line(x1, y1, x2, y2, 2, RGBA8(r, g, b, 255)); // draw all line.
			sf2d_draw_rectangle(x1, y1, 1, 1, RGBA8(255, 0, 0, 255)); // draw all point.
			x1 = x2;
			y1 = y2;
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
	int		x1 = 0;
	int		x2 = 0;
	int		y1 = 0;
	int		y2 = 0;
	int		iso = 2;

	while (x < env->x_point)
	{
		x1 = (x * env->gap) - (y * env->gap) + 200;
		if ((y + 1) < env->y_point)
			y1 = ((x * env->gap) + (y * env->gap) / iso + 0 + env->gap / iso) - (env->map[y][x] * env->level);
		else
			y1 = ((x * env->gap) + (y * env->gap) / iso + 0 + env->gap / iso);
		while (y <= env->y_point - 1)
		{
			x2 = (x * env->gap) - (y * env->gap) + 200;
			y2 = ((x * env->gap) + (y * env->gap) / iso + 0 + env->gap / iso) - (env->map[y][x] * env->level);
			sf2d_draw_line(x1, y1, x2, y2, 2, RGBA8(r, g, b, 255)); // draw all line.
			sf2d_draw_rectangle(x1, y1, 1, 1, RGBA8(255, 0, 0, 255)); // draw all point.
			x1 = x2;
			y1 = y2;
			y++;
		}
		x++;
		y = 0;
	}
}
