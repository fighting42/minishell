/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 21:26:21 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/24 23:42:01 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env(char **env, char *var)
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
		return (NULL);
	free(var);
	return (env[i] + len);
}

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

void	set_env(char **env, char *var, char *value)
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
	// OLDPWD 없을때도 있나 ?
	if (!env[i])
		return ;
	free(var);
	// free(env[i]);
	env[i] = ft_strjoin(var, value);
}

void	add_env(t_execinfo *execinfo, int cnt)
{
	int		size;
	int		i;
	int		j;
	char	**new_env;

	size = 0;
	while (execinfo->env->value[size])
		size++;
	new_env = malloc(sizeof(char *) * (size + cnt + 1));
	i = 0;
	while (i < size)
	{
		new_env[i] = ft_strdup(execinfo->env->value[i]);
		free(execinfo->env->value[i]);
		i++;
	}
	j = 1;
	i--;
	while (++i < size + cnt)
	{
		if (!ft_strchr(execinfo->cmd[j], '='))
			continue ;
		new_env[i] = execinfo->cmd[j];
		j++;
	}
	new_env[i] = NULL;
	free(execinfo->env->value);
	execinfo->env->value = new_env;
}

void	del_env(t_execinfo *execinfo, int cnt)
{
	int	i;
	int	j;
	char **env;

	env = execinfo->env->value;
	j = 0;
	while (++j < cnt + 1)
	{
		i = get_env_i(env, execinfo->cmd[j]);
		if (i < 0)
			continue ;
		while (env[i + 1])
		{
			env[i] = env[i + 1];
			i++;
		}
		env[i] = NULL;
		free(env[i]);
	}
}