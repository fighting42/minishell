/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:13:32 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/03 17:33:08 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

typedef struct s_redirct
{
	char				*value;
	t_type				type;
	struct s_redirct	*next;
}	t_redirct;

typedef struct s_execinfo
{
	t_env				*env;
	char				**cmd;
	char				*path;
	char				hd_cnt;
	int					pipe_cnt;
	t_redirct			*redirct;
	struct s_execinfo	*next;
}	t_execinfo;

t_token		*test_token(char *value, t_type type, int pipe, t_token *next);
t_cmdline	*test_cmdline(void);
void		execute(t_cmdline *cmdline, t_env *env);
void		exec_pipe(t_execinfo *execinfo, int flag);
char		*find_path(char **cmd, char **envp_path);
void		redirection(t_execinfo *execinfo);
t_execinfo	*init_execinfo(t_cmdline *cmdline, t_env *env);
void		unlink_heredoc(t_execinfo *execinfo);
void		print_error(char *errmsg, int flag, int status);
char		*errmsg(int flag, char *cmd1, char *cmd2, char *msg);

#endif