/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdline.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:31:45 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/26 12:45:55 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDLINE_H
# define CMDLINE_H

typedef struct s_env
{
	char	**value;
}	t_env;

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
	t_type			type;
	struct s_token	*next;
	int				pipe_flag;
}	t_token;

typedef struct s_cmdline
{
	t_token				*token;
	struct s_cmdline	*next;
	int					token_cnt;
}	t_cmdline;

#endif