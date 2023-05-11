/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daheepark <daheepark@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:56:08 by daheepark         #+#    #+#             */
/*   Updated: 2023/05/11 13:55:34 by daheepark        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_env_val(t_command *com, t_parse *parse, char *ret)
{
	while (parse->env_var[parse->dollar_index].value[com->e] != '\0')
	{
		ret[com->r] = parse->env_var[parse->dollar_index].value[com->e];
		com->r++;
		com->e++;
	}
	com->t += ft_strlen(parse->env_var[parse->dollar_index].ori);
	com->t += 1;
}

void	change_env_var(t_command *com, t_parse *parse, char *ret)
{
	int		quote;

	quote = 0;
	while (com->temp[com->t] != '\0')
	{
		quote = quote_status(com->temp[com->t], quote);
		if ((quote == 2 && com->temp[com->t] == '$') || \
			(quote == 0 && com->temp[com->t] == '$'))
		{
			com->e = 0;
			add_env_val(com, parse, ret);
			parse->dollar_index++;
			if (quote == 0)
				parse->env_flag = 1;
		}
		else
		{
			ret[com->r] = com->temp[com->t];
			com->r++;
			com->t++;
		}
	}
	ret[com->r] = '\0';
}

void	env_split(t_parse *parse, t_token *t_curr, char *ret_str)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(ret_str, ' ');
	while (split[i] != NULL)
	{
		append_token(parse, t_curr, split[i]);
		if (split[i + 1] != NULL)
			t_curr = create_token();
		i++;
	}
	parse->env_flag = 0;
}

char	*env_to_str(t_parse *parse, char *str)
{
	int			len;
	char		*ret;
	t_command	*com;

	com = malloc(sizeof(t_command));
	init_t_command(com);
	if (str == NULL)
		com->temp = parse->tmp[parse->i];
	else
		com->temp = str;
	len = len_env_to_str(parse, str);
	ret = (char *)malloc(sizeof(char) * len + 1);
	change_env_var(com, parse, ret);
	return (ret);
}
