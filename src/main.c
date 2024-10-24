/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoet <apoet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:57:23 by obouayed          #+#    #+#             */
/*   Updated: 2024/10/24 17:52:55 by apoet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void *get_data()
{
    static t_data data;
    return (&data);
}

int ft_pwd()
{
    
    char cwd[PATH_MAX];

    if (getcwd(cwd, PATH_MAX))
    {
        printf("%s\n", cwd);
        return (SUCCESS);
    }
    else
    {
        perror("Failure: getcwd\n");
        return (FAILURE);
    }
}

int ft_cd(char *direction)
{
    char *res;
    t_data *data = get_data(); 

    if (direction == "")
    {
        res = ft_strjoin("/home/", data->username);
        if (!res)
        {
            perror("Failure: malloc\n");
            return (FAILURE); // error malloc
        }
        chdir(res);
        free(res);
        ft_pwd();
        return (SUCCESS);
    }
    if (chdir(direction) != 0)
    {    
        perror("Error: ft_cd\n");
        return (ERROR);
    }
    else
        ft_pwd();
    return (SUCCESS);
}


int	main(int ac, char **av)
{

    t_data *data = get_data(); 
    data->username = getenv("USER");

	char *line;
	while (1)
	{
		line = readline("\n>>>>\n");
        ft_cd(line);
	}
	return (0);
}
