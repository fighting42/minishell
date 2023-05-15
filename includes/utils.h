/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 23:32:49 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/07 23:32:49 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

# define BUFFER_SIZE 1

typedef struct s_env_h
{
	t_envval	*env_var;
	int			dollar_index;
}	t_env_h;

// main.c
void		set_termios(void);
// error.c
void		*print_error(char *errmsg, int flag, int status);
char		*errmsg(int flag, char *cmd1, char *cmd2, char *msg);
int			check_null(t_cmdline *cmdline);
// gnl.c
char		*get_next_line(int fd);
// signal.c
void		init_signal(void);
void		signal_ctrl_d(void);
void		sigint_handler(int sig);
void		sigint_handler_heredoc(int sig);
void		print_signal(int status);
// ft_strjoin_free.c
char		*ft_strjoin_free_all(char *s1, char *s2);
char		*ft_strjoin_free_front(char *s1, char *s2);
char		*ft_strjoin_free_back(char *s1, char *s2);
// env_heredoc.c
t_envval	*chk_env_heredoc(char *str, t_env *env);
void		add_env_val_heredoc(t_command *com, t_env_h *env_h, char *ret);
void		change_env_var_heredoc(t_command *com, t_env_h *env_h, char *ret);
char		*env_to_str_heredoc(char *str, t_env_h *env_h);
char		*env_str_heredoc(char *str, t_env *env);
// env_heredoc_utils.c
int			count_dollar_heredoc(char *str);
void		env_index_heredoc(t_env_h *env_h, t_len_env *len_env);
void		dollar_case_heredoc(char *str, t_envval *env_var, \
								t_dollar_idx *dollar_i, t_env *env);
int			len_env_to_str_heredoc(char *str, t_env_h *env_h);
// free_utils.c
void		free_split(char **arr);
void		free_cmdline(t_cmdline *cmdline);
void		free_join(t_join *join);

#endif