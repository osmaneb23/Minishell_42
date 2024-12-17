/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoet <apoet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:19:21 by febouana          #+#    #+#             */
/*   Updated: 2024/12/17 02:11:08 by apoet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void exec_builtin(char **cmd)
{
    t_data *data;
    data = get_data();
    if (ft_strcmp(cmd[0], "pwd") == 0) //?OKOK
        data->exit_status = ft_pwd();
    else if (ft_strcmp(cmd[0], "cd") == 0) //?OKOK
        data->exit_status = ft_cd(cmd); 
    else if (ft_strcmp(cmd[0], "export") == 0) //?OKOK (mais il boude)
        data->exit_status = ft_export(cmd);  
    else if (ft_strcmp(cmd[0], "unset") == 0) //?OKOK  
        data->exit_status = ft_unset(cmd);
    else if (ft_strcmp(cmd[0], "env") == 0) //?OKOK
        data->exit_status = ft_env(); 
    else if (ft_strcmp(cmd[0], "exit") == 0) //?OKOK
        data->exit_status = ft_exit(cmd); 
    else if (ft_strcmp(cmd[0], "echo") == 0) //?OKOK
        data->exit_status = ft_echo(cmd);
}

void	launch_builtin(t_cmd *cmd)
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
}

