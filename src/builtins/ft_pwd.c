#include "../../includes/minishell.h"

//+ exit status OKOK
//! with no options
bool	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX)) //! cherche direct dans l'env
	{
	    printf("%s\n", cwd);
	    return (0);
	}
	else
		return (print_error("Error: getcwd\n"), 1);
}
