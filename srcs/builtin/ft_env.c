/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 16:12:21 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/03 17:38:16 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_execinfo *execinfo, int fd)
{
	int		i;
	char	**env;

	i = 0;
	env = execinfo->env->value;
	if (execinfo->cmd[1])
		print_error(errmsg(0, "env", execinfo->cmd[1], NO_FILE_ERR), EXIT_Y, 127);
	else
	{
		while (env[i])
			ft_putendl_fd(env[i++], fd);
	}
	return (0);
}
