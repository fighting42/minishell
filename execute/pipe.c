/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:55:30 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/17 00:22:20 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirection(t_redirct *redirct)
{
	if (redirct)
	{
		while (redirct)
		{
			if (redirct->type == STDIN) // + heredoc, append 처리
			{
				int fd = open(redirct->value, O_RDONLY);
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
			else if (redirct->type == STDOUT)
			{
				int fd = open(redirct->value, O_RDWR | O_CREAT | O_TRUNC, 0644);
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
			redirct = redirct->next;
		}
	}
}

void	pipe_exec(t_execinfo *execinfo, int flag)
{
	int			fds[2];
	pid_t		pid;
	int			status;

	pipe(fds);
	pid = fork(); // fork 실패 error처리
	if (pid == 0)
	{
		close(fds[0]);
		if (!flag) // 마지막 cmd
			dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		redirection(execinfo->redirct);
		if (check_builtin(execinfo->cmd[0]))
		{
			printf("builtin\n");
			return ;
		}
		execinfo->path = find_path(execinfo->cmd, pars_envp(execinfo->envp));
		if (execve(execinfo->path, execinfo->cmd, execinfo->envp) == -1)
			printf("command not found\n");
	}
	else
	{
		waitpid(pid, &status, 0);
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
	}
}
