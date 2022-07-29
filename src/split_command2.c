/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:17:50 by maxime            #+#    #+#             */
/*   Updated: 2022/07/29 18:57:46 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Free the split and return NULL in case of an error */
char	**free_split(char **arr)
{
	int	idx;

	idx = 0;
	while (arr[idx])
		free(arr[idx++]);
	free(arr);
	return (NULL);
}

/* Count the amount of splits we will have in order to pre-allocate */
int	count_splits(char *cmd, char *parsing)
{
	size_t	i;
	int		idx;
	int		capt;

	idx = 0;
	capt = 0;
	i = 0;
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] == ' ' && !capt)
			i++;
		if (cmd[i] && parsing[i] != 'E' && \
		(cmd[i] == '\'' || cmd[i] == '\"') && cmd[i + 1])
		{
			if (!capt)
				idx++;
			capt = !capt;
		}
		else if (cmd[i] && cmd[i] != ' ' && !capt)
			idx++;
		i++;
		if (i < ft_strlen(cmd)) {
			while (cmd[i] && cmd[i] != ' ' && !capt)
				i++;
		}
		else
			i = ft_strlen(cmd);
	}
	return (idx);
}
