/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:32:44 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/13 18:15:46 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_env(t_env *env, char *value)
{
	int		i;
	char	**new_env;

	if (ft_strchr(value, '='))
	{
		if (update_env(env, value))
			return ;
	}
	else
	{
		if (check_env(env, value))
			return ;
	}
	new_env = init_add_env(env->value);
	i = 0;
	while (env->value[i])
		free(env->value[i++]);
	free(env->value);
	new_env[i] = ft_strdup(value);
	env->value = new_env;
}

int	update_env(t_env *env, char *value)
{
	int		i;
	char	**tmp;
	char	*tmp2;

	tmp = ft_split(value, '=');
	i = 0;
	while (env->value[i])
	{
		tmp2 = ft_strjoin(tmp[0], "=");
		if (!ft_strncmp(env->value[i], tmp2, ft_strlen(tmp2)) || \
			!ft_strncmp(env->value[i], tmp[0], ft_strlen(env->value[i])))
		{
			free(env->value[i]);
			env->value[i] = ft_strdup(value);
			free_split(tmp);
			free(tmp2);
			return (1);
		}
		free(tmp2);
		i++;
	}
	free_split(tmp);
	return (0);
}

int	check_env(t_env *env, char *value)
{
	int		i;
	char	**tmp;
	char	*name;

	i = 0;
	while (env->value[i])
	{
		tmp = ft_split(env->value[i], '=');
		name = ft_strdup(tmp[0]);
		if (!ft_strncmp(value, name, ft_strlen(name)) && \
			!ft_strncmp(value, name, ft_strlen(value)))
		{
			free_split(tmp);
			free(name);
			return (1);
		}
		i++;
		free_split(tmp);
		free(name);
	}
	return (0);
}

void	swap_env(char **env_tmp, int i, int j)
{
	char	*tmp;

	tmp = env_tmp[i];
	env_tmp[i] = env_tmp[j];
	env_tmp[j] = tmp;
}

char	**sort_env(char **env, int cnt)
{
	int		i;
	int		j;
	char	**env_tmp;

	env_tmp = malloc(sizeof(char *) * (cnt + 1));
	i = -1;
	while (env[++i])
		env_tmp[i] = env[i];
	env_tmp[cnt] = NULL;
	i = 0;
	while (i < cnt - 1)
	{
		j = i + 1;
		while (j < cnt)
		{
			if (ft_strncmp(env_tmp[i], env_tmp[j], ft_strlen(env_tmp[i])) > 0)
				swap_env(env_tmp, i, j);
			j++;
		}
		i++;
	}
	return (env_tmp);
}
