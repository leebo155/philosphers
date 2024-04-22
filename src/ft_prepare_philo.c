/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 18:56:01 by bohlee            #+#    #+#             */
/*   Updated: 2023/09/16 11:18:12 by bohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_rule(int argc, t_rule *rule)
{
	int	return_value;

	return_value = 0;
	if (rule->num_of_philo == 0)
	{
		printf("ERROR: There must be at least 1 philosopher.\n");
		return_value++;
	}
	if (rule->time_to_die == 0 || rule->time_to_eat == 0
		|| rule->time_to_sleep == 0)
	{
		printf("ERROR: Time is required at least 1 millisecond.\n");
		return_value++;
	}
	if (argc - 1 == 5 && rule->num_of_times_must_eat == 0)
	{
		printf("ERROR: Number_of_times_each_philosopher_must_eat");
		printf(" is required at least 1 time.\n");
		return_value++;
	}
	if (pthread_mutex_init(&(rule->mic), 0)
		|| (pthread_mutex_init(&(rule->start_mutex), 0))
		|| (pthread_mutex_init(&(rule->exit_mutex), 0)))
		return_value++;
	return (return_value);
}

static void	ft_remove_philo(t_rule *rule, t_philo **philo,
		size_t size, int flag)
{
	size_t	index;

	ft_set_exit(rule);
	printf("ERROR: Problem detected making %zuth thread.\n", size);
	index = 0;
	while (flag && index < size)
		pthread_join((*philo)[index++].pth_id, 0);
	index = 0;
	while (flag && index < rule->num_of_philo)
	{
		ft_my_mutex_destroy(&((*philo)[index].fork));
		ft_my_mutex_destroy(&((*philo)[index].eat_mutex));
		ft_my_mutex_destroy(&((*philo)[index].eat_count_mutex));
		index++;
	}
	index = 0;
	while (!flag && index <= size)
	{
		ft_my_mutex_destroy(&((*philo)[index].fork));
		ft_my_mutex_destroy(&((*philo)[index].eat_mutex));
		ft_my_mutex_destroy(&((*philo)[index].eat_count_mutex));
		index++;
	}
	free(*philo);
}

static void	ft_select_forks(t_rule *rule, t_philo *philo, t_philo **philoes)
{
	if (philo->id % 2)
	{
		philo->first_fork = &((*philoes)[philo->id].fork);
		philo->second_fork = &((*philoes)[philo->id - 1].fork);
	}
	else
	{
		philo->first_fork = &((*philoes)[philo->id - 1].fork);
		philo->second_fork = &((*philoes)[philo->id].fork);
	}
	if (rule->num_of_philo % 2 == 0 && philo->id == rule->num_of_philo)
		philo->second_fork = &((*philoes)[0].fork);
	else if (rule->num_of_philo % 2 && philo->id == rule->num_of_philo)
	{
		philo->first_fork = &((*philoes)[0].fork);
		philo->second_fork = &((*philoes)[philo->id - 1].fork);
	}
	if (rule->num_of_philo == 1)
		philo->first_fork = &((*philoes)[0].fork);
}

static int	ft_make_philo(t_rule *rule, t_philo **philo)
{
	size_t	index;

	memset(*philo, 0, sizeof(t_philo) * rule->num_of_philo);
	index = 0;
	while (index < rule->num_of_philo)
	{
		if (pthread_mutex_init(&((*philo)[index].fork), 0)
			|| pthread_mutex_init(&((*philo)[index].eat_mutex), 0)
			|| pthread_mutex_init(&((*philo)[index].eat_count_mutex), 0))
		{
			ft_remove_philo(rule, philo, index, 0);
			return (1);
		}
		(*philo)[index].id = index + 1;
		(*philo)[index].rule = rule;
		index++;
	}
	index = 0;
	while (index < rule->num_of_philo)
		ft_select_forks(rule, &((*philo)[index++]), philo);
	return (0);
}

int	ft_prepare_philo(int argc, t_philo **philo, t_rule *rule)
{
	size_t	index;

	if (ft_check_rule(argc, rule))
		return (1);
	*philo = (t_philo *)malloc(sizeof(t_philo) * rule->num_of_philo);
	if (*philo == 0)
		return (1);
	if (ft_make_philo(rule, philo))
		return (1);
	index = 0;
	while (index < rule->num_of_philo)
	{
		if (pthread_create(&((*philo)[index].pth_id),
			0, ft_thread_fuction, (void *)&((*philo)[index])))
		{
			ft_remove_philo(rule, philo, index, 1);
			return (1);
		}
		index++;
	}
	return (0);
}
