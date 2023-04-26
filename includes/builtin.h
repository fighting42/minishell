/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:18:29 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/26 12:45:22 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

int		check_builtin(t_execinfo *execinfo);
int		check_builtin_fd(t_execinfo *execinfo, int fd);
int		ft_echo(char **cmd, int fd);
int		ft_cd(t_execinfo *execinfo);
int		ft_pwd(void);
int		ft_export(t_execinfo *execinfo);
int		ft_unset(t_execinfo *execinfo);
int		ft_env(t_execinfo *execinfo, int fd);
int		ft_exit(void);
// env_utils
char	**init_env(char **envp);
int		get_env_i(char **env, char *var);
char	*get_env(char **env, char *var);
void	set_env(char **env, char *var, char *value);
void	add_env(t_execinfo *execinfo, int cnt);
void	del_env(t_execinfo *execinfo, int cnt);

#endif