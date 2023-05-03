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

void	free_exec(t_execinfo *exec)
{
	t_redirct *tmp;

	free(exec->cmd);
	free(exec->path);
	tmp = exec->redirct;
	while (tmp)
	{
		free(exec->redirct);
		tmp = tmp->next;
	}
	free(exec);
}

char	*errmsg(int flag, char *cmd1, char *cmd2, char *msg)
{
	char	*tmp;

	tmp = NULL;
	if (flag)
		tmp = ft_strjoin(tmp, "minishell: ");
	if (cmd1)
		tmp = ft_strjoin(tmp, cmd1);
	if (cmd2)
		tmp = ft_strjoin(tmp, cmd2);
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
	int			i;
	int			last_flag;
	int			pipe_cnt;
	t_execinfo	*execinfo;

	while (cmdline)
	{
		i = 0;
		last_flag = 0;
		execinfo = init_execinfo(cmdline, env);
		if (!check_builtin(execinfo))
			return; // while문 안으로 들어가야 될듯
		pipe_cnt = execinfo->pipe_cnt;
		while (i < pipe_cnt + 1)
		{
			if (i == pipe_cnt)
				last_flag = 1;
			exec_pipe(execinfo, last_flag);
			free_exec(execinfo);
			execinfo = execinfo->next;
			i++;
		}
		wait_procs(pipe_cnt + 1);
		cmdline = cmdline->next;
	}
	i = 0;
	while (env->value[i])
		free(env->value[i++]);
	free(env->value);
}
