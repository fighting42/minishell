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

// error.c
void	print_error(char *errmsg, int flag, int status);
char	*errmsg(int flag, char *cmd1, char *cmd2, char *msg);
// gnl.c
char	*get_next_line(int fd);
// signal.c
void	init_signal(void);
void	signal_ctrl_d(void);
void	sigint_handler(int sig);
void	sigint_handler_heredoc(int sig);
void	set_termios(void);
//ft_strjoin_free.c
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strjoin_free_front(char *s1, char *s2);
char	*ft_strjoin_free_back(char *s1, char *s2);

#endif