/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:17:53 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/05 20:37:50 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_dollar
{
	char		*value;
}	t_dollar;

int			check_sep(char c, char *sep);
int			chk_whole_quote(char *str);
int			chk_quote_one(char *str, int flag);
int			is_not_ok_sep(char *str, char *sep);
t_dollar	*chk_env(char *str, t_env *env);
int			quote_status(char c, int quote);
char		*trans_env(t_env *env, char *str, int start, int size);
t_cmdline	*parsing(char *str, t_env *env);
char		*remove_quote(char *str);
int			check_sep(char c, char *sep);
int			length_str(char *str, char *sep, int k, int flag);
char		*make_str(char *str, char *sep, int k, int flag);
int			count_str(char *str, char *sep);
char		**parse_split(char *str, int count);
t_token		*create_token();
void		append_token(t_token *head, t_token *curr, char *value, int type);

#endif