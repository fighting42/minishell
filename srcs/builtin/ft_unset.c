/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:25:38 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/13 22:24:41 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_env_i(char **env, char *var)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin(var, "=");
	len = ft_strlen(var);
	while (env[i])
	{
		if (!ft_strncmp(env[i], tmp, len))
			break ;
		i++;
	}
	free(tmp);
	if (!env[i])
		return (-1);
	return (i);
}

void	del_env(t_env *env, char *var)
{
	int		i;

	i = get_env_i(env->value, var);
	if (i < 0)
		return ;
	free(env->value[i]);
	env->value[i] = env->value[i + 1];
	i++;
	while (env->value[i])
	{
		env->value[i] = env->value[i + 1];
		i++;
	}
	free(env->value[i]);
	env->value[i] = NULL;
}

int	ft_unset(t_pipeline *pipeline)
{
	int	i;

	i = 1;
	while (pipeline->cmd[i])
	{
		del_env(pipeline->env, pipeline->cmd[i]);
		i++;
	}
	return (0);
}
