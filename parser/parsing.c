/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:57:51 by dapark            #+#    #+#             */
/*   Updated: 2023/04/10 22:46:02 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*chk_env(char **envp, char *str, int start, int size)
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
	while (envp[i] != '\0')
	{
		if (ft_strncmp(envp[i], temp, size) == 0)
			break ;
		i++;
	}
	free(temp);
	while (envp[i][len] != '\0')
		len++;
	len = len - size + 1;
	ret = malloc(sizeof(char) * (len + 1));
	j = 0;
	while (j < len + 1)
	{
		ret[j] = envp[i][size + 1];
		j++;
		size++;
	}
	ret[j] = '\0';
	return (ret);
}

int	quote_status(char c, int quote)
{
	if (c == '\'')
	{
		if (quote == 1)
			return (0);
		else if (quote == 2)
			return (2);
		else
			return (1);
	}
	else if (c == '\"')
	{
		if (quote == 2)
			return (0);
		else if (quote == 1)
			return (1);
		else
			return (2);
	}
	return (quote);
}



t_cmdline	*parsing(char *str, char **envp)
{
	int			i, count, cnt_dollar, j;
	int			quote;
	t_cmdline	command;
	t_dollar	*env_var;
	
	char	sep = " |<>";
	i = 0, j = 0;
	cnt_dollar = 0;
	quote = 0;
	
	while (str[i] != '\0')
	{
		quote = quote_status(str[i], quote);
		if (quote == 2 && str[i] == '&' ||\
			quote == 0 && str[i] == '&')
			cnt_dollar += 1;
		i++;
	}
	env_var = malloc(sizeof(t_dollar) * cnt_dollar + 1);
	while (str[i] != '\0')
	{
		quote = quote_status(str[i], quote);
		if (quote == 2 && str[i] == '&' ||\
			quote == 0 && str[i] == '&')
		{
			count = i;
				return (-1);
			while (check_sep(str[count], sep) != 1)
				count++;
			env_var[j].value = chk_env(envp, str, i + 1, count - i - 1);
			j++;
			i = count ;
		}
		else
			i++;	
	}
	env_var[j].value = 0;
	count = count_str(str, sep);
	command.cmd = parse_split(count); //구분자대로 parsing
}
