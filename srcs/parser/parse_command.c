/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:45:20 by dapark            #+#    #+#             */
/*   Updated: 2023/05/11 23:51:30 by dapark           ###   ########.fr       */
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

char	*valid_join(t_parse *parse, int quote)
{
	int		curr_q;
	int		flag;
	char	*ret;
	char	*ret_add;

	curr_q = 0;
	flag = 0;
	ret = parse->tmp[parse->i];
	parse->i++;
	while (parse->tmp[parse->i] != NULL)
	{
		parse->j = 0;
		while (parse->tmp[parse->i][parse->j] != '\0')
		{
			curr_q = quote_status(parse->tmp[parse->i][parse->j], curr_q);
			if (curr_q == quote)
			{
				flag = 1;
				curr_q = chk_whole_quote(parse->tmp[parse->i], parse->j + 1);
				if (curr_q == 0)
				{
					ret = ft_strjoin_free(ret, parse->tmp[parse->i]);
					break ;
				}
				else
				{
					flag = 2;
					ret_add = valid_join(parse, curr_q);
					break ;
				}
			}
			parse->j++;
		}
		if (flag != 1 && flag != 2)
			ret = ft_strjoin_free(ret, parse->tmp[parse->i]);
		if (flag == 1)
			return (ret);
		if (flag == 2)
		{
			ret = ft_strjoin_free(ret, ret_add);
			return (ret);
		}
		parse->i++;
	}
	return (ret);
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
	// if (str == NULL)
	// 	free(temp);
	append_token(parse, t_curr, ret_str);
}

int	cmd_or_str(t_parse	*parse, t_token *t_curr)
{
	char	*tmp;
	int		quote;

	if (chk_whole_quote(parse->tmp[parse->i], 0) == 0)
		make_token_value(parse, NULL, t_curr);
	else
	{
		quote = chk_whole_quote(parse->tmp[parse->i], 0);
		tmp = valid_join(parse, quote);
		if (tmp == NULL)
			return (1);
		make_token_value(parse, tmp, t_curr);
	}
	move_index_j(parse);
	parse->type = -1;
	return (0);
}
