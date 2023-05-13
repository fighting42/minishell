/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:18:29 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/14 05:18:10 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

// builtin.c
int		check_builtin(t_exec *exec);
int		check_builtin_fd(t_pipeline *pipeline, int fd);
// env_utils1.c
char	**init_env(char **envp);
char	**init_add_env(char **env);
char	*get_env(char **env, char *var);
void	set_env(t_env *env, char *var, char *value);
void	free_env(t_env *env);
// env_utils2.c
void	add_env(t_env *env, char *value);
int		update_env(t_env *env, char *value);
int		check_env(t_env *env, char *value);
void	swap_env(char **env_tmp, int i, int j);
char	**sort_env(char **env, int cnt);
// ft_cd.c
int		ft_cd(t_pipeline *pipeline);
char	*set_path(char *cmd, char **env);
// ft_echo.c
int		ft_echo(char **cmd, int fd);
void	print_cmd(char **cmd, int i, int flag, int fd);
// ft_env.c
int		ft_env(t_pipeline *pipeline, int fd);
// ft_exit.c
int		ft_exit(t_exec *exec);
int		check_status(char *cmd);
long	ft_atol(char *str);
// ft_export.c
int		ft_export(t_pipeline *pipeline);
int		check_value(char **cmd, int i, int j);
void	print_env(char **env);
void	print_env_value(char **env_tmp, int i);
char	*error_cmd(char *cmd);
// ft_pwd.c
int		ft_pwd(int fd);
// ft_unset.c
int		ft_unset(t_pipeline *pipeline);
void	del_env(t_env *env, char *var);
int		get_env_i(char **env, char *var);

#endif