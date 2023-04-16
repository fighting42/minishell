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

#include "../minishell.h"

int check_builtin(char *cmd)
{
    if (!ft_strncmp("echo", cmd, ft_strlen(cmd)))
        return (1);
    else if (!ft_strncmp("cd", cmd, ft_strlen(cmd)))
        return (1);
    else if (!ft_strncmp("pwd", cmd, ft_strlen(cmd)))
        return (1);
    else if (!ft_strncmp("export", cmd, ft_strlen(cmd)))
        return (1);
    else if (!ft_strncmp("unset", cmd, ft_strlen(cmd)))
        return (1);
    else if (!ft_strncmp("env", cmd, ft_strlen(cmd)))
        return (1);
    else if (!ft_strncmp("exit", cmd, ft_strlen(cmd)))
        return (1);
    return (0);
}