/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 16:12:21 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/09 15:56:48 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_pipeline *pipeline, int fd)
{
	int		i;
	char	**env;

	i = 0;
	env = pipeline->env->value;
	if (pipeline->cmd[1])
		print_error(errmsg(0, "env", pipeline->cmd[1], "No such file or directory"), TRUE, 127);
	else
	{
		while (env[i])
			ft_putendl_fd(env[i++], fd);
	}
	return (0);
}
