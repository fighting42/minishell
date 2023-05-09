/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 01:50:13 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/09 01:50:13 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	extern int	g_status;

	ft_putendl_fd(errmsg, STDERR_FILENO);
	g_status = status;
	if (flag == TRUE)
		exit(status);
}
