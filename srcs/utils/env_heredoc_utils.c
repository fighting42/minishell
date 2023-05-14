/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_heredoc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daheepark <daheepark@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:04:07 by dapark            #+#    #+#             */
/*   Updated: 2023/05/15 02:25:14 by daheepark        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_dollar_heredoc(char *str)
{
	int	cnt_dollar;
	int	i;

	cnt_dollar = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			cnt_dollar++;
			while (str[i + 1] == '$')
				i++;
		}
		i++;
	}
	return (cnt_dollar);
}

void	env_index_heredoc(t_env_h *env_h, t_len_env *len_env)
{
	if (len_env->temp[len_env->k] == '$')
	{
		len_env->len += env_h->env_var[env_h->dollar_index].size_v;
		if (ft_strlen(env_h->env_var[env_h->dollar_index].ori) != 0)
			len_env->k += ft_strlen(env_h->env_var[env_h->dollar_index].ori);
		else
			len_env->k += 1;
		env_h->dollar_index++;
		len_env->chk++;
	}
	else
		len_env->len++;
}

void	dollar_case_heredoc(char *str, t_envval *env_var, \
		t_dollar_idx *dollar_i, t_env *env)
{
	int	count;

	count = dollar_i->i + 1;
	if (str[count] == '?')
		trans_question_mark(env_var, str, count + 1, dollar_i->j);
	else if (str[count] == '$')
		count = dollar_dollar(str, env_var, dollar_i, count);
	else if (str[count] == ' ' || str[count] == '\0')
	{
		env_var[dollar_i->j].value = ft_strdup("$");
		env_var[dollar_i->j].size_v = 1;
		env_var[dollar_i->j].ori = ft_strdup("");
	}
	else
	{
		while (check_sep(str[count], " |<>\'\"$") != 1 && str[count] != '\0')
			count++;
		env_var[dollar_i->j].value = trans_env(env, str, dollar_i->i + 1, \
									count - dollar_i->i - 1);
		env_var[dollar_i->j].ori = strdup_ori(str, dollar_i->i + 1, count - 1);
		if (env_var[dollar_i->j].value != NULL)
			env_var[dollar_i->j].size_v = ft_strlen(env_var[dollar_i->j].value);
	}
	dollar_i->j++;
	dollar_i->i = count;
}

int	len_env_to_str_heredoc(char *str, t_env_h *env_h)
{
	int			ret;
	t_len_env	*len_env;

	len_env = malloc(sizeof(t_len_env));
	init_len_env(len_env);
	len_env->temp = ft_strdup(str);
	while (len_env->temp[++len_env->k] != '\0')
		env_index_heredoc(env_h, len_env);
	env_h->dollar_index = env_h->dollar_index - len_env->chk;
	ret = len_env->len;
	free(len_env->temp);
	free(len_env);
	return (ret);
}
