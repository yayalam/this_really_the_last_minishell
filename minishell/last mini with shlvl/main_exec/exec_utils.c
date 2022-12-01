/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylambark <ylambark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 01:21:45 by ylambark          #+#    #+#             */
/*   Updated: 2022/12/01 01:21:46 by ylambark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	swap_fd_var(int *old_fd, int new_fd)
{
	*old_fd = new_fd;
}

void	fd_handler_builtin(t_one_cmd *my_cmd)
{
	if (my_cmd->fd.out != 1)
	{
		dup2(my_cmd->fd.out, 1);
		close(my_cmd->fd.out);
	}
	if (my_cmd->fd.in != 0)
	{
		dup2(my_cmd->fd.in, 0);
		close(my_cmd->fd.in);
	}
}

void	fd_handler_execve(t_one_cmd *my_cmd, int fd[2])
{
	if (my_cmd->fd.out != 1)
	{
		dup2(my_cmd->fd.out, 1);
		close(my_cmd->fd.out);
		if (fd[1] != 1)
			close(fd[1]);
	}
	if (my_cmd->fd.in != 0)
	{
		dup2(my_cmd->fd.in, 0);
		close(my_cmd->fd.in);
		if (fd[0] != 0)
			close(fd[0]);
	}
}

void	check_last_pid(int pid, int counter, int cmds_number)
{
	int	status;

	status = 0;
	if (counter == cmds_number)
	{
		waitpid(pid, &status, 0);
		if (!g_data.which)
			g_data.exit_status = WEXITSTATUS(status);
	}
}
