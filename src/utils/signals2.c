/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:31:59 by obouayed          #+#    #+#             */
/*   Updated: 2025/01/04 17:59:55 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// AAHAHAHAHAHHAH machine 0 - 1 Fehim : Broken pipe detected
void	sigpipe_handler(int signo)
{
	t_data	*data;

	data = get_data();
	if (signo == SIGPIPE)
	{
		if (data->tmp_env)
			ft_free_multi_array(data->tmp_env);
		destroy_child_process(SUCCESS, NULL);
	}
}
