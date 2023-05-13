/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:55:56 by daheepark         #+#    #+#             */
/*   Updated: 2023/05/13 15:26:20 by dapark           ###   ########.fr       */
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
		if (ft_strncmp("", parse->env_var[parse->dollar_cnt].ori, 1) != 0)
			free (parse->env_var[parse->dollar_cnt].ori);
		if (ft_strncmp("", parse->env_var[parse->dollar_cnt].value, 1) != 0)
			free (parse->env_var[parse->dollar_cnt].value);
		parse->dollar_cnt--;
	}
	free (parse->env_var);
	free(parse);
}
