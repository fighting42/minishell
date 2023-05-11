/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daheepark <daheepark@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:45:20 by dapark            #+#    #+#             */
/*   Updated: 2023/05/11 15:05:44 by daheepark        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_env_to_str(t_parse *parse, char *str)
{
	int		k;
	int		len;
	int		quote;
	int		chk;
	char	*temp;

	k = -1;
	quote = 0;
	len = 0;
	chk = 0;
	if (str == NULL)
		temp = parse->tmp[parse->i];
	else
		temp = str;
	while (temp[++k] != '\0')
	{
		quote = quote_status(temp[k], quote);
		if ((quote == 2 && temp[k] == '$') || \
			(quote == 0 && temp[k] == '$'))
		{
			len += parse->env_var[parse->dollar_index].size_v;
			if (ft_strlen(parse->env_var[parse->dollar_index].ori) != 0)
				k += ft_strlen(parse->env_var[parse->dollar_index].ori);
			else
				k += 1;
			parse->dollar_index++;
			chk++;
		}
		else
			len++;
	}
	parse->dollar_index = parse->dollar_index - chk;
	return (len);
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
					ret = ft_strjoin(ret, parse->tmp[parse->i]);
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
			ret = ft_strjoin(ret, parse->tmp[parse->i]);
		if (flag == 1)
			return (ret);
		if (flag == 2)
		{
			ret = ft_strjoin(ret, ret_add);
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
		temp = parse->tmp[parse->i];
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
