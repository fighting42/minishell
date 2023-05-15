/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:22:27 by dapark            #+#    #+#             */
/*   Updated: 2023/05/15 17:46:47 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirection_env(char *str, t_parse *parse)
{
	t_re_env	*env_re;

	env_re = malloc(sizeof(t_re_env));
	init_t_re_env(env_re);
	while (str[++env_re->i] != '\0')
	{
		env_re->quote = quote_status(str[env_re->i], env_re->quote);
		env_flag(str, env_re);
		while (check_sep(str[env_re->i], " ") == 1 && \
		str[env_re->i] != '\0' && env_re->flag == 1)
			env_re->i++;
		if (env_re->quote == 1)
			continue ;
		if ((env_re->quote == 0 || env_re->quote == 2) && \
		str[env_re->i] == '$' && env_re->flag == 1)
		{
			if (parse->env_var[env_re->dollar++].value == NULL)
				return (2);
		}
	}
	return (0);
}

void	env_flag(char *str, t_re_env *env_re)
{
	if (check_sep(str[env_re->i], "><") == 1)
	{
		env_re->i++;
		env_re->flag = 1;
		if (check_sep(str[env_re->i], "<") == 1)
		{
			env_re->i++;
			env_re->flag = 0;
		}
	}
}

void	init_t_re_env(t_re_env *env_re)
{
	env_re->dollar = 0;
	env_re->flag = 0;
	env_re->i = -1;
	env_re->quote = 0;
}
