#include "../../includes/minishell.h"

//?OKOK
//+ Affiche les variables exportes avec 
//+ la bonne syntaxe
int print_export_line(char *line)
{
    int i;
    
    i = 0;
    if (!line)
        return (ERROR);
    printf("declare -x ");
    while (line[i] != '=')
    {
        printf("%c", line[i]);
        i++;
    }
    printf("=");
    i++;
    printf("\"");
    while (line[i])
    {
        printf("%c", line[i]);
        i++;
    }
    printf("\"");
    printf("\n");
    return (SUCCESS);
}

//?OKOK
//+ Permet d'exporter une nouvelle variable seule
//+ ">export VAR" 
int export_just_new_var(t_env *envp, char *var)
{
    char *to_print;
    t_env *tmp;
    int len;

    tmp = envp;
    len = ft_strlen(var);
    while(tmp != NULL)
    {
        if (ft_strncmp(var, tmp->line, len) == 0)
            return (SUCCESS);
        tmp = tmp->next;
    }
    if (verif_var_char(var) == FAILURE)
    {
        printf("Error: export: %s: not a valid identifier\n", var);
        return (FAILURE);
    }
    to_print = ft_strdup(var);
    append_node_envp(&envp, to_print);
    return (SUCCESS);
}

//?OKOK
//+ Permet d'exporter une nouvelle variable et sa valeur
//+ ">export VAR=VAL" 
int export_new_var_and_val(t_env *envp, char *var_and_val)
{
    char *to_print;
    char **res;

    res = ft_split(var_and_val, '=');
    if (!res)
        return (ERROR);
    if (remplace_if_already_exist(res[0], res[1]) == SUCCESS)
    {
        ft_free_tabtab(res);
        return(SUCCESS);
    }
    if (verif_var_char(res[0]) == FAILURE)
    {
        printf("Error: export: %s: not a valid identifier\n", res[0]);
        ft_free_tabtab(res);
        return (FAILURE);
    }
    to_print = join_var_and_val(res[0], res[1]);
    append_node_envp(&envp, to_print);
    ft_free_tabtab(res);
    return (SUCCESS);
}

//?OKOK
//+ Permet d'afficher les variables exportes
//+ ">export" 
int export_just_display(t_data *data)
{
    int count;
    char **tab_envp;

    count = count_envp_nodes(data->envp);
    tab_envp = copy_envp_to_tab(data, data->envp);
    sort_envp_and_print(tab_envp, count);
    ft_free_tabtab(tab_envp);
    return (SUCCESS);
}

//?OKOK 
int ft_export(char **cmd_param)
{
    int i;
    t_data *data = get_data();

    i = 0;
    if (!data->envp || !cmd_param)
        return (ERROR);
    if (ft_strcmp(cmd_param[0], "export") == 0 && tabtablen(cmd_param) == 1)
    {
        export_just_display(data);
        return (SUCCESS);
    }
    while (cmd_param[1][i])
    {
        if (cmd_param[1][i] == '=')
        {
            if (export_new_var_and_val(data->envp, cmd_param[1]) == SUCCESS) //? +cas ou VAR existe deja
                return (SUCCESS);
            else
                return (FAILURE);
        }
        i++;
    }
    if (export_just_new_var(data->envp, cmd_param[1]) == SUCCESS)
        return (SUCCESS);
    return (FAILURE);
}
