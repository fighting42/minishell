/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 16:11:45 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/14 05:05:29 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_cmd(char **cmd, int i, int flag, int fd)
{
	if (!flag && !cmd[1])
	{
		ft_putstr_fd("\n", fd);
		return ;
	}
	while (cmd[i + 1])
	{
		ft_putstr_fd(cmd[i], fd);
		if (cmd[i])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (flag)
		ft_putstr_fd(cmd[i], fd);
	else
		ft_putendl_fd(cmd[i], fd);
}

int	ft_echo(char **cmd, int fd)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	flag = 0;
	while (cmd[i] && cmd[i][0] == '-')
	{
		j = 1;
		while (cmd[i][j] == 'n')
			j++;
		if (j == (int)ft_strlen(cmd[i]))
			flag = 1;
		else
			break ;
		i++;
	}
	print_cmd(cmd, i, flag, fd);
	return (0);
}
