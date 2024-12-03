#include "../../includes/minishell.h"


void ft_free_contents_nodes(t_data *data)
{
    t_cmd *cmd;

    if (!data)
        return ;
    if (data->pip[0] >= 0) 
        close(data->pip[0]);
    if (data->pip[1] >= 0) 
        close(data->pip[1] );
    cmd = data->cmd;
    while (cmd)
    {
        if (cmd->cmd_param)
            ft_free_multi_array(cmd->cmd_param);
        if (cmd->outfile >= 0) 
            close(cmd->outfile);
        if (cmd->infile >= 0) 
            close(cmd->infile);
        cmd->f_pid = 0;
        cmd = cmd->next;
    }
    cmd = NULL;
    printf("WATI-FREE-SUCCESS\n\n");
    // free les nodes (+ prev next) une par une en + ou deja fait ?
}

bool	print_error(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (true);
}

void escape_heredoc(char *limiter)
{
    print_error("warning: here-document delimited by end-of-file (wanted '");
    print_error(limiter);
    print_error("')\n");
}

//! cas prevu si ctrl-D ...mais ctrl-C ? 
bool heredoc_cpy(int fd, char *limiter)
{
    char *line;

    line = "";
    while (1)
    {
        line = readline("> ");
        if (!line)
            escape_heredoc(limiter);
        if (ft_strcmp(line, limiter) == 0) //if ctrl-D ==> rentre ici aussi
            break;
        ft_putstr_fd(line, fd);
        ft_putstr_fd("\n", fd);
        free(line);
    }
    free(line);
    close(fd);
    fd = open(".minishell.heredoc.tmp", O_RDONLY);
    if (fd == -1)
        return (false);
    return (true);
}

int heredoc(t_cmd *cmd, char *limiter)
{
    t_data* data = get_data();

    if (cmd->infile >= 0)
        close(cmd->infile);
    cmd->infile = open(".minishell.heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (cmd->infile == -1)
        return (ERROR); //? OKOK
    if (heredoc_cpy(cmd->infile, limiter) == false)
    {
        printf("UNLINK-FILE\n\n");
        unlink(".minishell.heredoc.tmp");
        ft_free_contents_nodes(data);
        return (FAILURE); //? OKOK
    }
    unlink(".minishell.heredoc.tmp");
    return (SUCCESS);
}

//! tmp