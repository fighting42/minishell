/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:55:30 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/16 22:54:18 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_exec(t_cmdinfo *cmdinfo)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		printf("fork error\n");
	else if (pid == 0)
	{
		if (check_builtin(cmdinfo->cmd[0]))
		{
			printf("builtin\n");
			return ;
		}
		cmdinfo->path = find_path(cmdinfo->cmd, pars_envp(cmdinfo->envp));
		if (execve(cmdinfo->path, cmdinfo->cmd, cmdinfo->envp) == -1)
			printf("command not found\n");
	}
	else
		waitpid(pid, &status, 0); // 마지막인자 0 ?
}

void	pipe_exec(t_cmdinfo *cmdinfo)
{
	int			fds[2];
	pid_t		pid;
	int			status;
	// t_redirct	*redirct;

	pipe(fds);
	pid = fork(); // fork 실패 error처리
	if (pid == 0)
	{
		printf("자식 %s\n", cmdinfo->cmd[0]);
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		// redirct = cmdinfo->redirct;
		// if (redirct)
		// {
		// 	while (redirct)
		// 	{
		// 		if (redirct->type == STDIN) // + heredoc, append 처리
		// 		{
		// 			int fd = open(redirct->value, O_RDONLY);
		// 			dup2(fd, STDIN_FILENO);
		// 			close(fd);
		// 		}
		// 		else if (redirct->type == STDOUT)
		// 		{
		// 			int fd = open(redirct->value, O_RDWR | O_CREAT | O_TRUNC, 0644);
		// 			dup2(fd, STDOUT_FILENO);
		// 			close(fd);
		// 		}
		// 		redirct = redirct->next;
		// 	}
		// }
		if (check_builtin(cmdinfo->cmd[0]))
		{
			printf("builtin\n");
			return ;
		}
		cmdinfo->path = find_path(cmdinfo->cmd, pars_envp(cmdinfo->envp));
		if (execve(cmdinfo->path, cmdinfo->cmd, cmdinfo->envp) == -1)
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