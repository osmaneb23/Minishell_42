/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:37:39 by obouayed          #+#    #+#             */
/*   Updated: 2024/01/06 23:34:16 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);
int					search_nl(t_list *stash);
t_list				*last_node(t_list *stash);
void				add_buffer(t_list **stash, int fd);
void				add_stash(char *buffer, t_list **stash);
char				*add_line(t_list *stash);
void				copy_str(t_list *list, char *str);
int					len_for_line(t_list *stash);
void				clear_stash(t_list **stash);
void				lstclear(t_list **stash, t_list *node, char *buffer);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

#endif