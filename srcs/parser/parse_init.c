/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daheepark <daheepark@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:04:02 by dapark            #+#    #+#             */
/*   Updated: 2023/05/09 15:50:06 by daheepark        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_parse(t_parse	*parse, char *str, t_env *env, t_cmdline *c_curr)
{
	int		cnt_split;

	parse->quote = 0;
	parse->i = 0;
	parse->j = 0;
	parse->dollar_index = 0;
	parse->type = 0;
	parse->last_pipe = 0;
	parse->cnt_pipe = 0;
	parse->num_pipe = 0;
	parse->c_head = c_curr;
	parse->env_var = chk_env(str, env);
	cnt_split = count_str(str, " |<>");
	parse->tmp = parse_split(str, cnt_split);
}
