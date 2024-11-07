#include "../../../includes/minishell.h"

//?OKOK
//+ Permet de verifier les caractères valides d'une VAR d'envp
int verif_var_char(char *var)
{
    int i;
    int j;
    char invalide_char[26] = "!@#$%^&*()+=,.:/?<>{}[]|-"; // OKOK

    i = 0;
    j = 0;  
    if (!var)
        return (ERROR);
    if (isdigit(var[0]))
        return (FAILURE);
    while (var[j])
    {
        while (invalide_char[i])
        {
            if (var[j] == invalide_char[i])
                return (FAILURE);
            i++;
        }
        i = 0;
        j++;
    }
    return (SUCCESS);
}

//?OKOK
//+ Permet de remplacer la valeur existante de VAR par VAL
int remplace_if_already_exist(char *var, char* val)
{
    char *to_print;
    t_data *data = get_data();
    t_env *tmp;
    int len;

    if (!data || !data->envp || !var || !val)
        return (ERROR);
    tmp = data->envp;
    len = ft_strlen(var);
    while(tmp != NULL)
    {
        if (ft_strncmp(var, tmp->line, len) == 0)
        {
            to_print = join_var_and_val(var, val);    
            tmp->line = to_print;
            return (SUCCESS);
        }
        tmp = tmp->next;
    }
    return (ERROR);
}

//+ Permet de trier un char**
int envp_tab_bubble_sort(char **envp, int count)
{
    char *temp;
    int i;

    i = 0;
    if (!envp || !*envp || count <= 0)
        return (ERROR);
    while (i < count - 1)
    {
        if (ft_strcmp(envp[i], envp[i + 1]) > 0)
        {
            temp = envp[i];
            envp[i] = envp[i + 1];
            envp[i + 1] = temp;
            i = 0;
        }
        else 
            i++;
    }
    return (SUCCESS);
}

//?OKOK
//+ Permet de trier un tabtab contenant env et de l'afficher 
int sort_envp_and_print(char **envp, int count)
{
    int i;

    i = 0;
    if (!envp || !*envp || count <= 0)
        return (ERROR);
    envp_tab_bubble_sort(envp, count);
    while (envp[i])
    {
        if (ft_strchr(envp[i], '='))
            print_export_line(envp[i]);
        else 
            printf("declare -x %s\n", envp[i]);
        i++;
    }
    return (SUCCESS);
}

//?OKOK
//+ Permet de convertir la liste env en tabtab et de la retourner
char **copy_envp_to_tab(t_data *data, t_env *envp)
{
    int i;
    t_env *tmp;
    char **env_tab;
    int count;
    
    i = 0;
    tmp = envp;
    count = count_envp_nodes(data->envp);
    env_tab = malloc((count + 1) * sizeof(char *));
    if (!env_tab || count == FAILURE)
        return (NULL);
    while (i < count)
    {
        env_tab[i] = strdup(tmp->line);
        if (!env_tab[i])
        {
            ft_free_tabtab(env_tab);
            return (NULL);
        }
        tmp = tmp->next;
        i++;
    }
    env_tab[count] = NULL; 
    return (env_tab);
}
