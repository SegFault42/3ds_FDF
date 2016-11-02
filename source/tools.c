#include "../include/fdf.h"

void	print_tab(t_env *env)
{
	int	i = 0;

	while (i < env->size_tab)
	{
		printf("%s\n", env->tab[i]);
		++i;
	}
}

void	select_map(t_env *env)
{
	if (env->left_or_right == 1)
		++env->iter_tab;
	else if (env->left_or_right == 0)
		--env->iter_tab;
	if (env->iter_tab == 0)
		env->iter_tab = env->size_tab -1;
	else if (env->iter_tab >= env->size_tab)
		env->iter_tab = 0;
	printf("\x1b[0;15H");
	printf("\x1b[35;1m%s\n\x1b[0m", env->tab[env->iter_tab]);
}

void	ft_tab_free_int(int **tab, int nb)
{
	int i = 0;
	while (i < nb)
	{
		free(tab[i]);
		++i;
	}
	free(tab);
}

void	ft_tab_free(char **tab)
{
	int	i = 0;

	while (tab[i])
		free(tab[i++]);
	free(tab);
}
