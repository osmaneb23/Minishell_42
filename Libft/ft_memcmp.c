/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:30:13 by obouayed          #+#    #+#             */
/*   Updated: 2023/12/01 14:07:48 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ss1;
	const unsigned char	*ss2;
	size_t				a;

	ss1 = (const unsigned char *)s1;
	ss2 = (const unsigned char *)s2;
	a = 0;
	while (a < n)
	{
		if (ss1[a] < ss2[a])
			return (-1);
		if (ss1[a] > ss2[a])
			return (1);
		a++;
	}
	return (0);
}
