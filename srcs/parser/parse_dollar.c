/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:16:08 by dapark            #+#    #+#             */
/*   Updated: 2023/05/06 21:25:50 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*trans_env(t_env *env, char *str, int start, int size)
{
	int	i, j;
	char *temp;
	int len;
	char *ret;

	i = 0;
	len = size + 1;
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
	if (env->value[i] == 0)
		return ("\n");
	while (env->value[i][len] != '\0')
		len++;
	len = len - size + 1;
	ret = malloc(sizeof(char) * (len + 1));
	j = 0;
	while (j < len + 1)
	{
		ret[j] = env->value[i][size + 1];
		j++;
		size++;
	}
	ret[j] = '\0';
	return (ret);
}

int	count_dollar(char *str)
{
	int	cnt_dollar;
	int	i;
	int	quote;

	cnt_dollar = 0;
	i = 0;
	quote = 0;
	while (str[i] != '\0')
	{
		quote = quote_status(str[i], quote);
		if ((quote == 2 && str[i] == '$') ||\
			(quote == 0 && str[i] == '$'))
			cnt_dollar++;
		i++;
	}
	return (cnt_dollar);
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

t_envval	*chk_env(char *str, t_env *env)
{
	t_envval	*env_var;
	char		*sep;
	int			i;
	int			j;
	int			quote;
	int			cnt_dollar;
	int			count;

	i = 0; 
	j = 0;
	cnt_dollar = count_dollar(str);
	quote = 0;
	sep = " |<\">";
	env_var = malloc(sizeof(t_envval) * (cnt_dollar + 1));
	i = 0;
	quote = 0;
	while (str[i] != '\0')
	{
		quote = quote_status(str[i], quote);
		if ((quote == 2 && str[i] == '$') ||\
			(quote == 0 && str[i] == '$'))
		{
			count = i + 1;
			if (str[count] == '?')
				env_var[j].value = ft_itoa(g_status);
			else
			{
				while (check_sep(str[count], sep) != 1 && str[count] != '\0')
					count++;
				env_var[j].value = trans_env(env, str, i + 1, count - i - 1);
				env_var[j].ori = strdup_ori(str, i + 1, count - i - 1);
			}
			j++;
			i = count ;
		}
		else
			i++;
	}
	env_var[j].value = NULL;
	return (env_var);
}
