/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:18:29 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/03 17:44:57 by yejinkim         ###   ########seoul.kr  */
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
int		ft_exit(t_execinfo *exec);
// env_utils
char	**init_env(char **envp);
char	**init_add_env(char **env);
int		get_env_i(char **env, char *var);
char	*get_env(char **env, char *var);
void	set_env(t_env *env, char *var, char *value);
void	add_env(t_env *env, char *value);
void	del_env(t_env *env, char *var);
char	*error_cmd(char *cmd);

#endif