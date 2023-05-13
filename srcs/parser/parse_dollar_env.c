/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daheepark <daheepark@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:16:42 by daheepark         #+#    #+#             */
/*   Updated: 2023/05/14 03:18:12 by daheepark        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_envval	*chk_env(char *str, t_env *env, t_parse *parse)
{
	t_envval		*env_var;
	t_dollar_idx	*dollar_i;	
	int				quote;
	int				i;

	quote = 0;
	i = -1;
	env_var = malloc(sizeof(t_envval) * (count_dollar(str, parse, 1) + 1));
	while (++i < parse->dollar_cnt)
		env_var[i].size_v = 0;
	dollar_i = malloc(sizeof(t_dollar_idx) * 1);
	dollar_i->i = 0;
	dollar_i->j = 0;
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

int	env_strcmp(char *env_str, char *temp)
{
	int		i;
	int		tmp;
	int		size;
	char	*str;

	tmp = 0;
	i = -1;
	while (env_str[++i] != '=')
		tmp++;
	str = malloc(sizeof(char) * tmp + 1);
	i = -1;
	while (env_str[++i] != '=')
		str[i] = env_str[i];
	str[i] = '\0';
	size = tmp;
	if ((int)strlen(temp) > tmp)
		size = strlen(temp);
	if (ft_strncmp(str, temp, size) == 0)
		tmp = 0;
	else
		tmp = 1;
	free(str);
	return (tmp);
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
	i = -1;
	while (env->value[++i] != 0)
	{
		if (env->value[i][0] == temp[0])
		{
			if (env_strcmp(env->value[i], temp) == 0)
				break ;
		}
	}
	free(temp);
	ret = make_env_str(env, i, size);
	return (ret);
}
