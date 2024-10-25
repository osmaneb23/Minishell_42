/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:07:24 by febouana          #+#    #+#             */
/*   Updated: 2024/10/24 19:04:57 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr2(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*str;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
	{
		str = (malloc(sizeof(char)));
		str[0] = '\0';
		return (str);
	}
	i = 0;
	while ((s[start + i]) && (i < len))
		i++;
	str = (char *)malloc(i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while ((s[start + i]) && (i < len))
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	if (str[i] == (char)c)
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		str[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*audd;
	size_t			i;

	if (size != 0 && nmemb > (size_t)-1 / size)
		return (0);
	i = 0;
	audd = malloc(nmemb * size);
	if (!audd)
		return (NULL);
	while (i < nmemb * size)
	{
		audd[i] = 0;
		i++;
	}
	return (audd);
}

char	*ft_strdup2(const char *s)
{
	size_t	size;
	char	*tab;
	size_t	i;

	size = ft_strlen(s);
	tab = (char *)malloc(size * sizeof(char) + 1);
	if (!tab)
		return (NULL);
	i = 0;
	while (s[i])
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
