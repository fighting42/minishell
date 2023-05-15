/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:50:08 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/15 14:45:15 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

long	ft_atol(char *str)
{
	long		i;
	long long	sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - '0');
		if (result * sign < (long long)-9223372036854775808ULL || \
				result * sign > (long long)9223372036854775807)
			print_error(errmsg(1, "exit", str, \
				"numeric argument required"), TRUE, 255);
	}
	return ((long)result * sign);
}

int	check_status(char *cmd)
{
	int	i;

	if (ft_strlen(cmd) > 20)
		return (1);
	i = 0;
	while (cmd[i])
	{
		if (!(ft_isdigit(cmd[i]) || cmd[i] == '-'))
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit(t_exec *exec)
{
	char		**cmd;

	cmd = exec->pipeline->cmd;
	if (!cmd[1])
		exit(g_status);
	if (check_status(cmd[1]))
		print_error(errmsg(TRUE, "exit", cmd[1], \
			"numeric argument required"), TRUE, 255);
	if (cmd[2])
	{
		print_error(errmsg(TRUE, "exit", NULL, \
			"too many arguments"), FALSE, 1);
		return (0);
	}
	if (0 < exec->pipe_cnt)
		return (0);
	ft_putendl_fd("exit", STDOUT_FILENO);
	g_status = ft_atol(cmd[1]);
	g_status %= 256;
	if (g_status < 0)
		g_status += 256;
	exit(g_status);
}
