/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 23:31:21 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/07 23:31:21 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_signal(int status)
{
	if (WTERMSIG(status) == 2 && WIFSIGNALED(status))
	{
		g_status = 130;
		ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
		ft_putstr_fd("\x1B[11D", STDOUT_FILENO);
		ft_putendl_fd("^C", STDOUT_FILENO);
	}
	if (WTERMSIG(status) == 3 && WIFSIGNALED(status))
	{
		g_status = 131;
		ft_putstr_fd("\x1B[11D", STDOUT_FILENO);
		ft_putendl_fd("^\\Quit: 3", STDOUT_FILENO);
	}
}

void	sigint_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\x1B[11D", STDOUT_FILENO);
		exit(1);
	}
}

void	sigint_handler(int sig)
{
	extern int	g_status;

	if (sig == SIGINT)
	{
		g_status = 1;
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_ctrl_d(void)
{
	ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
	ft_putstr_fd("\033[11C", STDOUT_FILENO);
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(0);
}

void	init_signal(void)
{
	set_termios();
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_DFL);
}
