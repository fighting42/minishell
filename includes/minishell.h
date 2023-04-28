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

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include "../srcs/libft/libft.h"

# include "cmdline.h"
# include "parsing.h"
# include "execute.h"
# include "builtin.h"
# include "errmsg.h"

#define NULL 0

int	g_status;

#endif