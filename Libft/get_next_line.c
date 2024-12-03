/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoet <apoet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:41:58 by febouana          #+#    #+#             */
/*   Updated: 2024/11/28 15:18:10 by apoet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// size_t	ft_strlen(const char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		i++;
// 	}
// 	return (i);
// }

static char	*set_line(char *line_buffer)
{
	char	*res;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == 0 || line_buffer[1] == 0)
		return (NULL);
	res = ft_substr2(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*res == 0)
	{
		free(res);
		res = NULL;
	}
	line_buffer[i + 1] = 0;
	return (res);
}

static char	*read_fd(int fd, char *audd, char *buffer)
{
	char	*tmp;
	ssize_t	byte_read;

	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(audd);
			return (NULL);
		}
		else if (byte_read == 0)
			break ;
		buffer[byte_read] = 0;
		if (!audd)
			audd = ft_strdup2("");
		tmp = audd;
		audd = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (audd);
}

char	*get_next_line(int fd)
{
	static char	*audd;
	char		*line;
	char		*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE == 0 || read(fd, 0, 0) < 0)
	{
		free(audd);
		free(buffer);
		audd = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = read_fd(fd, audd, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	audd = set_line(line);
	return (line);
}
