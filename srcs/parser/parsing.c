/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:57:51 by dapark            #+#    #+#             */
/*   Updated: 2023/05/05 22:08:05 by dapark           ###   ########.fr       */
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
		return ("\n");
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

t_dollar	*chk_env(char *str, t_env *env)
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
	sep = " |<>;";
	while (str[i] != '\0')
	{
		quote = quote_status(str[i], quote);
		if ((quote == 2 && str[i] == '$') ||\
			(quote == 0 && str[i] == '$'))
			cnt_dollar++;
		i++;
	}
	env_var = malloc(sizeof(t_dollar) * (cnt_dollar + 1));
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
				env_var[j].value = ft_itoa(g_status);
			else
			{
				while (check_sep(str[count], sep) != 1 && str[count] != '\0')
					count++;
				env_var[j].value = trans_env(env, str, i + 1, count - i - 1);
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

int	is_not_ok_sep(char *str, char *sep)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while(sep[j] != '\0')
		{
			if (str[i] == sep[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	chk_quote_one(char *str, int flag)
{
	int		j;
	char	quote;
	int		chk;

	j = 0;
	chk =0;
	while(str[j] != '\0')
	{
		if ((str[j] == '\'' || str[j] == '\"'))
		{
			chk++;
			if (chk == 1)
				quote = str[j];
			if (flag == 0 && chk != 0)
				return (j);
			if (chk == 1)
				break;
		}
		j++;
	}
	j++;
	while (str[j] != '\0')
	{
		if (str[j] == quote)
			return (j);
		j++;
	}
	return (-1);
}

int	chk_whole_quote(char *str)
{
	int	i;
	int	quote;

	quote = 0;
	i = 0;
	while (str[i] != '\0')
	{
		quote = quote_status(str[i], quote);
		i++;
	}
	if (quote == 1 || quote == 2)
		return (1);
	return (0);
}

t_cmdline	*parsing(char *str, t_env *env)
{
	t_cmdline	*c_head, *c_curr;
	t_token		*t_curr, *t_head;
	t_dollar	*env_var;
	char		**tmp;
	int			i, quote = 0, cnt_split, j, dollar_index;
	int			type;

	i = 0, j = 0, dollar_index = 0;
	if (chk_whole_quote(str) == 1)
	{
		printf("%s", "ERROR: quote error\n"); //따옴표 한 개일 경우
		return (0);
	}
	env_var = chk_env(str, env);
	c_head = malloc(sizeof(t_cmdline));
	c_curr = c_head;
	t_head = create_token();
	t_curr = t_head;
	c_curr->token = t_head;
	cnt_split = count_str(str, " |<>");
	tmp = parse_split(str, cnt_split);
	for (int i = 0; tmp[i] != NULL; i++)
		printf("tmp[%d] : %s\n", i, tmp[i]);
	while (tmp[i] != NULL)
	{
		j = 0;
		while (tmp[i][j] != '\0')
		{
			quote = quote_status(tmp[i][j], quote);
			if (tmp[i][j] == '|')
			{
				t_curr->pipe_flag = 1;
				while (tmp[i][j] != '\0')
				{
					quote = quote_status(tmp[i][j], quote);
					j++;
				}
			}
			else if (tmp[i][j] == '<')
			{
				if (tmp[i][j + 1] == '<')
					type = HEREDOC;
				else
					type = STDIN;
				while (check_sep(tmp[++i][0], " |<>") == 1)
				{
					if ((is_not_ok_sep(tmp[i], "|><")) == 1)
						return (0);
				}
				j = 0;
				while (tmp[i][j] != '\0')
				{
					quote = quote_status(tmp[i][j], quote);
					if ((quote == 2 && tmp[i][j] == '$') ||\
						(quote == 0 && tmp[i][j] == '$'))
					{
						printf(" < quote  : %d\n", quote);
						append_token(t_head, t_curr, env_var[dollar_index].value, type);
						dollar_index++;
						break;
					}
					append_token(t_head, t_curr, tmp[i], type);
					j++;
				}
				t_curr = create_token();
			}
			else if (tmp[i][j] == '>')
			{
				if (tmp[i][j + 1] == '>')
					type = APPEND;
				else
					type = STDOUT;
				while (check_sep(tmp[i + 1][0], " |<>") == 1)
				{
					if ((is_not_ok_sep(tmp[i + 1], "|><")) == 1)
						return (0);
				}
				// if ((quote == 2 && tmp[i][0] == '$') ||\
				// 	(quote == 0 && tmp[i][0] == '$'))
				// {
				printf(" > quote  : %d\n", quote);
				// 	append_token(t_head, t_curr, env_var[dollar_index].value, type);
				// 	dollar_index++;
				// }
				// else
				// 	append_token(t_head, t_curr, tmp[i], type);
				// t_curr = create_token();
				while (tmp[i][j] != '\0')
				{
					quote = quote_status(tmp[i][j], quote);
					j++;
				}
			}
			else if ((quote == 2 && tmp[i][j] == '$') ||\
					(quote == 0 && tmp[i][j] == '$'))
			{
				printf(" $ quote i == %d : %d\n", i, quote);
				append_token(t_head, t_curr, env_var[dollar_index].value, COMMAND);
				t_curr = create_token();
				dollar_index++;
				while (tmp[i][j] != '\0')
				{
					quote = quote_status(tmp[i][j], quote);
					j++;
				}
			}
			else if (tmp[i][j] == ' ')
				j++;
			//띄어쓰기 없이 바로 유효한 따옴표 들어왔을 때 처리
			else if (chk_quote_one(tmp[i], 0) != -1) //두번째 quote만날때까지 무조건 join
			{
				int n = 0; 
				char *temp = (char *)malloc(sizeof(char) * (j + 1));
				while (n++ < j)
					temp[n] = str[n];
				temp[n] = '\0';
				int	k = chk_quote_one(tmp[++i], 1);
				while (k == -1)
				{
					temp = ft_strjoin(temp, tmp[i]);
					k = chk_quote_one(tmp[++i], 1);
				}
				n = 0;
				char *last = (char *)malloc(sizeof(char) * (k + 1));
				while (n++ < k)
					last[n] = str[n];
				last[n] = '\0';
				temp = ft_strjoin(temp, last);
				append_token(t_head, t_curr, temp, COMMAND);
				t_curr = create_token();
				while (tmp[i][j] != '\0')
				{
					quote = quote_status(tmp[i][j], quote);
					j++;
				}
			}
			else if (is_not_ok_sep(tmp[i], "\', \"") == 1 && \
					(chk_quote_one(tmp[i], 0) == -1))
			{
				append_token(t_head, t_curr, remove_quote(tmp[i]), COMMAND);
				t_curr = create_token();
				while (tmp[i][j] != '\0')
				{
					quote = quote_status(tmp[i][j], quote);
					j++;
				}
			}
			else
			{
				if (tmp[i][j + 1] == '\0')
				{
					append_token(t_head, t_curr, tmp[i], COMMAND);
					t_curr = create_token();
				}
				j++;
			}
		}
		i++;
	}
	return (c_head);
}

int main(int argc, char **argv, char **envp)
{
	t_cmdline *str;
	t_token *prt;
	t_env temp;

	temp.value = envp;
	(void)argc;
	(void)argv;

	char *tmp = "echo $? | echo >> \"$PATH\"";
	printf("%s\n", tmp);
	g_status = 0;
	str = parsing(tmp, &temp);
	prt = str->token;
	while (prt)
	{
		printf("value: %s / type: %d / pipe_flag: %d\n", prt->value, prt->type, prt->pipe_flag);
		prt = prt->next;
	}	
	return (0);
}
