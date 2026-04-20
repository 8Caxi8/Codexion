/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansimoe <dansimoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 16:25:12 by dansimoe          #+#    #+#             */
/*   Updated: 2026/04/20 10:46:17 by dansimoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	take_dongle(pthread_mutex_t dongle, int coder_id)
{
	int				curr_time;
	struct timeval	time;

	gettimeofday(&time, NULL);
	curr_time = time.tv_usec - coders->start_time.tv_usec;
	pthread_mutex_lock(&dongle);
	printf("%d %d has taken a dongle\n", curr_time, coder_id);
}

void	compile(t_coder *coders, int coder_id)
{
	int				left_dongle;
	int				right_dongle;

	left_dongle = coder_id - 1;
	if (coder_id == ((t_coder *) coders)->parameters->no_coders)
		right_dongle = 0;
	else
		right_dongle = coder_id;
	take_dongle(coders->parameters->dongles[left_dongle], coder_id);
	take_dongle(coders->parameters->dongles[right_dongle], coder_id);
	curr_time = time.tv_usec - coders->start_time.tv_usec;
	printf("%d %d is compiling\n", curr_time, coder_id);
	usleep(((t_coder *) coders)->parameters->compile);
	pthread_mutex_unlock(&coders->parameters->dongles[left_dongle]);
	pthread_mutex_unlock(&coders->parameters->dongles[right_dongle]);
}

void debug(t_coder *coders, int coder_id)
{
	long	curr_time;

	curr_time = get_time_ms(coders->start_time);
	coder_write(curr_time, coder_id, "is debugging\n", coders->parameters->logging);
	usleep(((t_coder *) coders)->parameters->debug * 1000);
}

void refactor(t_coder *coders, int coder_id)
{
	long	curr_time;

	curr_time = get_time_ms(coders->start_time);
	coder_write(curr_time, coder_id, "is refactoring\n", coders->parameters->logging);
	usleep(((t_coder *) coders)->parameters->refactor * 1000);
}

void coder_write(long time, int id, const char message, pthread_mutex_t logging)
{
	pthread_mutex_lock(&logging);
	printf("%u %d %s", time, id, message);
	pthread_mutex_unlock(&logging);
}
