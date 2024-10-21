/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:19:27 by obouayed          #+#    #+#             */
/*   Updated: 2023/12/01 14:07:51 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*arr_dest;
	const char	*arr_src;

	if (!src && !dest)
		return (NULL);
	arr_dest = dest;
	arr_src = src;
	i = 0;
	while (i < n)
	{
		*arr_dest = *arr_src;
		arr_dest++;
		arr_src++;
		i++;
	}
	return (dest);
}
