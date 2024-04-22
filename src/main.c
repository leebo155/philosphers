/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 15:11:08 by bohlee            #+#    #+#             */
/*   Updated: 2023/09/17 15:05:32 by bohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_print_usage(void)
{
	printf("USAGE: philo number_of_philosophers time_to_die time_to_eat");
	printf(" time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	printf("\t◦ number_of_philosophers: The number of philosophers and also");
	printf(" the number of forks.\n");
	printf("\t◦ time_to_die (in milliseconds): If a philosopher didn’t start");
	printf(" eating time_to_die milliseconds since the beginning of their");
	printf(" last meal or the beginning of the simulation, they die.\n");
	printf("\t◦ time_to_eat (in milliseconds): The time it takes for a ");
	printf(" philosopher to eat. During that time, they will need to hold");
	printf(" two forks.\n");
	printf("\t◦ time_to_sleep (in milliseconds): The time a philosopher will");
	printf(" spend sleeping.\n");
	printf("\t◦ number_of_times_each_philosopher_must_eat (optional");
	printf(" argument): If all philosophers have eaten at least number_of_ti");
	printf("mes_each_philosopher_must_eat times, the simulation stops. If");
	printf(" not specified, the simulation stops when a philosopher dies.\n");
}

static void	ft_remove_rule(t_rule *rule)
{
	ft_my_mutex_destroy(&(rule->mic));
	ft_my_mutex_destroy(&(rule->start_mutex));
	ft_my_mutex_destroy(&(rule->exit_mutex));
}

static void	ft_destroy_everything(t_philo **philo, t_rule *rule)
{
	size_t	index;

	ft_set_exit(rule);
	pthread_mutex_lock(&(rule->mic));
	index = 0;
	while (index < rule->num_of_philo)
		pthread_mutex_unlock(&((*philo)[index++].fork));
	pthread_mutex_unlock(&(rule->mic));
	index = 0;
	while (index < rule->num_of_philo)
		pthread_join((*philo)[index++].pth_id, 0);
	index = 0;
	while (index < rule->num_of_philo)
	{
		ft_my_mutex_destroy(&((*philo)[index].fork));
		ft_my_mutex_destroy(&((*philo)[index].eat_mutex));
		ft_my_mutex_destroy(&((*philo)[index].eat_count_mutex));
		index++;
	}
	free(*philo);
	ft_remove_rule(rule);
}

void	ft_my_mutex_destroy(pthread_mutex_t *mutex)
{
	if ((pthread_mutex_lock(mutex)))
		return ;
	else
	{
		pthread_mutex_unlock(mutex);
		pthread_mutex_destroy(mutex);
	}
}

int	main(int argc, char *argv[])
{
	t_rule	rule;
	t_philo	*philo;

	if (argc - 1 != 4 && argc - 1 != 5)
	{
		ft_print_usage();
		return (1);
	}
	if (ft_make_rule(argc, argv, &rule))
	{
		ft_print_usage();
		return (1);
	}
	if (ft_prepare_philo(argc, &philo, &rule))
	{
		ft_remove_rule(&rule);
		return (1);
	}
	ft_philo_loop(argc, &philo, &rule);
	ft_destroy_everything(&philo, &rule);
	return (0);
}
