/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:04:02 by dapark            #+#    #+#             */
/*   Updated: 2023/05/15 17:48:17 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_parse(t_parse	*parse, char *str, t_env *env, t_cmdline *c_curr)
{
	int		cnt_split;

	parse->quote = 0;
	parse->i = -1;
	parse->j = 0;
	parse->dollar_index = 0;
	parse->dollar_cnt = 0;
	parse->type = COMMAND;
	parse->cnt_pipe = 0;
	parse->num_pipe = 0;
	parse->env_flag = 0;
	parse->c_head = c_curr;
	parse->env_var = chk_env(str, env, parse);
	cnt_split = count_str(str, " |<>");
	parse->tmp = parse_split(str, cnt_split);
}

void	init_rmv(t_rmv_quote *rmv)
{
	rmv->curr_q = 0;
	rmv->flag_q = 0;
	rmv->quote = 0;
	rmv->j = -1;
}

void	init_t_command(t_command *com)
{
	com->e = 0;
	com->r = 0;
	com->t = 0;
}

void	init_len_env(t_len_env *len_env)
{
	len_env->chk = 0;
	len_env->k = -1;
	len_env->quote = 0;
	len_env->len = 0;
}

void	init_join(t_join *join, t_parse *parse)
{
	char	*tmp;

	tmp = ft_strdup(parse->tmp[parse->i]);
	join->curr_q = 0;
	join->flag = 0;
	join->ret = tmp;
}
