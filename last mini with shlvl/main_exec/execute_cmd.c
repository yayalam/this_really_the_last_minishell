#include "../minishell.h"

void	builtin_ex(t_one_cmd *my_cmd, char ***env, t_one_element *head)
{
	int	in;
	int	out;

	out = dup(1);
	in = dup(0);
	if (my_cmd->redir && my_cmd->redir->head)
		redir_ex(my_cmd->redir, &my_cmd->fd);
	if (my_cmd->fd.in == -1)
	{
		g_data.exit_status = 1;
		g_data.which = 1;
		return ;
	}
	fd_handler_builtin(my_cmd);
	identify_builtin(my_cmd, env, head);
	dup2(in, 0);
	dup2(out, 1);
	g_data.which = 1;
}

int	cmd_executor(t_one_cmd *my_cmd, char **env, int fd[2])
{
	char	*cmd_path;
	int		pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		if (my_cmd->redir && my_cmd->redir->head)
		{
			redir_ex(my_cmd->redir, &my_cmd->fd);
			if (my_cmd->fd.in == -1)
				exit(1);
		}
		fd_handler_execve(my_cmd, fd);
		cmd_path = get_cmd(my_cmd->args[0], env);
		if (cmd_path)
			execve(cmd_path, my_cmd->args, env);
	}
	if (my_cmd->fd.in != 0)
		close(my_cmd->fd.in);
	if (my_cmd->fd.out != 1)
		close(my_cmd->fd.out);
	return (pid);
}
