/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylambark <ylambark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 01:21:19 by ylambark          #+#    #+#             */
/*   Updated: 2022/12/01 01:21:20 by ylambark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_SHLVL(char ***env)
{
	t_env_one_element	*tmp;

	g_data.ev = create_all_env_struct(*env);
	g_data.shlvl = ft_atoi(search_element_struct_env \
		(g_data.ev, "SHLVL")->value) + 1;
	tmp = search_element_struct_env(g_data.ev, "SHLVL");
	tmp->value = ft_itoa(g_data.shlvl);
	*env = from_struct_to_array(g_data.ev);
}

void	assign_global_data(char **env)
{
	g_data.env = env;
	g_data.ev = create_all_env_struct(env);
	g_data.tree = init_tree(g_data.tree);
	g_data.shell_state = READING;
}

void	run_new_minishell(char ***env)
{
	t_env_one_element	*tmp;

	tmp = NULL;
	tmp = search_element_struct_env(g_data.ev, "SHLVL");
	tmp->value = ft_itoa(g_data.shlvl);
	*env = from_struct_to_array(g_data.ev);
}

int	readline_luncher(char **rd_line, char ***env)
{
	*rd_line = readline(RED"Our " RESET GREEN "MiNiSh3ll " \
		RESET RED "<< <-*.*-> >> : " RESET);
	g_data.shell_state = EXECUTING;
	if (!*rd_line)
	{
		printf("exit\n");
		exit(1);
	}
	if (ft_strcmp(*rd_line, "") == EQUAL || ft_strisspace(*rd_line))
		return (1);
	if (ft_strncmp(*rd_line, "./minishell", 12) == 0)
		run_new_minishell(env);
	if (strlen(*rd_line) > 0)
		add_history(*rd_line);
	return (0);
}
