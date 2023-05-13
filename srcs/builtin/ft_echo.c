/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 16:11:45 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/14 01:37:36 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(char **cmd, int fd)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	j = 0;
	flag = 0;
	if (cmd[i] && cmd[i][j++] == '-')
	{
		while (cmd[i][j] == 'n')
			j++;
		if (j == (int)ft_strlen(cmd[i]))
			flag = 1;
		i++;
	}
	if (!cmd[i] && !flag)
		ft_putstr_fd("\n", fd);
	while (cmd[i + 1])
	{
		ft_putstr_fd(cmd[i + 1], fd);
		ft_putstr_fd(" ", fd);
		i++;
	}
	if (flag)
		ft_putstr_fd(cmd[i], fd);
	else
		ft_putendl_fd(cmd[i], fd);
	return (0);
}
