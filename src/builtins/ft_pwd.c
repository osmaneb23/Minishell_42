#include "../../includes/minishell.h"

//+ EXIT STATUS OKOK
//! with no options
bool	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX)) //! cherche direct dans l'env
	{
	    printf("%s\n", cwd);
	    return (SUCCESS);
	}
	else
		return (cleanup(1, "Error: getcwd\n", NO_EXIT, 2));
}
