/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:20:58 by slimane           #+#    #+#             */
/*   Updated: 2024/12/15 12:45:15 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*next_line;
	char		*my_line;

	if (fd < 0 || BUFFER_SIZE > INT_MAX || read(fd, NULL, 0) < 0)
	{
		if (next_line)
			free(next_line);
		next_line = NULL;
		return (NULL);
	}
	next_line = readed_fn(fd, next_line);
	if (next_line == NULL)
		return (NULL);
	my_line = ft_line(next_line);
	next_line = rm_padd(next_line);
	return (my_line);
}
