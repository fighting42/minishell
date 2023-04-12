/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daheepark <daheepark@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:57:51 by dapark            #+#    #+#             */
/*   Updated: 2023/04/13 02:10:29 by daheepark        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*trans_env(char **envp, char *str, int start, int size)
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
	while (envp[i] != 0)
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

t_dollar	*chk_env(char *str, char **envp)
{
	t_dollar	*env_var;
	char		*sep;
	int			i;
	int			j;
	int			quote;
	int			cnt_dollar;
	int			count;

	i = 0; 
	j = 0;
	cnt_dollar = 0;
	quote = 0;
	sep = " |<>";
	while (str[i] != '\0')
	{
		quote = quote_status(str[i], quote);
		if (quote == 2 && str[i] == '$' ||\
			quote == 0 && str[i] == '$')
			cnt_dollar++;
		i++;
	}
	printf("$: %d\n", cnt_dollar);
	env_var = malloc(sizeof(t_dollar) * cnt_dollar);
	i = 0;
	while (str[i] != '\0')
	{
		quote = quote_status(str[i], quote);
		if ((quote == 2 && str[i] == '$') ||\
			(quote == 0 && str[i] == '$'))
		{
			count = i + 1;
			while (check_sep(str[count], sep) != 1 && str[count] != '\0')
				count++;
			env_var[j].value = trans_env(envp, str, i + 1, count - i - 1);
			printf("%s\n", env_var[j].value);
			j++;
			i = count ;
		}
		else
			i++;	
	}
	env_var[j].value = 0;
	return (env_var);
}

t_cmdline	*parsing(char *str, char **envp)
{
	t_cmdline	*c_head, *c_curr, *c_prev;
	t_token		*t_head, *t_curr, *t_prev;
	t_dollar	*env_var;
	char		**tmp;
	int			i, quote, count, j;

	i = 0, j = 0;
	env_var = chk_env(str, envp);
	count = count_str(str, " |<>");
	tmp = parse_split(str, count, env_var); //구분자대로 parsing
	while (tmp[i][j] != '\0') //구분자와 같이 잘린 commands
	{
		if (i == 0)
		{
			c_head = malloc(sizeof(t_cmdline) * 1);

		}
		quote = quote_status(str[i], quote);
		if (str[i] == '|')
		{
			c_curr = malloc(sizeof(t_cmdline) * 1);
			c_head->next = c_curr;
		}
		else if (str[i] == '<')
		{

		}
		else if (str[i] == '>')
		
		else
		{
			if ((quote == 2 && str[i] == '$') ||\
				(quote == 0 && str[i] == '$'))
			{

			}
		}
	}
}

int main(int argc, char **argv, char **envp)
{
	char *str;
	if (argc != 1)
		str = parsing(argv[1], envp);
	return (0);
}
