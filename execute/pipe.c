/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:55:30 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/15 22:00:07 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_exec(t_cmdinfo *cmdinfo, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		printf("fork error\n");
	else if (pid == 0)
	{
		if (execve(cmdinfo->path, cmdinfo->cmd, envp) == -1)
			printf("command not found\n");
	}
	else
		waitpid(pid, &status, 0);
}