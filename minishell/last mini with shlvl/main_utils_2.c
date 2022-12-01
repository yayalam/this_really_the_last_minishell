/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylambark <ylambark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 01:21:16 by ylambark          #+#    #+#             */
/*   Updated: 2022/12/01 01:21:17 by ylambark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait(void)
{
	int	ex_stat;

	ex_stat = 0;
	while (1)
	{
		g_data.pid = waitpid(-1, &ex_stat, 0);
		if (g_data.pid == -1 && errno == EINTR)
			continue ;
		if (g_data.pid == -1)
			break ;
	}
	if (WIFSIGNALED(ex_stat))
	{
		g_data.exit_status = WTERMSIG(ex_stat) + 128;
		if (WTERMSIG(ex_stat) == SIGINT)
			write(1, "\n", 1);
	}
	g_data.which = 0;
}

void	mini_shell_executor(char **env)
{
	char	*rd_line;

	rd_line = NULL;
	assign_SHLVL(&env);
	while (1)
	{
		assign_global_data(env);
		if (readline_luncher(&rd_line, &env))
			continue ;
		g_data.lex = lexer(rd_line);
		if (!check_err_syntax(g_data.lex))
		{
			if (my_parser(&g_data.tree, g_data.lex->head, g_data.ev)
				== EXIT_FAILURE)
				continue ;
			main_execute (g_data.tree->root, &env, counter_number_of_cmds \
			(g_data.tree->root), g_data.lex->head);
			parse_lex_free(g_data.lex, g_data.tree);
			ft_wait();
		}
		else
			lexer_free(g_data.lex);
		free_all_srtuct_env(g_data.ev);
	}
}
