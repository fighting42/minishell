/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:06:34 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/15 13:07:45 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	fd_open(t_redirct *redirct)
{
	if (redirct->type == STDIN || redirct->type == HEREDOC)
		return (open(redirct->value, O_RDONLY));
	else if (redirct->type == STDOUT)
		return (open(redirct->value, O_RDWR | O_CREAT | O_TRUNC, 0644));
	else if (redirct->type == APPEND)
		return (open(redirct->value, O_RDWR | O_CREAT | O_APPEND, 0644));
	return (0);
}

void	do_redirct(t_redirct *redirct)
{
	int	fd;

	fd = fd_open(redirct);
	if (redirct->type == STDIN)
	{
		if (fd < 0)
			print_error(errmsg(TRUE, redirct->value, NULL, \
				"No such file or directory"), TRUE, 1);
		dup2(fd, STDIN_FILENO);
	}
	else if (redirct->type == HEREDOC)
		dup2(fd, STDIN_FILENO);
	else if (redirct->type == STDOUT || redirct->type == APPEND)
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redirct(t_exec *exec)
{
	t_redirct	*redirct;

	redirct = exec->pipeline->redirct;
	while (redirct)
	{
		do_redirct(redirct);
		redirct = redirct->next;
	}
}
