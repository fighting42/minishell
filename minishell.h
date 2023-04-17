/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:29:50 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/15 23:05:49 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// 헤더
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include "libft/libft.h"

// 구조체
typedef enum e_type
{
	STDIN,
	STDOUT,
	APPEND,
	HEREDOC,
	COMMAND,
}	t_type;

typedef struct s_token
{
	char			*value;
	t_type 			type;
	struct s_token	*next;
	int				pipe_flag;
}	t_token;

typedef struct s_cmdline
{
	t_token				*token; // cmd -> token 이름 수정 // 아라똥~~!!ㅎ_ㅎ
	struct s_cmdline	*next;
	int					token_cnt;
}	t_cmdline;

// parsing
typedef struct s_dollar
{
	char		*value;
}	t_dollar;

// execute
typedef struct s_redirct
{
	char				*value;
	t_type				type;
	struct s_redirct	*next;
}	t_redirct;

typedef struct s_cmdinfo
{
	char		**envp;
	char		**cmd;
	char		*path;
	t_redirct	*redirct;
}	t_cmdinfo;

typedef struct s_execinfo
{
	char		**envp;
	char		**cmd;
	char		*path;
	t_redirct	*redirct;
	struct s_execinfo *next;
}	t_execinfo;

// 함수
// parsing
int			check_sep(char c, char *sep);
int			length_str(char *str, char *sep, int k, int flag);
char		*make_str(char *str, char *sep, int k, int flag);
int			count_str(char *str, char *sep);
char		**parse_split(char *str, int count, t_dollar *env_var);
char		*trans_env(char **envp, char *str, int start, int size);
int			quote_status(char c, int quote);
t_cmdline	*parsing(char *str, char **envp);
t_dollar	*chk_env(char *str, char **envp);

// execute
t_token *test_token(char *value, t_type type, int pipe, t_token *next);
t_cmdline test_cmdline();
void	execute(t_cmdline *cmdline, char **envp);
void	pipe_exec(t_execinfo *execinfo, int flag);
int check_builtin(char *cmd, t_execinfo *execinfo);
char	*find_path(char **cmd, char **envp_path);
char	**pars_envp(char **envp);

#endif