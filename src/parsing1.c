/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 19:01:52 by mpeharpr          #+#    #+#             */
/*   Updated: 2022/08/04 14:58:33 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    print_structure(t_cmd_lst *cmd_t)
{
    int    idx;

    printf("\n-===- Debugging structure -===-\n");
    printf("- original: |%s|\n", cmd_t->original);
    printf("- binary: |%s|\n", cmd_t->binary);
    printf("- options_c: %d\n", cmd_t->options_c);
    printf("- options_v:\n");
    idx = 0;
    while (idx < cmd_t->options_c)
    {
        printf("        %d:  |%s|\n", idx, cmd_t->options_v[idx]);
        idx++;
    }
    printf("- input_c: %d\n", cmd_t->input_c);
    printf("- input_v:\n");
    idx = 0;
    while (idx < cmd_t->input_c)
    {
        printf("        %d:  |%s|\n", idx, cmd_t->input_v[idx]);
        idx++;
    }
    printf("- arg_c: %d\n", cmd_t->arg_c);
    printf("- arg_v:\n");
    idx = 0;
    while (idx < cmd_t->arg_c)
    {
        printf("        %d:  |%s|\n", idx, cmd_t->arg_v[idx]);
        idx++;
    }
    if (cmd_t->parsing_v)
    {
        printf("- parsing_v:\n");
        idx = 0;
        while (idx < cmd_t->arg_c)
        {
            printf("        %d:  |%s|\n", idx, cmd_t->parsing_v[idx]);
            idx++;
        }
    }
    printf("- output_type: %c\n", cmd_t->output_type);
    printf("- output_path: %s\n", cmd_t->output_path);
    printf("- input_path: %s\n", cmd_t->input_path);
    printf("- next: %p\n", cmd_t->next);
    printf("-===- End of debugging structure -===-\n\n");
    return (0);
}

static int	parse_order(t_cmd_lst *cmd_t, t_list *env)
{
	if (parse_quotes(cmd_t, env) == -1)
		return (-1);
	parse_counts(cmd_t);
	if (cmd_t->options_c > 0)
		parse_options(cmd_t);
	if (cmd_t->input_c > 0)
	{
		if (parse_input(cmd_t) == -1)
			return (-1);
	}
	if (parse_redirections(cmd_t) == -1)
		return (-1);
	print_structure(cmd_t);
	return (0);
}

static t_cmd_lst	*free_cmd_lst_and_ret_null(t_cmd_lst *cmd)
{
	free_command_lst(cmd);
	return (NULL);
}

/*
returns:
	-1 = NULL
	0 = do nothing
*/
static t_cmd_lst	*loop_new_command(t_list *env, int i, char **pipes)
{
	char		**split;
	int			idx;
	t_cmd_lst	*cmd_t;

	cmd_t = malloc(sizeof(t_cmd_lst));
	if (!cmd_t)
		return (NULL);
	initialize_structure(cmd_t);
	split = split_cmd_lst(pipes[i]);
	if (!split)
		return (free_cmd_lst_and_ret_null(cmd_t));
	idx = 0;
	while (split[idx])
		idx++;
	if (trim_whitespaces(&pipes[i]) == -1)
		return (free_cmd_lst_and_ret_null(cmd_t));
	cmd_t->original = pipes[i];
	cmd_t->arg_c = idx;
	cmd_t->arg_v = split;
	cmd_t->binary = cmd_t->arg_v[0];
	if (parse_order(cmd_t, env) == -1)
		return (free_cmd_lst_and_ret_null(cmd_t));
	else
		return (cmd_t);
}

t_cmd_lst	*initialize_command(char *line, t_list *env)
{
	t_cmd_lst	*cmd_t;
	t_cmd_lst	*head_bckp;
	char		**pipe_split;
	int			i;

	pipe_split = ft_split_out_quotes(line, '|');
	if (!pipe_split)
		return (NULL);
	i = 0;
	head_bckp = NULL;
	while (pipe_split[i])
	{
		cmd_t = loop_new_command(env, i, pipe_split);
		if (!cmd_t && !i)
			free_command_lst(head_bckp);
		if (!cmd_t)
			break ;
		if (!i)
			head_bckp = cmd_t;
		else
			ft_cmd_lstadd_back(&head_bckp, cmd_t);
		i++;
	}
	ft_free_2d_table(pipe_split);
	return (head_bckp);
}
