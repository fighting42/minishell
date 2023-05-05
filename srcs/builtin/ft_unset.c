/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:25:38 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/05 22:20:23 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_env_i(char **env, char *var)
{
	int	i;
	int	len;

	i = 0;
	var = ft_strjoin(var, "=");
	len = ft_strlen(var);
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, len))
			break ;
		i++;
	}
	if (!env[i])
		return (-1);
	free(var);
	return (i);
}

void	del_env(t_env *env, char *var)
{
	int	i;

	i = get_env_i(env->value, var);
	while (env->value[i + 1])
	{
		env->value[i] = env->value[i + 1];
		i++;
	}
	env->value[i] = NULL;
	free(env->value[i]);
}

int	ft_unset(t_execinfo *execinfo)
{
	int	i;
	int	j;

	i = 1;
	while (execinfo->cmd[i])
	{
		j = 0;
		while (execinfo->cmd[i][j])
		{
			if (!(ft_isalnum(execinfo->cmd[i][j])))
				print_error(errmsg(1, "unset", error_cmd(execinfo->cmd[i]), NOT_VALID_ERR), EXIT_Y, 1);
			j++;
		}
		del_env(execinfo->env, execinfo->cmd[i]);
		i++;
	}
	return (0);
}
