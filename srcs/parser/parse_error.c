/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:32:20 by dapark            #+#    #+#             */
/*   Updated: 2023/05/06 21:24:27 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error_case(char *str)
{
	if (chk_whole_quote(str, 0) == 1)
	{
		printf("%s", "ERROR: quote error\n"); //따옴표 한 개일 경우
		return (1);
	}
	return (0);
}