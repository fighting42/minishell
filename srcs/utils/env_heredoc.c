/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:06:52 by dapark            #+#    #+#             */
/*   Updated: 2023/05/12 21:33:33 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_envval	*chk_env_heredoc(char *str, t_env *env)
{
	t_envval		*env_var;
	t_dollar_idx	*dollar_i;	

	env_var = malloc(sizeof(t_envval) * (count_dollar_heredoc(str) + 1));
	dollar_i = malloc(sizeof(t_dollar_idx) * 1);
	dollar_i->i = 0;
	dollar_i->j = 0;
	while (str[dollar_i->i] != '\0')
	{
		if (str[dollar_i->i] == '$')
			dollar_case_heredoc(str, env_var, dollar_i, env);
		else
			dollar_i->i++;
	}
	env_var[dollar_i->j].value = NULL;
	free(dollar_i);
	return (env_var);
}

void	add_env_val_heredoc(t_command *com, t_env_h *env_h, char *ret)
{
	while (env_h->env_var[env_h->dollar_index].value[com->e] != '\0')
	{
		ret[com->r] = env_h->env_var[env_h->dollar_index].value[com->e];
		com->r++;
		com->e++;
	}
	com->t += ft_strlen(env_h->env_var[env_h->dollar_index].ori);
	com->t += 1;
}

void	change_env_var_heredoc(t_command *com, t_env_h *env_h, char *ret)
{
	while (com->temp[com->t] != '\0')
	{
		if (com->temp[com->t] == '$')
		{
			com->e = 0;
			add_env_val_heredoc(com, env_h, ret);
			env_h->dollar_index++;
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

char	*env_to_str_heredoc(char *str, t_env_h *env_h)
{
	int			len;
	char		*ret;
	t_command	*com;

	com = malloc(sizeof(t_command));
	init_t_command(com);
	com->temp = str;
	len = len_env_to_str_heredoc(str, env_h);
	ret = (char *)malloc(sizeof(char) * len + 1);
	change_env_var_heredoc(com, env_h, ret);
	free(com);
	return (ret);
}

char	*env_str_heredoc(char *str, t_env *env)
{
	t_env_h	*env_h;
	char	*ret;

	env_h = malloc(sizeof(env_h));
	env_h->dollar_index = 0;
	env_h->env_var = chk_env_heredoc(str, env);
	ret = env_to_str_heredoc(str, env_h);
	free(env_h->env_var);
	free(env_h);
	return (ret);
}
