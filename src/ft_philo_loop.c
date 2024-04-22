/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:36:40 by bohlee            #+#    #+#             */
/*   Updated: 2023/09/17 14:54:47 by bohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_get_msec(t_rule *rule, size_t *buffer)
{
	struct timeval	start;
	struct timeval	now;

	start = rule->start;
	if (gettimeofday(&now, 0))
	{
		ft_set_exit(rule);
		return (1);
	}
	*buffer = ((now.tv_sec - start.tv_sec) * 1000)
		+ ((now.tv_usec - start.tv_usec) / 1000);
	return (0);
}

static int	ft_check_eat_count(t_philo **philo, t_rule *rule, int argc)
{
	size_t	index;

	if (argc - 1 != 5)
		return (0);
	index = 0;
	while (index < rule->num_of_philo)
	{
		if (ft_get_eat_count(&((*philo)[index])) < rule->num_of_times_must_eat)
			return (0);
		index++;
	}
	ft_set_exit(rule);
	return (1);
}

static void	ft_kill_philo(size_t id, t_rule *rule)
{
	size_t	now;

	ft_set_exit(rule);
	if (pthread_mutex_lock(&(rule->mic)))
		return ;
	if (!(ft_get_msec(rule, &now)))
		printf("%zu %zu died\n", now, id);
	if (pthread_mutex_unlock(&(rule->mic)))
		return ;
}

static int	ft_check_died_philo(t_rule *rule, t_philo **philo)
{
	size_t	index;
	size_t	now;

	index = 0;
	while (index < rule->num_of_philo)
	{
		if (ft_get_msec(rule, &now))
			return (1);
		if (now - ft_get_eat_msec(&((*philo)[index])) >= rule->time_to_die)
		{
			ft_kill_philo(index + 1, rule);
			return (1);
		}
		index++;
	}
	return (0);
}

void	ft_philo_loop(int argc, t_philo **philo, t_rule *rule)
{
	if (pthread_mutex_lock(&(rule->start_mutex)))
	{
		ft_set_exit(rule);
		return ;
	}
	if (gettimeofday(&(rule->start), 0))
	{
		pthread_mutex_unlock(&(rule->start_mutex));
		return ;
	}
	if (pthread_mutex_unlock(&(rule->start_mutex)))
	{
		ft_set_exit(rule);
		return ;
	}
	while (!(ft_get_exit(rule)))
	{
		if (usleep(200))
			break ;
		if (ft_check_eat_count(philo, rule, argc))
			break ;
		if (ft_check_died_philo(rule, philo))
			break ;
	}
}
