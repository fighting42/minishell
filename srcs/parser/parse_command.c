/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:45:20 by dapark            #+#    #+#             */
/*   Updated: 2023/05/12 21:23:37 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_split(t_parse *parse, t_token *t_curr, char *ret_str)
{
	char	**split;
	int		i;
	char	*tmp;

	i = -1;
	split = ft_split(ret_str, ' ');
	free(ret_str);
	while (split[++i] != NULL)
	{
		tmp = ft_strdup(split[i]);
		append_token(parse, t_curr, tmp);
		if (split[i + 1] != NULL)
			t_curr = create_token();
	}
	parse->env_flag = 0;
	i = -1;
	while (split[++i] != NULL)
		free(split[i]);
	free(split);
}

int	valid_join_utils(t_parse *parse, t_join *join, int quote)
{
	while (parse->tmp[parse->i][parse->j] != '\0')
	{
		join->curr_q = quote_status(parse->tmp[parse->i][parse->j], 0);
		if (join->curr_q == quote)
		{
			join->flag = 1;
			join->curr_q = chk_whole_quote(parse->tmp[parse->i], parse->j + 1);
			if (join->curr_q == 0)
			{
				join->ret = ft_strjoin_free_front(join->ret, \
							parse->tmp[parse->i]);
				return (join->flag);
			}
			else
			{
				join->flag = 2;
				join->ret_add = valid_join(parse, join->curr_q, join);
				return (join->flag);
			}
		}
		parse->j++;
	}
	return (join->flag);
}

char	*valid_join(t_parse *parse, int quote, t_join *join)
{
	parse->i++;
	while (parse->tmp[parse->i] != NULL)
	{
		parse->j = 0;
		valid_join_utils(parse, join, quote);
		if (join->flag != 1 && join->flag != 2)
			join->ret = ft_strjoin_free_front(join->ret, parse->tmp[parse->i]);
		if (join->flag == 1)
		{
			free(join);
			return (join->ret);
		}
		if (join->flag == 2)
		{
			join->ret = ft_strjoin_free_all(join->ret, join->ret_add);
			free(join);
			return (join->ret);
		}
		parse->i++;
	}
	return (join->ret);
}

void	make_token_value(t_parse *parse, char *str, t_token *t_curr)
{
	char	*temp;
	char	*ret_str1;
	char	*ret_str;

	if (parse->type == -1)
		parse->type = COMMAND;
	if (str == NULL)
		temp = ft_strdup(parse->tmp[parse->i]);
	else
		temp = str;
	if (count_dollar(temp, parse, 0) == 0)
		ret_str = remove_quote(temp);
	else
	{
		ret_str1 = env_to_str(parse, str);
		ret_str = remove_quote(ret_str1);
		if (parse->env_flag == 1)
		{
			env_split(parse, t_curr, ret_str);
			return ;
		}
	}
	append_token(parse, t_curr, ret_str);
}

int	cmd_or_str(t_parse	*parse, t_token *t_curr)
{
	char	*tmp;
	int		quote;
	t_join	*join;

	join = malloc(sizeof(t_join));
	init_join(join, parse);
	if (chk_whole_quote(parse->tmp[parse->i], 0) == 0)
		make_token_value(parse, NULL, t_curr);
	else
	{
		quote = chk_whole_quote(parse->tmp[parse->i], 0);
		tmp = valid_join(parse, quote, join);
		if (tmp == NULL)
			return (1);
		make_token_value(parse, tmp, t_curr);
		free(tmp);
	}
	move_index_j(parse);
	parse->type = -1;
	return (0);
}
