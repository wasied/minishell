/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 02:50:08 by mpeharpr          #+#    #+#             */
/*   Updated: 2022/08/03 13:41:37 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		len;
	char	*ret;
	int		i;
	int		j;

	len = ft_strlen(s1) + ft_strlen(s2);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		ret[i] = s2[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	return (ret);
}

int	ft_free_2d_table(char **to_free)
{
	int	i;

	i = 0;
	while (to_free[i])
		free(to_free[i++]);
	free(to_free);
	return (-1);
}

/* Checks if the string contains a character */
int	ft_strincludes(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/* Concatenate 2 strings */
size_t	ft_strlcat(char *dst, char const *src, size_t nbr)
{
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen((char *)src);
	if (nbr >= dst_len)
	{
		dst += dst_len;
		nbr -= dst_len;
		ft_strlcpy(dst, src, nbr);
		return (dst_len + src_len);
	}
	else
		return (nbr + src_len);
	return (0);
}

/* Convert a splitted 2d array into a single string separated by a character */
char	*ft_arrjoin(char **split, size_t len, char sep)
{
	size_t	i;
	size_t	strlen;
	char	*str;

	i = 0;
	strlen = 0;
	while (i < len)
		strlen += ft_strlen(split[i++]) + 1;
	str = malloc(strlen * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < strlen)
		str[i++] = '\0';
	i = 0;
	while (i < len)
	{
		ft_strlcat(str, split[i], -1);
		if (i < len - 1)
			str[ft_strlen(str)] = sep;
		i++;
	}
	return (str);
}
