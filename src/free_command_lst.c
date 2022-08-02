#include "minishell.h"

static void	free_command2(t_cmd_lst *cmd_t)
{
	if (cmd_t->delimiter)
		free(cmd_t->delimiter);
	if (cmd_t->input_path)
		free(cmd_t->input_path);
	if (cmd_t->output_path)
		free(cmd_t->output_path);
	free(cmd_t);
}

static void	free_command(t_cmd_lst *cmd_t)
{
	int	idx;

	if (cmd_t->options_v)
		free(cmd_t->options_v);
	if (cmd_t->input_v)
		free(cmd_t->input_v);
	if (cmd_t->arg_v)
	{
		idx = 0;
		while (idx < cmd_t->arg_c)
			free(cmd_t->arg_v[idx++]);
		free(cmd_t->arg_v);
	}
	if (cmd_t->parsing_v)
	{
		idx = 0;
		while (idx < cmd_t->arg_c)
			free(cmd_t->parsing_v[idx++]);
		free(cmd_t->parsing_v);
	}
}

int	free_command_lst(t_cmd_lst *cmd_t)
{
	t_cmd_lst	*tmp;

	while (cmd_t)
	{
		tmp = cmd_t->next;
		free_command(cmd_t);
		free_command2(cmd_t);
		cmd_t = tmp;
	}
	return (0);
}
