/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 17:22:58 by bohlee            #+#    #+#             */
/*   Updated: 2023/09/02 18:21:41 by bohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_is_negative(char *str, size_t *index)
{
	size_t	count;

	count = 0;
	while ((9 <= str[(*index)] && str[(*index)] <= 13) || str[(*index)] == 32)
		(*index)++;
	while (str[(*index)] == '+' || str[(*index)] == '-')
	{
		if (str[(*index)] == '-')
			count++;
		(*index)++;
	}
	if (count % 2)
		return (1);
	return (0);
}

int	ft_atoi(char *str, size_t *buffer)
{
	size_t	index;
	size_t	number;
	size_t	old_number;
	int		dex;

	index = 0;
	number = 0;
	old_number = 0;
	if (ft_is_negative(str, &index))
		return (1);
	while ('0' <= str[index] && str[index] <= '9')
	{
		dex = 0;
		while (str[index] != "0123456789"[dex] && dex < 10)
			dex++;
		number = (number * 10) + dex;
		if (number < old_number)
			return (1);
		old_number = number;
		index++;
	}
	*buffer = number;
	return (0);
}
