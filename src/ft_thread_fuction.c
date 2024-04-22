/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_fuction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:52:46 by bohlee            #+#    #+#             */
/*   Updated: 2023/09/16 14:55:23 by bohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_print_status(t_philo *philo, char *str)
{
	size_t	now;

	if (pthread_mutex_lock(&(philo->rule->mic)))
	{
		ft_set_exit(philo->rule);
		return ;
	}
	if (ft_get_msec(philo->rule, &now))
		ft_set_exit(philo->rule);
	if (!(ft_get_exit(philo->rule)))
		printf("%zu %zu %s\n", now, philo->id, str);
	if (pthread_mutex_unlock(&(philo->rule->mic)))
		ft_set_exit(philo->rule);
}

static void	ft_waitting(ssize_t stop, t_philo *philo, int flag)
{
	size_t	start;
	size_t	now;

	if (ft_get_msec(philo->rule, &start))
		ft_set_exit(philo->rule);
	while (!(ft_get_exit(philo->rule)))
	{
		if (ft_get_msec(philo->rule, &now))
			ft_set_exit(philo->rule);
		if (start + stop <= now)
			break ;
		if (usleep(100))
			ft_set_exit(philo->rule);
	}
	if (flag && !(ft_get_exit(philo->rule)))
	{
		if (usleep(200))
			ft_set_exit(philo->rule);
		if (pthread_mutex_lock(&(philo->eat_mutex)))
			ft_set_exit(philo->rule);
		if (ft_get_msec(philo->rule, &(philo->eat_msec)))
			ft_set_exit(philo->rule);
		if (pthread_mutex_unlock(&(philo->eat_mutex)))
			ft_set_exit(philo->rule);
	}
}

static void	ft_starvation_wait(t_philo *philo, size_t time)
{
	size_t	now;

	if (ft_get_msec(philo->rule, &now))
	{
		ft_set_exit(philo->rule);
		return ;
	}
	if (now - ft_get_eat_msec(philo) < philo->rule->time_to_die / 2)
	{
		if (usleep(time))
			ft_set_exit(philo->rule);
	}
}

static void	ft_eat_sleep_and_think(t_philo *philo)
{
	ft_starvation_wait(philo, 200);
	if (pthread_mutex_lock(philo->first_fork))
		ft_set_exit(philo->rule);
	ft_print_status(philo, "has taken a fork");
	ft_starvation_wait(philo, 200);
	if (philo->rule->num_of_philo % 2 && philo->id == philo->rule->num_of_philo)
		ft_starvation_wait(philo, 100);
	if (pthread_mutex_lock(philo->second_fork))
		ft_set_exit(philo->rule);
	ft_print_status(philo, "has taken a fork");
	ft_print_status(philo, "is eating");
	ft_waitting(philo->rule->time_to_eat, philo, 1);
	if (pthread_mutex_lock(&(philo->eat_count_mutex)))
		ft_set_exit(philo->rule);
	(philo->eat_count)++;
	if (pthread_mutex_unlock(&(philo->eat_count_mutex)))
		ft_set_exit(philo->rule);
	ft_print_status(philo, "is sleeping");
	if (pthread_mutex_unlock(philo->first_fork))
		ft_set_exit(philo->rule);
	if (pthread_mutex_unlock(philo->second_fork))
		ft_set_exit(philo->rule);
	ft_waitting(philo->rule->time_to_sleep, philo, 0);
	ft_print_status(philo, "is thinking");
}

void	*ft_thread_fuction(void *void_philo)
{
	t_philo			*philo;

	philo = (t_philo *)void_philo;
	while (ft_get_start(philo->rule) && !(ft_get_exit(philo->rule)))
	{
		if (usleep(100))
			ft_set_exit(philo->rule);
	}
	if ((philo->id % 2 == 0 || philo->id == philo->rule->num_of_philo)
		&& philo->id != 1 && !(ft_get_exit(philo->rule)))
	{
		if (usleep(400))
			ft_set_exit(philo->rule);
		ft_print_status(philo, "is thinking");
	}
	while (!(ft_get_exit(philo->rule)))
		ft_eat_sleep_and_think(philo);
	return (0);
}
