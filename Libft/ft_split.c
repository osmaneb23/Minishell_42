/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:55:47 by obouayed          #+#    #+#             */
/*   Updated: 2023/12/01 14:05:29 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_all(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		s[i] = NULL;
		i++;
	}
	free(s);
}

static int	nb_words(const char *s, char delimiter)
{
	int	count;
	int	in_word;
	int	i;

	count = 0;
	in_word = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == delimiter)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static char	*copy_word(const char *s, char delimiter, char **result)
{
	int		length;
	char	*word;
	int		i;

	length = 0;
	while (s[length] && s[length] != delimiter)
		length++;
	word = (char *)malloc((length + 1) * sizeof(char));
	if (word == NULL)
	{
		free_all(result);
		return (NULL);
	}
	i = -1;
	while (++i < length)
		word[i] = s[i];
	word[length] = '\0';
	return (word);
}

static char	**splitter(char const *s, char c, char **result, int word_count)
{
	int	i;

	i = -1;
	while (*s)
	{
		if (*s != c)
		{
			result[++i] = copy_word(s, c, result);
			if (result[i] == NULL)
				return (NULL);
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	result[word_count] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	char	**result;

	if (s == NULL)
		return (NULL);
	word_count = nb_words(s, c);
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	return (splitter(s, c, result, word_count));
}
