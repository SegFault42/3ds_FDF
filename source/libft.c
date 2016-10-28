/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:56:50 by rabougue          #+#    #+#             */
/*   Updated: 2016/09/15 01:27:06 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"


static void	ft_split_count(char const *s, char c, int *j)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			*j = *j + 1;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
}

static void	ft_split_tab(char const *s, char **str, char c, int *j)
{
	int len;
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		len = 0;
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			while (s[i + len] != c && s[i + len] != '\0')
				len++;
			str[*j] = ft_strsub(s, i, len);
			*j = *j + 1;
		}
		i = i + len;
	}
	str[*j] = NULL;
}

char		**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		j;

	j = 1;
	if (s == NULL)
		return (NULL);
	ft_split_count(s, c, &j);
	str = (char **)malloc(sizeof(char *) * j);
	if (str != NULL)
	{
		j = 0;
		ft_split_tab(s, str, c, &j);
	}
	return (str);
}

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	str = NULL;
	str = malloc(sizeof(char) * size + 1);
	if (str == NULL)
		return (NULL);
	while (i < size)
	{
		str[i] = '\0';
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (strdup(s2));
	else if (s2 == NULL)
		return (strdup(s1));
	i = strlen(s1) + strlen(s2) + 1;
	str = (char *)malloc(sizeof(char) * i);
	if (str == NULL)
		return (NULL);
	strcpy(str, s1);
	strcat(str, s2);
	return (str);
}

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	str = ft_strnew(len);
	if (!str)
		return (NULL);
	while (i < start)
		i++;
	while (j < len)
	{
		str[j] = s[i];
		i++;
		j++;
	}
	return (str);
}

static int	split_stat(char **line, char **stat)
{
	char	*content2;
	int		len;

	content2 = NULL;
	if (!(*stat))
		return (0);
	if ((content2 = strchr(*stat, '\n')))
	{
		len = content2 - *stat;
		*line = ft_strsub(*stat, 0, len);
		free(*stat);
		if (strlen(++content2))
			*stat = strdup(content2);
		else
			*stat = NULL;
	}
	else if (strlen(*stat))
	{
		*line = *stat;
		*stat = NULL;
	}
	return (content2 ? 1 : 0);
}

static int	read_file(char *buf, char **line, char **stat)
{
	char	*content;
	char	*tmp;

	if ((content = strchr(buf, '\n')))
	{
		content[0] = '\0';
		tmp = ft_strjoin(*line, buf);
		free(*line);
		*line = tmp;
		if (strlen(++content))
			*stat = strdup(content);
	}
	else
	{
		tmp = ft_strjoin(*line, buf);
		free(*line);
		*line = tmp;
	}
	return (content ? 1 : 0);
}

int			get_next_line(int const fd, char **line)
{
	static char	*stat[256] = {NULL};
	char		*buf;
	int			ret;

	if (fd < 0 || line == NULL || BUFF_SIZE <= 0 || fd > 256)
		return (-1);
	*line = NULL;
	buf = ft_strnew(BUFF_SIZE);
	if (split_stat(line, &stat[fd]) == 1)
	{
		free(buf);
		return (1);
	}
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (read_file(buf, line, &stat[fd]) == 1)
			break ;
	}
	free(buf);
	if (ret > 0 || *line)
		return (1);
	return (ret);
}
