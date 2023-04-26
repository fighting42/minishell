/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:57:51 by dapark            #+#    #+#             */
/*   Updated: 2023/04/26 18:29:16 by dapark           ###   ########.fr       */
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
			env_var[j].value = trans_env(env, str, i + 1, count - i - 1);
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

int		count_colon(char *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 1;
	while (str[i] != '\0')
	{
		if (str[i] == ';')
			cnt++;
		i++;
	}
	return (cnt);
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
			if (flag == 0)
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
	while (str[i] != '\0')
	{
		quote = quote_status(str[i], quote);
		i++;
	}
	if (quote == 1)
		return (1);
	return (0);
}

t_cmdline	*parsing(char *str, t_env *env)
{
	t_cmdline	*c_head, *c_curr;
	t_token		*t_curr, *t_head, *t_prev;
	t_dollar	*env_var;
	char		**tmp;
	int			i, quote, cnt_split, j, cnt_colon, dollar_index;
	int			*r_flag;

	i = 0, j = 0, dollar_index = 0;
	if (chk_whole_quote(str) == 1)
	{
		printf("%s", "ERROR: quote error\n"); //따옴표 한 개일 경우
		return (0);
	}
	env_var = chk_env(str, env);
	cnt_colon = count_colon(str);
	c_head = malloc(sizeof(t_cmdline) * cnt_colon);
	c_curr = c_head;
	c_curr->token = create_token();
	t_head = c_curr->token;
	cnt_split = count_str(str, " |<>;");
	tmp = parse_split(str, cnt_split, env_var);
	int s = 0;
	while (tmp[i][j] != '\0')
	{
		j = 0;
		while (tmp[i][j] != '\0')
		{
			quote = quote_status(str[i], quote);
			if (tmp[i][j] == ';')
			{
				c_curr = c_curr->next;
				c_curr->token = create_token();
				t_curr = c_curr->token;
			}
			else if (tmp[i][j] == '|')
			{
				t_curr->pipe_flag = 1;
			}
			else if (tmp[i][j] == '<')
			{
				if (tmp[i][j + 1] == '<')
					r_flag = HEREDOC;
				//	t_curr->type = HEREDOC;
				else
					r_flag = STDIN;
				//	t_curr->type = STDIN;
				while (check_sep(tmp[++i][0], " |<>;") == 1)
				{
					if ((is_not_ok_sep(tmp[i], "|><;")) == 1)
						return (0);
				}
				t_curr->value = tmp[i];
				t_curr->next = create_token();
				t_curr = t_curr->next;
				i++;
				j = 0;
			}
			else if (tmp[i][j] == '>')
			{
				if (tmp[i][j + 1] == '>')
					r_flag = APPEND;
				//	t_curr->type = APPEND;
				else
					r_flag = STDOUT;
				//	t_curr->type = STDOUT;
				while (check_sep(tmp[++i][0], " |<>;") == 1)
				{
					if ((is_not_ok_sep(tmp[i], "|><;")) == 1)
						return (0);
				}
				t_curr->value = tmp[i];
				t_curr->next = create_token(0);
				t_curr = t_curr->next;
				i++;
				j = 0;
			}
			else if ((quote == 2 && tmp[i][j] == '$') ||\
					(quote == 0 && tmp[i][j] == '$'))
			{
				t_curr->value = env_var[dollar_index].value;
				t_curr->type = COMMAND;
				dollar_index++;
				t_curr->next = create_token(0);
				t_curr = t_curr->next;
				i++;
				j = 0;
			}
			else if (check_sep(tmp[i][0], " |<>;"))
			{
				j = chk_quote_one(tmp[i], 0);
				if (j != -1) //두번째 quote만날때까지 무조건 join
				{
					int n = 0;
					char *tmp = (char *)malloc(sizeof(char) * (j + 1));
					while (n++ < j)
						tmp[n] = str[n];
					tmp[n] = '\0';
					int	k = chk_quote_one(&tmp[++i], 1);
					while (k == -1)
					{
						tmp = ft_strjoin(tmp, &tmp[i]);
						k = chk_quote_one(&tmp[++i], 1);
					}
					n = 0;
					char *last = (char *)malloc(sizeof(char) * (k + 1));
					while (n++ < k)
						last[n] = str[n];
					last[n] = '\0';
					tmp = ft_strjoin(tmp, last);
					t_curr->value = tmp; //띄어쓰기 없이 바로 유효한 따옴표 들어왔을 때 처리해야됨
				}
				else
					t_curr->value = remove_quote(tmp[i]);
				t_curr->type = COMMAND;
				t_curr->next = create_token(0);
				t_curr = t_curr->next;
				i++;
				j = 0;
			}
			else
				j++;
		}
		i++;
	}
	c_curr->next = 0;
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

	char *tmp = "ls -al | echo $USER | echo \'$USER\'";
	str = parsing(tmp, &temp);
	prt = str->token;
	while (!prt)
	{
		printf("value: %s / type: %d / pipe_flag: %d\n", prt->value, prt->type, prt->pipe_flag);
		prt = prt->next;
	}	

	return (0);
}
