/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:18:03 by hdurand           #+#    #+#             */
/*   Updated: 2019/09/05 17:14:52 by hdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	ft_isspace(const char *str, int *i)
{
	*i = 0;
	while (str[*i] == '\t' || str[*i] == '\v' || str[*i] == '\n'
		|| str[*i] == '\r' || str[*i] == '\f' || str[*i] == 32)
		*i = *i + 1;
}

int	r_atoi(const char *strf)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (strf[i] > 47 && strf[i] < 58 && i < 10)
	{
		if (i == 9 && result > 214748364 && strf[i] - 48 >= 8)
			return (0);
		result = result * 10 + (strf[i] - 48);
		i++;
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	i;

	sign = 1;
	ft_isspace(str, &i);
	if (ft_isdigit(&str[i]) == 0)
		return (0);
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
		{
			if (str[i] == '-')
				sign = sign * -1;
			i++;
		}
		if (str[i] > 47 && str[i] < 58)
			return (r_atoi(&str[i]) * sign);
		else
			return (0);
	}
	return (0);
}
