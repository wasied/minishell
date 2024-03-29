/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennafl </var/mail/mbennafl>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:33:55 by mbennafl          #+#    #+#             */
/*   Updated: 2022/08/04 20:35:16 by mbennafl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoll_isvalid(const char *str)
{
	int	i;

	i = 0;
	if (ft_is_a_whitespace_or_empty_string(str) == 9)
		return (0);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i])
		return (0);
	return (9);
}

static void	ft_atoll_start_idx_and_sign(const char *str, size_t *i, \
int *sign)
{
	while (str[*i] && (str[*i] == 32 || (str[*i] >= 9 && str[*i] <= 13)))
		(*i)++;
	if (str[*i] == '-')
		*sign = -1;
	if (str[*i] == '+' || str[*i] == '-')
		(*i)++;
}

int	ft_atoll_mod_256(const char *str)
{
	long long	val;
	size_t		i;
	int			sign;

	i = 0;
	val = 0;
	sign = 1;
	if (!ft_atoll_isvalid(str))
	{
		errno = -735;
		return (-1);
	}
	ft_atoll_start_idx_and_sign(str, &i, &sign);
	while (str[i] >= '0' && str[i] < '9')
	{
		val += str[i] - '0';
		if (str[i + 1] > 47 && str[i + 1] < 58)
			val *= 10;
		i++;
	}
	return ((val * sign) % 256);
}
