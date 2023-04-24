/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:25:38 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/24 19:31:28 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(t_execinfo *execinfo)
{
	int	i;
	char *cmd;
	char **env;

	i = 0;

	cmd = ft_strjoin(execinfo->cmd[1], "=");
	env = execinfo->env->value;
	while (env[i])
	{
		if (!ft_strncmp(env[i], cmd, ft_strlen(cmd)))
			break ;
		i++;
	}
	if (!env[i])
		return (1); // error
	free(cmd);
	while (env[i + 1])
	{
		env[i] = env[i + 1];
		i++;
	}
	env[i] = NULL;
	free(env[i]);
	return (0);
}