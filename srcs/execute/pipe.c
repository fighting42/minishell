/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:55:30 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/21 18:12:21 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		redirection(execinfo);
		if (check_builtin(execinfo->cmd[0], execinfo))
			return ;
		execinfo->path = find_path(execinfo->cmd, pars_envp(execinfo->envp));
		g_exit_status = 0;
		if (execve(execinfo->path, execinfo->cmd, execinfo->envp) == -1)
			print_error(127, STDOUT_FILENO);
 	}
	else
	{
		waitpid(pid, &status, 0);
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
	}
}
