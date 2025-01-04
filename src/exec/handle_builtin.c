/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:19:21 by febouana          #+#    #+#             */
/*   Updated: 2025/01/04 17:55:59 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_builtin(char **cmd)
{
	t_data	*data;

	data = get_data();
	if (ft_strcmp(cmd[0], "pwd") == 0)
		data->exit_status = ft_pwd();
	else if (ft_strcmp(cmd[0], "cd") == 0)
		data->exit_status = ft_cd(cmd);
	else if (ft_strcmp(cmd[0], "export") == 0)
		data->exit_status = ft_export(cmd);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		data->exit_status = ft_unset(cmd);
	else if (ft_strcmp(cmd[0], "env") == 0)
		data->exit_status = ft_env();
	else if (ft_strcmp(cmd[0], "echo") == 0)
		data->exit_status = ft_echo(cmd);
	else if (ft_strcmp(cmd[0], "exit") == 0)
	{
		if (count_nb_sequences(data->token) == 1)
			data->exit_status = ft_exit(cmd, 1);
		else
			data->exit_status = ft_exit(cmd, 0);
	}
}

void	handle_builtin(t_cmd *cmd)
{
	int	save_stdout;

	save_stdout = -1;
	if (cmd->infile >= 0)
		close(cmd->infile);
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

bool	is_valid_cmd(char *cmd)
{
	if (check_command_in_path(cmd) == SUCCESS || is_builtin(cmd) == true
		|| access(cmd, X_OK) == 0)
		return (true);
	return (false);
}

// void	link_builtin_to_pipex(t_cmd *cmd, int *pip)
// {
// 	int	save_stdout;
// 	int	tmp_file;

// 	close(pip[0]);
// 	if (cmd->next->infile == -2)
// 	{
// 		tmp_file = open("/tmp/.minishell.builtinlink.",
// 				O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 		save_stdout = dup(STDOUT_FILENO);
// 		dup2(tmp_file, STDOUT_FILENO);
// 		exec_builtin(cmd->cmd_param);
// 		dup2(save_stdout, STDOUT_FILENO);
// 		close(save_stdout);
// 		close(tmp_file);
// 		tmp_file = open("/tmp/.minishell.builtinlink.", O_RDONLY);
// 		cmd->next->infile = tmp_file;
// 		unlink("/tmp/.minishell.builtinlink.");
// 	}
// 	close(pip[1]);
// }
