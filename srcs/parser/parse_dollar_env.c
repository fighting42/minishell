/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:16:42 by daheepark         #+#    #+#             */
/*   Updated: 2023/05/13 20:51:24 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_envval	*chk_env(char *str, t_env *env, t_parse *parse)
{
	t_envval		*env_var;
	t_dollar_idx	*dollar_i;	
	int				quote;

	quote = 0;
	env_var = malloc(sizeof(t_envval) * (count_dollar(str, parse, 1) + 1));
	dollar_i = malloc(sizeof(t_dollar_idx) * 1);
	dollar_i->i = 0;
	dollar_i->j = 0;
	quote = 0;
	while (str[dollar_i->i] != '\0')
	{
		quote = quote_status(str[dollar_i->i], quote);
		if ((quote == 2 && str[dollar_i->i] == '$') || \
			(quote == 0 && str[dollar_i->i] == '$'))
			dollar_case(str, env_var, dollar_i, env);
		else
			dollar_i->i++;
	}
	env_var[dollar_i->j].value = NULL;
	free(dollar_i);
	return (env_var);
}

char	*strdup_ori(char *str, int start, int end)
{
	int		i;
	int		j;
	char	*tmp;

	i = start;
	j = 0;
	tmp = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!tmp)
		return (0);
	while (i <= end)
	{
		tmp[j] = str[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*make_env_str(t_env *env, int i, int size)
{
	char	*ret;
	int		len;
	int		j;

	j = 0;
	len = size + 1;
	if (env->value[i] == 0)
		return (NULL);
	while (env->value[i][len] != '\0')
		len++;
	len = len - size + 1;
	ret = malloc(sizeof(char) * (len + 1));
	while (j < len + 1)
	{
		ret[j] = env->value[i][size + 1];
		j++;
		size++;
	}
	ret[j] = '\0';
	return (ret);
}

char	*trans_env(t_env *env, char *str, int start, int size)
{
	int		i;
	char	*temp;
	char	*ret;

	i = 0;
	temp = malloc(sizeof(char) * (size + 1));
	while (i < size)
	{
		temp[i] = str[start];
		i++;
		start++;
	}
	temp[i] = '\0';
	i = 0;
	while (env->value[i] != 0)
	{
		if (ft_strncmp(env->value[i], temp, size) == 0)
			break ;
		i++;
	}
	free(temp);
	ret = make_env_str(env, i, size);
	return (ret);
}
