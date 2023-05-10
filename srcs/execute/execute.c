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
	int			i;
	int			status;
	extern int	g_status;

	i = 0;
	while (i < cnt)
	{
		waitpid(-1, &status, 0);
		g_status = WEXITSTATUS(status);
		if (WTERMSIG(status) == 2 && WIFSIGNALED(status))
		{
			ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
			ft_putstr_fd("\x1B[11D", STDOUT_FILENO);
			ft_putendl_fd("^C", STDOUT_FILENO);
		}
		if (WTERMSIG(status) == 3 && WIFSIGNALED(status))
		{
			ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
			ft_putstr_fd("\x1B[11D", STDOUT_FILENO);
			ft_putendl_fd("^\\Quit: 3", STDOUT_FILENO);
		}
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
	exec->stdin_ori = dup(STDIN_FILENO);
	exec->stdout_ori = dup(STDOUT_FILENO);
	check_cmdline(cmdline, env, exec);
	return (exec);
}

void	execute(t_cmdline *cmdline, t_env *env)
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
	dup2(exec->stdin_ori, STDIN_FILENO);
	dup2(exec->stdout_ori, STDOUT_FILENO);
}
