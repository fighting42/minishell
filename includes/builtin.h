/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:18:29 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/06 17:35:20 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

int		check_builtin(t_exec *exec);
int		check_builtin_fd(t_pipeline *pipeline, int fd);
int		ft_echo(char **cmd, int fd);
int		ft_cd(t_pipeline *pipeline);
int		ft_pwd(void);
int		ft_export(t_pipeline *pipeline);
int		ft_unset(t_pipeline *pipeline);
int		ft_env(t_pipeline *pipeline, int fd);
int		ft_exit(t_exec *exec);
// env_utils
char	**init_env(char **envp);
char	**init_add_env(char **env);
int		get_env_i(char **env, char *var);
char	*get_env(char **env, char *var);
void	set_env(t_env *env, char *var, char *value);
void	add_env(t_env *env, char *value);
void	del_env(t_env *env, char *var);
void	free_env(t_env *env);
char	*error_cmd(char *cmd);

#endif