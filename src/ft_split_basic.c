/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_basic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennafl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 19:59:02 by mbennafl          #+#    #+#             */
/*   Updated: 2022/07/16 20:05:49 by mbennafl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**malloc_words(const char *str, char sep)
{
	int		i;
	int		nbr_words;
	char	**ret;

	if (str[0] != sep)
		nbr_words = 1;
	else
		nbr_words = 0;
	i = 1;
	while (str[i])
	{
		if (str[i] && str[i - 1] == sep && str[i] != sep)
			nbr_words++;
		i++;
	}
	ret = malloc(sizeof(char *) * (nbr_words + 1));
	if (!ret)
		return (NULL);
	ret[nbr_words] = NULL;
	return (ret);
}

static char	**fill(const char *str, char sep, char **ret)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j])
	{
		while (str[j] && str[j] == sep)
			j++;
		if (!str[j])
			break ;
		ret[i] = malloc(sizeof(char) * (ft_strlensep(&str[j], sep) + 1));
		if (!ret[i])
		{
			ft_free_2d_table(ret);
			return (NULL);
		}
		ft_strlcpy(ret[i], &str[j], ft_strlensep(&str[j], sep) + 1);
		while (str[j] && str[j] != sep)
			j++;
		i++;
	}
	return (ret);
}

char	**ft_split(const char *str, char sep)
{
	char	**ret;

	ret = malloc_words(str, sep);
	if (!ret)
		return (NULL);
	if (!fill(str, sep, ret))
		return (NULL);
	return (ret);
}
