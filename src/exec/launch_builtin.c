/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:19:21 by febouana          #+#    #+#             */
/*   Updated: 2024/12/04 16:19:51 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int exec_builtin(char **cmd)
{
    if (ft_strcmp(cmd[0], "cd") == 0)
        return (ft_cd(cmd));
    if (ft_strcmp(cmd[0], "pwd") == 0)
        return (ft_pwd());
    if (ft_strcmp(cmd[0], "export") == 0)
        return (ft_export(cmd));
    if (ft_strcmp(cmd[0], "unset") == 0)
        return (ft_unset(cmd));
    if (ft_strcmp(cmd[0], "env") == 0)
        return (ft_env());
    if (ft_strcmp(cmd[0], "exit") == 0)
        return (ft_exit(cmd));
    if (ft_strcmp(cmd[0], "echo") == 0)
        return (ft_echo(cmd));
    return (ERROR);
}

bool	launch_builtin(t_cmd *cmd)
{
	int	save_stdout;

	save_stdout = -1;
	if (cmd->outfile >= 0)
	{
		save_stdout = dup(STDOUT_FILENO);
		dup2(cmd->outfile, STDOUT_FILENO);
        close(cmd->outfile);
	}
	exec_builtin(cmd->cmd_param);
    if (cmd->outfile >= 0)
    {
        dup2(save_stdout, STDOUT_FILENO);
        close(save_stdout);
    }
	return (SUCCESS);
}

