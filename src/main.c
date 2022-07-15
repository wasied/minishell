/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:57:32 by mbennafl          #+#    #+#             */
/*   Updated: 2022/07/15 23:07:01 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_structure(t_cmd_lst *cmd_t)
{
	int	idx;

	printf("\n-===- Debugging structure -===-\n");
	printf("- original: |%s|\n", cmd_t->original);
	printf("- binary: |%s|\n", cmd_t->binary);
	
	printf("- options_c: %d\n", cmd_t->options_c);
	printf("- options_v:\n");
	idx = 0;
	while (idx < cmd_t->options_c)
	{
		printf("	%d:  |%s|\n", idx, cmd_t->options_v[idx]);
		idx++;
	}
	
	printf("- input_c: %d\n", cmd_t->input_c);
	printf("- input_v:\n");
	idx = 0;
	while (idx < cmd_t->input_c)
	{
		printf("	%d:  |%s|\n", idx, cmd_t->input_v[idx]);
		idx++;
	}

	printf("- arg_c: %d\n", cmd_t->arg_c);
	printf("- arg_v:\n");
	idx = 0;
	while (idx < cmd_t->arg_c)
	{
		printf("	%d:  |%s|\n", idx, cmd_t->arg_v[idx]);
		idx++;
	}
	
	printf("- parsing_v:\n");
	idx = 0;
	while (idx < cmd_t->input_c)
	{
		printf("	%d:  |%s|\n", idx, cmd_t->parsing_v[idx]);
		idx++;
	}

	printf("- next: %p\n", cmd_t->next);
	printf("-===- End of debugging structure -===-\n\n");
	return (0);
}

void	pipe_test_to_del(t_list **env)
{
/*	Pipe test	*/
	t_cmd_lst	*cmd1;
	t_cmd_lst	*cmd2;
	t_cmd_lst	*cmd3;

	cmd1 = initialize_command("ls", *env);
	cmd2 = initialize_command("exit", *env);
	cmd3 = initialize_command("wc -l", *env);
	cmd1->next = cmd2;
	cmd2->next = cmd3;
	cmd3->next = 0;
	ft_pipe(env, cmd1);
/*	Pipe		*/
}

int	new_cmd(t_list **env)
{
	char	*cmd_str;
	t_cmd_lst	*cmd_t;

	g_pid = 0;
	cmd_str = readline(SHELL_PREFIX); //PROTECT AGAINST READLINE ERRORS?
	if (!cmd_str)
		bi_exit(-1, env, NULL);
	if (cmd_str[0] != '\0')
	{
		add_history(cmd_str);
		cmd_t = initialize_command(cmd_str, *env);
		if (!cmd_t)
			print_error(0);
		if (cmd_t && !run(env, cmd_t))
			print_error(0);		//IS THAT ENOUGH?
		if (cmd_t)
			free_command_lst(cmd_t);
		if (!update_env_return(env))
			print_error(0);		//IS THAT ENOUGH?
	}
	if (cmd_str)
		free(cmd_str);
	new_cmd(env);
	return (9);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_list	*env;

	argc = (int)argc;
	argv = (char **)argv;
	env = NULL;
	init_env_list(&env, envp); // Still need to manage errors
	signals_init();
	if (!new_cmd(&env))
		return (0);//TREAT ERROR WITH ERRNO
	return (0);
}
