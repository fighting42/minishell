/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:56:08 by daheepark         #+#    #+#             */
/*   Updated: 2023/05/15 16:12:24 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_env_val(t_command *com, t_parse *parse, char *ret)
{
	char	*tmp;

	if (parse->env_var[parse->dollar_index].value == NULL)
	{
		com->t += ft_strlen(parse->env_var[parse->dollar_index].ori);
		com->t += 1;
		ret = NULL;
		return ;
	}
	if (parse->type == HEREDOC)
		tmp = ft_strjoin_free_back("$", \
			ft_strdup(&parse->env_var[parse->dollar_index].ori[com->e]));
	else
		tmp = &parse->env_var[parse->dollar_index].value[com->e];
	while (tmp[com->e] != '\0')
	{
		ret[com->r] = tmp[com->e];
		com->r++;
		com->e++;
	}
	com->t += ft_strlen(parse->env_var[parse->dollar_index].ori);
	com->t += 1;
	if (parse->type == HEREDOC)
		free(tmp);
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
			if (ret == NULL)
				return ;
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

void	env_index(t_parse *parse, t_len_env *len_env)
{
	len_env->quote = quote_status(len_env->temp[len_env->k], len_env->quote);
	if ((len_env->quote == 2 && len_env->temp[len_env->k] == '$') || \
		(len_env->quote == 0 && len_env->temp[len_env->k] == '$'))
	{
		len_env->len += parse->env_var[parse->dollar_index].size_v;
		if (ft_strlen(parse->env_var[parse->dollar_index].ori) != 0)
			len_env->k += ft_strlen(parse->env_var[parse->dollar_index].ori);
		else
			len_env->k += 1;
		parse->dollar_index++;
		len_env->chk++;
	}
	else
		len_env->len++;
}

int	len_env_to_str(t_parse *parse, char *str)
{
	int			ret;
	t_len_env	*len_env;

	len_env = malloc(sizeof(t_len_env));
	init_len_env(len_env);
	if (str == NULL)
		len_env->temp = ft_strdup(parse->tmp[parse->i]);
	else
		len_env->temp = ft_strdup(str);
	while (len_env->temp[++len_env->k] != '\0')
		env_index(parse, len_env);
	parse->dollar_index = parse->dollar_index - len_env->chk;
	ret = len_env->len;
	free(len_env->temp);
	free(len_env);
	return (ret);
}

char	*env_to_str(t_parse *parse, char *str)
{
	int			len;
	char		*ret;
	t_command	*com;

	com = malloc(sizeof(t_command));
	init_t_command(com);
	if (str == NULL)
		com->temp = ft_strdup(parse->tmp[parse->i]);
	else
		com->temp = ft_strdup(str);
	len = len_env_to_str(parse, str);
	if (len == 0)
		ret = NULL;
	else
		ret = (char *)malloc(sizeof(char) * len + 1);
	change_env_var(com, parse, ret);
	free(com->temp);
	free(com);
	if (ret == NULL)
		return (NULL);
	return (ret);
}
