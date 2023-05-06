/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:06:54 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/06 17:05:23 by yejinkim         ###   ########seoul.kr  */
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
	char	**new_env;

	if (!ft_strchr(value, '='))
		return ;
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

	tmp1 = ft_strjoin("\'", cmd); // ` 이거..
	tmp2 = ft_strjoin(tmp2, "\'");
	free(tmp1);
	return (tmp2);
}

int	ft_export(t_pipeline *pipeline)
{
	int	i;
	int	j;

	i = 1;
	while (pipeline->cmd[i])
	{
		j = 0;
		while (pipeline->cmd[i][j])
		{
			if (!(ft_isalnum(pipeline->cmd[i][j]) || (i != 0 && pipeline->cmd[i][j] == '=')))
				print_error(errmsg(1, "export", error_cmd(pipeline->cmd[i]), NOT_VALID_ERR), EXIT_Y, 1);
			j++;
		}
		add_env(pipeline->env, pipeline->cmd[i]);
		i++;
	}
	return (0);
}
