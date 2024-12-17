#include "../../includes/minishell.h"

void	redirect_input_output(t_cmd *cmd, int *pip)
{
	if (cmd->infile >= 0) // si redirection d'entree de precisee ?
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	if (cmd->outfile >= 0)
	{
		dup2(cmd->outfile, STDOUT_FILENO); // si redirection de sortie de precisee ? + //! secu
		close(cmd->outfile);
	}
	else if (cmd->next != NULL) // si cmd n'est pas la derniere cmd
		dup2(pip[1], STDOUT_FILENO);
}

void	parent_process(int *pip, t_cmd *next_cmd)
{
	close(pip[1]);
	if (next_cmd)
		next_cmd->infile = pip[0];
	else
		close(pip[0]);
}

int	destroy_child_process(int exit_status, char **to_be_free)
{
	t_data	*data;

	data = get_data();
	close_all_redi(data);
	if (to_be_free)
		ft_free_multi_array(to_be_free);
	if (data)
	{
		if (data->envp)
			destroy_envp_list(&data->envp);
		free_data(&data);
		if (data->line)
			free(data->line);
	}
	rl_clear_history();
	exit(exit_status);
}

void	child_process(t_cmd *cmd, int *pip, char **env)
{
	t_data	*data;
	char	*path;

	data = get_data();
	if (cmd->infile >= 0)
		close(pip[0]);
	if (cmd->outfile < 0 && cmd->next != NULL)
		cmd->outfile = pip[1];
	if (is_builtin(cmd->cmd_param[0]))
	{
		redirect_input_output(cmd, pip);
		exec_builtin(cmd->cmd_param);
	}
	else
	{
		redirect_input_output(cmd, pip);
		if (access(cmd->cmd_param[0], X_OK) == 0)
			execve(cmd->cmd_param[0], cmd->cmd_param, env);
		else
		{
			path = return_command_in_path(cmd->cmd_param[0]);
			if (!path)
				destroy_child_process(EXIT_MALLOC, env);
			execve(path, cmd->cmd_param, env);
			free(path);
		}
	}
	destroy_child_process(data->exit_status, env);
}


int	exec_cmd(t_data *data, t_cmd *cmd, int *pip)
{
	char	**env;

	env = copy_envp_to_tab(data, data->envp);
	if (!env)
		return (close_all_redi(data), cleanup(ERROR, ERR_MALLOC, ERROR, 2)); //? OKOK
	data->current_pid = fork();
	signal_child_process();
	if (data->current_pid == 0)
	{
		if (cmd->cmd_param && cmd->cmd_param[0])
			child_process(cmd, pip, env);
		else
			destroy_child_process(SUCCESS, env); // MY HERO 
	}
	else
	{
		if (env)
			ft_free_multi_array(env);
		parent_process(pip, cmd->next);
	}
	return (SUCCESS);
}

int	exec(t_data *data)
{
	t_cmd	*tmp;
	int		*pip;

	tmp = data->cmd;
	pip = data->pip;
	if (!tmp->skip_cmd && tmp->cmd_param && tmp->cmd_param[0] && is_builtin(tmp->cmd_param[0]) && cmd_list_len(data->cmd) == 1) //verif tmp->cmd_param pour "<< LIMITER"
	{
		printf("=======launch-builtin=======\n");
		launch_builtin(tmp);
		if (data->exit_status == EXIT_MALLOC)
			cleanup(EXIT_MALLOC, ERR_MALLOC, EXIT_MALLOC, 2); //!
		if (data->exit_status != SUCCESS)
			return (cleanup(NO_CHANGE, NULL, NO_EXIT, 2));
		return (SUCCESS);
	}
	printf("=======pipex=======\n");
	while (tmp)
	{
		if (pipe(pip) == -1)
			return (cleanup(ERROR, ERR_PIPE, ERROR, 2));
		exec_cmd(data, tmp, pip);
		tmp = tmp->next;
	}
	close_all_redi(data);
	wait_all(data);
	setup_signals();
	if (data->exit_status != SUCCESS)
		return (cleanup(NO_CHANGE, NULL, NO_EXIT, 2));
	return (SUCCESS);
}

// WIFEXITED ==> verifie le status
// WEXITSTATUS ==> retourne l'exit_status

//? =======================================================
// FEHIM:
//* corriger appel chemin absolu et executable
//* revoir comportement builtin // repertoire courant (ASKIP)
//* secu si envp entierement unset
//* revoir exit status de chaque builtins
//* corriger cmd_init (// "< infile | wc" ==> cas d'encule)
//* cas "<< LIMITER" rajouter heredoc pour sq seule et sans commande
//* faire au propre no such file or directory dans init_commands
//* revoir return ERR malloc...etc dans exec

//! reeeeeeee tester export

//! rajouter close redi dans exec_cmd

//! RAJOUTER CA DANS LES FREE DE FIN DE FN
	//! if (!access(".heredoc.tmp", F_OK))
	//! 	unlink(".heredoc.tmp");

//! changer printf en print_error si besoin

//? =======================================================




// Among these, exit status 125 is a special case. It is typically reserved but not explicitly 
// used by POSIX bash for a specific predefined purpose. While other exit statuses have defined 
// meanings (like 126 and 127 for execution errors), 125 remains somewhat unique in that it's 
// available but not standardized for a particular system-level function.
// Programmers sometimes use exit status 125 as a convention to indicate a "soft" or controlled 
// failure that differs from more critical errors, but this is not a POSIX-mandated standard. 
// It's essentially a "free" exit code that can be used flexibly in shell scripts without conflicting 
// with system-defined meanings.