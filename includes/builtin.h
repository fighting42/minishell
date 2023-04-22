/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:18:29 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/22 22:30:05 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

#include "minishell.h"

int check_builtin(t_execinfo *execinfo, int fd);
int	ft_echo(char **cmd, int fd);
int	ft_env(char **env, int fd);
int ft_pwd(void);
int	ft_export(t_execinfo *execinfo);

#endif