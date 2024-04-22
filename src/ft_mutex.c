/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:07:47 by bohlee            #+#    #+#             */
/*   Updated: 2023/09/17 15:03:07 by bohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_set_exit(t_rule *rule)
{
	if (pthread_mutex_lock(&(rule->exit_mutex)))
		return ;
	rule->exit = 1;
	if (pthread_mutex_unlock(&(rule->exit_mutex)))
		return ;
}

int	ft_get_exit(t_rule *rule)
{
	int	return_value;

	if (pthread_mutex_lock(&(rule->exit_mutex)))
		return (1);
	return_value = rule->exit;
	if (pthread_mutex_unlock(&(rule->exit_mutex)))
		return (1);
	return (return_value);
}

int	ft_get_start(t_rule *rule)
{	
	int	return_value;

	return_value = 1;
	if (pthread_mutex_lock(&(rule->start_mutex)))
	{
		ft_set_exit(rule);
		return (0);
	}
	if (rule->start.tv_sec != 0)
		return_value = 0;
	if (pthread_mutex_unlock(&(rule->start_mutex)))
	{
		ft_set_exit(rule);
		return (0);
	}
	return (return_value);
}

size_t	ft_get_eat_count(t_philo *philo)
{
	size_t	return_value;

	if (pthread_mutex_lock(&(philo->eat_count_mutex)))
	{
		ft_set_exit(philo->rule);
		return (0);
	}
	return_value = philo->eat_count;
	if (pthread_mutex_unlock(&(philo->eat_count_mutex)))
	{
		ft_set_exit(philo->rule);
		return (0);
	}
	return (return_value);
}

size_t	ft_get_eat_msec(t_philo *philo)
{
	size_t	return_value;

	if (pthread_mutex_lock(&(philo->eat_mutex)))
	{
		ft_set_exit(philo->rule);
		return (0);
	}
	return_value = philo->eat_msec;
	if (pthread_mutex_unlock(&(philo->eat_mutex)))
	{
		ft_set_exit(philo->rule);
		return (0);
	}
	return (return_value);
}
