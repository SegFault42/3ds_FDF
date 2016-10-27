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
	printf(BRED"%s\n"END, env->tab[env->iter_tab]);
}

void	ft_tab_free(char **tab)
{
	int	i = 0;

	while (tab[i])
		free(tab[i++]);
	free(tab);
}
