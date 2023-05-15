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
	free(pipeline->cmd);
	if (pipeline->path)
		free(pipeline->path);
	tmp = pipeline->redirct;
	while (tmp)
	{
		tmp = pipeline->redirct->next;
		if (pipeline->redirct->type == HEREDOC)
			free(pipeline->redirct->value);
		free(pipeline->redirct);
		pipeline->redirct = tmp;
	}
	free(pipeline);
	return (next);
}

void	wait_procs(int cnt)
{
	int			i;
	int			status;

	i = 0;
	while (i < cnt)
	{
		waitpid(-1, &status, 0);
		if (g_status == 0)
			g_status = WEXITSTATUS(status);
		print_signal(status);
		i++;
	}
}

t_exec	*init_exec(t_cmdline *cmdline, t_env *env)
{
	t_exec		*exec;

	g_status = 0;
	exec = malloc(sizeof(t_exec));
	exec->pipeline = NULL;
	exec->pipe_cnt = 0;
	exec->heredoc_cnt = 0;
	exec->stdin_ori = dup(STDIN_FILENO);
	exec->stdout_ori = dup(STDOUT_FILENO);
	check_cmdline(cmdline, env, exec);
	return (exec);
}

void	execute_end(t_exec *exec)
{
	unlink_heredoc();
	dup2(exec->stdin_ori, STDIN_FILENO);
	dup2(exec->stdout_ori, STDOUT_FILENO);
	close(exec->stdin_ori);
	close(exec->stdout_ori);
	if (exec->pipeline)
		next_pipeline(exec->pipeline);
	free(exec);
}

void	execute(t_cmdline *cmdline, t_env *env)
{
	int		i;
	int		last_flag;
	t_exec	*exec;

	if (check_null(cmdline))
		return ;
	i = -1;
	last_flag = 0;
	exec = init_exec(cmdline, env);
	if (exec->heredoc_cnt > 16)
		print_error(errmsg(TRUE, NULL, NULL, \
			"maximum here-document count exceeded"), TRUE, 2);
	while (++i < exec->pipe_cnt + 1)
	{
		if (!check_builtin(exec))
			break ;
		if (i == exec->pipe_cnt)
			last_flag = 1;
		if (check_heredoc(exec))
			break ;
		exec_fork(exec, last_flag);
		exec->pipeline = next_pipeline(exec->pipeline);
	}
	wait_procs(exec->pipe_cnt + 1);
	execute_end(exec);
}
