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

	while (y < env->y_point)
	{
		env->x1 = (x * env->gap) - (y * env->gap) + env->origin_x;
		if ((y + 1) < env->y_point)
			env->y1 = ((x * env->gap) + (y * env->gap) / env->iso + env->origin_y + env->gap / env->iso) - (env->map[y][x] * env->level);
		else
			env->y1 = ((x * env->gap) + (y * env->gap) / env->iso + env->origin_y + env->gap / env->iso);
		while (x <= env->x_point - 1)
		{
			env->x2 = (x * env->gap) - (y * env->gap) + env->origin_x;
			env->y2 = ((x * env->gap) + (y * env->gap) / env->iso + env->origin_y + env->gap / env->iso) - (env->map[y][x] * env->level);
			sf2d_draw_line(env->x1, env->y1, env->x2, env->y2, 2, RGBA8(env->r, env->g, env->b, 255)); // draw all line.
			/*sf2d_draw_rectangle(env->x1, env->y1, 1, 1, RGBA8(255, 0, 0, 255)); // draw all point.*/
			env->x1 = env->x2;
			env->y1 = env->y2;
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

	while (x < env->x_point)
	{
		env->x1 = (x * env->gap) - (y * env->gap) + env->origin_x;
		if ((y + 1) < env->y_point)
			env->y1 = ((x * env->gap) + (y * env->gap) / env->iso + env->origin_y + env->gap / env->iso) - (env->map[y][x] * env->level);
		else
			env->y1 = ((x * env->gap) + (y * env->gap) / env->iso + env->origin_y + env->gap / env->iso);
		while (y <= env->y_point - 1)
		{
			env->x2 = (x * env->gap) - (y * env->gap) + env->origin_x;
			env->y2 = ((x * env->gap) + (y * env->gap) / env->iso + env->origin_y + env->gap / env->iso) - (env->map[y][x] * env->level);
			sf2d_draw_line(env->x1, env->y1, env->x2, env->y2, 2, RGBA8(env->r, env->g, env->b, 255)); // draw all line.
			/*sf2d_draw_rectangle(env->x1, env->y1, 1, 1, RGBA8(255, 0, 0, 255)); // draw all point.*/
			env->x1 = env->x2;
			env->y1 = env->y2;
			y++;
		}
		x++;
		y = 0;
	}
}
