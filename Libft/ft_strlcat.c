/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:53:27 by obouayed          #+#    #+#             */
/*   Updated: 2023/12/01 14:08:21 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < n && s1[i])
	{
		i++;
	}
	while ((i + j + 1) < n && s2[j])
	{
		s1[i + j] = s2[j];
		j++;
	}
	if (i != n)
	{
		s1[i + j] = '\0';
	}
	return (i + ft_strlen(s2));
}
