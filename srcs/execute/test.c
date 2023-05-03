#include "../../includes/minishell.h"

t_token *test_token(char *value, t_type type, int pipe, t_token *next)
{
	t_token *t = malloc(sizeof(t_token));
	t->value = value;
	t->type = type;
	t->pipe_flag = pipe;
	t->next = next;
	return (t);
}

t_cmdline *test_cmdline(void)
{
	t_cmdline *cmdline=malloc(sizeof(t_cmdline));
	// t_cmdline *cmdline2=malloc(sizeof(t_cmdline));;
	t_token *t1;
	t_token *t2;
	t_token *t3;
	t_token *t4;
	// t_token *t5, *t6;
	// t_token *t7;

	// t7 = test_token("test/out", STDOUT, 0, NULL);
	// t6 = test_token("3", COMMAND, 0, NULL);
	// t5 = test_token("sleep", COMMAND, 1, t6);
	t4 = test_token("test/b", COMMAND, 0, NULL);
	t3 = test_token("cat", COMMAND, 1, t4);
	t2 = test_token("test/a", COMMAND, 0, t3);
	t1 = test_token("cat", COMMAND, 0, t2);

	// cmdline2->token = t4;
	// cmdline2->token_cnt = 1;
	// cmdline2->next = NULL;

	cmdline->token = t1;
	cmdline->next = NULL;
	
	return (cmdline);
}
