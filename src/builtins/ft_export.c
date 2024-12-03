#include "../../includes/minishell.h"

//? utils_export.c

void ft_free_var_and_val(char **var, char **val)
{
    free(var);
    free(val);
}

int search_egal_symbol(char *cmd_param)
{
    int i;

    i = 0;
    while (cmd_param[i])
    {
        if (cmd_param[i] == '=')
            return (i);
        i++;
    }
    return (-1);
}

char *return_var(char *var_and_val, int limit)
{
    char *var;
    int start;

    start = 0;
    var = (char *)malloc(sizeof(char) * (limit + 1));
    if (!var)
        return (NULL);
    while (start < limit)
    {
        var[start] = var_and_val[start];
        start++;
    }
    var[start] = '\0';
    return(var);
}

char *return_val(char *var_and_val, int start)
{
    char *val;
    int limit;
    int i;

    i = 0;
    limit = ft_strlen(var_and_val);
    val = (char *)malloc(sizeof(char) * (limit - start));
    if (!val)
        return(NULL);
    start++;
    while (start < limit)
    {
        val[i] = var_and_val[start];
        start++;
        i++;
    }
    val[i] = '\0';
    return(val);
}

// ======================================================================================

//? ft_export.c

//?OKOK
//+ Affiche les variables exportes avec 
//+ la bonne syntaxe
int print_export_line(char *line)
{
    int i;
    
    i = 0;
    if (!line)
        return (ERROR);
    printf("export ");
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
int export_new_var_and_val(t_env *envp, char *var_and_val, int i)
{
    char *to_print;
    char *var;
    char *val;

    var = return_var(var_and_val, i);
    val = return_val(var_and_val, i);
    ft_free_var_and_val(&var, &val);
    if (verif_var_char(var) == FAILURE)
    {
        printf("Error: export: %s: not a valid identifier\n", var_and_val);
        return (ft_free_var_and_val(&var, &val), FAILURE);
    }
    if (remplace_if_already_exist(var, val) == SUCCESS)
        return(ft_free_var_and_val(&var, &val), SUCCESS);
    if (ft_strcmp(val, "") == 0) 
    {
        to_print = join_var_and_val(var, "");
        return (append_node_envp(&envp, to_print));
    }
    to_print = join_var_and_val(var, val);
    append_node_envp(&envp, to_print);
    return (ft_free_var_and_val(&var, &val), SUCCESS);
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
    ft_free_multi_array(tab_envp);
    return (SUCCESS);
}

//?OKOK 
int ft_export(char **cmd_param)
{
    int i;
    int j;
    t_data *data = get_data();

    i = 0;
    j = 1;
    if (!data->envp || !cmd_param)
        return (ERROR);
    if (ft_strcmp(cmd_param[0], "export") == 0 && tabtablen(cmd_param) == 1)
        return (export_just_display(data), SUCCESS);
    while (cmd_param[j])
    {
        i = search_egal_symbol(cmd_param[j]);
        if (i >= 0)
            export_new_var_and_val(data->envp, cmd_param[j], i);
        if (i == -1)
        {
            printf("TESTEUUUUUUUUH\n\n");
            export_just_new_var(data->envp, cmd_param[j]);
        }
        else //! si res == 0 | uile ???
            return (ERROR); //!
        j++;
    }
    return (FAILURE);
}

//* cas msg d'erreur "VAR=val"
//* cas "VAR1=ehbfnwekfj=weofhjwefjkn=wefouih"
//* cas "VAR1=val1 VAR2=val2"
//* cas avec "VAR1="
