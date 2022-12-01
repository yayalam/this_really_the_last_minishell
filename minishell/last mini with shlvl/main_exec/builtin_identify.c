/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_identify.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylambark <ylambark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 01:21:41 by ylambark          #+#    #+#             */
/*   Updated: 2022/12/01 01:21:42 by ylambark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_buitlin(char *command)
{
	if (command && (ft_strcmp(command, "unset") == EQUAL))
		return (1);
	else if (command && (ft_strcmp(command, "echo") == EQUAL))
		return (1);
	else if (command && (ft_strcmp(command, "pwd") == EQUAL))
		return (1);
	else if (command && (ft_strcmp(command, "cd") == EQUAL))
		return (1);
	else if (command && (ft_strcmp(command, "env") == EQUAL))
		return (1);
	else if (command && (ft_strcmp(command, "exit") == EQUAL))
		return (1);
	else if (command && (ft_strcmp(command, "export") == EQUAL))
		return (1);
	return (0);
}

void	identify_builtin(t_one_cmd *command, char ***env, t_one_element *head)
{
	if (command->args[0] && (ft_strcmp(command->args[0], "unset") == EQUAL))
		ft_unset(command, env);
	else if (command->args[0] && (ft_strcmp(command->args[0], "echo") == EQUAL))
		ft_echo(command, head, *env);
	else if (command->args[0] && (ft_strcmp(command->args[0], "pwd") == EQUAL))
		ft_pwd();
	else if (command->args[0] && (ft_strcmp(command->args[0], "cd") == EQUAL))
		ft_cd(command, env);
	else if (command->args[0] && (ft_strcmp(command->args[0], "exit") == EQUAL))
		ft_exit(command, *env);
	else if (command->args[0] && (ft_strcmp(command->args[0], \
				"export") == EQUAL))
		ft_export(env, command, head);
	else if (command->args[0] && (ft_strcmp(command->args[0], "env") == EQUAL))
		ft_env(command, *env);
}
