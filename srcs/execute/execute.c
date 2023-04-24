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

void	print_error(char *cmd, int status, int fd)
{
	ft_putstr_fd("minishell: ", fd);
	if (cmd)
	{
		ft_putstr_fd(cmd, fd);
		ft_putstr_fd(": ", fd);
	}
	if (status == 127)
		ft_putendl_fd("command not found", fd);
	else if (status == 2)
		ft_putendl_fd("maximum here-document count exceeded", fd); // heredoc error
	else
		ft_putstr_fd(strerror(errno), fd);
	g_exit_status = status;
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
	if (check_builtin(execinfo))
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
