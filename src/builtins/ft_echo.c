#include "../includes/minishell.h"

bool verif_echo_dollar(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == '$')
            return (true);
        i++;
    }
    return (false);
}

int print_until_dollar(char *line)
{
    int i;

    i = 0;
    while (line[i] && line[i] != '$')
    {
        printf("%c", line[i]);
        i++;
    }
    printf("\n");
}

// le cas ou $ est seul ==> print "$\n"
// le cas ou $ est en milieu de mot ==> on print tout jusqu'au $ puis '\n'
//! ne peux pas finir sans le parsing (single et double quotes)
int ft_echo(char *line)
{
    if (strcmp(line, "") == 0)
        printf("\n");
    if (strcmp(line, "$") == 0)
        printf("$\n");
    else
    {
        if (verif_echo_dollar(line))
            print_until_dollar(line);
        else 
            printf("%s\n", line);
    }
}



//? ==========================
//? gerer cas $
//? gerer -n