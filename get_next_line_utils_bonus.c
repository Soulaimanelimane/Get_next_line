/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:34:20 by slimane           #+#    #+#             */
/*   Updated: 2024/12/14 23:56:51 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

static void	ft_strcat(char *dest, char *src)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(dest);
	while (src[i])
	{
		dest[len] = src[i];
		i++;
		len++;
	}
	dest[len] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*all_strs;

	if (!s1)
		s1 = ft_strdup("");
	if (!s1 || !s2)
		return (free(s1), s1);
	all_strs = malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!all_strs)
		return (free(s1), NULL);
	all_strs[0] = '\0';
	ft_strcat(all_strs, s1);
	ft_strcat(all_strs, s2);
	free(s1);
	return (all_strs);
}

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	if ((char)c == '\0')
		return (s);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*ft_strdup(char *src)
{
	int		i;
	char	*str;

	i = 0;
	if (!src)
		return (NULL);
	str = malloc(ft_strlen(src) + 1);
	if (!str)
		return (NULL);
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
