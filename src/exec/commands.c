/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoet <apoet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:43:47 by obouayed          #+#    #+#             */
/*   Updated: 2024/11/21 16:54:10 by apoet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//*OKOK
bool	add_cmd_to_list(t_cmd *cmd, t_cmd *data_cmd)
{
	t_cmd	*last;

	last = last_command(data_cmd);
	if (!last)
		return (cleanup(ERROR, "Error: impossible to get last command\n", ERROR,
				2));
	last->next = cmd;
	cmd->prev = last;
	return (SUCCESS);
}

//*OKOK
//? Libère une liste chaînée de commandes
void free_cmds(t_cmd **cmd_list)
{
    t_cmd *current;
    t_cmd *next;
    int i;

    if (!cmd_list || !(*cmd_list))
        return;
    current = *cmd_list;
    while (current)
    {
        next = current->next;
        if (current->cmd_param)
        {
            i = 0;
            while (current->cmd_param[i])
            {
                free(current->cmd_param[i]);
                i++;
            }
            free(current->cmd_param);
        }
        free(current);
        current = next;
    }
    *cmd_list = NULL;
}

//*OKOK
//? Compte le nombre de commandes en vérifiant les pipes
int count_nbr_cmd(t_token *token)
{
    t_token *tmp;
    int i = 0;

    if (!token)
        return (FAILURE);
    tmp = token;
    while (tmp)
    {
        if (strcmp(tmp->value, "|") == 0 || tmp->type == PIPE)
            i++;
        tmp = tmp->next;
    }
    return (i + 1);
}

//*OKOK
//? Compte les paramètres de commande
int count_cmd_param(t_token *og_token)
{
    t_token *token = og_token;
    unsigned int i = 0;

    while (token && token->type != PIPE)
    {
        if (token->type >= 1 && token->type <= 4)
        {
            if (token->next && token->next->type == ARG)
                i--;
        }
        else
            i++;
        token = token->next;
    }
    return (i);
}

//! =======================================================================================

//*OKOK
//? Initialise un fichier pour une commande donnée
int init_file(t_cmd *cmd, char *filename, int type)
{
    if (!cmd || !filename)
        return (ERROR);
    if ((type == INPUT || type == HEREDOC) && cmd->infile > -2)
        close(cmd->infile);
    if ((type == TRUNC || type == APPEND) && cmd->outfile > -2)
        close(cmd->outfile);
    if (type == INPUT)
        cmd->infile = open(filename, O_RDONLY);
    else if (type == TRUNC)
        cmd->outfile = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    else if (type == APPEND)
        cmd->outfile = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (cmd->infile == -1 || cmd->outfile == -1)
    {
        perror("Error: File operation failed");
        return (ERROR);
    }
    return (SUCCESS);
}

//*OKOK
//? Initialise les paramètres de commande
char **init_cmd_param(t_token *og_token)
{
    char **cmd_param;
    int i;
    t_token *token;

    token = og_token;
    i = count_cmd_param(token);
    if (i == 0 || i == FAILURE)
        return (NULL);
    cmd_param = malloc(sizeof(char *) * (i + 1));
    if (!cmd_param)
    {
        perror("Error: malloc failed");
        return (NULL);
    }
    cmd_param[i] = NULL;
    i = 0;
    while (token && token->type != PIPE)
    {
        if (token->type >= 1 && token->type <= 4)
        {
            if (token->next && token->next->type == ARG)
                token = token->next->next;
			else
                return (NULL);
        }
        else
        {
            cmd_param[i] = ft_strdup(token->value);
            if (!cmd_param[i])
            {
                perror("Error: malloc failed"); //FREE 
                return (NULL);
            }
            i++;
            token = token->next;
        }
    }
    return (cmd_param);
}

//*OKOK
//? Remplit les nœuds de commandes avec des données
int fill_cmd_nodes(t_data *data)
{
    t_cmd *cmd;
    t_token *token;

    token = data->token;
    cmd = data->cmd;
    while (token && cmd)
    {
        if ((token->type >= 1 && token->type <= 4) && token->next && token->next->type == ARG)
        {
            if (access(token->next->value, F_OK) == 0)
            {
                init_file(cmd, token->next->value, token->type);
                if (token->next->next) //! MON PRECIEUX
                    token = token->next->next;
                if (!cmd->prev && token->type == ARG && (check_command_in_path(token->value) == SUCCESS || is_builtin(token->value) == true))
                    token->type = CMD;
            }
            else
                return (ERROR);
        }
        if (token && token->type == PIPE)
            cmd = cmd->next;
        if (token && token->type == CMD)
        {
			cmd->cmd_param = init_cmd_param(token);
			if (!cmd->cmd_param)
				return (ERROR); //besoin de free les precedents noeud si deja init
        }
    	token = token->next;
    }
    return (SUCCESS);
}

//*OKOK
//? Initialise les nœuds de commandes
int init_cmd_nodes(t_data *data)
{
    t_cmd *cmd;
    t_token *token;
    int nbr_cmd;

    if (!data || !data->token)
        return (ERROR);
    token = data->token;
    nbr_cmd = count_nbr_cmd(token);
    if (nbr_cmd <= 0)
        return (ERROR);
    while (nbr_cmd > 0)
    {
        cmd = malloc(sizeof(t_cmd));
        if (!cmd)
        {
            perror("Error: malloc failed");
            free_cmds(&data->cmd);
            return (ERROR);
        }
        cmd->infile = -2;
        cmd->outfile = -2;
        cmd->cmd_param = NULL;
        cmd->next = NULL;
        cmd->prev = NULL; 
        if (!data->cmd)
            data->cmd = cmd;
        else
            add_cmd_to_list(cmd, data->cmd);
        nbr_cmd--;
    }
    return (SUCCESS);
}

int init_cmd(t_data *data)
{
    if (!data || !data->token)
        return (ERROR);
    if (init_cmd_nodes(data) == ERROR)
        return (ERROR);
    if (fill_cmd_nodes(data) == ERROR)
        return (ERROR);




// t_cmd * tmp = data->cmd;
// printf("\n\n1=%s\n", tmp->cmd_param[0]);
// printf("1=%s\n", tmp->cmd_param[1]);
// printf("1=%s\n\n", tmp->cmd_param[2]);
// tmp = tmp->next;
// printf("2=%s\n", tmp->cmd_param[0]);
// printf("2=%s\n", tmp->cmd_param[1]);
// printf("2=%s\n\n", tmp->cmd_param[2]);
// tmp = tmp->next;
// printf("3=%s\n", tmp->cmd_param[0]);
// printf("3=%s\n", tmp->cmd_param[1]);
// printf("3=%s\n", tmp->cmd_param[2]);

    // free_cmds(&data->cmd);
    
	return (SUCCESS);
}


//! Trier et normer ce fichier de golmon
	//? mettre les initalisation de cmd et token dans init_cmd plutot que dans fill_cmd_nodes()
//! Ajouter gestion des redirections pour les builtins...
//! ...rajouter les builtins dans pipex
//! Implementer gestion HEREDOC

    //! fd pas close par outfile dans init

//! Ne pas oublier les cas "cd -" + unset PWD



//* FN_FREE
//* free : cmd->cmd->param
//* free : la liste t_cmd
//* ((+ close fd apres exec))