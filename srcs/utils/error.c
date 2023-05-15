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

	tmp = malloc(sizeof(char) * 1);
	tmp[0] = '\0';
	if (flag)
		tmp = ft_strjoin_free_front(tmp, "minishell: ");
	if (cmd1)
	{
		tmp = ft_strjoin_free_front(tmp, cmd1);
		tmp = ft_strjoin_free_front(tmp, ": ");
	}
	if (cmd2)
	{
		tmp = ft_strjoin_free_front(tmp, cmd2);
		tmp = ft_strjoin_free_front(tmp, ": ");
	}
	if (msg)
		tmp = ft_strjoin_free_front(tmp, msg);
	return (tmp);
}

void	*print_error(char *errmsg, int flag, int status)
{
	ft_putendl_fd(errmsg, STDERR_FILENO);
	g_status = status;
	free(errmsg);
	if (flag == TRUE)
		exit(status);
	return (NULL);
}

int	check_null(t_cmdline *cmdline)
{
	t_token	*tmp;

	tmp = cmdline->token;
	while (!tmp->value)
	{
		tmp = tmp->next;
		if (!tmp)
			return (1);
	}
	return (0);
}
