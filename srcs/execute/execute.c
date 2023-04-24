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

void	print_error(char *err, char *cmd, char *msg, int status)
{
	if (!err)
		ft_putstr_fd("minishell: ", STDERR_FILENO);
	else
	{
		ft_putstr_fd(err, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	g_status = status;
	write(2, ft_itoa(g_status), 3); write(2, "\n", 1); // exit_status test !
	exit(EXIT_FAILURE);
}

void	execute(t_cmdline *cmdline, t_env *env)
{
	int			i;
	int			last_flag;
	int			pipe_cnt;
	t_execinfo	*execinfo;

	i = 0;
	last_flag = 0;
	execinfo = init_execinfo(cmdline, env);
	if (!check_builtin(execinfo))
		return ; // 수정필요
	pipe_cnt = execinfo->pipe_cnt;
	while (i < pipe_cnt + 1)
	{
		if (i == pipe_cnt)
			last_flag = 1;
		pipe_exec(execinfo, last_flag);
		execinfo = execinfo->next;
		i++;
	}
}
