/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:18:29 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/24 23:20:25 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

#include "minishell.h"

int check_builtin(t_execinfo *execinfo);
int	check_builtin_fd(t_execinfo *execinfo, int fd);
char	*get_env(char **env, char *var);
void	set_env(char **env, char *var, char *value);
void	add_env(t_execinfo *execinfo, int cnt);
void	del_env(t_execinfo *execinfo, int cnt);
int	ft_echo(char **cmd, int fd);
int	ft_cd(t_execinfo *execinfo);
int ft_pwd(void);
int	ft_export(t_execinfo *execinfo);
int	ft_unset(t_execinfo *execinfo);
int	ft_env(t_execinfo *execinfo, int fd);
int	ft_exit(void);

#endif