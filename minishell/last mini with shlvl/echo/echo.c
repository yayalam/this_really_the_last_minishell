/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylambark <ylambark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 01:22:36 by ylambark          #+#    #+#             */
/*   Updated: 2022/12/01 01:22:37 by ylambark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_one_cmd *cmd, t_one_element *head, char **env)
{
	int	i;
	int	j;
	int	b;

	b = 0;
	i = check_echo_args(cmd->args);
	if (i <= 1)
		i = 1;
	else
		b = 1;
	while (cmd->args[i])
	{
		j = ft_strjoin_echo(&cmd,
				search_key_all_env(head, cmd->args[i], env), env, i);
		write(1, cmd->args[i], ft_strlen(cmd->args[i]));
		add_number_to(&i, j);
		if (cmd->args[i])
			write(1, " ", 1);
	}
	if (!b)
		write(1, "\n", 1);
	g_data.exit_status = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}
