/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils2.C                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 00:37:40 by maxime            #+#    #+#             */
/*   Updated: 2022/08/03 14:06:41 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_next_id(t_cmd_lst *cmd_t, int size, char **arr, char *input)
{
	int		i;
	int		j;
	char	*diff;

	printf("Searching the right id for |%s| in the array:\n", input);
	for (int c = 0; arr[c]; c++)
		printf("	%d: |%s|\n", c, arr[c]);

	i = 0;
	while (i < size)
	{
		diff = ft_strnstr(arr[i], input, -1);
		if (diff)
		{
			j = 0;
			while (cmd_t->parsing_v[i][j])
			{
				if (cmd_t->parsing_v[i][j] == 'S')
					break ;
				j++;
			}
			if ((size_t)j == ft_strlen(cmd_t->parsing_v[i]))
			{
				printf("Found id %d: |%s|\n\n", i, arr[i]);
				return (i);
			}
		}
		i++;
	}
	return (-1);
}

int	free_and_return(char *str)
{
	free(str);
	return (-1);
}