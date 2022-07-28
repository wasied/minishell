/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 23:11:22 by mpeharpr          #+#    #+#             */
/*   Updated: 2022/07/28 16:31:03 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Make sure that there is an even amount of single & doubles quotes in
the command line - this way, we can make sure all quotes are closing and
we don't have any unclosed quote as specified in the subject */
static int	quotes_even(char *cmd)
{
	int	i;
	int	simples;
	int	doubles;

	simples = 0;
	doubles = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
			simples++;
		else if (cmd[i] == '\"')
			doubles++;
		i++;
	}
	return (simples % 2 == 0 && doubles % 2 == 0);
}

static int	alloc_last_split(char **arritem, char *cmd, int i, int last)
{
	if (i > last)
	{
		*arritem = ft_substr(cmd, last, i - last);
		if (!*arritem)
			return (-1); // Memory error
	}
	return (0);
}

static void	init_split(char *cmd, int *idx, int *capt, int *i)
{
	*idx = 0;
	*capt = 0;
	*i = 0;
	while (cmd[*i] && cmd[*i] == ' ')
		(*i)++;
}

/* Split the str with spaces + simple & double quotes */
static int	split_with_quotes(char *cmd, char **arr, char *parsing)
{
	int	i;
	int	idx;
	int	capt;
	int	last;

	init_split(cmd, &idx, &capt, &i);
	last = i;
	while (cmd[i])
	{
		if (cmd[i] && parsing[i] != 'E' && (cmd[i] == '\'' || cmd[i] == '\"') && cmd[i + 1])
			capt = !capt;
		else if (cmd[i] && cmd[i] == ' ' && !capt)
		{
			arr[idx] = ft_substr(cmd, last, i - last);
			if (!arr[idx])
				return (-1); // Memory error
			idx++;
			while (cmd[i + 1] && cmd[i + 1] == ' ')
				i++;
			last = i + 1;
		}
		i++;
	}
	return (alloc_last_split(&arr[idx], cmd, i, last));
}

/* Splitting the command line and return a 2D array */
char	**split_cmd_lst(char *cmd)
{
	int		splitc;
	char	**splitv;
	int		idx;
	char	*parsing;

	if (!cmd)
		return (NULL); // In case cmd is invalid
	parsing = ft_strdup_char('M', ft_strlen(cmd));
	if (!quotes_even(cmd))
		return (NULL); // In case quotes are not closed, SHOULD STILL WORK
	splitc = count_splits(cmd, parsing);
	if (splitc <= 0)
		return (NULL); // In case cmd is empty
	splitv = malloc(sizeof(char *) * (splitc + 1));
	if (!splitv)
		return (NULL); // In case of memory error
	idx = 0;
	while (idx <= splitc)
		splitv[idx++] = NULL;
	if (split_with_quotes(cmd, splitv, parsing) == -1)
	{
		free(parsing);	
		return (free_split(splitv));
	}
	free(parsing);
	return (splitv);
}
