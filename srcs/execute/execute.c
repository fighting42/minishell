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
		free(tmp);
		tmp = pipeline->redirct->next;
	}
	return (next);
}

char	*errmsg(int flag, char *cmd1, char *cmd2, char *msg)
{
	char	*tmp;

	tmp = "";
	if (flag)
		tmp = ft_strjoin(tmp, "minishell: ");
	if (cmd1)
	{
		tmp = ft_strjoin(tmp, cmd1);
		tmp = ft_strjoin(tmp, ": ");
	}
	if (cmd2)
	{
		tmp = ft_strjoin(tmp, cmd2);
		tmp = ft_strjoin(tmp, ": ");
	}
	if (msg)
		tmp = ft_strjoin(tmp, msg);
	return (tmp);
}

void	print_error(char *errmsg, int flag, int status)
{
	ft_putendl_fd(errmsg, STDERR_FILENO);
	g_status = status;
	write(2, ft_itoa(g_status), 3); write(2, "\n", 1); // exit_status test !
	if (flag == EXIT_Y)
		exit(EXIT_FAILURE);
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

void	execute(t_cmdline *cmdline, t_env *env)
{
	int		i;
	int		last_flag;
	t_exec	*exec;

	int fd_in = dup(STDIN_FILENO);
	int fd_out = dup(STDOUT_FILENO);

	i = 0;
	last_flag = 0;
	if (cmdline->token->value == NULL)
		return ;
	exec = init_exec(cmdline, env);
	while (i < exec->pipe_cnt + 1)
	{
		if (!check_builtin(exec))
			break ;
		if (i == exec->pipe_cnt)
			last_flag = 1;
		exec_pipe(exec, last_flag);
		exec->pipeline = next_pipeline(exec->pipeline);
		i++;
	}
	wait_procs(exec->pipe_cnt + 1);
	free(exec);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
}
