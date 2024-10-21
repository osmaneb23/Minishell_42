/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:22:02 by obouayed          #+#    #+#             */
/*   Updated: 2023/11/22 13:48:34 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total;

	total = nmemb * size;
	if (total <= 0)
		return (malloc(0));
	if (total / nmemb != size)
		return (NULL);
	ptr = (unsigned char *)malloc(total);
	if (!(ptr))
		return (ptr);
	ft_bzero(ptr, total);
	return (ptr);
}
