/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:06:54 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/11 05:39:33 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**init_add_env(char **env)
{
	int		i;
	char	**tmp;

	i = 0;
	while (env[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (env[++i])
		tmp[i] = ft_strdup(env[i]);
	tmp[i++] = NULL;
	tmp[i] = NULL;
	return (tmp);
}

void	add_env(t_env *env, char *value)
{
	int		i;
	char	**ret;
	char	**new_env;

	if (ft_strchr(value, '='))
	{
		ret = ft_split(value, '=');
		i = 0;
		while (env->value[i])
		{
			if (!ft_strncmp(env->value[i], ft_strjoin(ret[0], "="), ft_strlen(ret[0]) + 1) || \
				!ft_strncmp(env->value[i], ret[0], ft_strlen(env->value[i])))
			{
				env->value[i] = value;
				return ;
			}
			i++;
		}
	}
	i = 0;
	while (env->value[i])
	{
		if (!ft_strncmp(value, env->value[i], ft_strlen(value)) && \
			!ft_strncmp(value, env->value[i], ft_strlen(env->value[i])))
				return ;
		i++;
	}
	new_env = init_add_env(env->value);
	i = 0;
	while (new_env[i])
		free(env->value[i++]);
	new_env[i] = ft_strdup(value);
	free(env->value);
	env->value = new_env;
}

char	*error_cmd(char *cmd)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = "";
	tmp2 = "";
	tmp1 = ft_strjoin("`", cmd);
	tmp2 = ft_strjoin(tmp1, "\'");
	free(tmp1);
	return (tmp2);
}

void	print_env(char **env)
{
	int		cnt;
	int		i;
	int		j;
	char	*tmp;
	char	**sort_env;

	cnt = 0;
	while (env[cnt])
		cnt++;
	sort_env = malloc(sizeof(char *) * (cnt + 1));
	i = -1;
	while (env[++i])
		sort_env[i] = env[i];
	
	i = 0;
	while (i < cnt - 1)
	{
		j = i + 1;
		while (j < cnt)
		{
			if (ft_strncmp(sort_env[i], sort_env[j], ft_strlen(sort_env[i])) > 0)
			{
				tmp = sort_env[i];
				sort_env[i] = sort_env[j];
				sort_env[j] = tmp;
			}
			j++;
		}
		i++;
	}

	i = -1;
	while (++i < cnt)
	{
		if (sort_env[i][0] == '_' && sort_env[i][1] == '=')
			continue ;
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		j = 0;
		while (sort_env[i][j])
		{
			if (j > 1 && sort_env[i][j - 1] == '=')
				ft_putchar_fd('\"', STDOUT_FILENO);
			ft_putchar_fd(sort_env[i][j], STDOUT_FILENO);
			j++;
		}
		if (j > 1 && sort_env[i][j - 1] == '=')
			ft_putchar_fd('\"', STDOUT_FILENO);
		if (ft_strchr(sort_env[i], '='))
			ft_putchar_fd('\"', STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	free(sort_env);
}

int	ft_export(t_pipeline *pipeline)
{
	int	i;
	int	j;

	if (!pipeline->cmd[1])
		print_env(pipeline->env->value);
	i = 1;
	while (pipeline->cmd[i])
	{
		j = 0;
		while (pipeline->cmd[i][j])
		{
			if (!(ft_isalnum(pipeline->cmd[i][j]) || (j != 0 && pipeline->cmd[i][j] == '=') || \
				pipeline->cmd[i][j] == '_') || ft_isdigit(pipeline->cmd[i][0]))
			{
				print_error(errmsg(TRUE, "export", error_cmd(pipeline->cmd[i]), "not a valid identifier"), FALSE, 1);
				return (0);
			}
			j++;
			if (pipeline->cmd[i][j] == '=')
				break ;
		}
		add_env(pipeline->env, pipeline->cmd[i]);
		i++;
	}
	return (0);
}
