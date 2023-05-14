/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:13:32 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/06 20:16:44 by yejinkim         ###   ########seoul.kr  */
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

typedef struct s_pipeline
{
	char				**cmd;
	char				*path;
	t_env				*env;
	t_redirct			*redirct;
	struct s_pipeline	*next;
}	t_pipeline;

typedef struct s_exec
{
	t_pipeline	*pipeline;
	int			heredoc_cnt;
	int			pipe_cnt;
	int			stdin_ori;
	int			stdout_ori;
}	t_exec;

// execute.c
void		execute(t_cmdline *cmdline, t_env *env);
void		execute_end(t_exec *exec);
t_exec		*init_exec(t_cmdline *cmdline, t_env *env);
void		wait_procs(int cnt);
t_pipeline	*next_pipeline(t_pipeline *pipeline);
// heredoc.c
int			check_heredoc(t_exec *exec);
char		*fork_heredoc(t_redirct *redirct, t_exec *exec);
void		do_heredoc(t_redirct *redirct, t_exec *exec, char *file);
void		unlink_heredoc(void);
// init.c
void		check_cmdline(t_cmdline *cmdline, t_env *env, t_exec *exec);
t_pipeline	*create_pipeline(t_cmdline *cmdline, int i, int prev, t_env *env);
void		split_cmdline(t_token *token, t_pipeline *pipeline, int cnt);
void		append_redirct(t_pipeline *pipeline, t_token *token);
void		append_pipeline(t_exec *exec, t_pipeline *pipeline);
// pipe.c
void		exec_fork(t_exec *exec, int flag);
void		exec_cmd(int fds[2], t_exec *exec, int flag);
char		*find_path(char **cmd, char **envp_path);
char		**pars_envp(char **envp);
char		*path_join(char **envp_path, char **cmd);
// redirection.c
void		redirct(t_exec *exec);
void		do_redirct(t_redirct *redirct);
int			fd_open(t_redirct *redirct);

#endif