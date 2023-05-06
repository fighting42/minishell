/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:04:02 by dapark            #+#    #+#             */
/*   Updated: 2023/05/06 23:11:13 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_parse(t_parse	*parse, char *str, t_env *env)
{
	int	cnt_split;

	parse->c_head = malloc(sizeof(t_cmdline));
	parse->t_head = create_token();
	parse->c_head->token = parse->t_head;
	parse->quote = 0;
	parse->i = 0;
	parse->j = 0;
	parse->dollar_index = 0;
	parse->type = 0;
	parse->env_var = chk_env(str, env);
	cnt_split = count_str(str, " |<>");
	parse->tmp = parse_split(str, cnt_split);
}