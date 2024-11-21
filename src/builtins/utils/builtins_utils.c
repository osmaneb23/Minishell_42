#include "../../../includes/minishell.h"

//?OKOK
//+ Permet de free un char**
void	ft_free_tabtab(char **tabtab)
{
	int	i;

	i = 0;
	while (tabtab[i])
    {
		free(tabtab[i]);
        i++;
    }
    free(tabtab);
	tabtab = NULL;
}

//?OKOK
//+ Permet de compter les lignes d'un char**
int tabtablen(char **s)
{
    int i;

    i = 0;
    while (s[i] != NULL)
        i++;
    return (i);
}

//?OKOK
//+ Permet de joindre une VAR, un '=' ainsi qu'une VAL
//+ Retourne le resultat
char	*join_var_and_val(char const *s1, char const *s2)
{
	char	*str;
	int		i, j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 2); //? 1 pour '=' 1 pour '\0'
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
    str[i] = '=';
    i++;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = 0;
	return (str);
}

//?OKOK
//+ Permet de compter le nombre de noeud dans la liste env
int count_envp_nodes(t_env *envp)
{
    t_env *tmp;
    int i;

    i = 0;
    if (!envp || !envp->next)
        return (FAILURE);
    tmp = envp;
    while(tmp != NULL)
    {
        i++;
        tmp = tmp->next;
    }
    return (i);
}