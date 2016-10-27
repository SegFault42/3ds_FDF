#ifndef FDF_H
#define FDF_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
/*#include <3ds.h>*/
#include <sf2d.h>

#define BUFF_SIZE 32

#define WIDTH_TOP 400
#define HEIGHT_TOP 320
#define ORIGIN_X (WIDTH_TOP / 2)
#define ORIGIN_Y (HEIGHT_TOP / 2)

# define BLACK		"\033[30m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define PURPLE		"\033[35m"
# define CYAN		"\033[36m"
# define WHITE		"\033[37m"
# define ORANGE		"\033[38;5;208m"
# define PINK		"\033[38;5;13m"
# define GREY		"\033[38;5;246m"

# define BBLACK		"\033[40m"
# define BRED		"\033[41m"
# define BGREEN		"\033[42m"
# define BYELLOW	"\033[43m"
# define BBLUE		"\033[44m"
# define BPURPLE	"\033[45m"
# define BCYAN		"\033[46m"
# define BWHITE		"\033[47m"
# define BORANGE	"\033[48;5;208m"
# define BPINK		"\033[48;5;13m"
# define BGREY		"\033[48;5;246m"

# define END		"\033[0m"

#define CONFIG_3D_SLIDERSTATE (*(float *)0x1FF81080)

typedef struct		s_env
{
	char				**tab;
	int				**map;
	int				size_tab;
	unsigned int	iter_tab;
	int				left_or_right;
	int				y_point;
	int				x_point;
	int				x1;
	int				x2;
	int				y1;
	int				y2;
	int				gap;
	int				speed;
	int				level;
	int				origin_x;
	int				origin_y;
}					t_env;

//int		get_next_line(int const fd, char **line);

void	get_maps(t_env *env);
int		count_file(t_env *env);

//====================================draw.c===================================
void	draw_y_line(t_env *env);
void	draw_x_line(t_env *env);
//=============================================================================

//====================================tools.c==================================
void	print_tab(t_env *env);
void	select_map(t_env *env);
//=============================================================================

#endif
