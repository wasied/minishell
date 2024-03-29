/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_out_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennafl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 19:21:53 by mbennafl          #+#    #+#             */
/*   Updated: 2022/08/05 12:58:10 by mbennafl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	count_words(const char *str, char sep, int *nbr_words)
{
	int	i;

	i = -1;
	if (str[0] == sep)
	{
		print_err_unclosed_pipe(nbr_words);
		return ;
	}
	while (str[++i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (!str[i])
		{
			print_err_unclosed_pipe(nbr_words);
			return ;
		}
		if (i && str[i - 1] == sep && str[i] != sep)
			(*nbr_words)++;
		if (str[i] == '\'' && closing_idx(str, i + 1, '\'') != -1)
			i = closing_idx(str, i + 1, '\'');
		else if (str[i] == '\"' && closing_idx(str, i + 1, '\"') != -1)
			i = closing_idx(str, i + 1, '\"');
	}
}

static char	**malloc_words(const char *str, char sep)
{
	int		nbr_words;
	char	**ret;

	if (str[0] != sep)
		nbr_words = 1;
	else
		nbr_words = 0;
	count_words(str, sep, &nbr_words);
	if (nbr_words == -1)
		return (NULL);
	ret = malloc(sizeof(char *) * (nbr_words + 1));
	if (!ret)
		return (NULL);
	ret[nbr_words] = NULL;
	return (ret);
}

static int	find_next_sep_out_quotes_idx(const char *str, int i, char sep)
{
	int	capt_single;
	int	capt_double;

	capt_single = 0;
	capt_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !capt_double && \
		(capt_single || closing_idx(str, i + 1, '\'') != -1))
			capt_single = !capt_single;
		else if (str[i] == '\"' && !capt_single && \
		(capt_double || closing_idx(str, i + 1, '\"') != -1))
			capt_double = !capt_double;
		else if (str[i] == sep && !capt_single && !capt_double)
			return (i);
		i++;
	}
	return (i);
}

static char	**ft_split_out_quotes_loop(const char *str, char sep, char **ret)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (!str[i])
			break ;
		ret[j] = malloc(sizeof(char) * (-i + 1 + \
			find_next_sep_out_quotes_idx(str, i, sep)));
		if (!ret[j])
		{
			ft_free_2d_table(ret);
			return (NULL);
		}
		ft_strlcpy(ret[j], &str[i], \
			find_next_sep_out_quotes_idx(str, i, sep) - i + 1);
		i = find_next_sep_out_quotes_idx(str, i, sep);
		j++;
	}
	return (ret);
}

char	**ft_split_out_quotes(const char *str, char sep)
{
	char	**ret;

	if (!str)
		return (NULL);
	ret = malloc_words(str, sep);
	if (!ret)
		return (NULL);
	if (!ft_split_out_quotes_loop(str, sep, ret))
		return (NULL);
	return (ret);
}
