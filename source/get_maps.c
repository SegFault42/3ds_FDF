#include "../include/fdf.h"

int		count_file(t_env *env)
{
	DIR				*directory = NULL;
	struct dirent	*dir = NULL;

	directory = opendir("./Maps/");
	if (directory)
	{
		while ((dir = readdir(directory)) != NULL)
			++env->size_tab;
		closedir(directory);
		/*env->size_tab -= 2; // substract "." and ".."*/
	}
	else
		printf("Error : No such file or directory\n");
	return (env->size_tab);
}

void	get_maps(t_env *env)
{
	DIR				*directory = NULL;
	struct dirent	*dir = NULL;
	int				i = 0;

	env->size_tab = count_file(env);
	directory = opendir("./Maps/");
	if (directory)
	{
		env->tab = (char **)malloc(sizeof(char *) * env->size_tab);
		while ((dir = readdir(directory)) != NULL)
		{
			if ((dir->d_name[0] != '.' && strlen(dir->d_name) != 1) &&
				(strstr(dir->d_name, "..") == NULL && strlen(dir->d_name) != 2))
			{
				env->tab[i] = strdup(dir->d_name);
				++i;
			}
		}
		closedir(directory);
	}
	else
		printf("Error : No such file or directory\n");
	return ;
}
