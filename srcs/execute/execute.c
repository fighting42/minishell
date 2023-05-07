/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:29:30 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/16 23:06:18 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_pipeline	*next_pipeline(t_pipeline *pipeline)
{
	t_pipeline	*next;
	t_redirct	*tmp;

	next = pipeline->next;
	if (pipeline->cmd)
		free(pipeline->cmd);
	if (pipeline->path)
		free(pipeline->path);
	tmp = pipeline->redirct;
	while (tmp)
	{
		tmp = pipeline->redirct->next;
		free(pipeline->redirct);
		pipeline->redirct = tmp;
	}
	return (next);
}

void	wait_procs(int cnt)
{
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	while (i < cnt)
	{
		pid = waitpid(-1, &status, 0);
		i++;
	}
}

t_exec	*init_exec(t_cmdline *cmdline, t_env *env)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	exec->pipeline = NULL;
	exec->pipe_cnt = 0;
	exec->heredoc_cnt = 0;
	check_cmdline(cmdline, env, exec);
	return (exec);
}

void	exec_pipeline(t_cmdline *cmdline, t_env *env)
{
	int		i;
	int		last_flag;
	t_exec	*exec;

	i = 0;
	last_flag = 0;
	exec = init_exec(cmdline, env);
	while (i < exec->pipe_cnt + 1)
	{
		if (!check_builtin(exec))
			break ;
		if (i == exec->pipe_cnt)
			last_flag = 1;
		exec_fork(exec, last_flag);
		exec->pipeline = next_pipeline(exec->pipeline);
		i++;
	}
	wait_procs(exec->pipe_cnt + 1);
	free(exec);
}

void	execute(t_cmdline *cmdline, t_env *env)
{
	int		fd_in;
	int		fd_out;

	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	exec_pipeline(cmdline, env);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
}
