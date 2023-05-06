/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:13:32 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/06 17:39:02 by yejinkim         ###   ########seoul.kr  */
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
}	t_exec;

void	execute(t_cmdline *cmdline, t_env *env);
void	exec_pipe(t_exec *exec, int flag);
char	*find_path(char **cmd, char **envp_path);
void	redirct(t_exec *exec);
t_exec	*init_exec(t_cmdline *cmdline, t_env *env);
void	unlink_heredoc(t_exec *exec);
void	print_error(char *errmsg, int flag, int status);
char	*errmsg(int flag, char *cmd1, char *cmd2, char *msg);

#endif