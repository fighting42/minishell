/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:29:50 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/10 22:44:36 by yejinkim         ###   ########seoul.kr  */
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

typedef struct s_cmdline
{
	char				**cmd;
	t_type 				type;
	struct s_cmdline	*next;
}	t_cmdline;

// execute
void	execute(t_cmdline *cmdline, char **envp);

// parsing


#endif