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

t_cmdline test_cmdline(void)
{
	t_cmdline cmdline;
	// t_token *t1, 
	t_token *t2, *t3;
	t_token *t4;
	// t_token *t5, *t6, *t7;

	// t7 = test_token("test/out", STDOUT, 0, NULL);
	// t6 = test_token("a", COMMAND, 0, t7);
	// t5 = test_token("grep", COMMAND, 0, t6);
	t4 = test_token("ca", COMMAND, 0, NULL);
	t3 = test_token("end2", HEREDOC, 0, t4);
	t2 = test_token("end1", HEREDOC, 0, t3);
	// t1 = test_token("end1", HEREDOC, 0, t2);
	cmdline.token = t2;
	cmdline.token_cnt = 3;
	cmdline.next = NULL;
	
	return (cmdline);
}

// #include <string.h>
// int main(int arvc, char **argv, char **envp)
// {
// 	char path[10] = "/bin";
// 	char **cmd;
// 	cmd = malloc(sizeof(char *) * 2);
// 	cmd[0] = "a";
// 	cmd[1] = NULL;
// 	if (execve(path, cmd, envp) == -1)
// 		printf("%s\n", strerror(0));
// 	return (0);
// }