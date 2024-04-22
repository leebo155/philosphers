/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 15:10:25 by bohlee            #+#    #+#             */
/*   Updated: 2023/09/17 15:38:00 by bohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_rule
{
	struct timeval	start;
	pthread_mutex_t	start_mutex;
	size_t			num_of_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			num_of_times_must_eat;
	pthread_mutex_t	mic;
	int				exit;
	pthread_mutex_t	exit_mutex;
}				t_rule;

typedef struct s_philo
{
	size_t			id;
	pthread_t		pth_id;
	pthread_mutex_t	fork;
	pthread_mutex_t	eat_mutex;
	size_t			eat_msec;
	size_t			eat_count;
	pthread_mutex_t	eat_count_mutex;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	t_rule			*rule;
}				t_philo;

int		ft_make_rule(int argc, char **argv, t_rule *rule);
int		ft_atoi(char *str, size_t *buffer);
int		ft_prepare_philo(int argc, t_philo **philo, t_rule *rule);
void	*ft_thread_fuction(void *void_philo);
void	ft_philo_loop(int argc, t_philo **philo, t_rule *rule);
void	ft_my_mutex_destroy(pthread_mutex_t *mutex);
void	ft_set_exit(t_rule *rule);
int		ft_get_exit(t_rule *rule);
int		ft_get_start(t_rule *rule);
int		ft_get_msec(t_rule *rule, size_t *buffer);
size_t	ft_get_eat_msec(t_philo *philo);
size_t	ft_get_eat_count(t_philo *philo);

#endif
