/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:06:54 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/13 20:37:54 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*error_cmd(char *cmd)
{
	char	*tmp;

	tmp = "";
	tmp = ft_strjoin("`", cmd);
	tmp = ft_strjoin_free_front(tmp, "\'");
	return (tmp);
}

void	print_env_value(char **env_tmp, int i)
{
	int	j;

	j = 0;
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	while (env_tmp[i][j])
	{
		if (j > 1 && env_tmp[i][j - 1] == '=')
			ft_putchar_fd('\"', STDOUT_FILENO);
		ft_putchar_fd(env_tmp[i][j], STDOUT_FILENO);
		j++;
	}
	if (j > 1 && (env_tmp[i][j - 1] == '=' && env_tmp[i][j - 2] != '='))
		ft_putchar_fd('\"', STDOUT_FILENO);
	if (ft_strchr(env_tmp[i], '='))
		ft_putchar_fd('\"', STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	print_env(char **env)
{
	int		cnt;
	int		i;
	char	**env_tmp;

	cnt = 0;
	while (env[cnt])
		cnt++;
	env_tmp = sort_env(env, cnt);
	i = -1;
	while (++i < cnt)
	{
		if (env_tmp[i][0] == '_' && env_tmp[i][1] == '=')
			continue ;
		print_env_value(env_tmp, i);
	}
	free(env_tmp);
}

int	check_value(char **cmd, int i, int j)
{
	while (cmd[i][j])
	{
		if (!(ft_isalnum(cmd[i][j]) || (j != 0 && cmd[i][j] == '=') || \
			cmd[i][j] == '_') || ft_isdigit(cmd[i][0]))
		{
			print_error(errmsg(TRUE, "export", error_cmd(cmd[i]), \
				"not a valid identifier"), FALSE, 1);
			return (1);
		}
		j++;
		if (cmd[i][j] == '=')
			break ;
	}
	return (0);
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
		if (check_value(pipeline->cmd, i, j))
			return (0);
		add_env(pipeline->env, pipeline->cmd[i]);
		i++;
	}
	return (0);
}
