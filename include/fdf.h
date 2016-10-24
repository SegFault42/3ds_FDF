#ifndef FDF_H
#define FDF_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
/*#include <3ds.h>*/
#include <sf2d.h>

typedef struct		s_env
{
	char			**tab;
	int				size_tab;
	unsigned int	iter_tab;
	int				left_or_right;
}					t_env;

void	get_maps(t_env *env);
int		count_file(t_env *env);

#endif
