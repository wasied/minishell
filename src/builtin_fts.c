/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:04:24 by mbennafl          #+#    #+#             */
/*   Updated: 2022/07/08 15:41:56 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_echo(int fd, t_cmd_lst *cmd)
{
	int	err;
	int	i;
	int	newline;

	if (!cmd->input_v)
		return (9);
	i = 0;
	newline = 1;
	while (i < cmd->input_c)
	{
		err = ft_putstr_fd(fd, cmd->input_v[i]);
		if (err == -1)
			return (0);		//IS THAT ENOUGH? PRINTING THE ERR IN TREAT CMD FUNCTION
		if (cmd->input_v[i + 1] && write(fd, " ", 1) == -1)
			return (0);
		if (cmd->options_v && cmd->options_v[i] && \
			!ft_strncmp(cmd->options_v[i], "-n", 3))
			newline = 0;
		i++;
	}
	if (newline)
		err = write(fd, "\n", 1);
	if (err == -1)
		return (0);		//IS THAT ENOUGH? PRINTING THE ERR IN TREAT CMD FUNCTION
	return (9);
}

int	bi_cd(int fd, t_cmd_lst *cmd)
{
	int	err;

	(void)fd;

	if (!cmd->input_v || !cmd->input_v[0])
		return (0);
	err = chdir(cmd->input_v[0]);
	if (err == -1)
		return (0);		//IS THAT ENOUGH? PRINTING THE ERR IN TREAT CMD FUNCTION
	return (9);
}

int	bi_pwd(int fd)
{
	char	*cwd;
	int		err;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (0);		//IS THAT ENOUGH? PRINTING THE ERR IN TREAT CMD FUNCTION
	err = ft_putstr_fd(fd, cwd);
	if (err == -1)
		return (0);		//IS THAT ENOUGH? PRINTING THE ERR IN TREAT CMD FUNCTION
	if (write(fd, "\n", 1) == -1)
		return (0);		//IS THAT ENOUGH? PRINTING THE ERR IN TREAT CMD FUNCTION
	return (9);
}

int	bi_exit(int fd, t_list **env)
{
	(void)fd;
	ft_lstclear(env);
	rl_clear_history();
	exit(0);
}
