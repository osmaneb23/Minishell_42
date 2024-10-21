/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:21:14 by obouayed          #+#    #+#             */
/*   Updated: 2023/12/01 14:08:38 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	a;

	a = 0;
	if (c > 127)
	{
		while (s[a])
		{
			if (s[a] == (char)c)
				return ((char *)&s[a]);
			a++;
		}
		return (NULL);
	}
	while (s[a])
		a++;
	while (a >= 0)
	{
		if (s[a] == c)
			return ((char *)&s[a]);
		a--;
	}
	return (NULL);
}
