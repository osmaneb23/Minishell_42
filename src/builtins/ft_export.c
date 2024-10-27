#include "../includes/minishell.h"

//! doit trier dans l'ordre alphabetique (((CLC)))
void print_export(char *line)
{
    int i;
    
    i = 0;
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
}

#include <unistd.h>
int export_no_args()
{
    int i;
    t_data *data = get_data();
    t_env *tmp;

    i = 0;
    if (!data || !data->envp)
        return (ERROR);
    tmp = data->envp;
    while(tmp != NULL)
    {
        print_export(tmp->line);
        tmp = tmp->next;
    }
    return (SUCCESS);
}


//? =============
//? rajouter systeme de trie dans l'ordre alphabetique 
//? ATTENTION aux noms et caracteres invalides pour la creation de variables 

//export_no_args()
//? Boucler sur chaque lettre de l'alphabet pour print dans l'ordre demande

//export_with_args()
//==> creer une nouvelle variable
//? Rajouter une verif pour noms et caracteres invalides...
//? ... puis l'ajouter a la suite des variables d'environnement de envp grace a append_envp()

//==> exporter une variable deja existante
//? 

//! EXPORT ==> UNSET ==> CD (change PWD/OLDPWD)