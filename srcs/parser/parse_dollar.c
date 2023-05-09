/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daheepark <daheepark@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:16:08 by dapark            #+#    #+#             */
/*   Updated: 2023/05/09 11:53:25 by daheepark        ###   ########.fr       */
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
		return ("");
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

	int count = 0;
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

void	trans_question_mark(t_envval *env_var, char *str, int start, int j)
{
	int		i;
	int		len;
	int		l;
	int		k = 0;
	char	*ret;
	char	*tmp;
	char	*g_str;

	l = start;
	len = 0;
	g_str = ft_itoa(g_status);
	while (!(check_sep(str[l], " ><|") == 1 || str[l] == '\0'))
		l++;
	if (len == 0)
	{
		env_var[j].value = ft_itoa(g_status); // 함수로 만들기 -> $?뒤의 것들 다 붙이기
		env_var[j].size_v = 1;
		env_var[j].ori = "?";
		return ;
	}
	else
	{
		tmp = malloc(sizeof(char) * l - start + 1);
		while (start < l)
		{
			tmp[k] = str[start];
			k++;
			start++;
		}
		tmp[k] = '\0';
		ret = ft_strdup(g_str);
		ret = ft_strjoin(ret, tmp);
		env_var[j].value = ret; // 함수로 만들기 -> $?뒤의 것들 다 붙이기
		env_var[j].size_v = ft_strlen(ret);
		env_var[j].ori = ft_strjoin("$?", tmp);
	}
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
	sep = " |<\">$";
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
				trans_question_mark(env_var, str, count + 1, j);
			else if (str[count] == ' ' || str[count] == '\0')
			{
				env_var[j].value = "$";
				env_var[j].size_v = 1;
				env_var[j].ori = "";
			}
			else
			{
				while (check_sep(str[count], sep) != 1 && str[count] != '\0')
					count++;
				env_var[j].value = trans_env(env, str, i + 1, count - i - 1);
				env_var[j].ori = strdup_ori(str, i + 1, count - 1);
				env_var[j].size_v = ft_strlen(env_var[j].value);
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
