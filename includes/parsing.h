/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:17:53 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/26 12:47:24 by yejinkim         ###   ########seoul.kr  */
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
int			length_str(char *str, char *sep, int k, int flag);
char		*make_str(char *str, char *sep, int k, int flag);
int			count_str(char *str, char *sep);
char		**parse_split(char *str, int count, t_dollar *env_var);
char		*trans_env(char **envp, char *str, int start, int size);
int			quote_status(char c, int quote);
t_cmdline	*parsing(char *str, char **envp);
t_dollar	*chk_env(char *str, char **envp);

#endif