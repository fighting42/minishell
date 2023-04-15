/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:29:50 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/15 22:28:26 by yejinkim         ###   ########seoul.kr  */
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
typedef struct s_redirect
{
	t_token				*token;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_cmdinfo
{
	char		**cmd;
	char		*path;
	t_redirect	*redirect;
}	t_cmdinfo;

// 함수
// parsing
int			check_sep(char c, char *sep);
int			length_str(char *str, char *sep, int k);
char		*make_str(char *str, char *sep, int k);
int			count_str(char *str, char *sep);
char		**parse_split(char *str, int count, t_dollar *env_var);
char		*trans_env(char **envp, char *str, int start, int size);
int			quote_status(char c, int quote);
t_cmdline	*parsing(char *str, char **envp);
t_dollar	*chk_env(char *str, char **envp);

// execute
void	execute(t_cmdline *cmdline, char **envp);
void	cmd_exec(t_cmdinfo *cmdinfo, char **envp);

#endif