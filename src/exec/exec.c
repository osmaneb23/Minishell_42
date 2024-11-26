#include "../../includes/minishell.h"

char *get_path_next(char **path) 
{
    char *dir;
    char *next;

    if (!path || !*path)
        return NULL;
    dir = *path;
    next = ft_strchr(*path, ':');
    if (next) 
    {
        *next = '\0';
        *path = next + 1;
    } 
    else
        *path = NULL;
    return dir;
}

char *check_solo_path(char *dir, char *command) 
{
    char *full_path;
    char *tmp;

    if (!dir || !command)
        return NULL;
    tmp = ft_strjoin(dir, "/");
    if (!tmp)
        return NULL;
    full_path = ft_strjoin(tmp, command);
    free(tmp);
    if (!full_path)
        return NULL;
    if (access(full_path, X_OK) == 0)
        return full_path; 
    else 
    {
        free(full_path);
        return NULL;
    }
}

char *return_command_in_path(char *command) 
{
    char *path;
    char *path_copy;
    char *original_ptr;
    char *dir;
    char *full_path;

    if (!command)
        return NULL;
    path = getenv("PATH");
    if (!path)
        return NULL;
    path_copy = ft_strdup(path);
    if (!path_copy)
        return NULL;
    original_ptr = path_copy;
    dir = get_path_next(&path_copy);
    while (dir) 
    {
        full_path = check_solo_path(dir, command);
        if (full_path) 
        {
            free(original_ptr);
            return full_path;
        }
        dir = get_path_next(&path_copy);
    }
    free(original_ptr);
    return NULL;
}

// ======================================================================
// ======================================================================
// ======================================================================

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
    // if (ft_strcmp(cmd[0], "echo") == 0)
    //     return (ft_echo());
    return (ERROR);
}

//infile outfile -1
// int launch_builtin(t_cmd *cmd)
// {
// //! rediriger vers la bonne sortie safe auparavant si redirection de detectee
//  	int	save_stdout;

// 	save_stdout = -1;
// 	if (cmd->outfile >= 0)
// 	{
// 		save_stdout = dup(1);
// 		dup2(cmd->outfile, 1);
// 	}
// 	exec_builtin(cmd->cmd_param);
// //! remet la sortie initiale (sauf si plusieurs arguments ???)
// 	if (cmd->outfile >= 0)
// 	{
// 		dup2(save_stdout, STDOUT_FILENO);
// 		close (save_stdout);
// 	}
//     return (SUCCESS);
// }

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

// ======================================================================
// ======================================================================
// ======================================================================

int redirect_input_output(t_cmd *cmd, int *pip) 
{
    if (cmd->infile >= 0) //si redirection d'entree de precisee ?
    {
        dup2(cmd->infile, STDIN_FILENO);
        close(cmd->infile);
    }
    if (cmd->outfile >= 0) 
    {
        dup2(cmd->outfile, STDOUT_FILENO); //si redirection de sortie de precisee ? + //! secu
        close(cmd->outfile);
    }
    else if (cmd->next != NULL) //si cmd n'est pas la derniere cmd 
        dup2(pip[1], STDOUT_FILENO);
    return (SUCCESS);
}

int child_process(t_data *data, t_cmd *cmd, int *pip) 
{
    char* path;
    char** env;

    if (cmd->infile >= 0)
        close(pip[0]); // Ferme le côté lecture du pipe inutilisé
    if (cmd->outfile < 0 && cmd->next != NULL)
        cmd->outfile = pip[1];
    if (is_builtin(cmd->cmd_param[0])) 
    {    
        launch_builtin(cmd);
        if (cmd->outfile >= 0) 
            close(cmd->outfile);
        if (cmd->infile >= 0) 
            close(cmd->infile);
        if (pip[1] >= 0) 
            close(pip[1]);
        if (pip[0] >= 0) 
            close(pip[0]);
        exit(0); // Utilise un code de sortie propre
    } 
    else 
    {
        redirect_input_output(cmd, pip);
        env = copy_envp_to_tab(data, data->envp);
        if (!env)
            return (ERROR); //FREE
        path = return_command_in_path(cmd->cmd_param[0]);
        execve(path, cmd->cmd_param, env);
        ft_free_tabtab(env);
        free(path);
    }
    return (SUCCESS);
}

int parent_process(int *pip, t_cmd *next_cmd) 
{
    close(pip[1]); // Ferme le côté écriture du pipe
    if (next_cmd)
        next_cmd->infile = pip[0]; // Passe le côté lecture du pipe à la prochaine commande
    else
        close(pip[0]); // Ferme le côté lecture si c'est la dernière commande
    return (SUCCESS);
}

int exec_cmd(t_data *data, t_cmd *cmd, int *pip) 
{
    cmd->f_pid = fork();
    if (cmd->f_pid == -1)
        return (ERROR);
    if (cmd->f_pid == 0) 
    {
        if (cmd && cmd->cmd_param[0])
            return (child_process(data, cmd, pip));
        else
            return (ERROR); //FREE
    } 
    else
        return (parent_process(pip, cmd->next));
}

int	wait_all(t_data *data)
{
    t_cmd   *cmd;
	int		status;
	int		pid;
    
    cmd = data->cmd;
    while (cmd)
    {
        if (data->pip[1] >= 0) 
            close(data->pip[1]);
        if (data->pip[0] >= 0) 
            close(data->pip[0]);
        if (cmd->outfile >= 0) 
            close(cmd->outfile);
        if (cmd->infile >= 0) 
            close(cmd->infile);
        pid = waitpid(0, &status, 0);
        if (pid == -1)
            return (ERROR);
        if (pid == data->cmd->f_pid) // verifie s'il s'agit du id de fork
        {
			if (WIFEXITED(status))
				data->exit_status = WEXITSTATUS(status);
        }
        cmd = cmd->next;
    }
    return (SUCCESS);
}

int close_all_fd(t_data* data)
{
    t_cmd   *cmd;
    
    cmd = data->cmd;
    while (cmd)
    {
        if (data->pip[1] >= 0) 
            close(data->pip[1]);
        if (data->pip[0] >= 0) 
            close(data->pip[0]);
        if (cmd->outfile >= 0) 
            close(cmd->outfile);
        if (cmd->infile >= 0) 
            close(cmd->infile);
        cmd = cmd->next;
    }
    return (SUCCESS);    
}

int exec(t_data *data) 
{    
    t_cmd *tmp;
    int *pip;

    init_cmd(data); //! belek return
    tmp = data->cmd;
    pip = data->pip;
    if (is_builtin(tmp->cmd_param[0]) && t_cmd_len(data->cmd) == 1)
        return (launch_builtin(tmp));
    while (tmp)
    {
        if (pipe(pip) == -1)
            return (ERROR); //FREE
        exec_cmd(data, tmp, pip);
        if (tmp->outfile >= 0) 
            close(tmp->outfile);
        if (tmp->infile >= 0) 
            close(tmp->infile);
        tmp = tmp->next;
    }
    wait_all(data);
    return (SUCCESS);
}

//* STDIN  == 0 
//* STDERR == 1
//* STDOUT == 2

//! ajouter gestion error_status dans wait_all
//! ajouter lauch_builtin dans exec_cmd
//! 

// WIFEXITED ==> verifie le status
// WEXITSTATUS ==> retourne l'exit_status 


//! secu dup2
