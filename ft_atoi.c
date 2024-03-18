/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:31:38 by shamdoun          #+#    #+#             */
/*   Updated: 2024/03/18 00:48:58 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	o_return(int sign)
{
	if (sign < 0)
		return (0);
	return (-1);
}

unsigned char	*remove_spaces(unsigned char *s)
{
	while (*s == ' ' || *s == '\t'
		|| *s == '\n' || *s == '\r'
		|| *s == '\v' || *s == '\f')
		s++;
	return (s);
}

unsigned char	*find_sign(unsigned char *s, int *sign)
{
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			(*sign) *= -1;
		s++;
	}
	return (s);
}

int	ft_atoi(const char *str)
{
	int				sign;
	long			result;
	unsigned char	*s;

	s = (unsigned char *)str;
	result = 0;
	sign = 1;
	s = remove_spaces(s);
	s = find_sign(s, &sign);
	if (*s < '0' || *s > '9')
		exit(1);
	while (*s >= '0' && *s <= '9')
	{
		result = (result * 10) + (*s - '0');
		if ((result > INT_MAX && sign == 1)
			|| (-result < INT_MIN && sign == -1))
			exit(1);
		s++;
	}
	if (*s != '\0')
		exit(1);
    if (sign < 0)
        exit(1);
	return ((int)result * sign);
}
