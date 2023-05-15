/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:17:53 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/15 17:46:18 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_envval
{
	char		*value;
	char		*ori;
	int			size_v;
}	t_envval;

typedef struct s_parse
{
	t_cmdline	*c_head;
	t_token		*t_head;
	int			i;
	int			j;
	int			quote;
	int			type;
	int			env_flag;
	int			dollar_cnt;
	int			dollar_index;
	int			num_pipe;
	int			cnt_pipe;
	char		**tmp;
	t_envval	*env_var;
}	t_parse;

typedef struct s_dollar_idx
{
	int	i;
	int	j;
}	t_dollar_idx;

typedef struct s_rmv_quote
{
	int	flag_q;
	int	curr_q;
	int	quote;
	int	j;
}	t_rmv_quote;

typedef struct s_command
{
	int		r;
	int		t;
	int		e;
	char	*temp;
}	t_command;

typedef struct s_len_env
{
	int		k;
	int		chk;
	char	*temp;
	int		quote;
	int		len;
}	t_len_env;

typedef struct s_join
{
	int		flag;
	int		curr_q;
	char	*ret;
	char	*ret_add;
}	t_join;

typedef struct s_re_env
{
	int		flag;
	int		i;
	int		quote;
	int		dollar;
}	t_re_env;

//parse_command.c
int			cmd_or_str(t_parse	*parse, t_token *t_curr);
void		make_token_value(t_parse *parse, char *str, t_token *t_curr);
char		*valid_join(t_parse *parse, int quote, t_join *join);
void		env_split(t_parse *parse, t_token *t_curr, char *ret_str);
int			valid_join_utils(t_parse *parse, t_join *join, int quote);

//parse_command_env.c
int			len_env_to_str(t_parse *parse, char *str);
void		env_index(t_parse *parse, t_len_env *len_env);
void		add_env_val(t_command *com, t_parse *parse, char *ret);
void		change_env_var(t_command *com, t_parse *parse, char *ret);
char		*env_to_str(t_parse *parse, char *str);

//parse_dollar_env.c
t_envval	*chk_env(char *str, t_env *env, t_parse *parse);
char		*trans_env(t_env *env, char *str, int start, int size);
char		*make_env_str(t_env *env, int i, int size);
char		*strdup_ori(char *str, int start, int end);
int			env_strcmp(char *env_str, char *temp);

//parse_dollar.c
int			count_dollar(char *str, t_parse *parse, int flag);
void		question_mark_str(char *str, t_envval *env_var, int j, int start);
void		trans_question_mark(t_envval *env_var, char *str, int start, int j);
void		dollar_case(char *str, t_envval *env_var, \
						t_dollar_idx *dollar_i, t_env *env);
int			dollar_dollar(char *str, t_envval *env_var, \
						t_dollar_idx *dollar_i, int count);

//parse_error.c
int			error_quote(char *str);
int			pipe_error(char *str);
int			pipe_the_end(char *str, t_parse *parse);
int			consecutive_pipe_error(char *str, int i);
int			redirection_error(char *str, t_parse *parse);
int			redirection_env(char *str, t_parse *parse);

//parse_error_2.c
int			redirection_env(char *str, t_parse *parse);
void		env_flag(char *str, t_re_env *env_re);
void		init_t_re_env(t_re_env *env_re);

//parse_init.c
void		init_parse(t_parse	*parse, char *str, t_env *env, \
						t_cmdline *c_curr);
void		init_rmv(t_rmv_quote *rmv);
void		init_t_command(t_command *com);
void		init_len_env(t_len_env *len_env);
void		init_join(t_join *join, t_parse *parse);

//parse_quote.c
char		*remove_quote(char *str);
int			chk_str_len(char *str);
void		make_ret_str(char *str, char *ret);

//parse_quote_utils.c
int			quote_status(char c, int quote);
int			chk_whole_quote(char *str, int k);

//parse_redir_pipe.c
int			redirection_stdin(t_parse *parse);
int			redirection_stdout(t_parse *parse);
int			check_pipe(t_parse *parse, t_token *t_curr);
void		count_pipe(char *str, t_parse *parse);

//parse_split.c
int			length_str(char *str, char *sep, int k, int flag);
char		*make_str(char *str, char *sep, int k, int flag);
int			count_str(char *str, char *sep);
char		**parse_split(char *str, int count);
int			is_not_ok_sep(char *str, char *sep);

//parse_utils.c
int			check_sep(char c, char *sep);
t_token		*create_token(void);
void		append_token(t_parse *parse, t_token *curr, char *value);
void		move_index_j(t_parse *parse);

//parsing.c
t_cmdline	*parsing(char *str, t_env *env);
int			parse_case(t_parse *parse, t_token *t_curr);
int			redirection_case(t_parse *parse);
int			parse_loop(t_parse *parse, t_token *t_curr);
int			error_case(char *str, t_parse *parse);

//parse_free.c
void		free_parse(t_parse *parse);
void		*end_program(t_parse *parse, int ret);

#endif