/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 01:39:30 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/16 02:39:30 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(t_execinfo *execinfo)
{
	int	i;
	int	j;
	int flag;

	i = 1;
	j = 0;
	flag = 0;
	while (execinfo->cmd[i][j] == '-')
	{
		j++;
		while (execinfo->cmd[i][j])
		{
			if (execinfo->cmd[i][j] != 'n')
				return (0); // echo option error
			j++;
		}
		i++;
		j = 0;
		flag = 1;
	}
	if (flag)
		printf("%s", execinfo->cmd[i]);
	else
		printf("%s\n", execinfo->cmd[i]);
	return (1);
}

int	ft_env(t_execinfo *execinfo)
{
	int	i;

	i = 0;
	while (execinfo->envp[i])
		printf("%s\n", execinfo->envp[i++]);
	return (1);
}

int ft_pwd(void)
{
	char	*ret;

	ret = getcwd(NULL, 0);
	printf("%s\n", ret);
	free(ret);
	return (1);
}

int check_builtin(char *cmd, t_execinfo *execinfo)
{
    if (!ft_strncmp("echo", cmd, ft_strlen(cmd)))
        return (ft_echo(execinfo));
    else if (!ft_strncmp("cd", cmd, ft_strlen(cmd)))
        return (1);
    else if (!ft_strncmp("pwd", cmd, ft_strlen(cmd)))
        return (ft_pwd());
    else if (!ft_strncmp("export", cmd, ft_strlen(cmd)))
        return (1);
    else if (!ft_strncmp("unset", cmd, ft_strlen(cmd)))
        return (1);
    else if (!ft_strncmp("env", cmd, ft_strlen(cmd)))
        return (ft_env(execinfo));
    else if (!ft_strncmp("exit", cmd, ft_strlen(cmd)))
        return (1);
    return (0);
}