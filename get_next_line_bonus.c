/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 23:40:00 by slimane           #+#    #+#             */
/*   Updated: 2024/12/16 22:04:42 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*readed_fn(int fd, char *next)
{
	int		readed;
	char	*joined_buf;
	char	*content;

	content = malloc((size_t)BUFFER_SIZE + 1);
	if (content == NULL)
		return (free(next), NULL);
	while (!(ft_strchr(next, '\n')))
	{
		readed = read(fd, content, BUFFER_SIZE);
		if (readed < 0)
			return (free(next), NULL);
		if (readed == 0)
			break ;
		content[readed] = '\0';
		joined_buf = ft_strjoin(next, content);
		if (joined_buf == NULL)
			return (free(content), free(next), NULL);
		next = joined_buf;
	}
	free(content);
	return (next);
}

char	*ft_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str || !*str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
		line = malloc(i + 1);
	else
		line = malloc(i + 2);
	if (!line)
		return (free(str), str = NULL, NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i])
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*rm_padd(char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (free(str), NULL);
	new_str = ft_strdup(&str[i + 1]);
	if (!new_str)
		return (free(str), NULL);
	free(str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*next_line[OPEN_MAX];
	char		*my_line;

	if (fd < 0 || BUFFER_SIZE > INT_MAX || fd > OPEN_MAX
		|| read(fd, NULL, 0) < 0)
	{
		if (fd <= OPEN_MAX && fd >= 0)
		{
			if (next_line[fd])
				free(next_line[fd]);
			next_line[fd] = NULL;
		}
		return (NULL);
	}
	next_line[fd] = readed_fn(fd, next_line[fd]);
	if (next_line[fd] == NULL)
		return (NULL);
	my_line = ft_line(next_line[fd]);
	next_line[fd] = rm_padd(next_line[fd]);
	return (my_line);
}
