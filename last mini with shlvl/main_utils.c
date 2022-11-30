#include "minishell.h"

void assign_SHLVL(char ***env)
{
	t_env_one_element	*tmp;

	g_data.ev = create_all_env_struct(*env);
	g_data.shlvl = ft_atoi(search_element_struct_env(g_data.ev,"SHLVL")->value) + 1;
	tmp = search_element_struct_env(g_data.ev,"SHLVL");
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

void run_new_minishell(char ***env)
{
	t_env_one_element	*tmp;
	
	tmp = NULL;
	tmp = search_element_struct_env(g_data.ev,"SHLVL");
	tmp->value = ft_itoa(g_data.shlvl);
	*env = from_struct_to_array(g_data.ev);
}

int	readline_luncher(char **rd_line,char ***env)
{
	*rd_line = readline(RED"Our " RESET GREEN "MiNiSh3ll " RESET RED "<< <-*.*-> >> : " RESET);
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
		if (readline_luncher(&rd_line,&env))
			continue ;
		g_data.lex = lexer(rd_line);
		if (!check_err_syntax(g_data.lex))
		{
			if (my_parser(&g_data.tree, g_data.lex->head, g_data.ev)
				== EXIT_FAILURE)
				continue ;
			main_execute(g_data.tree->root, &env, counter_number_of_cmds(g_data.tree->root),
				g_data.lex->head);
			parse_lex_free(g_data.lex, g_data.tree);
			ft_wait();
		}
		else
			lexer_free(g_data.lex);
		free_all_srtuct_env(g_data.ev);
	}
}
