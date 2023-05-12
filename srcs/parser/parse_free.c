/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:55:56 by daheepark         #+#    #+#             */
/*   Updated: 2023/05/12 23:27:06 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_parse(t_parse *parse)
{
	int	i;

	i = -1;
	while (parse->tmp[++i])
	{
		printf("free tmp %s\n", parse->tmp[i]);
		free (parse->tmp[i]);
	}
	free (parse->tmp);
	// while (parse->dollar_cnt >= 0)
	// {
	// 	free (parse->env_var[parse->dollar_cnt].ori);
	// 	free (parse->env_var[parse->dollar_cnt].value);
	// 	parse->dollar_cnt--;
	// }
	// free (parse->env_var);
}
