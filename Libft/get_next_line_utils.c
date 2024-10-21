/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:04:25 by obouayed          #+#    #+#             */
/*   Updated: 2024/01/06 23:35:09 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	search_nl(t_list *stash)
{
	int	i;

	if (!stash)
		return (0);
	stash = last_node(stash);
	while (stash)
	{
		i = 0;
		while (stash->content[i] != 0)
		{
			if (stash->content[i] == '\n')
				return (1);
			i++;
		}
		stash = stash->next;
	}
	return (0);
}

t_list	*last_node(t_list *stash)
{
	if (!stash)
		return (NULL);
	while (stash->next)
		stash = stash->next;
	return (stash);
}

int	len_for_line(t_list *stash)
{
	int	len;
	int	i;

	len = 0;
	if (!stash)
		return (0);
	while (stash)
	{
		i = 0;
		while (stash->content[i] && stash->content[i] != '\n')
		{
			i++;
			len++;
		}
		if (stash->content[i] == '\n')
			return (len + 1);
		stash = stash->next;
	}
	return (len);
}

void	copy_str(t_list *stash, char *str)
{
	int	i;
	int	k;

	if (!stash)
		return ;
	k = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				str[k++] = '\n';
				str[k] = '\0';
				return ;
			}
			str[k++] = stash->content[i++];
		}
		stash = stash->next;
	}
	str[k] = '\0';
}

void	lstclear(t_list **stash, t_list *node, char *buffer)
{
	t_list	*tmp;

	if (!stash)
		return ;
	while (*stash)
	{
		tmp = (*stash)->next;
		free((*stash)->content);
		free(*stash);
		*stash = tmp;
	}
	*stash = NULL;
	if (node->content[0])
		*stash = node;
	else
	{
		free(buffer);
		free(node);
	}
}
