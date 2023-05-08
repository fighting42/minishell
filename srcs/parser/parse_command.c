/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:45:20 by dapark            #+#    #+#             */
/*   Updated: 2023/05/08 22:02:47 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_env_to_str(t_parse *parse, char *str)
{
	int	k;
	int	len;
	int	quote;
	int	chk;
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
		if ((quote == 2 && temp[k] == '$') ||\
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

char	*env_to_str(t_parse *parse, char *str)
{
	int		len;
	int		k;
	int		n;
	int		m;
	int		quote;
	char	*ret;
	char	*temp;

	k = 0;
	n = 0;
	m = 0;
	quote = 0;
	if (str == NULL)
		temp = parse->tmp[parse->i];
	else
		temp = str;
	len = len_env_to_str(parse, str);
	ret = (char *)malloc(sizeof(char) * len + 1);
	while (temp[k] != '\0')
	{
		quote = quote_status(temp[k], quote);
		if ((quote == 2 && temp[k] == '$') ||\
			(quote == 0 && temp[k] == '$'))
		{
			while(parse->env_var[parse->dollar_index].value[m] != '\0')
			{
				ret[n] = parse->env_var[parse->dollar_index].value[m];
				n++;
				m++;
			}
			k += ft_strlen(parse->env_var[parse->dollar_index].ori);
			k += 1;
			parse->dollar_index++;
		}
		else
		{
			ret[n] = temp[k];
			n++;
			k++;
		}
	}
	ret[n] = '\0';
	return (ret);
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
		while(parse->tmp[parse->i][parse->j] != '\0')
		{
			curr_q = quote_status(parse->tmp[parse->i][parse->j], curr_q);
			if (curr_q == quote)
			{
				flag = 1;
				curr_q = chk_whole_quote(parse->tmp[parse->i], parse->j + 1);
				if (curr_q == 0)
				{
					ret = ft_strjoin(ret, parse->tmp[parse->i]);
					break;
				}
				else
				{
					flag = 2;
					//ret = ft_strjoin(ret, parse->tmp[parse->i]);
					ret_add = valid_join(parse, curr_q); 
					break;
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
	char	*tmp;
	char	*tmp1;

	if (parse->type == 0)
		parse->type = COMMAND;
	if (str == NULL)
	{
		if (count_dollar(parse->tmp[parse->i]) == 0)
		{
			tmp = remove_quote(parse->tmp[parse->i]);
			append_token(parse->c_head->token, t_curr, tmp, parse->type);
		}
		else
		{
			tmp1 = env_to_str(parse, NULL); //환경변수 바꾸고
			tmp = remove_quote(tmp1); // 따옴표 제거
			append_token(parse->c_head->token, t_curr, tmp, parse->type);
		}
	}
	else
	{
		if (count_dollar(str) == 0)
		{
			tmp = remove_quote(str);
			append_token(parse->c_head->token, t_curr, tmp, parse->type);
		}
		else
		{
			tmp1 = env_to_str(parse, str); //환경변수 바꾸고
			tmp = remove_quote(tmp1); // 따옴표 제거
			append_token(parse->c_head->token, t_curr, tmp, parse->type);
		}
	}
}

int	cmd_or_str(t_parse	*parse, t_token *t_curr)
{
	char	*tmp;
	char	*tmp1;
	int		quote;

	if (chk_whole_quote(parse->tmp[parse->i], 0) == 0) // 따옴표없거나 쌍으로 잘 있음
		make_token_value(parse, NULL, t_curr);
	else // 따옴표 세트 나올때까지 strjoin -> 그 str을 위의 if에다가 넣어
	{
		quote = chk_whole_quote(parse->tmp[parse->i], 0);
		tmp = valid_join(parse, quote);
		if (tmp == NULL)
			return (1);
		make_token_value(parse, tmp, t_curr); 
	}
	move_index_j(parse);
	parse->type = 0;
	return (0);
}
