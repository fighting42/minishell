#include "../minishell.h"

t_token *test_token(char *value, t_type type, int pipe, t_token *next)
{
	t_token *t = malloc(sizeof(t_token));
	t->value = value;
	t->type = type;
	t->pipe_flag = pipe;
	t->next = next;
	return (t);
}

t_cmdline test_cmdline()
{
	t_cmdline cmdline;
	t_token *t1, *t2, *t3;
	// t_token *t4, *t5, *t6, *t7;

	// t7 = test_token("test/out", STDOUT, 0, NULL);
	// t6 = test_token("a", COMMAND, 0, t7);
	// t5 = test_token("grep", COMMAND, 0, t6);
	// t4 = test_token("in", STDIN, 1, t5);
	t3 = test_token("a", COMMAND, 0, NULL);
	t2 = test_token("grep", COMMAND, 0, t3);
	t1 = test_token("test", STDIN, 0, t2);
	cmdline.token = t1;
	cmdline.token_cnt = 3;
	cmdline.next = NULL;
	
	return (cmdline);
}