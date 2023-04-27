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
	t_cmdline *cmdline2=malloc(sizeof(t_cmdline));;
	// t_token *t1;
	t_token *t2, *t3;
	//t_token *t4;
	// t_token *t5, *t6, *t7;

	// t7 = test_token("test/out", STDOUT, 0, NULL);
	// t6 = test_token("a", COMMAND, 0, t7);
	// t5 = test_token("grep", COMMAND, 0, t6);
	// t4 = test_token("test2=b", COMMAND, 0, NULL);
	t3 = test_token("922337203685477580", COMMAND, 0, NULL);
	t2 = test_token("exit", COMMAND, 0, t3);
	// t1 = test_token("export", COMMAND, 0, t2);

	// cmdline2->token = t4;
	cmdline2->token_cnt = 1;
	cmdline2->next = NULL;

	cmdline->token = t2;
	cmdline->token_cnt = 2;
	cmdline->next = NULL;
	
	return (cmdline);
}
