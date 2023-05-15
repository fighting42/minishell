/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:55:56 by daheepark         #+#    #+#             */
/*   Updated: 2023/05/15 17:45:49 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_parse(t_parse *parse)
{
	int	i;

	i = -1;
	while (parse->tmp[++i])
		free (parse->tmp[i]);
	free (parse->tmp);
	parse->dollar_cnt--;
	while (parse->dollar_cnt >= 0)
	{
		if (parse->env_var[parse->dollar_cnt].ori != NULL)
			free (parse->env_var[parse->dollar_cnt].ori);
		if (parse->env_var[parse->dollar_cnt].value != NULL)
			free (parse->env_var[parse->dollar_cnt].value);
		parse->dollar_cnt--;
	}
	free (parse->env_var);
	free(parse);
}

void	*end_program(t_parse *parse, int ret)
{
	free(parse->c_head->token);
	free(parse->c_head);
	free_parse(parse);
	if (ret == 2)
		return (print_error(errmsg(TRUE, NULL, NULL, \
		"ambiguous redirect"), FALSE, 1));
	else
		return (print_error(errmsg(TRUE, NULL, NULL, \
		"syntax error"), FALSE, 258));
}
