/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:29:50 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/10 22:41:23 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// 헤더
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>

// parsing
typedef struct s_token
{
	char		*value;
	t_type 		type;
	t_token		*next;
}	t_token;

typedef struct s_dollar
{
	char		*value;
}	t_dollar;

// 구조체
typedef enum e_type
{
	STDIN,
	STDOUT,
	APPEND,
	HEREDOC,
	COMMAND,
}	t_type;

typedef struct s_cmdline
{
	t_token		*cmd;
	t_type		type;
	t_cmdline	*next;
}	t_cmdline;

#endif