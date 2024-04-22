/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_rule.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 16:11:38 by bohlee            #+#    #+#             */
/*   Updated: 2023/09/02 18:27:54 by bohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_print_error(int num)
{
	printf("ERROR: invalid argument input [");
	if (num == 1)
		printf("number_of_philosophers");
	else if (num == 2)
		printf("time_to_die");
	else if (num == 3)
		printf("time_to_eat");
	else if (num == 4)
		printf("time_to_sleep");
	else if (num == 5)
		printf("number_of_times_each_philosopher_must_eat");
	printf("]\n");
}

int	ft_make_rule(int argc, char **argv, t_rule *rule)
{
	int		arg_index;
	size_t	atoi_buffer;

	arg_index = 0;
	memset(rule, 0, sizeof(t_rule));
	while (++arg_index < argc)
	{
		if (ft_atoi(argv[arg_index], &atoi_buffer))
		{
			ft_print_error(arg_index);
			return (1);
		}
		if (arg_index == 1)
			rule->num_of_philo = atoi_buffer;
		else if (arg_index == 2)
			rule->time_to_die = atoi_buffer;
		else if (arg_index == 3)
			rule->time_to_eat = atoi_buffer;
		else if (arg_index == 4)
			rule->time_to_sleep = atoi_buffer;
		else if (arg_index == 5)
			rule->num_of_times_must_eat = atoi_buffer;
	}
	return (0);
}
